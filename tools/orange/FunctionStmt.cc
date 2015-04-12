/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/FunctionStmt.h>
#include <orange/generator.h>
#include <orange/IfStmts.h>

FunctionStmt::FunctionStmt(std::string name, ParamList parameters, SymTable* symtab) : Block(symtab) {
	m_name = name;
	m_parameters = parameters;
}

FunctionStmt::FunctionStmt(std::string name, AnyType* type, ParamList parameters, SymTable* symtab) : Block(symtab) {
	m_name = name; 
	m_type = type; 
	m_parameters = parameters;
}

std::string FunctionStmt::getClonesFullSignature(ArgList args) {
	std::string ret_name = m_name + "_"; 
	for (auto arg : args) {
		AnyType* type = arg->getType();

		if (type->isIntegerTy()) {
			int width = type->getIntegerBitWidth();
			switch (width) {
				case 1:
					ret_name += "T";
					break;
				case 8:
					ret_name += (type->isSigned() ? "b" : "B");
					break; 
				case 16:
					ret_name += (type->isSigned() ? "s" : "S");
					break;
				case 32:
					ret_name += (type->isSigned() ? "i" : "I");
					break;
				case 64:
					ret_name += (type->isSigned() ? "l" : "L");
					break;
				default:
					ret_name += "?";
					break;
			}
		} else if (type->isFloatTy()) {
			ret_name += "f";
		} else if (type->isDoubleTy()) {
			ret_name += "F";
		}

		for (int i = 0; i < type->getPointerLength(); i++) {
			ret_name += "p";
		}
	}

	return ret_name;
}

FunctionStmt* FunctionStmt::createGenericClone(ArgList args) {
	// If we're not a generic, we shouldn't be trying to make a clone.
	if (isGeneric() == false) {
		return nullptr;
	}

	if (args.size() != m_parameters.size()) {
		throw CompilerMessage(*this, "Mismatched number of arguments while calling " + m_name + "!");
	}

	std::string cloned_name = getClonesFullSignature(args);

	// Does a clone with that name already exist? If so, return that clone.
	for (auto clone : m_clones) {
		if (clone->m_name == cloned_name) {
			return clone;
		}
	}

	// Create paramlist from args
	ParamList cloned_params; 

	for (int i = 0; i < args.size(); i++) {
		VarExpr* curParam = m_parameters[i];
		VarExpr* newParam = new VarExpr(curParam->name(), args[i]->getType());
		cloned_params.push_back(newParam);
	}

	// Otherwise, create that clone here, add it to the list, and return it.
	FunctionStmt* clone;
	
	if (m_type) {
		clone = new FunctionStmt(cloned_name, m_type, cloned_params, symtab()->clone());	
	} else {
		clone = new FunctionStmt(cloned_name, cloned_params, symtab()->clone());
	}

	for (auto stmt : m_statements) {
		auto clonedStmt = stmt->clone();
		clone->addStatement(clonedStmt);

		// if the stmt is a block, set its parent to the clone's symtab IFF 
		// their symtab's parent is the one for our current function statement
		if (Block* block = dynamic_cast<Block*>(clonedStmt)) {
			if (block->symtab()->parent()->ID() == symtab()->ID()) {
				block->symtab()->setParent(clone->symtab());
			}
		}

		if (IfStmts* ifStmts = dynamic_cast<IfStmts*>(clonedStmt)) {
			for (auto block : ifStmts->blocks()) {
				block->symtab()->setParent(clone->symtab());
			}
		}
	}

	m_clones.push_back(clone);
	return clone;
}


AnyType* FunctionStmt::getType() {
	AnyType *ret = m_type; 

	// This should not happen; getType() should only be called against clones.
	if (isGeneric()) {
		throw CompilerMessage(*this, "Cannot get type of a generic function.");
	}

	GE::runner()->pushBlock(this);

	// Here, invalid type means that it needs to be redefined for this function.
	bool invalidType = (m_type == nullptr || m_type->isVoidTy() || m_type->isIDTy());
	if (invalidType && m_looking == false) {
		// Set m_looking to true so we don't recursively try to get the type of FunctionStmt
		m_looking = true;
		
		// If we don't have an explicit type set, we have to determine it from our body and nested bodies.
		AnyType* foundRet = searchForReturn();
		ret = foundRet ? foundRet : ASTNode::getType();
		m_type = ret;
		m_looking = false;
	} 

	GE::runner()->popBlock();

	return ret;
}

Value* FunctionStmt::Codegen() {
	// Check to see if we're a generic function. 
	// If we are, we only should generate our clones since we're incomplete. 
	if (isGeneric()) {
		for (auto clone : m_clones) {
			clone->Codegen();
		}

		return nullptr;
	}


	// Push ourselves onto the stack first.
	GE::runner()->pushBlock(this);

	// Create a list of types that serve as our function's arguments
	std::vector<Type*> Args;

	for (auto param : m_parameters) {
		Args.push_back(param->getLLVMType());
	}

	// Create the function itself, and set it as our AST value.
	FunctionType* funcType = FunctionType::get(getLLVMType(), Args, m_isVarArg);
	Function* generatedFunc = Function::Create(funcType, m_linkageType, m_name, GE::module());
	m_value = generatedFunc;

	// TODO: Set argument names, if any (generatedFunc->arg_begin, setName on iterator)
	auto arg_it = generatedFunc->arg_begin();
	for (unsigned int i = 0; i < Args.size(); i++, arg_it++) {
		arg_it->setName(m_parameters[i]->name());
	}


	// Before generating, we need to get the current insert block so we don't lose our place.
	auto oldInsertBlock = GE::builder()->GetInsertBlock();

	// Create basic block and set our insertion point to it.
	BasicBlock *funcBody = BasicBlock::Create(GE::runner()->context(), "entry", generatedFunc);
	BasicBlock *funcEnd = BasicBlock::Create(GE::runner()->context(), "exit", generatedFunc);
	GE::builder()->SetInsertPoint(funcBody);

	// Set up values for children statements to use. 
	Value *retVal = nullptr; 
	if (getType()->isVoidTy() == false) {
		retVal = GE::builder()->CreateAlloca(getLLVMType(), nullptr, "return");
		m_retVal = retVal;
	}

	m_blockEnd = funcEnd;

	// Create our paramters. 
	arg_it = generatedFunc->arg_begin();
	for (int i = 0; i < Args.size(); i++, arg_it++) {
		Value *paramV = GE::builder()->CreateAlloca(arg_it->getType());
		GE::builder()->CreateStore(arg_it, paramV); 
		m_parameters[i]->setValueTo(paramV);
	}

	// Generate the body, which will add code to our new insert block
	generateStatements();

	// If our body has a return statement, then we don't have to do anything else here.
	// If we don't have a return statement or a terminator (current block doesn't have a return):
	//		- Are we a main function? If we are, force return 0.
	//		- Are we an auto return? If not, throw an error about a missing return of type for function
	// We only want to check for a return statement in the direct body; no nested bodies. The reason for this is that 
	// if we _need_ a return type, it _needs_ to be in the main body. 
	if (hasReturn() == false && GE::builder()->GetInsertBlock()->getTerminator() == nullptr) {
		if (isRoot()) {
			GE::builder()->CreateStore(ConstantInt::getSigned(funcType->getReturnType(), 0), m_retVal);
		} else if (m_type != nullptr && m_type->isVoidTy() == false) {
			throw CompilerMessage(*this, "Missing return type; expected a " + m_type->string());
		}

		// Jump to the end now.
		GE::builder()->CreateBr(m_blockEnd);
	} 

	GE::builder()->SetInsertPoint(m_blockEnd);

	// Let's return from the function now; returning our value if we have one (e.g., we're not a void func)
	if (retVal != nullptr) {
		GE::builder()->CreateRet(GE::builder()->CreateLoad(retVal));
	} else {
		GE::builder()->CreateRetVoid();
	}

	// Optimize our function.
	GE::sharedEngine()->functionOptimizer()->run(*generatedFunc);

	// Finally, restore our insert block, pop our block and return our function 
	GE::builder()->SetInsertPoint(oldInsertBlock);
	GE::runner()->popBlock();
	return m_value;
}

ASTNode* FunctionStmt::clone() {
	ParamList clonedParams;

	for (auto param : m_parameters) {
		clonedParams.push_back((VarExpr*)param->clone());
	}

	FunctionStmt* clonedFunc = nullptr; 

	if (m_type) {
		clonedFunc = new FunctionStmt(m_name, m_type, clonedParams, symtab()->clone());	
	} else {
		clonedFunc = new FunctionStmt(m_name, clonedParams, symtab()->clone());	
	}

	for (auto stmt : m_statements) {
		auto clonedStmt = stmt->clone();
		clonedFunc->addStatement(clonedStmt);

		// if the stmt is a block, set its parent to the clone's symtab IFF 
		// their symtab's parent is the one for our current function statement
		if (Block* block = dynamic_cast<Block*>(clonedStmt)) {
			if (block->symtab()->parent()->ID() == symtab()->ID()) {
				block->symtab()->setParent(clonedFunc->symtab());
			}
		}

		if (IfStmts* ifStmts = dynamic_cast<IfStmts*>(clonedStmt)) {
			for (auto block : ifStmts->blocks()) {
				block->symtab()->setParent(clonedFunc->symtab());
			}
		}
	}

	return clonedFunc;
}

std::string FunctionStmt::string() {
	std::stringstream ss;

	GE::runner()->pushBlock(this);

	ss << m_name << ":" << std::endl;

	for (ASTNode *s : m_statements) {
		if (s == nullptr) continue;
		ss << "\t" << s->string() << std::endl;
	}

	GE::runner()->popBlock();
	return ss.str();
}

bool FunctionStmt::isGeneric() const {
	for (auto param : m_parameters) {
		// *DON'T* use getType() here! that searches up the symtab tree. we only want 
		// the deepest level here.
		if (param->type() == nullptr || param->type()->isVoidTy()) {
			return true; 
		}
	}

	return false;
}

BasicBlock* FunctionStmt::createBasicBlock(std::string name) {
	auto llvmFunction = (Function*)getValue();

	if (llvmFunction == nullptr) {
		throw std::runtime_error("LLVM function not generated yet!");
	}

	return BasicBlock::Create(GE::runner()->context(), name, llvmFunction, getBlockEnd());
}


void FunctionStmt::resolve() {
	if (m_resolved) return; 
	// Don't set m_resolved here; let Block::resolve do it.

	// If we don't exist in the parent symtab, add us as a reference.
	// If the parent doesn't exist, we're in the global block, so 
	// nothing could call is anyway.
	if (symtab()->parent() != nullptr) {
		bool added = symtab()->parent()->create(m_name, this);
		if (added == false) {
			throw std::runtime_error("Can't create function " + m_name + ". Something with that name already exists!");
		}
	}

	// Add us to our own symtab so we can do recursion.
	bool added = symtab()->create(m_name, this);
	if (added == false) {
		throw std::runtime_error("Can't create function " + m_name + ". Something with that name already exists!");
	}	

	// Add us as a structure.
	symtab()->setStructure(this);

	if (isGeneric()) {
		// We don't actually want to resolve our parameters or body since as a generic function, they will never 
		// be used. Instead, let's just resolve our clones here.
		for (auto clone : m_clones) {
			clone->resolve();
		}

		m_resolved = true;
		return; 
	}

	// Push our symtab into the stack and add our parameters to the symbol table.
	GE::runner()->pushBlock(this);

	for (auto param : m_parameters) param->create();

	GE::runner()->popBlock();

	Block::resolve();
}

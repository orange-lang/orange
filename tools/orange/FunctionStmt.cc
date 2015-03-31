/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/FunctionStmt.h>
#include <orange/generator.h>

FunctionStmt::FunctionStmt(std::string name, ArgList arguments, SymTable* symtab) : Block(symtab) {
	m_name = name;
}

FunctionStmt::FunctionStmt(std::string name, AnyType* type, ArgList arguments, SymTable* symtab) : Block(symtab) {
	m_name = name; 
	m_type = type; 
}

AnyType* FunctionStmt::getType() {
	if (m_type == nullptr) {
		// If we don't have an explicit type set, we have to determine it from our body and nested bodies.
		AnyType* foundRet = searchForReturn();
		return foundRet ? foundRet : ASTNode::getType();
	} 

	return m_type;
}

Value* FunctionStmt::Codegen() {
	// Push ourselves onto the stack first.
	GE::runner()->pushBlock(this);

	// Create a list of types that serve as our function's arguments
	std::vector<Type*> Args;

	// Create the function itself, and set it as our AST value.
	FunctionType* funcType = FunctionType::get(getLLVMType(), Args, m_isVarArg);
	Function* generatedFunc = Function::Create(funcType, m_linkageType, m_name, GE::module());
	m_value = generatedFunc;

	// TODO: Set argument names, if any (generatedFunc->arg_begin, setName on iterator)

	// Before generating, we need to get the current insert block so we don't lose our place.
	auto oldInsertBlock = GE::builder()->GetInsertBlock();

	// Create basic block and set our insertion point to it.
	BasicBlock *funcBody = BasicBlock::Create(getGlobalContext(), "entry", generatedFunc);
	BasicBlock *funcEnd = BasicBlock::Create(getGlobalContext(), "exit", generatedFunc);
	GE::builder()->SetInsertPoint(funcBody);

	// Set up values for children statements to use. 
	Value *retVal = nullptr; 
	if (getType()->isVoidTy() == false) {
		retVal = GE::builder()->CreateAlloca(getLLVMType(), nullptr, "return");
		m_retVal = retVal;
	}

	m_blockEnd = funcEnd;

	// Generate the body, which will add code to our new insert block
	generateStatements();

	// If our body has a return statement, then we don't have to do anything else here.
	// If we don't have a return statement:
	//		- Are we a main function? If we are, force return 0.
	//		- Are we an auto return? If not, throw an error about a missing return of type for function
	// We only want to check for a return statement in the direct body; no nested bodies. The reason for this is that 
	// if we _need_ a return type, it _needs_ to be in the main body. 
	if (hasReturn() == false) {
		if (isRoot()) {
			GE::builder()->CreateStore(ConstantInt::getSigned(funcType->getReturnType(), 0), m_retVal);
		} else if (m_type != nullptr) {
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
	ArgList clonedArgs;

	for (auto arg : m_arguments) {
		clonedArgs.push_back((VarExpr*)arg->clone());
	}

	FunctionStmt* clonedFunc = nullptr; 

	if (m_type) {
		clonedFunc = new FunctionStmt(m_name, m_type, clonedArgs, symtab()->clone());	
	} else {
		clonedFunc = new FunctionStmt(m_name, clonedArgs, symtab()->clone());	
	}

	for (auto stmt : m_statements) {
		clonedFunc->addStatement(stmt->clone());
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

void FunctionStmt::resolve() {
	if (m_resolved) return; 

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

	// TODO: set up our arguments, if any, into the symbol table.

	Block::resolve();
}

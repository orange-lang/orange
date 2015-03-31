#include "gen/FunctionStatement.h"
#include "gen/Block.h"
#include "gen/generator.h"
#include "gen/CastingEngine.h"
#include <helper/string.h>


FunctionStatement::FunctionStatement(std::string* name, ArgList *args, Block *body) {
	this->name = name ? *name : "";
	this->args = args;
	this->body = body;

	if (args == nullptr) {
		this->args = new ArgList();
	}

	// Create this as a symbol in our parent.
	if (CG::Symtabs.top()->parent) {
		DEBUG_MSG("Adding " << this->name << " to parent " << CG::Symtabs.top()->parent->ID);

		CG::Symtabs.top()->parent->create(this->name);
		CG::Symtabs.top()->parent->objs[this->name]->isFunction = true; 
		CG::Symtabs.top()->parent->objs[this->name]->reference = (Statement *)this; 
	}

	// Add arguments to symbol table
	for (ArgExpr *expr : *(this->args)) {	
		CG::Symtabs.top()->create(expr->name);

		if (expr->type == nullptr) {
			continue;
		}

		if (expr->type && expr->getType()->isArrayTy()) {
			// change to be a pointer, since all array arguments for a function are passed by reference 
			expr->type = new AnyType(&expr->type->type, expr->type->arrays_size(), nullptr);
		}

		if (expr->type) {
			CG::Symtabs.top()->objs[expr->name]->setType(expr->type->getType()->getPointerTo());
		}
		CG::Symtabs.top()->objs[expr->name]->isSigned = expr->type->isSigned();
	}
}

std::string FunctionStatement::string() {
	std::stringstream ss;
	ss << "[ID: " << body->symtab->ID << "] " << name << "( ";
	for (unsigned int i = 0; i < args->size(); i++) {
		ss << (*args)[i]->string() << " ";
		if (i + 1 != args->size())
			ss << ", ";
	}
	ss << "):\n";

	std::vector<std::string> lines = split(body->string(), '\n');
	for (std::string line : lines) {
		ss << "\t" << line << std::endl;
	}

	return ss.str();
}

std::string FunctionStatement::getTemplatedInstance(ExprList *callArgs, bool forceExporting) {
	ArgList *newArgs = args->clone();

	bool requires_templating = false;

	// set up newArgs
	for (int i = 0; i < callArgs->size(); i++) {
		Type *callType = callArgs->at(i)->getType();

		// every argument in callArgs needs a type. 
		if (callType == nullptr) {
			// throw an exception 
			throw std::runtime_error("One of the arguments calling function " + name + " does not have a type.");
		}

		// callArgs size must match newArgs size
		if (i >= newArgs->size()) {
			// throw an exception: out of bounds 
			throw std::runtime_error("Calling too many arguments for function " + name + ".");
		}

		// If newArgs[i] doesn't have a type, take on type of callType.
		// If it does have a type, and callType can't be casted to it, 
		// throw an error.  
		if (newArgs->at(i)->type == nullptr) {
			newArgs->at(i)->type = AnyType::Create(callType);
			requires_templating = true;
		} else if (CanTypeBeCasted(callType, newArgs->at(i)->getType()) == false) {
			// we can't cast callType to newArgs[i] type, so an exception should be thrown. 
			// we only have to handle the error here; there's nothign to be done if we can
			// be cast.
			throw std::runtime_error("Cannot cast a type for function " + name);
		} 
	}

	// we need at least one argument that didn't have a type 
	// for us to need to template ourselves.
	if (requires_templating == false) {
		return name;
	}

	// determine name from newArgs. 
	std::stringstream templated_name; 
	templated_name << name; 

	for (ArgExpr *ae : *newArgs) {
		templated_name << "__" << ae->type->string(true);
	}

	std::string templated_name_str = templated_name.str();

	FunctionStatement *clone = nullptr; 
	for (FunctionStatement *fstmt : clones) {
		if (fstmt->name == templated_name_str) {
			clone = fstmt; 
			break; 
		}
	}	

	if (clone == nullptr) {
		// 1. clone the body of original function (implement a clone() for the AST)
		Block *cloned_body = body->clone();

		// 2. push the symtab of the cloned body's symtab
		CG::Symtabs.push(cloned_body->symtab);

		// 3. create the new function statement (this should set the types in the symtab)
		FunctionStatement *clone = new FunctionStatement(&templated_name_str, newArgs, cloned_body);

		// this line indicates we're not calling our generic with "export foo(typeA, typeB)"
		// and we're setting it up so that unused generics after optimization can be deleted.
		if (forceExporting == false) { 
			clone->isClone = true;
		}

		// 4. pop the symtab.
		CG::Symtabs.pop();

		// 5. add the function statement to clones.
		clones.push_back(clone);

		return templated_name_str; 
	} else {
		// the clone already exists, so just delete the argument list we made and get out. 
		DEBUG_MSG(templated_name_str << " ALREADY EXISTS! ONLY RETURNING NAME");

		delete newArgs; 
		return templated_name_str; 
	}

	std::cerr << "fatal: Unreachable code in FunctionStatement. Exiting...\n";
	exit(1);
	return name;
}

void FunctionStatement::resolve() {
	if (resolved)
		return; 

	// we only want to resolve the body of the function that has all of its types
	resolved = true;

	bool argsResolved = true;
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];

		if (arg->type == nullptr) {
			argsResolved = false;
			break; 
		}
	}

	if (argsResolved) {
		DEBUG_MSG("RESOLVING " << name);

		body->resolve();
	}

	for (FunctionStatement *clone : clones) {
		clone->resolve();
	}	
}

Value* FunctionStatement::Codegen() {
	// Set new symtab
	CG::Symtabs.push(body->symtab);

	bool hasReturn = body->hasReturnStatement();
	bool argsResolved = true;

	std::vector<Type*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];

		if (arg->type == nullptr) {
			std::cout << "warning: function " << name << " didn't have arguments resolved.\n";
			argsResolved = false;
			break; 
		}

		Args[i] = arg->type->getType();
	}

	if (argsResolved == false) {
		CG::Symtabs.pop();

		for (FunctionStatement *clone : clones) {
			clone->Codegen();
		}

		return nullptr;
	}

	DEBUG_MSG("GETTING RETURN TYPE FOR FUNCTION BLOCK");
	bool noRet = false; 
	Type *retType = body->getReturnType();

	if (hasReturn == false && retType == nullptr && body->statements.size() > 0) {
		retType = body->getLastStatementType();
	}

	if (retType && retType->isVoidTy()) {
		DEBUG_MSG("NO RET FOR FUNCTION " << name << " (VOID TY)");
		noRet = true;
	}

	if (retType == nullptr) {
		DEBUG_MSG("NO RET FOR FUNCTION " << name);

		noRet = true; 
		retType = Type::getVoidTy(getGlobalContext());
	}

	DEBUG_MSG("GOT RETURN TYPE FOR FUNCTION BLOCK");

	FunctionType *FT = FunctionType::get(retType, Args, false);

	auto linkage = Function::ExternalLinkage;
	if (isClone)
		linkage = Function::LinkOnceODRLinkage;

	Function *TheFunction = Function::Create(FT, linkage, name, CG::TheModule);

	if (CG::Symtabs.top()->parent) {
		// Set function for the PARENT symtab (the one that could call this function)
		CG::Symtabs.top()->parent->create(name);
		CG::Symtabs.top()->parent->objs[name]->setValue(TheFunction);
	}

	// Set function for the CURRENT symtab (for recursion)
	CG::Symtabs.top()->create(name);
	CG::Symtabs.top()->objs[name]->setValue(TheFunction);

	auto arg_it = TheFunction->arg_begin();
	for (unsigned int i = 0; i < args->size(); i++, arg_it++) {
		arg_it->setName((*args)[i]->name);
	}

	auto IP = CG::Builder.GetInsertBlock();
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	BasicBlock *ExitBB = BasicBlock::Create(getGlobalContext(), "", TheFunction);
	CG::Symtabs.top()->TheFunction = TheFunction;
	CG::Symtabs.top()->FunctionName = new std::string(name);

	CG::Symtabs.top()->FunctionEnd = ExitBB;

	CG::Builder.SetInsertPoint(BB);

	Value *v = nullptr;  
	if (noRet == false) {
		DEBUG_MSG("SETTING UP RETVAL FOR SYMTAB " << CG::Symtabs.top()->ID);
		v = CG::Builder.CreateAlloca(retType, nullptr, "");
		CG::Symtabs.top()->retVal = v;
	}

	arg_it = TheFunction->arg_begin();
	for (unsigned int i = 0; i < args->size(); i++, arg_it++) {
		Value *v = CG::Builder.CreateAlloca(arg_it->getType());
		CG::Builder.CreateStore(arg_it, v);
		CG::Symtabs.top()->create((*args)[i]->name);
		CG::Symtabs.top()->objs[(*args)[i]->name]->setValue(v);
	}

	Value *finalV = body->Codegen();
	DEBUG_MSG("COMPLETED CODEGEN FUNCTION BLOCK");

	if (hasReturn == false && finalV) {
		BasicBlock *bb = CG::Symtabs.top()->getFunctionEnd();
		if (bb == nullptr) {
			std::cerr << "fatal: no Function End found!\n";
			exit(1);
		}

		if (body->statements.back()->returnsPtr() && finalV->getType()->isPointerTy()) {
			finalV = CG::Builder.CreateLoad(finalV);
		}

		if (CG::Symtabs.top()->getRetVal())
			CG::Builder.CreateStore(finalV, CG::Symtabs.top()->getRetVal());
		finalV = CG::Builder.CreateBr(bb);
	} else if (finalV == nullptr || retType == nullptr) {
		CG::Builder.CreateBr(ExitBB);		
	}

	if (noRet == true) {
		CG::Builder.SetInsertPoint(ExitBB);
		CG::Builder.CreateRetVoid();
	} else {
		CG::Builder.SetInsertPoint(ExitBB);

		Value *r = CG::Builder.CreateLoad(v);
		CG::Builder.CreateRet(r);
	}

	CG::Symtabs.pop();
	
	if (IP != nullptr)
		CG::Builder.SetInsertPoint(IP);
	
	CG::TheFPM->run(*TheFunction);

	for (FunctionStatement *clone : clones) {
		clone->Codegen();
	}

	DEBUG_MSG("FINISHED CODEGEN FOR FunctionStatement " << name << " (SYMTAB: " << body->symtab->ID << ")");
	return TheFunction;
}

FunctionStatement::~FunctionStatement() {
	delete args;
	delete body;
}
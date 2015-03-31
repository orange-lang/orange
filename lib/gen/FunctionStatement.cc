#include "gen/FunctionStatement.h"
#include "gen/Block.h"
#include "gen/generator.h"

FunctionStatement::FunctionStatement(std::string* name, ArgList *args, Block *body) {
	this->name = name ? *name : "";
	this->args = args;
	this->body = body;

	if (args == nullptr) {
		this->args = new ArgList();
	}

	// Create this as a symbol in our parent.
	if (CG::Symtab->parent) {
		CG::Symtab->parent->create(this->name);
		CG::Symtab->parent->objs[this->name]->isFunction = true; 
		CG::Symtab->parent->objs[this->name]->reference = (Statement *)this; 
	}

	// Add arguments to symbol table
	for (ArgExpr *expr : *(this->args)) {	
		CG::Symtab->create(expr->name);

		if (expr->type == nullptr) {
			continue;
		}

		if (expr->type) {
			CG::Symtab->objs[expr->name]->setType(expr->type->getType()->getPointerTo());
		}
		CG::Symtab->objs[expr->name]->isSigned = expr->type->isSigned();
	}
}

void FunctionStatement::resolve() {
	if (resolved)
		return; 

	resolved = true;

	body->resolve();
}

Value* FunctionStatement::Codegen() {
	// Set new symtab
	auto oldSymtab = CG::Symtab;
	CG::Symtab = body->symtab;

	bool hasReturn = body->hasReturnStatement();

	std::vector<Type*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];

		if (arg->type == nullptr) {
			std::cout << "warning: function " << name << " didn't have arguments resolved.\n";
			return nullptr; 
		}

		Args[i] = arg->type->getType();
	}

	DEBUG_MSG("GETTING RETURN TYPE FOR FUNCTION BLOCK");
	bool noRet = false; 
	Type *retType = body->getReturnType();

	if (hasReturn == false && retType == nullptr && body->statements.size() > 0) {
		retType = body->statements.back()->getType();
	}

	if (retType == nullptr) {
		DEBUG_MSG("NO RET FOR FUNCTION " << name);

		noRet = true; 
		retType = Type::getVoidTy(getGlobalContext());
	}

	DEBUG_MSG("GOT RETURN TYPE FOR FUNCTION BLOCK");

	FunctionType *FT = FunctionType::get(retType, Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

	if (CG::Symtab->parent) {
		// Set function for the PARENT symtab (the one that could call this function)
		CG::Symtab->parent->create(name);
		CG::Symtab->parent->objs[name]->setValue(TheFunction);
	}

	// Set function for the CURRENT symtab (for recursion)
	CG::Symtab->create(name);
	CG::Symtab->objs[name]->setValue(TheFunction);

	auto arg_it = TheFunction->arg_begin();
	for (unsigned int i = 0; i < args->size(); i++, arg_it++) {
		arg_it->setName((*args)[i]->name);
	}

	auto IP = CG::Builder.GetInsertBlock();
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	BasicBlock *ExitBB = BasicBlock::Create(getGlobalContext(), "", TheFunction);
	CG::Symtab->TheFunction = TheFunction;
	CG::Symtab->FunctionName = new std::string(name);

	CG::Symtab->FunctionEnd = ExitBB;

	CG::Builder.SetInsertPoint(BB);

	Value *v = nullptr;  
	if (noRet == false) {
		DEBUG_MSG("SETTING UP RETVAL FOR SYMTAB " << CG::Symtab->ID);
		v = CG::Builder.CreateAlloca(retType, nullptr, "");
		CG::Symtab->retVal = v;
	}

	arg_it = TheFunction->arg_begin();
	for (unsigned int i = 0; i < args->size(); i++, arg_it++) {
		Value *v = CG::Builder.CreateAlloca(arg_it->getType());
		CG::Builder.CreateStore(arg_it, v);
		CG::Symtab->create((*args)[i]->name);
		CG::Symtab->objs[(*args)[i]->name]->setValue(v);
	}

	Value *finalV = body->Codegen();

	if (hasReturn == false && finalV) {
		BasicBlock *bb = CG::Symtab->getFunctionEnd();
		if (bb == nullptr) {
			std::cerr << "fatal: no Function End found!\n";
			exit(1);
		}

		std::string className = body->statements.back()->getClass();
		if (returnsPtr(className) && finalV->getType()->isPointerTy()) {
			finalV = CG::Builder.CreateLoad(finalV);
		}

		CG::Builder.CreateStore(finalV, CG::Symtab->getRetVal());
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

	CG::Symtab = oldSymtab;
	
	if (IP != nullptr)
		CG::Builder.SetInsertPoint(IP);
	
	CG::TheFPM->run(*TheFunction);

	DEBUG_MSG("FINISHED CODEGEN FOR FunctionStatement");
	return TheFunction;
}

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
	CG::Symtab->parent->create(this->name);
	CG::Symtab->parent->objs[this->name]->isFunction = true; 
	CG::Symtab->parent->objs[this->name]->reference = (Statement *)this; 
}

Value* FunctionStatement::Codegen() {
	std::vector<Type*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];
		Args[i] = arg->type->getType();
	}

	bool noRet = false; 
	Type *retType = body->getReturnType();

	if (retType == nullptr) {
		noRet = true; 
		retType = Type::getVoidTy(getGlobalContext());
	}

	FunctionType *FT = FunctionType::get(retType, Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

	// Set function for the PARENT symtab (the one that could call this function)
	CG::Symtab->create(name);
	CG::Symtab->objs[name]->setValue(TheFunction);

	// Set new symtab
	auto oldSymtab = CG::Symtab;
	CG::Symtab = body->symtab;

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
	CG::Symtab->FunctionEnd = ExitBB;

	CG::Builder.SetInsertPoint(BB);

	Value *v = nullptr;  
	if (noRet == false) {
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

	body->Codegen();

	if (noRet == true) {
		bool hasReturn = false; 
		for (Statement *stmt : body->statements) {
			if (stmt->getClass() == "ReturnExpr") {
				hasReturn = true; 
				break; 
			}
		}

		if (hasReturn == false) 
			CG::Builder.CreateBr(ExitBB);

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

	return TheFunction;
}

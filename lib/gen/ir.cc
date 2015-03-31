#include "gen/AST.h"
#include <gen/generator.h>

typedef CodeGenerator CG;

Type *VarExpr::getType() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		return nullptr;
	}
	
	return o->getType();
}

Type *FuncCallExpr::getType() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) return nullptr; 

	// we found it. do reference 
	FunctionStatement *ref = (FunctionStatement *)(o->reference);
	if (ref == nullptr) {
		std::cerr << "fatal: symtab for " << name << " has no reference to object.\n";
		exit(1); 
	}	

	return ref->body->getReturnType(); 
	// return o->getType();
}


Value* VarExpr::Codegen() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Fatal: no symbol " << name << " found.\n";
		return nullptr;
	}

	return o->getValue();
}

Value* IntVal::Codegen() {
	return ConstantInt::get(getGlobalContext(), APInt(size, value));
}

Value* UIntVal::Codegen() {
	return ConstantInt::get(getGlobalContext(), APInt(size, value));
}

Value* ReturnExpr::Codegen() {
	BasicBlock *bb = CG::Symtab->getFunctionEnd();
	if (expr) {
		Value *v = expr->Codegen();

		if (dynamic_cast<VarExpr*>(expr)) {
			v = CG::Builder.CreateLoad(v);
		}

		CG::Builder.CreateStore(v, CG::Symtab->retVal);
		Value *r = CG::Builder.CreateBr(bb);
		return r; 
	} else {
		return CG::Builder.CreateBr(bb);
	}
}

Value* FuncCallExpr::Codegen() {
	std::vector<Value*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		auto arg = (*args)[i];
		Args[i] = arg->Codegen();
	}

	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr || o->getValue() == nullptr) {
		std::cerr << "Error: no function called " << name << " found.";
		return nullptr;
	}

	return CG::Builder.CreateCall(o->getValue(), Args, name);
}


bool isSigned(Expression *e) {
	if (dynamic_cast<IntVal*>(e)) {
		return true;
	} else if (dynamic_cast<UIntVal*>(e)) {
		return false;
	} else if (dynamic_cast<VarExpr*>(e)) {
		VarExpr *ve = (VarExpr *)e;
		Symobj* p = CG::Symtab->find(ve->name);
		return p->isSigned;
	} else {
		std::cerr << "Fatal: can't determined if expression is signed!\n";
	}
	
	return false;
}

Type *BinOpExpr::getType() { 
	if (LHS->getType() == RHS->getType()) {
		return LHS->getType(); 
	} else {
		std::cerr << "fatal: binop LHS and RHS have different types.\n";
		exit(1);
		return nullptr; 
	}

	return nullptr; 
}


Value* BinOpExpr::Codegen() {
	Value *L = LHS->Codegen();

	if (op == '=' && L == nullptr) {
		printf("((TODO: CREATE VARIABLE. FATAL.))\n");
	}


	Value *R = RHS->Codegen();
  if (dynamic_cast<VarExpr*>(RHS)) {
  	R = CG::Builder.CreateLoad(R, ((VarExpr*)RHS)->name);
  }

	if (!L || !R) return nullptr;

	switch (op) {
		case '+':
	 	case '-':
	 	case '*':
	 	case '/':
		  if (dynamic_cast<VarExpr*>(LHS)) {
		  	L = CG::Builder.CreateLoad(L, ((VarExpr*)LHS)->name);
		  }
		  break;
	}

	switch (op) {
		case '+':
			return CG::Builder.CreateAdd(L, R);
		case '-':
			return CG::Builder.CreateSub(L, R);
		case '*':
			return CG::Builder.CreateMul(L, R);
		case '/':
			// if one of them is signed, they're both signed.
			if (isSigned(LHS) || isSigned(RHS)) {
				return CG::Builder.CreateSDiv(L, R);
			} else {
				return CG::Builder.CreateUDiv(L, R);
			}
			
			return CG::Builder.CreateSDiv(L, R);
		case '=':
			return CG::Builder.CreateStore(R, L);
		default:
			printf("Unhandled: %c\n", op);
			return nullptr;
	}

	return nullptr;
}

Type* Block::getReturnType() {
	Type *ret; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	for (auto stmt : statements) {
	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	ret = ((ReturnExpr *)stmt)->expr->getType();
			CG::Symtab = oldSymtab;	  	
	  	return ret; 
	  }
	}

	CG::Symtab = oldSymtab;
	return nullptr;
}


Value* FunctionStatement::Codegen() {
	std::vector<Type*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];
		Args[i] = getType(arg->type);
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


Value* Block::Codegen() {
	for (Statement *stmt : statements) {
		stmt->Codegen();

	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	break; // only process one return statement per block. 
	  	// anything else is unreachable.
	  }
	}



	return nullptr;
}

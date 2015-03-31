#include "gen/AST.h"

Module *CodeGenerator::TheModule;
IRBuilder<> CodeGenerator::Builder(getGlobalContext());
Symtab* CodeGenerator::Symtab = nullptr;
FunctionPassManager* CodeGenerator::TheFPM;

typedef CodeGenerator CG;

void CodeGenerator::init() {
	TheModule = new Module("orange", getGlobalContext());
	
	FunctionPassManager *OurFPM = new FunctionPassManager(TheModule);
	TheModule->setDataLayout("");
	
	OurFPM->add(createBasicAliasAnalysisPass());
	OurFPM->add(createInstructionCombiningPass());
	OurFPM->add(createReassociatePass());
	OurFPM->add(createGVNPass());
	OurFPM->add(createCFGSimplificationPass());
	OurFPM->add(createDeadCodeEliminationPass());
	OurFPM->doInitialization();
	TheFPM = OurFPM;
}

void CodeGenerator::Generate(Block *globalBlock) {
	std::vector<Type*> Args;
	FunctionType *FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),
		Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "", TheModule);

	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	CG::Symtab = globalBlock->symtab;
	
	globalBlock->Codegen();

	TheModule->dump();
}

Type *VarExpr::getType() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		return nullptr;
	}
	
	return o->getType();
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
	Value *v = expr->Codegen();

	if (dynamic_cast<VarExpr*>(expr)) {
		v = CG::Builder.CreateLoad(v);
	}

	return CG::Builder.CreateRet(v);
}

Value* FuncCallExpr::Codegen() {
	std::vector<Value*> Args(args->size());
	for (int i = 0; i < args->size(); i++) {
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
		std::cout << ve->name << " signed: " << p->isSigned << std::endl;
		return p->isSigned;
	} else {
		std::cerr << "Fatal: can't determined if expression is signed!\n";
	}
	
	return false;
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
			return CG::Builder.CreateAdd(L, R, "addtmp");
		case '-':
			return CG::Builder.CreateSub(L, R, "subtmp");
		case '*':
			return CG::Builder.CreateMul(L, R, "multmp");
		case '/':
			// if one of them is signed, they're both signed.
			if (isSigned(LHS) || isSigned(RHS)) {
				return CG::Builder.CreateSDiv(L, R, "divtmp");
			} else {
				return CG::Builder.CreateUDiv(L, R, "divtmp");
			}
			
			return CG::Builder.CreateSDiv(L, R, "divtmp");
		case '=':
			return CG::Builder.CreateStore(R, L);
		default:
			printf("Unhandled: %c\n", op);
			return nullptr;
	}

	return nullptr;
}

Type* FunctionStatement::getReturnType() {
	Type *ret; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = body->symtab;

	for (auto stmt : body->statements) {
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
	for (int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];
		Args[i] = getType(arg->type);
	}

	FunctionType *FT = FunctionType::get(getReturnType(), Args, false);
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
	for (int i = 0; i < args->size(); i++, arg_it++) {
		arg_it->setName((*args)[i]->name);
	}

	auto IP = CG::Builder.GetInsertBlock();
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	CG::Builder.SetInsertPoint(BB);

	arg_it = TheFunction->arg_begin();
	for (int i = 0; i < args->size(); i++, arg_it++) {
		Value *v = CG::Builder.CreateAlloca(arg_it->getType());
		CG::Builder.CreateStore(arg_it, v);
		CG::Symtab->create((*args)[i]->name);
		CG::Symtab->objs[(*args)[i]->name]->setValue(v);
	}

	body->Codegen();

	// IF VOID, CREATE RET VOID HERE

	CG::Symtab = oldSymtab;
	
	if (IP != nullptr)
		CG::Builder.SetInsertPoint(IP);
	
	CG::TheFPM->run(*TheFunction);

	return TheFunction;
}


Value* Block::Codegen() {
	for (Statement *stmt : statements) {
		stmt->Codegen();
	}

	return nullptr;
}

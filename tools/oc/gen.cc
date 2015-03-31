#include "AST.h"

Module *CodeGenerator::TheModule;
IRBuilder<> CodeGenerator::Builder(getGlobalContext());
std::stack< std::map<std::string, Value*> *> CodeGenerator::Context;

typedef CodeGenerator CG;

Value* CodeGenerator::getValue(std::string name) {
	// search up the stack...
	auto copy = std::stack< std::map<std::string, Value*> *>(Context);
	while (copy.empty() == false) {
		auto top = copy.top();
		auto it = top->find(name);
		if (it != top->end()) {
			return it->second;
		}
		copy.pop();
	}

	return nullptr;
}


void CodeGenerator::init() {
	TheModule = new Module("orange", getGlobalContext());
}

void CodeGenerator::Generate(Block *globalBlock) {
	std::vector<Type*> Args;
	FunctionType *FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),
		Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "", TheModule);

	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	std::map<std::string, Value*> *CurCtx = new std::map<std::string, Value*>();
	CG::Context.push(CurCtx);

	globalBlock->Codegen();

	printf("((TODO: CODE OPTIMIZATION))\n");

	TheModule->dump();
}

Type *VarExpr::getType() {
	Value *v = CG::getValue(name);
	if (v == nullptr) return nullptr; 
	return v->getType();
}

Value* VarExpr::Codegen() {
	// search up the stack for the variable. if it doesn't exist, return null.
	Value *v = CG::getValue(name);
	return v;

	// Value *v = new AllocaInst(IntegerType::get(getGlobalContext(), 64), name, CG::Builder.GetInsertBlock());
}

Value* IntVal::Codegen() {
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

	return CG::Builder.CreateCall(CG::getValue(name), Args, name);
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
			printf("((TODO: NEED TO KNOW TYPE FOR DIVISION))\n");
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
	for (auto stmt : body->statements) {
	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	return ((ReturnExpr *)stmt)->expr->getType();
	  }
	}

	return nullptr;
}


Value* FunctionStatement::Codegen() {
	std::vector<Type*> Args(args->size());
	for (int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];
		if (arg->type == "int" || arg->type == "int64") {
			Args[i] = Type::getInt64Ty(getGlobalContext());
		} else if (arg->type == "int8") {
			Args[i] = Type::getInt8Ty(getGlobalContext());
		} else if (arg->type == "int16") {
			Args[i] = Type::getInt16Ty(getGlobalContext());
		} else if (arg->type == "int32") {
			Args[i] = Type::getInt32Ty(getGlobalContext());
		} else if (arg->type == "uint8") {
			Args[i] = Type::getInt8Ty(getGlobalContext());
		} else if (arg->type == "uint16") {
			Args[i] = Type::getInt16Ty(getGlobalContext());
		} else if (arg->type == "uint32") {
			Args[i] = Type::getInt32Ty(getGlobalContext());
		} else if (arg->type == "uint" || arg->type == "uint64") {
			Args[i] = Type::getInt64Ty(getGlobalContext());
		} else if (arg->type == "float") {
			Args[i] = Type::getFloatTy(getGlobalContext());
		} else if (arg->type == "double") {
			Args[i] = Type::getDoubleTy(getGlobalContext());
		} else {
			printf("FunctionStatement: unknown type %s!\n", arg->type.c_str());
		}
	}

	printf("((TODO: DETERMINE FUNCTION RETURN TYPE. SYMTAB SHOULD INCLUDE MORE THAN JUST VALUE, FILL AS CALCULATED))\n");
	Type *retType = getReturnType();

	FunctionType *FT = FunctionType::get(Type::getInt64Ty(getGlobalContext()), Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

	(*CG::Context.top())[name] = TheFunction;

	std::map<std::string, Value*> *CurCtx = new std::map<std::string, Value*>();

	auto arg_it = TheFunction->arg_begin();
	for (int i = 0; i < args->size(); i++, arg_it++) {
		arg_it->setName((*args)[i]->name);
	}

	CG::Context.push(CurCtx);

	auto IP = CG::Builder.GetInsertBlock();
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	CG::Builder.SetInsertPoint(BB);

	arg_it = TheFunction->arg_begin();
	for (int i = 0; i < args->size(); i++, arg_it++) {
		Value *v = CG::Builder.CreateAlloca(arg_it->getType());
		CG::Builder.CreateStore(arg_it, v);
		(*CurCtx)[(*args)[i]->name] = v;
	}

	body->Codegen();

	// IF VOID, CREATE RET VOID HERE

	CG::Context.pop();

	if (IP != nullptr)
		CG::Builder.SetInsertPoint(IP);

	return TheFunction;
}


Value* Block::Codegen() {
	for (Statement *stmt : statements) {
		stmt->Codegen();
	}

	return nullptr;
}

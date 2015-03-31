#include <iostream>
#include "parser.h"

static Module *TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value*> NamedValues;
static FunctionPassManager *TheFPM;

void Parser::Dump() {
	TheModule->dump();
}

Parser::Parser(std::vector<Lexeme*> lexemes) {
	this->lexemes = lexemes;
	LLVMContext &Context = getGlobalContext();
	TheModule = new Module("orange", getGlobalContext());

	FunctionPassManager *OurFPM = new FunctionPassManager(TheModule);
	TheModule->setDataLayout("E");

	OurFPM->add(createBasicAliasAnalysisPass());
	OurFPM->add(createInstructionCombiningPass());
	OurFPM->add(createReassociatePass());
	OurFPM->add(createGVNPass());
	OurFPM->add(createCFGSimplificationPass());
	OurFPM->add(createDeadCodeEliminationPass());
	OurFPM->doInitialization();
	TheFPM = OurFPM;

	// do optimization setup
}

Value *OID::Codegen() {
  Value *v = new AllocaInst(IntegerType::get(getGlobalContext(), 64), name, Builder.GetInsertBlock());
  return Builder.CreateLoad(v, name);
}

Value *OInt::Codegen() {
	switch(type) {
		case TYPE_INT8:
			return ConstantInt::get(getGlobalContext(), APInt(8, (int8_t)value));
		case TYPE_INT16:
			return ConstantInt::get(getGlobalContext(), APInt(16, (int16_t)value));
		case TYPE_INT32:
			return ConstantInt::get(getGlobalContext(), APInt(32, (int32_t)value));
		case TYPE_INT64:
			return ConstantInt::get(getGlobalContext(), APInt(64, (int64_t)value));
		default:
			return nullptr;
	}
}

Value *OVariable::Codegen() {
  Value *v = new AllocaInst(IntegerType::get(getGlobalContext(), 64), name, Builder.GetInsertBlock());
  return Builder.CreateStore(value->Codegen(), v);
}

Value *OBinopStatement::Codegen() {
	Value *L = LHS->Codegen();
	Value *R = RHS->Codegen();
	if (L == nullptr || R == nullptr) {
		return nullptr;
	}

	switch (op) {
		case PLUS:
			return Builder.CreateAdd(L, R, "addtmp");
		case MINUS:
			return Builder.CreateSub(L, R, "subtmp");
		case TIMES:
			return Builder.CreateMul(L, R, "multmp");
		case DIVIDE:
			return Builder.CreateSDiv(L, R, "divtmp");
		default:
			printf("%s\n", LexemeMap[op]);
			return nullptr;
	}

	return nullptr;
}


Function *OFunction::Codegen() {
	std::vector<Type*> Args(args.size(), Type::getDoubleTy(getGlobalContext()));
	FunctionType *FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),
		Args, false); 
	Function *func = Function::Create(FT, Function::ExternalLinkage, name, TheModule);

	auto arg_it = func->arg_begin();
	for (int i = 0; i < Args.size(); i++, arg_it++) {
		arg_it->setName(args[i]->name);
	}

  auto IP = Builder.GetInsertBlock();
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", func);
  Builder.SetInsertPoint(BB);

  for (OStatement *statement : block->Statements) {
  	Value *v = statement->Codegen();
  }

  Builder.CreateRetVoid();

	TheFPM->run(*func);

  if (IP != nullptr)
	  Builder.SetInsertPoint(IP);	

	return func;
}

Function *OBlock::Codegen() {
	std::vector<Type*> Args;
	FunctionType *FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),
		Args, false); 
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "", TheModule);

  auto IP = Builder.GetInsertBlock();
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  for (OStatement *statement : Statements) {
  	// Generate code for each statement. 
  	Value *v = statement->Codegen();
  }


  if (IP != nullptr)
	  Builder.SetInsertPoint(IP);

	return TheFunction;
}

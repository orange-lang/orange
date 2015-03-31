#include "gen/FunctionStatement.h"
#include "gen/Block.h"
#include "gen/generator.h"
#include <helper/string.h>

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


FunctionStatement::FunctionStatement(std::string* name, ArgList *args, Block *body) {
	this->name = name ? *name : "";
	this->args = args;
	this->body = body;

	if (args == nullptr) {
		this->args = new ArgList();
	}

	// Create this as a symbol in our parent.
	if (CG::Symtabs.top()->parent) {
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

		if (expr->type) {
			CG::Symtabs.top()->objs[expr->name]->setType(expr->type->getType()->getPointerTo());
		}
		CG::Symtabs.top()->objs[expr->name]->isSigned = expr->type->isSigned();
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
	CG::Symtabs.push(body->symtab);

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
		retType = body->getLastStatementType();
	}

	if (retType == nullptr) {
		DEBUG_MSG("NO RET FOR FUNCTION " << name);

		noRet = true; 
		retType = Type::getVoidTy(getGlobalContext());
	}

	DEBUG_MSG("GOT RETURN TYPE FOR FUNCTION BLOCK");

	FunctionType *FT = FunctionType::get(retType, Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

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

		std::string className = body->statements.back()->getClass();
		if (returnsPtr(className) && finalV->getType()->isPointerTy()) {
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

	DEBUG_MSG("FINISHED CODEGEN FOR FunctionStatement");
	return TheFunction;
}

FunctionStatement::~FunctionStatement() {
	delete args;
	delete body;
}
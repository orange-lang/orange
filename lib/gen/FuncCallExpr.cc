#include "gen/generator.h"
#include "gen/Symtab.h"
#include "gen/ArgExpr.h"
#include "gen/Block.h"
#include "gen/Values.h"
#include "gen/FunctionStatement.h"
#include "gen/FuncCallExpr.h"
#include "gen/CastingEngine.h"

FuncCallExpr::FuncCallExpr(std::string name, ExprList *args) {
	DEBUG_MSG("STARTING FuncCallExpr " << name << " CTOR");

	this->name = name;
	this->args = args;

	// try to find function in symbol table 
	// go through its arguments. get their types. 
	// if the types don't exist, create them here.
	Symobj *func = CG::Symtab->find(name);
	if (func == nullptr) {
		std::cerr << "fatal: calling function that hasn't been declared.\n";
		exit(1);
	}

	// we're not going to through an error if it's null, since that is the 
	// case for external functions 
	DEBUG_MSG("FINISHED FuncCallExpr CTOR");
}

void FuncCallExpr::resolve() {
	if (resolved)
		return;

	// Look at our arguments. Get the type of each argument, and if 
	// the function is missing it, snag it. 
	DEBUG_MSG("RESOLVE ARGUMENTS IN FUNCTION " << name);

	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		exit(1);
	}

	if (o->reference == nullptr) {
		std::cerr << "Fatal: no reference for function object\n";
		exit(1); 
	}

	resolved = true;

	if (o->reference->getClass() == "FunctionStatement") {
		FunctionStatement *fstmt = (FunctionStatement *)o->reference;
		for (int i = 0; i < fstmt->args->size(); i++) {
			if (fstmt->args->at(i)->type != nullptr) continue;
			std::string argName = fstmt->args->at(i)->name;
			DEBUG_MSG("RESOLVE ARGUMENT " << argName << " WITH " << args->at(i)->string() << 
				" (" << args->at(i)->getClass() << ")");

			fstmt->args->at(i)->type = AnyType::Create(args->at(i)->getType());

			// Set the type of the argument inside the symbol table too, since that's not updated.
			Symobj *arg = fstmt->body->symtab->find(argName);
			if (arg->getType() == nullptr) {
				arg->setType(args->at(i)->getType()->getPointerTo());
			}
		}

		for (int i = fstmt->args->size(); i < args->size(); i++) {
			args->at(i)->resolve();
		}

		extern Block *globalBlock;
		std::cout << globalBlock->string() << std::endl;

		fstmt->resolve();
	} else if (o->reference->getClass() == "ExternFunction") {
		// Resolve arguments in external function calls.

		for (int i = 0; i < args->size(); i++) {
			DEBUG_MSG("RESOLVE ARGUMENT " << args->at(i)->string());
			args->at(i)->resolve();
		}

	}

}

Type *FuncCallExpr::getType() {
	DEBUG_MSG("((FuncCallExpr) GETTING TYPE OF " << this->string());

	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		return nullptr; 
	}

	if (o->reference == nullptr) {
		std::cerr << "Fatal: no reference for function object\n";
		return nullptr; 
	}

	if (o->getValue() && isa<Function>(o->getValue())) {
		Function *f = (Function *)o->getValue();
		return f->getReturnType();
	}

	if (o->getValue() == nullptr && o->reference->getClass() == "FunctionStatement") { 
		FunctionStatement *fstmt = (FunctionStatement *)o->reference;
		fstmt->body->symtab->FunctionName = new std::string(fstmt->name);
		Type *t = fstmt->body->getReturnType();

		bool hasReturn = fstmt->body->hasReturnStatement(); 
		if (hasReturn == false && t == nullptr && fstmt->body->statements.size() > 0) {
			t = fstmt->body->statements.back()->getType();
		}

		return t;
	}

	if (o->getType()) {
		return o->getType();
	}

	std::cerr << "Error: couldn't return anything for FuncCallExpr\n"; 
	return nullptr; 
}

Value* FuncCallExpr::Codegen() {
	DEBUG_MSG("GENERATING FuncCallExpr");

	std::vector<Value*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		auto arg = (*args)[i];
		Args[i] = arg->Codegen();

		if (arg->getClass() == "VarExpr") {
			Args[i] = CG::Builder.CreateLoad(Args[i]);
		}
	}

	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr || o->getValue() == nullptr) {
		std::cerr << "Error: no function called " << name << " found.";
		return nullptr;
	}

	if (isa<Function>(o->getValue())) {
		Function *f = cast<Function>(o->getValue());
		// const auto fargs = f->getArgumentList();
		if (f->isVarArg() == false && f->arg_size() != args->size()) {
			std::cerr << "Fatal: function arguments do not match number of arguments in callee\n";
			exit(1);
		}

		int i = 0;
		for (auto it = f->arg_begin(); it != f->arg_end(); ++it, ++i) {
			Value *arg = it;
			auto larg = (*args)[i];

			bool isSigned = false; 
			if (dynamic_cast<IntVal *>(larg)) {
				isSigned = true;
			}

			CastValueToType(&Args[i], arg->getType(), isSigned, true);
		}

		if (f->isVarArg() == true) {
			// C functions require that if a float is used as a variable arugment, it must be promoted to double.  
			for (auto it = args->begin() + i; it != args->end(); i++, it++) {
				if (Args[i]->getType()->isFloatTy()) {
					CastValueToType(&Args[i], Type::getDoubleTy(getGlobalContext()), false);
				}
			}
		}
	}

	Value *v = CG::Builder.CreateCall(o->getValue(), Args);
	return v;
}
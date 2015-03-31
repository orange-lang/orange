#include "gen/generator.h"
#include "gen/Symtab.h"
#include "gen/ArgExpr.h"
#include "gen/Block.h"
#include "gen/Values.h"
#include "gen/FunctionStatement.h"
#include "gen/FuncCallExpr.h"
#include "gen/CastingEngine.h"

FuncCallExpr::FuncCallExpr(std::string name, ExprList *args) {
	this->name = name;
	this->args = args;

	// try to find function in symbol table 
	// go through its arguments. get their types. 
	// if the types don't exist, create them here.
	Symobj *func = CG::Symtabs.top()->find(name);
	if (func == nullptr) {
		std::cerr << "fatal: calling function that hasn't been declared.\n";
		exit(1);
	}
}

void FuncCallExpr::resolve() {
	if (resolved)
		return;

	Symobj *o = CG::Symtabs.top()->find(name);
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
		// First, we want to get the function and go through its arguments
		FunctionStatement *fstmt = (FunctionStatement *)o->reference;
 	
 		// If that function is resolved, we don't want to resolve it again. 

 		int totalResolved = 0; 

		// Look at our arguments. Get the type of each argument, and if 
		// the function is missing it, snag it. 
		for (unsigned int i = 0; i < fstmt->args->size(); i++, totalResolved++) {
			// First, we want to resolve our argument
			args->at(i)->resolve();

			// Next, we want to check the arg for the function.
			ArgExpr *arg = fstmt->args->at(i);

			if (arg->type != nullptr) {
				Type *src = arg->type->getType(); 
				Type *test = args->at(i)->getType();				

				if (ShouldTypesMorph(src, test) == false || arg->isLocked == true) 
					continue;
			}

			std::string argName = arg->name;

			// Now, in the symtab for the function, we want to set the type for the arg 
			fstmt->body->symtab->objs[argName]->setType(args->at(i)->getType()->getPointerTo());
			arg->type = AnyType::Create(args->at(i)->getType());
		}

		// Resolve any other arguments we might have 
		for (int i = totalResolved; i < args->size(); i++) {
			args->at(i)->resolve();
		}

		fstmt->resolve();
	} else if (o->reference->getClass() == "ExternFunction") {
		// Resolve arguments in external function calls.

		for (int i = 0; i < args->size(); i++) {
			args->at(i)->resolve();
		}

	}

}

Type *FuncCallExpr::getType() {
	DEBUG_MSG("((FuncCallExpr) GETTING TYPE OF " << this->string());

	std::string currFunction = CG::Symtabs.top()->getFunctionName();
	if (name == currFunction) 
		return nullptr; 		

	Symobj *o = CG::Symtabs.top()->find(name);
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
			t = fstmt->body->getLastStatementType();
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
	std::vector<Value*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		auto arg = (*args)[i];
		Args[i] = arg->Codegen();

		if (arg->getClass() == "VarExpr") {
			Args[i] = CG::Builder.CreateLoad(Args[i]);
		}
	}

	Symobj *o = CG::Symtabs.top()->find(name);
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
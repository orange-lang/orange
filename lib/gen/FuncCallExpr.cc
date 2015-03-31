/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/generator.h"
#include "gen/Symtab.h"
#include "gen/ArgExpr.h"
#include "gen/Block.h"
#include "gen/Values.h"
#include "gen/FunctionStatement.h"
#include "gen/FuncCallExpr.h"
#include "gen/CastingEngine.h"
#include "gen/Reference.h"

FuncCallExpr::FuncCallExpr(std::string name, ExprList *args) {
	this->name = name;
	this->args = args;

	// try to find function in symbol table 
	// go through its arguments. get their types. 
	// if the types don't exist, create them here.
	Symobj *func = CG::Symtabs.top()->find(name);
	if (func == nullptr) {
		std::cerr << "fatal: calling function " << name << " that hasn't been declared.\n";
		CG::Symtabs.top()->dump();
		exit(1);
	}
}

void FuncCallExpr::resolve() {
	if (resolved)
		return;
	resolved = true;

	Symobj *o = CG::Symtabs.top()->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		exit(1);
	}

	if (o->isFunction == false) {
		std::cout << "fatal: found " << name << " from symtab " << CG::Symtabs.top()->ID << ", but it's not a function!\n";
		exit(1);
	}

	if (o->reference == nullptr) {
		std::cerr << "Fatal: no reference for function object\n";
		exit(1); 
	}

	// First, resolve all of our arguments.
	// We're going to be handling stuff with the functions 
	// so if it's a FunctionStatement, we need to have the types 
	// resolved. 
	for (int i = 0; i < args->size(); i++) {
 		// If arg(i) is a varexpr with a type of array, then 
 		// change it to passing in the reference. 
 		Type *argType = args->at(i)->getType();
 		if (argType && argType->isArrayTy()) {
 			args->at(i) = new Reference(args->at(i)); 
 		}

		args->at(i)->resolve();
	}


	if (o->reference->getClass() == "FunctionStatement") {
		FunctionStatement *fstmt = (FunctionStatement *)o->reference; 

		// We want to know what generic (templated) function we will be calling.
		// getTemplatedInstance() may return the original name of the function,
		// in which case a templated has not been created.
		// On error, getTemplatedInstance() will throw an exception.
		// 
		// getTemplatedInstance will create a unique duplicate function with the 
		// arguments that are being called. If the function with that specific 
		// number of arguments already exists, it will not be created. The name 
		// is then returned. 
		try {
			name = fstmt->getTemplatedInstance(args);	
		} catch (std::runtime_error& e) {
			std::cerr << "fatal: could not created generic function for " << name << std::endl; 
			std::cerr << "reason: " << e.what() << std::endl;
			exit(1);
		}
	} 

	o->reference->resolve();
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

	if (o->isFunction == false) {
		std::cout << "fatal: found " << name << " from symtab " << CG::Symtabs.top()->ID << ", but it's not a function!\n";		
		CG::Symtabs.top()->dump();
		exit(1);
	}

	if (o->reference == nullptr) {
		std::cerr << "Fatal: no reference for function object (symtab: " << CG::Symtabs.top()->ID << ")\n";
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

		if (arg->returnsPtr()) {
			Args[i] = CG::Builder.CreateLoad(Args[i]);
		}
	}

	Symobj *o = CG::Symtabs.top()->find(name);
	if (o == nullptr || o->getValue() == nullptr) {
		std::cerr << "fatal: no function called " << name << " found.\n";
		CG::Symtabs.top()->dump();
		exit(1);
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

FuncCallExpr::~FuncCallExpr() {
	delete args;
}
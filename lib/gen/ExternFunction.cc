/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/ExternFunction.h"
#include "gen/generator.h"
#include "gen/ArgExpr.h"

ExternFunction::ExternFunction(AnyType *returnType, std::string name, ArgList *args) {
	this->returnType = returnType;
	this->name = name;
	this->args = args;

	DEBUG_MSG("ADDING EXTERNAL FUNCTION " << name << " TO SYMTAB " << CG::Symtabs.top()->ID << " PTR: " << this);

	CG::Symtabs.top()->create(this->name);
	CG::Symtabs.top()->objs[this->name]->isFunction = true; 
	CG::Symtabs.top()->objs[this->name]->setType(returnType->getType()); 
	CG::Symtabs.top()->objs[this->name]->reference = (Statement *)this; 
}

void ExternFunction::resolve() {
	if (resolved == true)	
		return;

	// Nothing to do for ExternFunction::resolve.

	resolved = true; 
}

Value* ExternFunction::Codegen() { 
	std::vector<Type*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		ArgExpr *arg = (*args)[i];
		Args[i] = arg->getType();
	}

	FunctionType *FT = FunctionType::get(returnType->getType(), Args, args->isVarArg);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

	CG::Symtabs.top()->create(name);
	CG::Symtabs.top()->objs[name]->setValue(TheFunction);

	return TheFunction; 
}

ExternFunction::~ExternFunction() {
	delete returnType;
	delete args;
}
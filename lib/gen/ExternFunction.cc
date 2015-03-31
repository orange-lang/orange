#include "gen/ExternFunction.h"
#include "gen/generator.h"
#include "gen/ArgExpr.h"

ExternFunction::ExternFunction(AnyType *returnType, std::string name, ArgList *args) {
	this->returnType = returnType;
	this->name = name;
	this->args = args;

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
		Args[i] = arg->type->getType();
	}

	FunctionType *FT = FunctionType::get(returnType->getType(), Args, args->isVarArg);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, name, CG::TheModule);

	CG::Symtabs.top()->create(name);
	CG::Symtabs.top()->objs[name]->setValue(TheFunction);

	return TheFunction; 
}


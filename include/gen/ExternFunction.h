#ifndef __EXTERN_FUNCTION_H__
#define __EXTERN_FUNCTION_H__
#include "AST.h"

class ExternFunction : public Statement {
public:
	virtual std::string getClass() { return "ExternFunction"; }

	AnyType *returnType; 
	std::string name; 
	ArgList *args;	

	virtual bool isSigned() { return returnType->isSigned(); }

	void resolve();

	Value* Codegen();

	virtual Statement* clone() { 
		ExternFunction *ret = new ExternFunction(returnType->clone(), name, args->clone());
		return ret;
	}

	ExternFunction(AnyType *returnType, std::string name, ArgList *args);

	~ExternFunction();
};

#endif 
#ifndef __EXTERN_FUNCTION_H__
#define __EXTERN_FUNCTION_H__
#include "AST.h"

class ExternFunction : public Statement {
public:
	virtual std::string getClass() { return "ExternFunction"; }

	AnyType *returnType; 
	std::string name; 
	ArgList *args;	

	Value* Codegen();

	ExternFunction(AnyType *returnType, std::string name, ArgList *args);
};

#endif 
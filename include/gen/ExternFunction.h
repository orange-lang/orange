/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __EXTERN_FUNCTION_H__
#define __EXTERN_FUNCTION_H__
#include "AST.h"
#include "AnyType.h"

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
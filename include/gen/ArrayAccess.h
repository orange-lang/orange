/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ARRAY_ACCESS_H__
#define __ARRAY_ACCESS_H__
#include "AST.h"

class ArrayAccess : public Expression {
public: 
	Expression *array, *idx; 
	
	virtual std::string getClass() { return "ArrayAccess"; }

	virtual bool returnsPtr() { return true; }

	virtual std::string string();
	virtual Type* getType();
	virtual void resolve();
	virtual Value* Codegen();

	virtual ASTNode* clone() { 
		ArrayAccess *ret = new ArrayAccess((Expression *)array->clone(), (Expression *)idx->clone());
		return ret;
	}

	ArrayAccess(Expression *array, Expression *idx);
}; 

#endif 


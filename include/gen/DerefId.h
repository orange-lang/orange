/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __DEREFID_H__
#define __DEREFID_H__
#include "AST.h"
#include "VarExpr.h"

class DerefId : public Expression {
public:
	Expression *id; 
	int pointers = 0;

	virtual std::string getClass() { return "DerefId"; }
	virtual std::string string();

	virtual Value* Codegen();
	virtual Type* getType();

	virtual bool isConstant() { return false; }
	virtual bool returnsPtr() { return true; }

	virtual ASTNode* clone() { 
		DerefId *ret = new DerefId((VarExpr *)id->clone());
		ret->pointers = pointers;
		return ret; 
	}


	DerefId(Expression *id) : id(id) { }

	~DerefId();
}; 

#endif 
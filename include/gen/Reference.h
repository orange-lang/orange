/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __REFERENCE_H__
#define __REFERENCE_H__
#include "AST.h"

class Reference : public Expression {
public:
	virtual std::string getClass() { return "Reference"; }

	virtual bool isConstant() { return false; }
	virtual bool returnsPtr() { return false; }

	virtual std::string string();
	virtual Type* getType();
	virtual void resolve();
	virtual Value* Codegen();

	Expression *value; 

	virtual ASTNode* clone() { 
		Reference* ret = new Reference((Expression *)value->clone());
		return ret;
	}

	Reference(Expression *value) : value(value) {};
};

#endif 

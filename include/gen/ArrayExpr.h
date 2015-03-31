/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ARRAY_EXPR_H__
#define __ARRAY_EXPR_H__
#include "AST.h"

class ArrayExpr : public Expression {
public:
	virtual std::string getClass() { return "ArrayExpr"; }

	ExprList *elements;

	virtual Value* Codegen();
	virtual Type *getType();
	virtual std::string string();
	virtual void resolve();
	virtual bool returnsPtr() { return true; }

	virtual bool isConstant();

	virtual ASTNode* clone() { 
		ExprList *elements_clone = new ExprList();
		for (auto v : *elements) {
			elements_clone->push_back((Expression *)v->clone());			
		}

		ArrayExpr *ret = new ArrayExpr(elements_clone);
		return ret;
	}

	ArrayExpr(ExprList *list) : elements(list) { }
};

#endif 
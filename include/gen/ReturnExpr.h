/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __RETURN_EXPR_H__
#define __RETURN_EXPR_H__
#include "AST.h"

class ReturnExpr : public Expression {
public:
	virtual std::string getClass() { return "ReturnExpr"; }

	Value* Codegen();

	Expression *expr;

	virtual bool isSigned() { return expr->isSigned(); }

	void resolve();

	virtual bool isConstant() { return expr->isConstant(); }


	virtual std::string string() {
		if (expr) 
			return "RETURN " + expr->string();
		else 
			return "RETURN";
	}

	virtual ASTNode* clone() { 
		ReturnExpr* ret = new ReturnExpr((Expression *)expr->clone());
		return ret; 
	}

	ReturnExpr(Expression *expr) : expr(expr) {}

	~ReturnExpr();
};

#endif
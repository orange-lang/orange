/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __INCREMENT_EXPR_H__
#define __INCREMENT_EXPR_H__
#include "AST.h"

class IncrementExpr : public Expression {
public:
	virtual std::string getClass() { return "IncrementExpr"; }

	virtual bool isConstant() { return false; }

	virtual std::string string();
	virtual Type* getType();
	virtual void resolve();
	virtual Value* Codegen();

	Expression *expr; 
	std::string op; 
	bool prefixIncrement = false; 

	virtual ASTNode* clone() { 
		IncrementExpr *ret = new IncrementExpr((Expression *)expr->clone(), op, prefixIncrement);
		return ret; 
	}

	IncrementExpr(Expression *expr, std::string op, bool prefixIncrement);
};

#endif 
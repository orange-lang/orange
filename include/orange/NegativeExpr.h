/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_NEGATIVE_EXPR_H__
#define __ORANGE_NEGATIVE_EXPR_H__

#include "AST.h"
#include "Values.h"

class NegativeExpr : public Expression {
private:
	Expression* m_expr;
public:
	virtual std::string getClass() { return "NegativeExpr"; }

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		return new NegativeExpr((Expression*)m_expr->clone());
	}

	virtual std::string string();

	virtual OrangeTy* getType();

	virtual bool isSigned() { return true; }

	NegativeExpr(Expression *expr);
};

#endif 

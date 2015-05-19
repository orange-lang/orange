/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_TERNARY_EXPR_H__
#define __ORANGE_TERNARY_EXPR_H__

#include "AST.h"

class TernaryExpr : public Expression {
private:
	Expression* m_condition;
	Expression* m_true_expr; 
	Expression* m_false_expr; 
public:
	virtual std::string getClass() { return "TernaryExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual void resolve();

	virtual bool isSigned();

	virtual Expression* condition();

	virtual Expression* trueExpression();

	virtual Expression* falseExpression();

	TernaryExpr(Expression* condition, Expression* trueExpr, Expression* falseExpr);
};

#endif 
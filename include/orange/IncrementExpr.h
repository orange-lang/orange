/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_INCREMENT_EXPR_H__
#define __ORANGE_INCREMENT_EXPR_H__

#include "AST.h"
#include "Values.h"

class IncrementExpr : public Expression {
private:
	Expression* m_expr;
	bool m_preincrement = false;
	StrElement m_op;
public:
	virtual std::string getClass() { return "IncrementExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual void resolve();

	virtual bool isSigned();

	IncrementExpr(Expression* expression, StrElement op, bool preincrement = false);
};

#endif 
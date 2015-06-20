/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_DEREF_EXPR_H__
#define __ORANGE_DEREF_EXPR_H__

#include "AST.h"

class DerefExpr : public Expression {
private:
	Expression* m_expr;
public:
	virtual std::string getClass() { return "DerefExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual bool isSigned();

	virtual bool returnsPtr();

	DerefExpr(Expression* expr);
};

#endif 

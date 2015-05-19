/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_CAST_EXPR_H__
#define __ORANGE_CAST_EXPR_H__

#include "AST.h"

class CastExpr : public Expression {
private:
	OrangeTy* m_type; 
	Expression* m_expr;
public:
	virtual std::string getClass() { return "CastExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual void resolve();

	virtual bool isSigned();

	CastExpr(OrangeTy* type, Expression* expr);
};

#endif 
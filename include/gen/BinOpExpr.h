/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __BIN_OP_EXPR_H__
#define __BIN_OP_EXPR_H__

#include "AST.h"

class BinOpExpr : public Expression {
public:
	virtual std::string getClass() { return "BinOpExpr"; }

	Value* Codegen();

	Type *getType();

	Expression *LHS;
	std::string op;
	Expression *RHS;

	virtual bool isSigned();

	virtual void resolve();

	virtual bool isConstant() { return LHS->isConstant() && RHS->isConstant(); }

	virtual ASTNode* clone() { 
		BinOpExpr *ret = new BinOpExpr((Expression *)LHS->clone(), op, (Expression *)RHS->clone());
		return ret;
	}

	virtual std::string string() {
		std::stringstream ss;
		ss << "( " << LHS->string() << " " << op << " " << RHS->string() << " )";
		return ss.str();
	}

	BinOpExpr(Expression *LHS, std::string op, Expression *RHS);

	~BinOpExpr();
};

#endif
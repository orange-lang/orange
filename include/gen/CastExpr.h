/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __CASTEXPR_H__ 
#define __CASTEXPR_H__
#include "AST.h"
#include "AnyType.h"

class CastExpr : public Expression {
public:
	AnyType *type;
	Expression *expr;

	virtual std::string getClass() { return "CastExpr"; }
	virtual Type *getType() { return type->getType(); }
	virtual bool isSigned() { return type->isSigned(); }

	virtual Value* Codegen();

	virtual std::string string() {
		std::string type_str = type->getTypeStr();
		for (int i = 0; i < type->getNumPointers(); i++) 
			type_str += "*";
		return "(" + type_str + ")" + expr->string(); 
	}

	virtual bool isConstant() { return expr->isConstant(); }

	virtual ASTNode* clone() { 
		CastExpr *ret = new CastExpr((AnyType *)type->clone(), (Expression *)expr->clone());
		return ret;
	}


	CastExpr(AnyType *type, Expression *expr) : type(type), expr(expr) {}

	~CastExpr();
};

#endif 
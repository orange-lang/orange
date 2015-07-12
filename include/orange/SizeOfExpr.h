/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_SIZE_OF_EXPR_H__
#define __ORANGE_SIZE_OF_EXPR_H__

#include "AST.h"
#include "OrangeTypes.h"

class SizeOfExpr : public Expression {
private:
	OrangeTy* m_type = nullptr; 
	Expression* m_expr = nullptr;

	unsigned int getPrimitiveSize(OrangeTy* primitive);
public:
	virtual std::string getClass() { return "SizeOfExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual void resolve();

	virtual OrangeTy* getType() const { 
		return IntTy::getUnsigned(64); 
	}

	virtual bool isSigned() { return false; }

	SizeOfExpr(OrangeTy* type);
	SizeOfExpr(Expression* expr);
};

#endif 

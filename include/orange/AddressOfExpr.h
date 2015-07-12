/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ADDRESS_OF_EXPR_H__
#define __ORANGE_ADDRESS_OF_EXPR_H__

#include "AST.h"

class AddressOfExpr : public Expression {
private:
	Expression* m_expr;
public:
	virtual std::string getClass() { return "AddressOfExpr"; }

	virtual std::string string(); 

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual void resolve();

	AddressOfExpr(Expression* expr);
};

#endif 

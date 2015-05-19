/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_DOT_EXPR_H__
#define __ORANGE_DOT_EXPR_H__

#include "AST.h"

class AnyID;

class DotExpr : public Expression {
private:
	AnyID* m_LHS = nullptr;
	std::string m_RHS; 

	ASTNode* m_obj = nullptr;
public:
	virtual std::string getClass() { return "DotExpr"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual void resolve();

	virtual bool isSigned();

	DotExpr(AnyID* LHS, std::string RHS);
};

#endif 
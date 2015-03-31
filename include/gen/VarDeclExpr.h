/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __VARDECL_EXPR_H__
#define __VARDECL_EXPR_H__
#include "AST.h"
#include "AnyType.h"

class VarDeclExpr : public Expression {
public:
	virtual std::string getClass() { return "VarDeclExpr"; }
	
	AnyType *type; 
	std::string name;
	Expression *value;

	Value* Codegen();

	virtual bool isSigned() { return type->isSigned(); }

	virtual Type* getType() {
		return type->getType();
	}

	virtual std::string string() {
		return name;
	}

	virtual ASTNode* clone() { 
		std::string* name_p = new std::string(name); 
		VarDeclExpr* ret = new VarDeclExpr((AnyType *)type->clone(), name_p, (Expression*)value->clone());
		delete name_p; 
		return ret;
	}

	virtual bool returnsPtr() { return true; }


	virtual bool isConstant() { return false; }

	virtual void resolve();

	VarDeclExpr(AnyType *type, std::string *name, Expression *value);

	~VarDeclExpr();
};

#endif 
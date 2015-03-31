/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __VAR_EXPR_H__
#define __VAR_EXPR_H__
#include "AST.h"
#include "AnyType.h"

class VarExpr : public Expression {
public:
	virtual std::string getClass() { return "VarExpr"; }

	Value* Codegen();
	Type *getType();

	std::string name;

	virtual bool isSigned();

	virtual bool isConstant() { return false; }

	virtual bool returnsPtr() { return true; }

	virtual std::string string() {
		std::stringstream ss;

		if (getType()) {
			auto a = AnyType::Create(getType()); 
			ss << "(" << a->string() << ")";
			delete a;
		} else {
			ss << "(id)";
		}
		ss << name; 
		return ss.str();
	}

	virtual ASTNode* clone() { 
		VarExpr* ret = new VarExpr(name);
		return ret;
	}

	VarExpr(std::string name) : name(name) { }
};

#endif 
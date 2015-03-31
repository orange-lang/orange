/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ARG_EXPR_H__
#define __ARG_EXPR_H__
#include "AST.h"
#include "AnyType.h"

class ArgExpr : public Statement {
public:
	Value* Codegen() {
		printf("ArgExpr::Codegen()\n");
		return nullptr;
	}

	AnyType *type;
	std::string name;
	bool isLocked = false;

	Type *getType();

	Statement *clone();

	virtual bool isSigned() { return type->isSigned(); }
	virtual bool isConstant() { return false; }

	virtual std::string string() {
		std::stringstream ss;
		if (type && type->getTypeStr() != "") {
			ss << type->getTypeStr() << " ";
		}
		ss << name;
		return ss.str();
	}

	ArgExpr(AnyType* type, std::string* name);
};

#endif 
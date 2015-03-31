#ifndef __ARG_EXPR_H__
#define __ARG_EXPR_H__
#include "AST.h"

class ArgExpr : public Statement {
public:
	Value* Codegen() {
		printf("ArgExpr::Codegen()\n");
		return nullptr;
	}

	AnyType *type;
	std::string name;
	bool isLocked = false;

	virtual bool isSigned() { return type->isSigned(); }

	virtual std::string string() {
		std::stringstream ss;
		if (type && type->type != "") {
			ss << type->type << " ";
		}
		ss << name;
		return ss.str();
	}

	ArgExpr(AnyType* type, std::string* name);
};

#endif 
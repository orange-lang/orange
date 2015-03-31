#ifndef __VAR_EXPR_H__
#define __VAR_EXPR_H__
#include "AST.h"

class VarExpr : public Expression {
public:
	Value* Codegen();
	Type *getType();

	std::string name;

	virtual std::string string() {
		return name;
	}

	VarExpr(std::string name) : name(name) { }
};

#endif 
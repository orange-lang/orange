#ifndef __FUNC_CALL_EXPR_H__
#define __FUNC_CALL_EXPR_H__
#include "AST.h"

class FuncCallExpr : public Expression {
public:
	virtual std::string getClass() { return "FuncCallExpr"; }

	Value* Codegen();

	Type *getType();

	std::string name;
	ExprList *args;

	void resolve();

	virtual std::string string() {
		std::stringstream ss;
		ss << name << "( ";
		for (unsigned int i = 0; i < args->size(); i++) {
			ss << (*args)[i]->string() << " ";
			if (i + 1 != args->size())
				ss << ", ";
		}
		ss << ")";

		return ss.str();
	}

	FuncCallExpr(std::string name, ExprList *args);
};

#endif
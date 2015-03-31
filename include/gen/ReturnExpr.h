#ifndef __RETURN_EXPR_H__
#define __RETURN_EXPR_H__
#include "AST.h"

class ReturnExpr : public Expression {
public:
	Value* Codegen();

	Expression *expr;

	virtual std::string string() {
		return "RETURN " + expr->string();
	}

	ReturnExpr(Expression *expr) : expr(expr) {}
};

#endif
#ifndef __RETURN_EXPR_H__
#define __RETURN_EXPR_H__
#include "AST.h"

class ReturnExpr : public Expression {
public:
	virtual std::string getClass() { return "ReturnExpr"; }

	Value* Codegen();

	Expression *expr;

	virtual bool isSigned() { return expr->isSigned(); }


	virtual std::string string() {
		if (expr) 
			return "RETURN " + expr->string();
		else 
			return "RETURN";
	}

	ReturnExpr(Expression *expr) : expr(expr) {}
};

#endif
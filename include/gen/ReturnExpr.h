#ifndef __RETURN_EXPR_H__
#define __RETURN_EXPR_H__
#include "AST.h"

class ReturnExpr : public Expression {
public:
	virtual std::string getClass() { return "ReturnExpr"; }

	Value* Codegen();

	Expression *expr;

	virtual bool isSigned() { return expr->isSigned(); }

	void resolve();

	virtual bool isConstant() { return expr->isConstant(); }


	virtual std::string string() {
		if (expr) 
			return "RETURN " + expr->string();
		else 
			return "RETURN";
	}

	virtual Statement* clone() { 
		ReturnExpr* ret = new ReturnExpr((Expression *)expr->clone());
		return ret; 
	}

	ReturnExpr(Expression *expr) : expr(expr) {}

	~ReturnExpr();
};

#endif
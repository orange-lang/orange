#ifndef __NEGATIVE_EXPR__
#define __NEGATIVE_EXPR__
#include "AST.h"

class NegativeExpr : public Expression {
public:
	Expression *expr;

	virtual std::string getClass() { return "NegativeExpr"; }
	virtual Value* Codegen();
	virtual Type *getType() { return expr->getType(); }
	virtual std::string string() { return "-" + expr->string(); }

	virtual bool isConstant() { return expr->isConstant(); }


	NegativeExpr(Expression *expr) : expr(expr) {}

	~NegativeExpr();
};

#endif 
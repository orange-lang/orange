#ifndef __BIN_OP_EXPR_H__
#define __BIN_OP_EXPR_H__

#include "AST.h"

class BinOpExpr : public Expression {
public:
	virtual std::string getClass() { return "BinOpExpr"; }

	Value* Codegen();

	Type *getType();

	Expression *LHS;
	std::string op;
	Expression *RHS;

	virtual bool isSigned();

	virtual void resolve();

	virtual std::string string() {
		std::stringstream ss;
		ss << "( " << LHS->string() << " " << op << " " << RHS->string() << " )";
		return ss.str();
	}

	BinOpExpr(Expression *LHS, std::string op, Expression *RHS);

	~BinOpExpr();
};

#endif
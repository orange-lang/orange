#ifndef __BIN_OP_EXPR_H__
#define __BIN_OP_EXPR_H__

#include "AST.h"

class BinOpExpr : public Expression {
public:
	Value* Codegen();

	Type *getType();


	Expression *LHS;
	char op;
	Expression *RHS;

	virtual std::string string() {
		std::stringstream ss;
		ss << "( " << LHS->string() << " " << op << " " << RHS->string() << " )";
		return ss.str();
	}

	BinOpExpr(Expression *LHS, char op, Expression *RHS);
};

#endif
#ifndef __ARRAY_EXPR_H__
#define __ARRAY_EXPR_H__
#include "AST.h"

class ArrayExpr : public Expression {
public:
	virtual std::string getClass() { return "ArrayExpr"; }

	ExprList *elements;

	virtual Value* Codegen();
	virtual Type *getType();
	virtual std::string string();
	virtual void resolve();
	virtual bool returnsPtr() { return true; }

	virtual bool isConstant();

	ArrayExpr(ExprList *list) : elements(list) { }
};

#endif 
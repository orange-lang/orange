#ifndef __VARDECL_EXPR_H__
#define __VARDECL_EXPR_H__
#include "AST.h"

class VarDeclExpr : public Expression {
public:
	virtual std::string getClass() { return "VarDeclExpr"; }
	
	AnyType *type; 
	std::string name;
	Expression *value;

	Value* Codegen();

	virtual bool isSigned() { return type->isSigned(); }

	virtual Type* getType() {
		return type->getType();
	}

	virtual std::string string() {
		return name;
	}

	virtual void resolve();

	VarDeclExpr(AnyType *type, std::string *name, Expression *value);
};

#endif 
#ifndef __VAR_EXPR_H__
#define __VAR_EXPR_H__
#include "AST.h"

class VarExpr : public Expression {
public:
	virtual std::string getClass() { return "VarExpr"; }

	Value* Codegen();
	Type *getType();

	std::string name;

	virtual bool isSigned();

	virtual std::string string() {
		std::stringstream ss;

		if (getType()) {
			auto a = AnyType::Create(getType()); 
			ss << "(" << a->type << ")";
			delete a;
		} else {
			ss << "(id)";
		}
		ss << name; 
		return ss.str();
	}

	VarExpr(std::string name) : name(name) { }
};

#endif 
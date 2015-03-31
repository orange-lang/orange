#ifndef __VAR_EXPR_H__
#define __VAR_EXPR_H__
#include "AST.h"
#include "AnyType.h"

class VarExpr : public Expression {
public:
	virtual std::string getClass() { return "VarExpr"; }

	Value* Codegen();
	Type *getType();

	std::string name;

	virtual bool isSigned();

	virtual bool isConstant() { return false; }

	virtual bool returnsPtr() { return true; }

	virtual std::string string() {
		std::stringstream ss;

		if (getType()) {
			auto a = AnyType::Create(getType()); 
			ss << "(" << a->string() << ")";
			delete a;
		} else {
			ss << "(id)";
		}
		ss << name; 
		return ss.str();
	}

	virtual ASTNode* clone() { 
		VarExpr* ret = new VarExpr(name);
		return ret;
	}

	VarExpr(std::string name) : name(name) { }
};

#endif 
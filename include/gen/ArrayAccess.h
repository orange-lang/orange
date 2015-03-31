#ifndef __ARRAY_ACCESS_H__
#define __ARRAY_ACCESS_H__
#include "AST.h"

class ArrayAccess : public Expression {
public: 
	virtual std::string getClass() { return "ArrayAccess"; }

	virtual bool isConstant() { return false; }
	virtual bool returnsPtr() { return true; }

	virtual std::string string();
	virtual Type* getType();
	virtual void resolve();
	virtual Value* Codegen();

	Expression *array, *idx; 

	virtual ASTNode* clone() { 
		ArrayAccess *ret = new ArrayAccess((Expression *)array->clone(), (Expression *)idx->clone());
		return ret;
	}

	ArrayAccess(Expression *array, Expression *idx);
}; 

#endif 


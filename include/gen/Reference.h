#ifndef __REFERENCE_H__
#define __REFERENCE_H__
#include "AST.h"

class Reference : public Expression {
public:
	virtual std::string getClass() { return "Reference"; }

	virtual bool isConstant() { return false; }
	virtual bool returnsPtr() { return false; }

	virtual std::string string();
	virtual Type* getType();
	virtual void resolve();
	virtual Value* Codegen();

	Expression *value; 

	Reference(Expression *value) : value(value) {};
};

#endif 

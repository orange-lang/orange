#ifndef __DEREFID_H__
#define __DEREFID_H__
#include "AST.h"

class VarExpr; 

class DerefId : public Expression {
public:
	VarExpr *id; 
	int pointers = 0;

	virtual std::string getClass() { return "DerefId"; }
	virtual std::string string();

	virtual Value* Codegen();
	virtual Type* getType();

	DerefId(VarExpr *id) : id(id) { }

	~DerefId();
}; 

#endif 
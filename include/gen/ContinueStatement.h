#ifndef __CONTINUE_STATEMENT_H__ 
#define __CONTINUE_STATEMENT_H__

#include "AST.h"

class ContinueStatement : public Expression {
public:
	Value* Codegen();

	virtual std::string getClass() { return "ContinueStatement"; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual Statement* clone() { 
		return new ContinueStatement(); 
	}
};


#endif 
#ifndef __BREAK_STATEMENT_H__ 
#define __BREAK_STATEMENT_H__

#include "AST.h"

class BreakStatement : public Expression {
public:
	Value* Codegen();

	virtual std::string getClass() { return "BreakStatement"; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual ASTNode* clone() { 
		return new BreakStatement(); 
	}
};


#endif 
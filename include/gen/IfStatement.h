#ifndef __IF_STATEMENT_H__
#define __IF_STATEMENT_H__

#include "AST.h"
#include "Block.h"
#include "CondBlock.h"

class IfStatement : public Expression {
private:
public:
	std::vector<Block *> blocks;

	Value* Codegen();
	Type *getType();

	virtual std::string getClass() { return "IfStatement"; }
	virtual bool returnsPtr() { return true; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual Statement* clone() { 
		IfStatement *ret = new IfStatement();
		for (Block *b : blocks)
			ret->blocks.push_back(b->clone());
		return ret; 
	}

	IfStatement() { }

	~IfStatement();
};

#endif 
#ifndef __CONDBLOCK_H__
#define __CONDBLOCK_H__
#include "Block.h"

class CondBlock : public Block {
public:
	Expression *condition; 

	int inverted = false;

	virtual Block* clone();

	CondBlock(Expression *cond, int inverted = false) : condition(cond), inverted(inverted) { } 
	CondBlock(Expression *cond, Block *block, int inverted = false);

	~CondBlock();
};

#endif 
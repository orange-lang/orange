#ifndef __CONDBLOCK_H__
#define __CONDBLOCK_H__
#include "Block.h"

class CondBlock : public Block {
public:
	Value* Codegen();

	Expression *condition; 

	CondBlock(Expression *cond) : condition(cond) { } 
	CondBlock(Expression *cond, Block *block);
};

#endif 
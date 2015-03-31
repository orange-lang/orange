/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

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
#include "gen/CondBlock.h"

CondBlock::CondBlock(Expression *cond, Block *block) {
	condition = cond; 

	// Copy block 
	for (Statement *stmt : block->statements) {
		statements.push_back(stmt);
	}

	this->symtab = block->symtab; 
}
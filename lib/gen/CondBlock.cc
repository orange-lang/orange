#include "gen/CondBlock.h"
#include "gen/generator.h"


CondBlock::CondBlock(Expression *cond, Block *block, int inverted) {
	condition = cond; 

	// Copy block 
	for (Statement *stmt : block->statements) {
		statements.push_back(stmt);
	}

	this->symtab = block->symtab; 
	this->inverted = inverted;
}

Block* CondBlock::clone() {
	CondBlock* ret = new CondBlock((Expression *)condition->clone(), inverted);
	ret->symtab = symtab->clone();
	ret->symtab->parent = CG::Symtabs.top();
	CG::Symtabs.push(ret->symtab);
	for (Statement *stmt : statements) 
		ret->statements.push_back((Statement *)stmt->clone());
	CG::Symtabs.pop();
	return ret;
}

CondBlock::~CondBlock() {
	delete condition;
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CondBlock.h>
#include <orange/IfStmts.h>

Value* CondBlock::CodegenCondition() {
	return m_condition->Codegen();
}

ASTNode* CondBlock::clone() {
	CondBlock* clonedBlock = new CondBlock((Expression *)m_condition->clone(), symtab()->clone());

	for (auto stmt : m_statements) {
		auto clonedStmt = stmt->clone();
		clonedBlock->addStatement(clonedStmt);

		// if the stmt is a block, set its parent to the clone's symtab IFF 
		// their symtab's parent is the one for our current function statement
		if (Block* block = dynamic_cast<Block*>(clonedStmt)) {
			if (block->symtab()->parent()->ID() == symtab()->ID()) {
				block->symtab()->setParent(clonedBlock->symtab());
			}
		}

		if (IfStmts* ifStmts = dynamic_cast<IfStmts*>(clonedStmt)) {
			for (auto block : ifStmts->blocks()) {
				block->symtab()->setParent(clonedBlock->symtab());
			}
		}
	}

	return clonedBlock;
}


void CondBlock::resolve() {
	if (m_resolved) return; 
	m_condition->resolve();
	Block::resolve();
}

CondBlock::CondBlock(Expression* condition, SymTable* tab) : Block(tab) {
	if (condition == nullptr) {
		throw std::runtime_error("condition must not be null for CondBlock!");
	}

	m_condition = condition; 
}

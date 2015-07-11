/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CondBlock.h>
#include <orange/IfStmts.h>
#include <orange/generator.h>

Value* CondBlock::CodegenCondition() {
	GE::runner()->pushBlock(this);

	m_value = m_condition->Codegen();

	GE::runner()->popBlock();
	
	return m_value;
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
				block->symtab()->setContainer(clonedBlock->symtab());
			}
		}

		if (IfStmts* ifStmts = dynamic_cast<IfStmts*>(clonedStmt)) {
			for (auto block : ifStmts->blocks()) {
				block->symtab()->setParent(clonedBlock->symtab());
				block->symtab()->setContainer(clonedBlock->symtab());
			}
		}
	}

	clonedBlock->copyProperties(this);
	return clonedBlock;
}


void CondBlock::resolve() {
	pushBlock();
	m_condition->resolve();
	popBlock();
	
	Block::resolve();
}

CondBlock::CondBlock(Expression* condition, SymTable* tab, bool inverted) : Block(tab) {
	if (condition == nullptr) {
		throw std::runtime_error("condition must not be null for CondBlock!");
	}

	m_condition = condition; 
	m_inverted = inverted;

	addChild("m_condition", m_condition);
}

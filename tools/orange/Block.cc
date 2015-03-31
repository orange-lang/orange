/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/Block.h>
#include <orange/Runner.h>
#include <orange/generator.h>

SymTable* Block::symtab() const {
	return m_symtab;
}


void Block::addStatement(ASTNode* statement) {
	// After we're locked, we can't add any more statements.
	// The user also shouldn't be able to add nullptr as a statement.
	if (m_locked == true || statement == nullptr) return;

	m_statements.push_back(statement);
}

void Block::generateStatements() {
	Runner* curRunner = GeneratingEngine::sharedEngine()->active();

	for (ASTNode* stmt : m_statements) {
		try {
			stmt->Codegen();
		} catch (CompilerMessage& e) {
			curRunner->log(e);
		}
	}
}

Value* Block::Codegen() {
	m_locked = true;

	GE::runner()->pushBlock(this);

	generateStatements();

	GE::runner()->popBlock();
	return nullptr;
}

ASTNode* Block::clone() {
	Block* clonedBlock = new Block(m_symtab->clone());
	for (auto stmt : m_statements) {
		clonedBlock->addStatement(stmt->clone());
	}
	return clonedBlock;
}

std::string Block::string() {
	std::stringstream ss;

	GE::runner()->pushBlock(this);

	for (ASTNode *s : m_statements) {
		if (s == nullptr) continue;
		ss << s->string() << std::endl;
	}

	GE::runner()->popBlock();
	return ss.str();
}

void Block::resolve() {
	if (m_resolved) return;
	m_resolved = true;
	m_locked = true;

	// Resolve all of our statements.
	for (auto stmt : m_statements) {
		stmt->resolve();
	}
}

Block::Block(SymTable* symtab) {
	m_symtab = symtab;
}
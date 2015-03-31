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

bool Block::isRoot() const { 
	// We're the root block if our symbol table doesn't have a parent.
	return m_symtab && m_symtab->parent() == nullptr; 
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

			if (stmt->getClass() == "ReturnStmt") break;
		} catch (CompilerMessage& e) {
			curRunner->log(e);
		} catch (std::runtime_error& e) {
			CodeLocation loc = stmt->location();
			CompilerMessage msg(ERROR, e.what(), curRunner->pathname(), loc.row_begin, loc.row_end, loc.col_begin, loc.col_end);
			curRunner->log(msg);
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

bool Block::hasReturn() {
	return returnType() != nullptr; 
}

AnyType* Block::returnType() {
	for (ASTNode *s : m_statements) {
		if (s->getClass() == "ReturnStmt") return s->getType(); 
	}

	return nullptr;
}

AnyType* Block::searchForReturn() {
	AnyType* retType = nullptr; 

	for (ASTNode *s : m_statements) {
		if (s->getClass() == "ReturnStmt") {
			if (retType == nullptr) {
				retType = s->getType(); 
			} else {
				// We want to change retType to be the highest precedence return type.
				retType = CastingEngine::GetFittingType(retType, s->getType());
			}
		} else if (s->isBlock() && s->getClass() != "FunctionStmt") {
			// If we're a block (and not a function, since that shouldn't affect this), look for returns.
			Block* block = (Block*)s; 
			AnyType* innerRetType = block->searchForReturn();

			if (innerRetType) {
				retType = CastingEngine::GetFittingType(retType, innerRetType);				
			} 
		}
	}

	return retType;
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

	Runner* curRunner = GE::runner();

	GE::runner()->pushBlock(this);

	// Resolve all of our statements.
	for (auto stmt : m_statements) {
		try {
			stmt->resolve();
		} catch (CompilerMessage& e) {
			curRunner->log(e);
		} catch (std::runtime_error& e) {
			CodeLocation loc = stmt->location();
			CompilerMessage msg(ERROR, e.what(), curRunner->pathname(), loc.row_begin, loc.row_end, loc.col_begin, loc.col_end);
			curRunner->log(msg);
		}
	}

	GE::runner()->popBlock();
}

Block::Block(SymTable* symtab) {
	m_symtab = symtab;
}
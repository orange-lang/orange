/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/Block.h>
#include <orange/runner.h>
#include <orange/generator.h>
#include <orange/IfStmts.h>

SymTable* Block::symtab() const {
	return m_symtab;
}

void Block::pushBlock() {
	GE::runner()->pushBlock(this);
}

void Block::popBlock() {
	GE::runner()->popBlock();
}


bool Block::isRoot() const { 
	return m_symtab && m_symtab->root(); 
}

void Block::addStatement(ASTNode* statement) {
	// After we're locked, we can't add any more statements.
	// The user also shouldn't be able to add nullptr as a statement.
	if (m_locked == true || statement == nullptr) return;

	statement->setParent(this);
	m_statements.push_back(statement);

	addChild(statement);
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
	for (ASTNode *s : m_statements) {
		if (s->getClass() == "ReturnStmt") return true; 
	}

	return false;
}

bool Block::hasJump() {
	for (ASTNode *s : m_statements) {
		if (s->getClass() == "ReturnStmt" || s->getClass() == "LoopSkip") return true; 
	}

	return false;
}

OrangeTy* Block::returnType() {
	for (ASTNode *s : m_statements) {
		if (s->getClass() == "ReturnStmt") return s->getType(); 

		// If we have if statements, look inside of those.
		if (s->getClass() == "IfStmts") {
			IfStmts* ifStmts = (IfStmts*)s; 
			for (auto block : ifStmts->blocks()) {
				auto retTypeNestedBlock = block->returnType();
				if (retTypeNestedBlock) return retTypeNestedBlock; 
			}
		}
	}

	return nullptr;
}

OrangeTy* Block::searchForReturn() {
	OrangeTy* retType = nullptr; 

	for (ASTNode *s : m_statements) {		
		if (s->getClass() == "ReturnStmt") {
			// If we've found an ID ty, keep searching. 
			OrangeTy* sReturnType = s->getType();
			
			if (sReturnType == nullptr || sReturnType->isIDTy()) continue;

			if (retType == nullptr) {
				retType = sReturnType; 
			} else {
				// We want to change retType to be the highest precedence return type.
				retType = CastingEngine::GetFittingType(retType, sReturnType);
			}
		} else if (s->isBlock() && s->getClass() != "FunctionStmt") {
			// If we're a block (and not a function, since that shouldn't affect this), look for returns.
			Block* block = (Block*)s; 
			OrangeTy* innerRetType = block->searchForReturn();

			if (innerRetType) {
				retType = CastingEngine::GetFittingType(retType, innerRetType);				
			} 
		} else if (s->getClass() == "IfStmts") {
			IfStmts* ifStmts = (IfStmts *)s; 

			for (auto block : ifStmts->blocks()) {
				OrangeTy* innerRetType = block->searchForReturn();
				
				if (innerRetType == nullptr || innerRetType->isIDTy() || innerRetType->isVoidTy()) continue;
			
				retType = retType ? CastingEngine::GetFittingType(retType, innerRetType) : innerRetType;
			}
		}
	}

	return retType;
}


ASTNode* Block::clone() {
	Block* clonedBlock = new Block(m_symtab->clone());
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

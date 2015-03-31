/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <orange/runner.h>
#include <orange/generator.h>

Runner::Runner(std::string pathname) {
	m_pathname = pathname;

	bool added = GeneratingEngine::sharedEngine()->addRunner(this);
	if (added == false) {
		throw std::runtime_error("File cannot be added as an entity twice.");
	}

	// Create the global block
	SymTable *globalSymtab = new SymTable(nullptr);
	m_block = new Block(globalSymtab);
	pushBlock(m_block);
}

void Runner::haltRun() {
	m_isRunning = false;
}

bool Runner::hasError() {
	for (auto msg : m_messages) {
		if (msg.type() == ERROR) return true; 
	}

	return false;
}

RunResult Runner::run() {
	// First, set us to running and activate us as the current runner.
	m_isRunning = true;
	GeneratingEngine::sharedEngine()->setActive(this);

	// Try to find our file...
	FILE *file = fopen(pathname().c_str(), "r");
	if (file == nullptr) {
		// Halt our current run and return an error.
		haltRun();

		CompilerMessage msg(NO_FILE, "file " + pathname() + " not found.", pathname(), -1, -1, -1, -1);
		return RunResult(pathname(), false, 1, msg);
	}

	// Parse the file. get yyin and yyparse and use them
	extern FILE* yyin;
	extern int yyparse();
	extern int yyonce; // used to get the endline
	extern void yyflushbuffer();

	yyflushbuffer(); // reset buffer 
	yyonce = 0; // reset yyonce 
	yyin = file; // give flex the file 
	yyparse(); // and do our parse.

	// TODO: run the code.
	int retCode = 0;

	// Do cleanup.
	fclose(file);
	m_isRunning = false;

	bool succeeded = (retCode == 0) && (hasError() == false); 
	return RunResult(pathname(), succeeded, retCode, m_messages);
}

void Runner::log(CompilerMessage message) {
	// We only want to log if we're currently running.
	if (m_isRunning == false) return;

	m_messages.push_back(message);
}

std::string Runner::pathname() const {
	return m_pathname; 
}

void Runner::pushBlock(Block* block) {
	// We don't want to push anything if it's nullptr.
	if (block == nullptr) return;

	m_blocks.push(block);
}

Block* Runner::popBlock() {
	if (m_blocks.empty()) return nullptr;
	Block* top = m_blocks.top();
	m_blocks.pop();
	return top;
}

Block* Runner::makeBlock() {
	// First, get the top block 
	Block* top = topBlock();

	// Create a new block with a new symtable, linked to the top block. 
	SymTable *newSymtab = new SymTable(top->symtab());
	Block* newBlock = new Block(new SymTable(newSymtab));

	pushBlock(newBlock); 
	return newBlock;
}

Block* Runner::topBlock() {
	if (m_blocks.empty()) return nullptr;

	return m_blocks.top();
}

Block* Runner::mainBlock() const {
	return m_block;
}

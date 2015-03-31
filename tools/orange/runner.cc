/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <orange/runner.h>
#include <orange/generator.h>
#include <orange/AnyType.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>

Runner::Runner(std::string pathname) {
	m_pathname = pathname;

	bool added = GeneratingEngine::sharedEngine()->addRunner(this);
	if (added == false) {
		throw std::runtime_error("File cannot be added as an entity twice.");
	}

	// Create the global block
	SymTable *globalSymtab = new SymTable(nullptr);
	m_function = new FunctionStmt("__INTERNAL_main", new AnyType("int"), globalSymtab);
	pushBlock(m_function);

	// Create LLVM stuff; module, builder, etc
	m_module = new Module("orange", getGlobalContext());
	m_module->setTargetTriple(sys::getProcessTriple());

	m_builder = new IRBuilder<>(getGlobalContext());

	m_functionOptimizer = new FunctionPassManager(m_module);
	m_functionOptimizer->doInitialization();
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

	try {
		yyflushbuffer(); // reset buffer 
		yyonce = 0; // reset yyonce 
		yyin = file; // give flex the file 
		yyparse(); // and do our parse.

		// Now that we've parsed everything, let's analyze and resolve code...
		mainFunction()->resolve();

		if (debug())
			std::cout << mainFunction()->string() << std::endl;

		Value *function = mainFunction()->Codegen();

		// TODO: do module optimization.

		if (debug())
			m_module->dump();

		int retCode = hasError() == false ? runModule((Function *)function) : 1;

		// Do cleanup.
		fclose(file);
		m_isRunning = false;

		bool succeeded = (retCode == 0) && (hasError() == false); 
		return RunResult(pathname(), succeeded, retCode, m_messages);
	} catch (CompilerMessage& e) {
		std::cerr << "fatal: " << e.what() << std::endl;
		exit(1);
	} catch (std::runtime_error& e) {
		std::cerr << "fatal: " << e.what() << std::endl;
		exit(1);
	}
}

int Runner::runModule(Function *function) {
	// MCJIT requires the target & asm printer to be initalized 
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  // Create our builder & engine to run the function 
	EngineBuilder builder((std::unique_ptr<Module>(m_module)));

	ExecutionEngine* engine = builder
		.setVerifyModules(true)
		.create();

	// MCJIT requires the engine to be finalized before running it.
	engine->finalizeObject();

	std::vector<GenericValue> args;
	return engine->runFunction((Function *)function, args).IntVal.getSExtValue();

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

FunctionStmt* Runner::mainFunction() const {
	return m_function;
}

Module* Runner::module() const {
	return m_module;
}

IRBuilder<>* Runner::builder() const {
	return m_builder;
}

FunctionPassManager* Runner::functionOptimizer() const {
	return m_functionOptimizer;
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#ifndef __ORANGE_RUNER_H__
#define __ORANGE_RUNER_H__

#include "run.h"
#include "SymTable.h"
#include "Block.h"
#include "FunctionStmt.h"

/**
 * Runner is a class that will run or build a file. It starts with the name 
 * of the path being built. It contains a list of messages that have been 
 * generated during this run. Calling the run() method will compile the code
 * and run it as JIT. Calling the build() method will build the code to 
 * native. 
 */
class Runner {
private:
	std::string m_pathname;
	std::vector<CompilerMessage> m_messages;

	bool m_isRunning;

	/**
	 * Halts the run. Does shut down stuff.
	 */
	void haltRun();

	/**
	 * The symbol table stack; these are
	 * pushed and popped at will by the parser.
	 */ 
	std::stack<Block *> m_blocks;

	/**
	 * The global block for this runner.
	 */
	FunctionStmt* m_function = nullptr;

	/**
	 * The module for this runner.
	 */
	Module* m_module = nullptr;

	/**
	 * The builder for this runner.
	 */
	IRBuilder<>* m_builder = nullptr;

	/**
	 * The PassManager used to optimize functions.
	 */
	FunctionPassManager *m_functionOptimizer;
public:
	/**
	 * Returns whether or not there is at least one error in the run.
	 */
	bool hasError();

	/**
	 * Starts a run. The code will be compiled and ran directly. Returns a run result.
	 */
	RunResult run(); 

	/**
	 * Starts a build. The code will be compiled and built into a native binary. 
	 * Returns a run result of the build.
	 */
	BuildResult build();

	/**
	 * Logs a message to this run. It will be stored internally and return after 
	 * the current run/build finishes. If this run is not currently running, 
	 * nothing will happen.
	 *
	 * @param message The message to log for this run.
	 */
	void log(CompilerMessage message); 

	/**
	 * Gets the pathname registered to this runner.
	 *
	 * @return The pathname registered to this runner.
	 */
	std::string pathname() const; 

	/**
	 * Pushes a block to the stack for this Runner.
	 * If block is null, nothing will happen.
	 *
	 * @param bloc The block to push.
	 */
	void pushBlock(Block* block);

	/**
	 * Pops a block from the stack for this Runner.
	 *
	 * @return The block that was just popped.
	 */
	Block* popBlock();

	/**
	 * Creates a block and adds it to the stack.
	 * The block created will be parented to the top of the 
	 * stack.
	 *
	 * @return The block that was just created.
	 */
	Block* makeBlock();

	/**
	 * Returns the top block on the stack.
	 *
	 * @return The block on the top of the stack.
	 */
	Block* topBlock();

	/**
	 * Gets the global block for this runner.
	 *
	 * @return The global block.
	 */
	FunctionStmt* mainFunction() const;

	/**
	 * Gets the LLVM module assigned to this runner.
	 *
	 * @return The module assigned to this runner.
	 */
	Module* module() const;

	/**
	 * Gets the LLVM builder assigned to this rnuner.
	 *
	 * @return The LLVM builder assigned to this runner.
	 */
	IRBuilder<>* builder() const;

	/**
	 * Gets the FunctionPassManager assigned to this runner.
	 *
	 * @return The FunctionPassManager assigned to this runner.
	 */
	FunctionPassManager* functionOptimizer() const;

	/**
	 * Creates an instance of Runner and registers it inside of the GeneratingEngine.
	 */
	Runner(std::string pathname);
};

#endif
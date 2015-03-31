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

/**
 * Runner is a class that will run or build a file or project. It starts with the name 
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
	std::stack<SymTable *> m_symtabs;
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
	 * Pushes a symbol table to the stack for this Runner.
	 * If symtab is null, nothing will happen.
	 *
	 * @param symtab The symbol table to push.
	 */
	void pushSymtab(SymTable* symtab);

	/**
	 * Pops a symbol table from the stack for this Runner.
	 *
	 * @return The symbol table that was just popped.
	 */
	SymTable* popSymtab();

	/**
	 * Creates a symbol table and adds it to the stack.
	 * The symbol table created will be parented to the top of the 
	 * stack.
	 *
	 * @return The symbol table that was just created.
	 */
	SymTable* makeSymtab();

	/**
	 * Returns the top symbol table on the stack.
	 *
	 * @return The symbol table on the top of the stack.
	 */
	SymTable* topSymtab();

	/**
	 * Creates an instance of Runner and registers it inside of the GeneratingEngine.
	 */
	Runner(std::string pathname);
};

#endif
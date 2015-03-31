/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#ifndef __ORANGE_RUN_H__
#define __ORANGE_RUN_H__

#include <helper/args.h>
#include <helper/link.h>
#include "file.h"
#include "error.h"

/**
 * RunResult is a class to inform the user about whether or not a 
 * run or compile has succeeded. It has a list of messages from the compiler
 */
class RunResult {
private:
	bool m_pass;
	std::vector<CompilerMessage> m_messages;
public:
	/**
	 * Determines whether or not the run passed.
	 * 
	 * @return True if the run passed, false otherwise.
	 */
	bool passed() const;

	/**
	 * Get the list of messages from the run, if any. 
	 *
	 * @return The list of messages, which may be empty.
	 */
	std::vector<CompilerMessage> messages() const;


	/**
	 * Get the list of errors from the run, if any. This list is 
	 * constructed from the messages list. 
	 *
	 * @return The list of errors, which may be empty.
	 */
	std::vector<CompilerMessage> errors() const;

	/**
	 * Get the list of warnings from the run, if any. This list is 
	 * constructed from the messages list. 
	 *
	 * @return The list of warnings, which may be empty.
	 */
	std::vector<CompilerMessage> warnings() const;

	RunResult() {}
	RunResult(bool pass, CompilerMessage message);
	RunResult(bool pass, std::vector<CompilerMessage> messages);
};

/**
 * Invoked from the command line parser, this will run a file or project as 
 * invoked. 
 *
 * @param run The run state from the command line parser.
 */ 
void doRunCommand(cOptionsState run);

/**
 * Runs a file directly without compiling it.
 *
 * @return A RunResult, with a list of errors, if any.
 */
RunResult runFile(std::string filename);

/**
 * Runs a project directly without compiling it.
 *
 * @return A RunResult that will contain if it succeeded with a list of errors, if any.
 */
RunResult runProject(path projectPath);


#endif
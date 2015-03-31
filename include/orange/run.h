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
 * BuildResult is a class to inform the user about whether or not a 
 * build has succeeded. It also contains a list of messages from the compiler.
 */
class BuildResult {
protected:
	bool m_pass;
	std::vector<CompilerMessage> m_messages;
	std::string m_filename;
	unsigned long long m_runtime;

	boost::posix_time::ptime startTime, endTime;
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

	/**
	 * Starts the run, starting a timer to detect how long the run took.
	 */
	void start();

	/**
	 * Finishes the run, ending the timer.
	 *
	 * @param pass Whether or not the test passed.
	 * @param messages The list of messages the occured during the run.
	 */
	void finish(bool pass, CompilerMessage message);
	void finish(bool pass, std::vector<CompilerMessage> messages);

	/**
	 * Gets the amount of time in milliseconds that this run took.
	 *
	 * @return The number of milliseconds that this run was running for.
	 */
	unsigned long long runtime() const; 

	/**
	 * Gets the filename from this run.
	 *
	 * @return The filename from this run.
	 */
	std::string filename() const;

	BuildResult() { }
	BuildResult(std::string filename) { m_filename = filename; }
	BuildResult(std::string filename, bool pass, CompilerMessage message);
	BuildResult(std::string filename, bool pass, std::vector<CompilerMessage> messages);
};

/**
 * RunResult is a class to inform the user about whether or not a 
 * run or compile has succeeded. It has a list of messages from the compiler
 */
class RunResult : public BuildResult {
private:
	unsigned m_retcode;
public:
	/**
	 * Finishes the run, ending the timer.
	 *
	 * @param pass Whether or not the test passed.
	 * @param code The return code from the run
	 * @param messages The list of messages the occured during the run.
	 */
	void finish(bool pass, int code, CompilerMessage message);
	void finish(bool pass, int code, std::vector<CompilerMessage> messages);

	/**
	 * Gets the return code from the run. This value is meaningless if 
	 * pass is false.
	 *
	 * @return Return code from the run.
	 */
	int returnCode() const;

	RunResult() { }
	RunResult(std::string filename) { m_filename = filename; }
	RunResult(std::string filename, bool pass, int code, CompilerMessage message);
	RunResult(std::string filename, bool pass, int code, std::vector<CompilerMessage> messages);
};

/**
 * Invoked from the command line parser, this will run a file or project as 
 * invoked. 
 *
 * @param run The run state from the command line parser.
 */ 
void doRunCommand(cOptionsState run, bool doDebug);

/**
 * Runs a file directly without compiling it.
 *
 * @return A RunResult, with a list of errors, if any.
 */
RunResult runFile(std::string filename, bool doDebug);

/**
 * Runs a project directly without compiling it.
 *
 * @return A RunResult that will contain if it succeeded with a list of errors, if any.
 */
RunResult runProject(path projectPath, bool doDebug);


#endif
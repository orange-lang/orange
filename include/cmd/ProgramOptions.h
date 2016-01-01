/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#pragma once

#include <string>

class OptionsState;

/**
 * Defines command line options to be passed in to a program.
 * -h and --help are always available in any state.
 */
class ProgramOptions {
private:
	std::string m_program_name = "";

	OptionsState* m_main_state = nullptr;
	OptionsState* m_current_state = nullptr;

	/// Returns the help string for the current state.
	std::string getHelpString();
public:
	/**
	 * Returns the program name.
	 * @return Returns the program name.
	 */
	std::string getProgramName() const;

	/**
	 * Gets the current state of the command line options.
	 * @return The command line options' current state.
	 */
	OptionsState* getCurrentState() const;

	/**
	 * Gets the main state (i.e., the initial state) of the command line options.
	 * @return Returns the main state.
	 */
	OptionsState* getMainState() const;

	/**
	 * Parse the command line options provided through the command line.
	 * This method will modify setting flags and call run() on the final
	 * state set by the program.
	 */
	int parse(int argc, char** argv);

	/**
	 * Adds a new state to the main state.
	 * Equivalent to calling getMainState()->addState(OptionsState*);
	 * @param newState The state to add to the main state.
	 */
	void addState(OptionsState* newState);

	/**
	 * Constructs a new ProgramOptions to use for parsing command line options.
	 * @param programName
	 * 	The name of the program. This is _not_ argv[0]. It is the name of the
	 * 	program you wish to display in the help menu.
	 */
	ProgramOptions(std::string programName);
};

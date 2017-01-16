/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>

class StateFlag;

/**
 * A state in the options. Each state can transition to other states.
 * A state is accessed by typing the name of the state in the command line.
 */
class OptionsState {
private:
	/**
	 * Name of this state.
	 */
	std::string m_state_name;

	/**
	 * A list of states that can be transferred to.
	 */
	std::vector<OptionsState *> m_states;

	/**
	 * A list of flags that this state can have.
	 */
	std::vector<StateFlag *> m_flags;
	
	/**
	 * The OptionsState that will receieve the run command
	 * If nothing, this->run will be called. 
	 */
	OptionsState* m_run_delegate = nullptr;
public:
	/// Returns the state name.
	std::string getStateName() const;
	
	/**
	 * Looks in the list of states to return a state by name.
	 * @param stateName The name of the state to get.
	 * @return Returns the state by the given name. Nullptr if it doesn't exist.
	 */
	OptionsState* getState(std::string stateName) const;
	
	/// Gets the list of states that this state can transfer to.
	std::vector<OptionsState *> getStates() const;

	/// Gets the list of flags assigned to this state.
	std::vector<StateFlag *> getFlags() const;
	
	/**
	 * Gets a flag of this state by name.
	 * @param name The name of the flag to get.
	 * @return Returns the flag, if it exists.
	 */
	StateFlag* getFlag(std::string name) const;
	
	/// Gets the delegate to forward run to. nullptr by default.
	OptionsState* getRunDelegate() const;

	/**
	 * Adds a state to the list of transferrable states when this state is 
	 * active.
	 * @param newState The state to add.
	 */
	void addState(OptionsState* newState);

	/**
	 * Adds a flag to the list of flags that can be set on this state.
	 */
	void addFlag(StateFlag* newFlag);
	
	/** 
	 * If set, when this state is supposed to have its run 
	 * function called, runDelegate->run will be called instead.
	 * @param runDelegate The state to forward run to.
	 */
	void setRunDelegate(OptionsState* runDelegate);

	/**
	 * Runs code for this state. This function will only be called if
	 * this state does not transfer to any other states. Does nothing
	 * unless this function is overloaded by a child class.
	 * @param args The arguments used to call this state.
	 */
	virtual int run(std::vector<std::string> args);

	OptionsState(std::string stateName);
	
	virtual ~OptionsState();
};

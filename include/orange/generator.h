/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#ifndef __ORANGE_GENERATOR_H__
#define __ORANGE_GENERATOR_H__

#include <map>
#include "runner.h"

/**
 * GeneratingEngine is a class that handles all information about runs and builds.
 * It keeps track of the current file being compiled. 
 */
class GeneratingEngine {
private:
	std::map<std::string, Runner *> m_runners; 
	Runner* m_active;

	// We want to prevent the user from creating their own instance;
	// use sharedEngine instead.
	GeneratingEngine();
public:
	/**
	 * Adds a runner to the GeneratingEngine instance.
	 * 
	 * @param runner The runner to add.
	 *
	 * @return True if the runner was added; false if it already exists under that name.
	 */
	bool addRunner(Runner* runner);
	
	/**
	 * Returns the active runner.
	 *
	 * @return The active runner.
	 */
	Runner* active() const; 

	/**
	 * Sets the active runner.
	 *
	 * @param runner The runner to make active.
	 */
	void setActive(Runner* runner);

	/**
	 * Returns a singleton instance of GeneratingEngine.
	 *
	 * @return A shared instance of GeneratingEngine.
	 */
	static GeneratingEngine *sharedEngine();

	/**
	 * Returns the active runner for the shared engine.
	 *
	 * @return The active runner of the shared instance.
	 */
	static Runner* runner();
};

typedef GeneratingEngine GE;

#endif
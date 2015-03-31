/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <helper/args.h>
#include <helper/link.h>
#include <orange/file.h>
#include <orange/run.h>
#include <orange/test.h>

int main(int argc, char** argv) {
	cOptions options("Orange WIP"); 

	/*
	 * Set up our "run" state to run files.
	 */
	cOptionsState run("run", "Runs a single file or a project.", "run [filename]", "The run command will\
 either run a file or a project directly. Entering run without a filename will run a project, if it exists.\
  If you are not in a project, an error will be displayed. Running a file does not require you to be in an Orange project.");
	options.mainState.addState(&run); 

	/*
	 * Set up our "test" state to test files.
	 */
	cOptionsState test("test", "Tests files and projects in the test/ directory.", "test [folder|filename|project]", "The test command\
 is used to test every file and project inside of the test/ folder. It will run recursively, through each subdirectory. If a subdirectory\
 contains a orange.settings.json file, it is treated as a sub project. Otherwise, every file inside of the directory will be ran as its own\
  individual program.");
  options.mainState.addState(&test);

	// Parse our options
	options.parse(argc, argv);

	if (run.isActive()) {
		doRunCommand(run);
	} else if (test.isActive()) {
		doTestCommand(test);
	}

	return 0;
}


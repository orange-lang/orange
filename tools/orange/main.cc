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
#include <orange/test.h>
#include <orange/orange.h>

#include <orange/commands/CodeExecutor.h>
#include <orange/commands/RunCommand.h>
#include <orange/commands/BuildCommand.h>

int main(int argc, char** argv) {
	CodeExecutor *executor = new CodeExecutor();

	cOptions options("Orange WIP"); 

  cCommandOption debug({"debug", "D"}, "Print debugging info", false);

	RunCommand* runCommand = new RunCommand();
 	runCommand->add(&debug);
	options.mainState.addState(runCommand); 

	BuildCommand* buildCommand = new BuildCommand();
	buildCommand->add(&debug);
	options.mainState.addState(buildCommand);

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

	if (runCommand->isActive()) {
		runCommand->run();
	} else if (buildCommand->isActive()) {
		buildCommand->run();
	} else if (test.isActive()) {
		doTestCommand(test);
	} 

	return 0;
}


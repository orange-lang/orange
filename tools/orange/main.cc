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
#include <orange/orange.h>

#include <orange/commands/CodeExecutor.h>
#include <orange/commands/RunCommand.h>
#include <orange/commands/BuildCommand.h>
#include <orange/commands/TestCommand.h>

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

	TestCommand* testCommand = new TestCommand();
  options.mainState.addState(testCommand);

	// Parse our options
	options.parse(argc, argv);

	if (runCommand->isActive()) {
		runCommand->run();
	} else if (buildCommand->isActive()) {
		buildCommand->run();
	} else if (testCommand->isActive()) {
		testCommand->run();
	} 

	return 0;
}


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
#include <helper/args.h>
#include <helper/link.h>
#include <orange/file.h>
#include <orange/orange.h>

#include <orange/commands/CodeExecutor.h>
#include <orange/commands/RunCommand.h>
#include <orange/commands/BuildCommand.h>
#include <orange/commands/TestCommand.h>

int main(int argc, char** argv) {
	cOptions options("Orange WIP"); 

  cCommandOption* debug = new cCommandOption({"debug", "D"}, "Print debugging info", false);
  cCommandOption* output = new cCommandOption({"o", "output"}, "Specify output name", true);

	RunCommand* runCommand = new RunCommand();
 	runCommand->add(debug);
	options.mainState.addState(runCommand);

	BuildCommand* buildCommand = new BuildCommand();
	buildCommand->add(debug);
	buildCommand->add(output);
	options.mainState.addState(buildCommand);

	TestCommand* testCommand = new TestCommand();
  options.mainState.addState(testCommand);

	// Parse our options
	options.parse(argc, argv);

	options.currentState()->run();

	delete testCommand;
	delete buildCommand;
	delete runCommand;
	delete debug;
	delete output;

	return 0;
}

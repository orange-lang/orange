/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <iostream>
#include <util/link.h>
#include <cmd/ProgramOptions.h>
#include <cmd/OptionsState.h>
#include <orange/RunCommand.h>
#include <orange/BuildCommand.h>
#include <orange/TestCommand.h>


int main(int argc, char** argv) {
	auto options = new ProgramOptions("Orange WIP");

	auto runState = new RunCommand();
	auto buildState = new BuildCommand();
	auto testState = new TestCommand();

	options->addState(runState);
	options->addState(buildState);
	options->addState(testState);

	options->getMainState()->setRunDelegate(runState);

	int retCode = 0;
	
	try
	{
    	// Run our program.
    	retCode = options->parse(argc, argv);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		retCode = 1;
	}
	
	delete runState;
	delete buildState;
	delete testState;
	delete options;
}

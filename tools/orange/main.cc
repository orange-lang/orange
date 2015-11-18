/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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

int main(int argc, char** argv) {
	auto options = new ProgramOptions("Orange WIP");

	auto runState = new RunCommand();
	auto buildState = new OptionsState("build");
	auto testState = new OptionsState("test");

	options->addState(runState);
	options->addState(buildState);
	options->addState(testState);

	options->getMainState()->setRunDelegate(runState);

	// Parse our options
	options->parse(argc, argv);

	return 0;
}

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <iostream>
#include <orange/RunCommand.h>
#include <grove/Builder.h>

int RunCommand::run(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		std::cerr << "run cannot run a project at this time.\n";
		std::cerr << "Pass in a file to run as an argument.\n";
		return 1;
	}

	// Run a thing.
	std::string program_to_run = args[0];

	try {
		auto builder = new Builder(program_to_run);
		builder->compile();

		int result = builder->run();

		if (result != 0)
		{
			return result;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}

RunCommand::RunCommand()
: OptionsState("run")
{
	// Do nothing.
}

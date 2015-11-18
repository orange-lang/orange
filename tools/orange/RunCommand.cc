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

void RunCommand::run(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		throw std::runtime_error("run takes an argument");
	}

	// Run a thing.
	std::string program_to_run = args[0];

	try {
		auto builder = new Builder(program_to_run);
		builder->compile();

		int result = builder->run();

		if (result != 0)
		{
			exit(result);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		exit(1);
	}
}

RunCommand::RunCommand()
: OptionsState("run")
{
	// Do nothing.
}

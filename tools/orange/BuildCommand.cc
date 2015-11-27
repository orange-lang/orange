/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <iostream>
#include <orange/BuildCommand.h>
#include <grove/Builder.h>

int BuildCommand::run(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		throw std::runtime_error("build takes an argument");
	}
	
	// Run a thing.
	std::string program_to_run = args[0];
	
	try {
		auto builder = new Builder(program_to_run);
		builder->compile();
		
		builder->link("");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}

BuildCommand::BuildCommand()
: OptionsState("build")
{
	// Do nothing.
}

/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <iostream>
#include <memory>
#include <orange/BuildCommand.h>
#include <grove/Builder.h>
#include <cmd/StateFlag.h>

int BuildCommand::run(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		std::cerr << "build cannot build a project at this time.\n";
		std::cerr << "Pass in a file to build as an argument.\n";
		return 1;
	}
	
	// Run a thing.
	std::string program_to_run = args[0];
	
	try {
		auto builder = new Builder(program_to_run);
		builder->compile();
		
		if (m_output->getUsed())
		{
			builder->link(m_output->getValue());
		}
		else
		{
    		builder->link("");
		}
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
	m_output = std::shared_ptr<StateFlag>(new StateFlag("o", "output", true));
	
	addFlag(m_output.get());
}

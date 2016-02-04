/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdio.h>
#include <fcntl.h>
#include <liborange/TestCommand.h>
#include <liborange/Builder.h>
#include <libast/Module.h>

#include <util/file.h>

#include <llvm/Support/TimeValue.h>

#include <unistd.h>

#ifdef _WIN32
const char* NULLFILE = "NUL";
#else
const char* NULLFILE = "/dev/null";
#endif

void TestCommand::disableOutput()
{
	fflush(stdout);
	output_backup = dup(STDOUT_FILENO);
	
	auto new_fd = open(NULLFILE, O_WRONLY);
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
}

void TestCommand::enableOutput()
{
	fflush(stdout);
	dup2(output_backup, STDOUT_FILENO);
	close(output_backup);
}

int TestCommand::run(std::vector<std::string> args)
{
	auto builder = new Builder();
	
	std::vector<std::string> test_files;
	auto proj_dir = findProjectDirectory("orange.settings.json");
	
	if (args.size() == 0)
	{
		auto test_path = combinePaths(proj_dir, "test/");
    	test_files = getFilesRecursive(test_path, ".or");
	}
	else
	{
		for (unsigned int i = 0; i < args.size(); i++)
		{
			auto test_path = combinePaths(proj_dir, "test/" + args.at(i));
			auto files = getFilesRecursive(test_path, ".or");
			test_files.insert(test_files.end(), files.begin(), files.end());
		}
	}
	
	// Number of results (. or F) printed to the screen.
	int nres_printed = 0;
	
	uint32_t tot_time = 0;
	uint32_t npassed = 0;
	uint32_t nfailed = 0;
	
	std::tuple<std::string, uint32_t> longest_test =
		std::make_tuple<std::string, uint32_t>("", 0);
	
	std::vector<std::tuple<std::string, std::string>> errors;
	
	for (auto test : test_files)
	{
		builder->clearModules();
		
		// Have path be relative from project directory
		auto short_path = test.substr(proj_dir.length() + 1);
		
		int statusCode = 0;
		
		disableOutput();
		
		auto start_time = llvm::sys::TimeValue::now();
		
		try
		{
			builder->addModule(new Module(builder, test));
			builder->compile();
			
			statusCode = builder->run();
			
			if (statusCode != 0)
			{
    			errors.push_back(std::make_tuple(short_path, "returned "
				 "nonzero"));
			}
		}
		catch (std::exception& e)
		{
			statusCode = 1;
			
			errors.push_back(std::make_tuple(short_path, e.what()));
		}
		
		auto finish_time = llvm::sys::TimeValue::now();
		auto diff = finish_time - start_time;
		
		tot_time += diff.milliseconds();
		
		if (std::get<0>(longest_test) == "" ||
			diff.milliseconds() > std::get<1>(longest_test))
		{
			longest_test = std::make_tuple(short_path, diff.milliseconds());
		}
		
		enableOutput();
		
		if (statusCode == 0)
		{
			std::cout << ".";
			npassed++;
		}
		else
		{
			std::cout << "F";
			nfailed++;
		}
		
		if ((++nres_printed % 40) == 0)
		{
			std::cout << "\n";
		}
			
		
		std::flush(std::cout);
	}
	
	std::cout << "\n\n";
	
	int percPassed = ((float)npassed/(float)(npassed+nfailed)) * 100;
	float avgSecs = tot_time/(float)(npassed+nfailed)/1000.0f;
	
	std::cout << "Test results (" << tot_time/1000.0f << " seconds)\n";
	std::cout << "\t" << npassed << "/" << (npassed+nfailed)
	          << " tests passed (" << percPassed << "%).\n";
	std::cout << "\t" << avgSecs << " seconds to run on average.\n";
	std::cout << "\tLongest test was: " << std::get<0>(longest_test)
	          << " (" << std::get<1>(longest_test)/1000.0f << " seconds)\n\n";
	
	if (errors.size() > 0)
	{
		std::cout << "Errors:\n";
		
		for (auto error : errors)
		{
			std::cout << "\t" << std::get<0>(error) << ":\n\t\t"
			          << std::get<1>(error) << std::endl;
		}
		
    	std::cout << "\n";
	}
	
	
	return 0;
}

TestCommand::TestCommand()
: OptionsState("test")
{
	
}
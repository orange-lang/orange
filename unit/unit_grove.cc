/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <test/TestLib.h>
#include <test/Comparisons.h>

#include <grove/Builder.h>

#include <util/file.h>

#include <cstdio>
#include <fstream>


START_TEST_MODULE();

ADD_TEST(TestBuildProgram, "Test building a simple program.");
int TestBuildProgram()
{
	auto temp_path = getTempFile("test", "or");
	std::ofstream file(temp_path);
	
	if (file.is_open() == false)
	{
		std::cerr << "Couldn't open " << temp_path << std::endl;
		std::remove(temp_path.c_str());
		return 1;
	}
	
	// Write small orange program to file.
	file << "return 0;" << std::endl;
	file.close();
	
	// create our builder.
	auto builder = new Builder(temp_path);
	int result = builder->build();
	
	std::remove(temp_path.c_str());
	return cmpEq(result, 0);
}

ADD_TEST(TestRet1, "Test program that returns 1.");
int TestRet1()
{
	auto temp_path = getTempFile("test", "or");
	std::ofstream file(temp_path);
	
	if (file.is_open() == false)
	{
		std::cerr << "Couldn't open " << temp_path << std::endl;
		std::remove(temp_path.c_str());
		return 1;
	}
	
	// Write small orange program to file.
	file << "return 1;" << std::endl;
	file.close();
	
	// create our builder.
	auto builder = new Builder(temp_path);
	int result = builder->build();
	
	std::remove(temp_path.c_str());
	return cmpEq(result, 1);
}

ADD_TEST(TestRet2, "Test program that returns 2.");
int TestRet2()
{
	auto temp_path = getTempFile("test", "or");
	std::ofstream file(temp_path);
	
	if (file.is_open() == false)
	{
		std::cerr << "Couldn't open " << temp_path << std::endl;
		std::remove(temp_path.c_str());
		return 1;
	}
	
	// Write small orange program to file.
	file << "return 2;" << std::endl;
	file.close();
	
	// create our builder.
	auto builder = new Builder(temp_path);
	int result = builder->build();
	
	std::remove(temp_path.c_str());
	return cmpEq(result, 2);
}

ADD_TEST(TestAllPrograms, "Test building all basic programs in test dir.")
int TestAllPrograms()
{
	int exitCode = 0;
	
	auto test_path = combinePaths(getWorkingDirectory(), "test/basic");
	auto test_files = getFilesRecursive(test_path);
	
	for (auto path : test_files)
	{
		try
		{
			auto builder = new Builder(path);
		
    		if (builder->build() != 0)
    		{
    			std::cout << "Retcode 1: " << path << std::endl;
    			exitCode = 1;
    		}		
		}
		catch (std::exception& e)
		{
			std::cout << "Failed: " << path << std::endl;
			std::cout << "\tReason: " << e.what() << std::endl;
			exitCode = 1;
		}
	}
	
	return exitCode;
}


RUN_TESTS();
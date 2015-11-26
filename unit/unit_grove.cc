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

#include <grove/exceptions/file_error.h>

#include <util/file.h>

#include <sstream>
#include <cstdio>
#include <fstream>


START_TEST_MODULE();

ADD_TEST(TestNoProgram, "Test building a nonexistant program.");
int TestNoProgram()
{
	try {
		auto builder = new Builder("/fake_path_O123ZCVAQ.tmp");
		builder->compile();
		builder->run();
	}
	catch (file_error& e)
	{
		return pass();
	}
	catch (std::exception& e)
	{
		return fail();
	}
	
	return fail();
}

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
	builder->compile();
	
	int result = builder->run();
	
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
	builder->compile();
	
	int result = builder->run();
	
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
	builder->compile();
	
	int result = builder->run();
	
	std::remove(temp_path.c_str());
	return cmpEq(result, 2);
}

ADD_TEST(TestMatchingFunctions, "Test program that has two matching functions");
int TestMatchingFunctions()
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
	file << R"EOF(
		def foo(int a)
			return 1
		end

		def foo(int a)
			return 1
		end

		return 0
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return 0;
	}
	
	ADD_ERROR(TestMatchingFunctions, "No exception caught");
	std::remove(temp_path.c_str());
	return 1;
}

ADD_TEST(TestMatchingGenerics, "Test program that has two matching generics");
int TestMatchingGenerics()
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
	
	file << R"EOF(
    	def foo(var f, int a)
    		return 1
    	end
    	def foo(var f, int a)
    		return 1
    	end
    	return 0
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return 0;
	}
	
	ADD_ERROR(TestMatchingGenerics, "No exception caught");
	std::remove(temp_path.c_str());
	return 1;
}

#define ADD_TEST_FOLDER(name, folder)\
ADD_TEST(name, "Test building " #folder " programs in test/" #folder ".")\
int name(){\
	int exitCode = 0;\
	auto test_path = combinePaths(getWorkingDirectory(), "test/" #folder);\
	auto test_files = getFilesRecursive(test_path);\
	for (auto path : test_files){\
		try{\
			auto builder = new Builder(path); builder->compile();\
			int val = builder->run();\
			if (val != 0) {exitCode = 1; \
				std::stringstream ss; ss << path << " returned " << val;\
				ADD_ERROR(name, ss.str()); }\
		}\
		catch(std::exception& e){\
			std::stringstream ss; ss << path << ": " << e.what();\
			ADD_ERROR(name, ss.str()); exitCode = 1;}}\
	return exitCode;}

ADD_TEST_FOLDER(TestEmptyPrograms, empty);
ADD_TEST_FOLDER(TestReturnPrograms, return);
ADD_TEST_FOLDER(TestMathPrograms, math);
ADD_TEST_FOLDER(TestFunctionPrograms, functions);
ADD_TEST_FOLDER(TestVariablePrograms, variables);
ADD_TEST_FOLDER(TestGenericFunctions, generic_functions);
ADD_TEST_FOLDER(TestIfPrograms, if);
ADD_TEST_FOLDER(TestRecursionPrograms, recursion);
ADD_TEST_FOLDER(TestLoopPrograms, loops);
ADD_TEST_FOLDER(TestPointerPrograms, pointers);
ADD_TEST_FOLDER(TestArrayPrograms, array);
ADD_TEST_FOLDER(TestTernaryPrograms, ternary);
ADD_TEST_FOLDER(TestEnumPrograms, enum);
ADD_TEST_FOLDER(TestBuiltinPrograms, builtin);
ADD_TEST_FOLDER(TestProgramPrograms, programs);
ADD_TEST_FOLDER(TestBugPrograms, bugs);

RUN_TESTS();
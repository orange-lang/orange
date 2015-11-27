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
#include <grove/exceptions/already_defined_error.h>
#include <grove/exceptions/already_defined_sig_error.h>

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
	catch (already_defined_sig_error& e)
	{
		std::remove(temp_path.c_str());
		return 0;
	}
	
	ADD_ERROR(TestMatchingGenerics, "No exception caught");
	std::remove(temp_path.c_str());
	return 1;
}

ADD_TEST(TestSameVariable, "Test program that has two variables with the same name");
int TestSameVariable()
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
	var a = 5
	var b = 6
	var c = 7
	var a = 8
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (already_defined_error& e)
	{
		std::remove(temp_path.c_str());
		return pass();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return fail();
	}
	
	ADD_ERROR(TestMatchingGenerics, "No exception caught");
	std::remove(temp_path.c_str());
	return fail();
}

ADD_TEST(TestSameNameStructs, "Test program that has two different structures with the same name");
int TestSameNameStructs()
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
	def foo()
		return 5
	end
	
	enum foo
		TESTING = 0
	end
	
	var a = 5
	var b = 6
	var c = foo.TESTING
	var d = foo()
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (already_defined_error& e)
	{
		std::remove(temp_path.c_str());
		return pass();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return fail();
	}
	
	
	ADD_ERROR(TestSameNameStructs, "No exception caught");
	std::remove(temp_path.c_str());
	return fail();
}

ADD_TEST(TestSameNameStructsUnused, "Test program that has two unused different structures with the same name (function, enum)");
int TestSameNameStructsUnused()
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
	def foo()
	return 5
	end
	
	enum foo
	TESTING = 0
	end
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (already_defined_error& e)
	{
		std::remove(temp_path.c_str());
		return pass();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return fail();
	}
	
	
	ADD_ERROR(TestSameNameStructsUnused, "No exception caught");
	std::remove(temp_path.c_str());
	return fail();
}

ADD_TEST(TestSameNameStructsUnusedReverse, "Test program that has two unused different structures with the same name (enum, function)");
int TestSameNameStructsUnusedReverse()
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
	enum foo
	TESTING = 0
	end
	
	def foo()
	return 5
	end
	)EOF";
	
	file.close();
	
	// create our builder.
	try
	{
		auto builder = new Builder(temp_path);
		builder->compile();
	}
	catch (already_defined_error& e)
	{
		std::remove(temp_path.c_str());
		return pass();
	}
	catch (std::exception& e)
	{
		std::remove(temp_path.c_str());
		return fail();
	}
	
	
	ADD_ERROR(TestSameNameStructsUnusedReverse, "No exception caught");
	std::remove(temp_path.c_str());
	return fail();
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
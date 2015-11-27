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
#include <grove/exceptions/undefined_error.h>
#include <grove/exceptions/binop_error.h>

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

#define TEST_EXCEPTION(TestName, catchException, body)\
ADD_TEST(TestName, "Test catching " #catchException " for " #TestName ".")\
int TestName(){\
auto temp_path = getTempFile("test", "or"); std::ofstream file(temp_path);\
if (file.is_open() == false) { std::remove(temp_path.c_str()); return fail(); }\
file << body; file.close();\
try { auto builder = new Builder(temp_path); builder->compile(); }\
catch (catchException& e) { std::remove(temp_path.c_str()); return pass(); }\
catch (std::exception& e) { std::remove(temp_path.c_str()); return fail(); }\
ADD_ERROR(TestName, "No exception caught");\
std::remove(temp_path.c_str()); return fail(); }

TEST_EXCEPTION(TestMatchingGenerics, already_defined_sig_error, R"EOF(
	def foo(var f, int a)
		return 1
	end
	def foo(var f, int a)
		return 1
	end
	return 0
)EOF");

TEST_EXCEPTION(TestSameVariable, already_defined_error, R"EOF(
   var a = 5
   var b = 6
   var c = 7
   var a = 8
)EOF");

TEST_EXCEPTION(TestSameNameStructs, already_defined_error, R"EOF(
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
)EOF");

TEST_EXCEPTION(TestMatchingFunctions, already_defined_sig_error, R"EOF(
	def foo(int a)
		return 1
	end
	def foo(int a)
		return 1
	end
	return 0
)EOF");


TEST_EXCEPTION(UndefinedVariable, undefined_error, R"EOF(
	var foo = a + 5
)EOF");

TEST_EXCEPTION(UndefinedFunction, undefined_error, R"EOF(
   foobar();
)EOF");

TEST_EXCEPTION(TestSameNameStructsUnused, already_defined_error, R"EOF(
	def foo()
		return 5
	end
	enum foo
		TESTING = 0
	end
)EOF");

TEST_EXCEPTION(TestSameNameStructsUnusedReverse, already_defined_error, R"EOF(
	enum foo
		TESTING = 0
	end
	def foo()
		return 5
	end
)EOF");

TEST_EXCEPTION(TestDuplicateEnumMembers, already_defined_error, R"EOF(
	enum Testing
		FOO = 0
		BAR
		FOO
    end
)EOF");

TEST_EXCEPTION(TestInvalidBinOpOperands, binop_error, R"EOF(
	var a = 5
	var ptr = &a
	var foo = ptr + 2.3
)EOF");

ADD_TEST(TestJITPrograms, "Test running programs in test JIT");
int TestJITPrograms()
{
	int exitCode = 0;
	auto test_path = combinePaths(getWorkingDirectory(), "test/");
	auto test_files = getFilesRecursive(test_path);
	
	for (auto path : test_files)
	{
		try
		{
			auto builder = new Builder(path);
			builder->compile();
			
			int val = builder->run();
			if (val != 0)
			{
				exitCode = 1;
				std::stringstream ss;
				ss << path << " returned " << val;
				ADD_ERROR(TestJITPrograms, ss.str());
			}
		}
		catch(std::exception& e)
		{
			std::stringstream ss;
			ss << path << ": " << e.what();
			ADD_ERROR(TestJITPrograms, ss.str());
			exitCode = 1;
		}
	}
	
	return exitCode;
}


RUN_TESTS();
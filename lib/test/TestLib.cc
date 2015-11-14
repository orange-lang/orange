/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <iostream>

#include <test/TestLib.h>
#include <test/Test.h>

TestingEngine* TestingEngine::shared()
{
		return singleton;
}

void TestingEngine::addTest(Test* t)
{
	tests.push_back(t);
}

int TestingEngine::run()
{
	std::vector<Test*> failed;

	int retCode = 0;

	for (auto test : tests)
	{
		int val = 0;
		try
		{
    		val = test->func();
		}
		catch (std::exception& e)
		{
			test->errors.push_back(e.what());
			val = 1;
		}
		
		if (val != 0)
		{
			failed.push_back(test);
			retCode = 1;
		}
	}

	if (failed.size() == 0)
	{
		return retCode;
	}

	std::cout << "Failed:\n";
	for (auto fail : failed)
	{
		std::cout << "\t" << fail->desc << std::endl;
		for (auto error : fail->errors)
		{
			std::cout << "\t\t" << error << std::endl;
		}
	}

	return retCode;
}

TestingEngine::TestingEngine()
{
	// Do nothing.
}

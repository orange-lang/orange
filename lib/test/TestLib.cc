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
	std::vector<std::string> failed;

	int retCode = 0;

	for (auto test : tests)
	{
		if (test->func() != 0)
		{
			failed.push_back(test->desc);
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
		std::cout << "\t" << fail << std::endl;
	}

	return retCode;
}

TestingEngine::TestingEngine()
{
	// Do nothing.
}

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>

#include "Test.h"

class TestingEngine
{
private:
	static TestingEngine* singleton;

	std::vector<Test *> tests;
public:
	static TestingEngine* shared();

	void addTest(Test* t);

	int run();

	TestingEngine();
};

#define START_TEST_MODULE() TestingEngine* TestingEngine::singleton = new TestingEngine();

#define ADD_TEST(n,d) int n(void); static Test TestLib__test__##n(n,d);
#define RUN_TESTS() \
	int main() { return TestingEngine::shared()->run(); }

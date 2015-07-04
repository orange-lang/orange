/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __TEST_COMMAND_H__
#define __TEST_COMMAND_H__

#include <vector>
#include "CodeExecutor.h"
#include "../run.h"
#include "../file.h"

class TestCommand : public CodeExecutor {
private:
	const int MAX_CHARACTERS_PER_LINE = 40;

	std::vector<RunResult *> m_results;
	int m_added_characters = 0;

	std::string base_path = "";
	std::string makeRelative(std::string p);

	void runOnPath(std::string p);
public:
	float totalTestTime();
	float avgTestTime();
	int numPassedTests();
	int numFailedTests();
	std::string longestTest();

	void displayResults();  

	virtual void run();
	TestCommand();
	~TestCommand();
};

#endif 
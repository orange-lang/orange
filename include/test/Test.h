/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>

typedef int (*TestFunction)(void);

struct Test {
	TestFunction func;
	std::string desc;
	
	std::vector<std::string> errors;

	Test(TestFunction func, std::string desc);
};

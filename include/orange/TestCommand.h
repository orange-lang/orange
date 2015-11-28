/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <cmd/OptionsState.h>

/**
 * TestCommand runs all tests in the test/ directory of an orange project.
 */
class TestCommand : public OptionsState
{
protected:
	int output_backup;
	
	void disableOutput();
	void enableOutput();
public:
	virtual int run(std::vector<std::string> args) override;
	
	TestCommand();
};
/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <cmd/OptionsState.h>

/**
 * RunCommand supports running a file.
 */
class RunCommand : public OptionsState
{
private:
	std::shared_ptr<StateFlag> m_debug;
public:
	virtual int run(std::vector<std::string> args) override;

	RunCommand();
};

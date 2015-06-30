/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __RUN_COMMAND_H__
#define __RUN_COMMAND_H__

#include "CodeExecutor.h"

class RunCommand : public CodeExecutor {
public:
	virtual void run();
	RunCommand();
};

#endif 
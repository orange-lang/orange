/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "code_error.h"

class undefined_error : public code_error
{
protected:
	std::string m_name = "";
public:
	undefined_error(CodeBase* element, std::string name);
};
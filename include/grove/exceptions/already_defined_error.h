/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "code_error.h"

/**
 * already_defined_error is an error to represent a structure that has already
 * been defined.
 */
class already_defined_error : public code_error
{
protected:
	CodeBase* m_original = nullptr;
	std::string m_name = "";
public:
	already_defined_error(CodeBase* element, CodeBase* original,
						  std::string name, bool isVariable = true);
};
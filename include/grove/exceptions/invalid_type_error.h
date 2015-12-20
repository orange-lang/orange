/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "code_error.h"

class Type;

/**
 * invalid_type_error is used when a given type is invalid.
 * the message will be equivalent to desc + ty->getString().
 */
class invalid_type_error : public code_error
{
public:
	invalid_type_error(CodeBase* element, std::string desc, const Type* ty);
};
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
 * access_denied_error represents an error where an access to an 
 * element was rejected.
 */
class access_denied_error : public code_error
{
protected:
	CodeBase* m_original = nullptr;
	std::string m_description;
	std::string m_name = "";
public:
	access_denied_error(const CodeBase* element, const CodeBase* original,
						std::string description);
};

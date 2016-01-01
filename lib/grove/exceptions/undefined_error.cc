/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/undefined_error.h>

undefined_error::undefined_error(CodeBase* element, std::string name)
: code_error(element)
{
	m_name = name;
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: "
	   << "undefined reference to " << m_name << "\n"
	   << getContext(element);
	
	m_error = ss.str();
}
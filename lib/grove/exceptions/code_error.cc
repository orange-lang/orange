/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/code_error.h>
#include <grove/exceptions/fatal_error.h>

#include <grove/CodeBase.h>

std::string code_error::fileWithPosition(CodeBase *element)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	std::stringstream ss;
	ss << element->getLocation().file << ":"
       << element->getLocation().first_line << ":";
	
	return ss.str();
}

const char* code_error::what() const noexcept
{
	return m_error.c_str();
}

code_error::code_error(CodeBase* element)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	std::stringstream ss;
	
	ss << "A generic error has been generated at "
	   << fileWithPosition(element) << ".\n\n";
	
	ss << "Please report this error to the maintainers, "
	   << "as while your code does have a legitimate issue, "
	   << "there should have been a more specific error created.";
	
	m_error = ss.str();
}
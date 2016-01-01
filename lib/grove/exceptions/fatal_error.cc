/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/fatal_error.h>
#include <sstream>

const char* fatal_error::what() const noexcept
{
	return m_error.c_str();
}

fatal_error::fatal_error(std::string msg)
{
	std::stringstream ss;
	ss << "FATAL ERROR: " << msg << "\n\n";
	ss << "This is probably a compiler bug! Please report this issue with ";
	ss << "the error you're experiencing, how you invoked orange ";
	ss << "and the code that caused this issue.";
	
	m_error = ss.str();
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/already_defined_error.h>
#include <grove/exceptions/fatal_error.h>

already_defined_error::already_defined_error(CodeBase* element,
											 CodeBase* original,
											 std::string name)
: code_error(element)
{
	if (original == nullptr)
	{
		throw fatal_error("original was nullptr");
	}
	
	m_original = original;
	m_name = name;
	
	std::stringstream ss;
	ss << fileWithPosition(element) << ": error: "
	   << "variable " << m_name << " cannot be redefined\n"
	   << getContext(element) << "\n\n";
	ss << fileWithPosition(original) << ": previous definition "
	   << "is here\n" << getContext(original);
	
	m_error = ss.str();
}
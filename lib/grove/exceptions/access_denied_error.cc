/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/access_denied_error.h>

access_denied_error::access_denied_error(const CodeBase* element,
										 const CodeBase* original,
										 std::string description)
: code_error(element)
{
	std::stringstream ss;
	
	ss << fileWithPosition(original) << ": error: " << description
	   << " is inaccessible from here\n" << getContext(original) << "\n\n";
	
	ss << fileWithPosition(element) << ": original definition "
 	   << "is here\n" << getContext(element);
	
	m_error = ss.str();
}
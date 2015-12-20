/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/invalid_type_error.h>
#include <grove/exceptions/fatal_error.h>

#include <grove/types/Type.h>

invalid_type_error::invalid_type_error(CodeBase* element, std::string desc,
									   const Type* ty)
: code_error(element)
{
	if (ty == nullptr)
	{
		throw fatal_error("ty is nullptr");
	}
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: "
	   << desc << " " << ty->getString() << "\n"
	   << getContext(element);
	
	m_error = ss.str();
}
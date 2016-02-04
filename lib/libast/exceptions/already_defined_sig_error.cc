/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/exceptions/already_defined_sig_error.h>
#include <libast/exceptions/fatal_error.h>

already_defined_sig_error::already_defined_sig_error(CodeBase* element,
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
	<< m_name << " already defined with this signature\n"
	<< getContext(element) << "\n\n";

	ss << fileWithPosition(original) << ": previous definition "
	<< "is here\n" << getContext(original);
	
	m_error = ss.str();
}
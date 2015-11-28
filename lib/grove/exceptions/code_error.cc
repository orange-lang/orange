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

#include <fstream>

std::string code_error::getContext(CodeBase *element)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	std::ifstream file(element->getLocation().file);
	if (file.is_open() == false)
	{
		throw fatal_error("couldn't open file for context");
	}
	
	for (int i = 0; i < element->getLocation().first_line - 1; i++)
	{
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	std::string line;
	std::getline(file, line);
	
	file.close();
	
	return line;
}

std::string code_error::fileWithPosition(CodeBase *element)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	std::stringstream ss;
	ss << element->getLocation().file << ":"
       << element->getLocation().first_line << ":"
	   << element->getLocation().first_column;
	
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

code_error::code_error(CodeBase* element, std::function<std::string()> cb)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: " << cb() << "\n"
	   << getContext(element);
	
	m_error = ss.str();
}

code_error::code_error(CodeBase* element, CodeBase* ref,
					   std::function<std::string()> cb)
{
	if (element == nullptr)
	{
		throw fatal_error("element cannot be nullptr");
	}
	
	if (ref == nullptr)
	{
		throw fatal_error("ref was nullptr");
	}
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: " << cb() << "\n"
	   << getContext(element) << "\n\n"
	   << fileWithPosition(ref) << ": initially defined here\n"
	   << getContext(ref);
	m_error = ss.str();
}


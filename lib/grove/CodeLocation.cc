/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CodeLocation.h>

CodeLocation::CodeLocation(std::string file, int first_line, int last_line,
						   int first_column, int last_column)
: file(file), first_line(first_line), last_line(last_line),
  first_column(first_column), last_column(last_column)
{
	// Do nothing
}

CodeLocation::CodeLocation(const CodeLocation& other)
{
	file = other.file;
	first_line = other.first_line;
	last_line = other.last_line;
	first_column = other.first_column;
	last_column = other.last_column;
}

CodeLocation::CodeLocation(CodeLocation&& other) noexcept
{
	file = other.file;
	first_line = other.first_line;
	last_line = other.last_line;
	first_column = other.first_column;
	last_column = other.last_column;
	
	other.file = "";
	other.first_column = 0;
	other.last_column = 0;
	other.first_line = 0;
	other.last_line = 0;
}

CodeLocation& CodeLocation::operator=(const CodeLocation& other)
{
	CodeLocation tmp(other);
	*this = std::move(tmp);
	return *this;
}

CodeLocation& CodeLocation::operator=(CodeLocation&& other) noexcept
{
	file = other.file;
	first_line = other.first_line;
	last_line = other.last_line;
	first_column = other.first_column;
	last_column = other.last_column;
	
	other.file = "";
	other.first_column = 0;
	other.last_column = 0;
	other.first_line = 0;
	other.last_line = 0;
	return *this;
}
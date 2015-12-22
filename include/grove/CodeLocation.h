/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

struct CodeLocation
{
	std::string file = "";
	
	int first_line = 0;
	int last_line = 0;
	int first_column = 0;
	int last_column = 0;
	
	CodeLocation(std::string file, int first_line, int last_line,
				 int first_column, int last_column);
	
	CodeLocation(const CodeLocation& other);
	CodeLocation(CodeLocation&& other) noexcept;
	
	CodeLocation& operator=(const CodeLocation& other);
	CodeLocation& operator=(CodeLocation&& other) noexcept;
};
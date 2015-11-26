/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
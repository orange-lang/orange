/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <util/assertions.h>

void assertExists(const void* ptr, std::string str)
{
	if (ptr == nullptr)
	{
		throw std::runtime_error(str);
	}
}

void assertEqual(const void* ptr_a, const void* ptr_b, std::string str)
{
	if (ptr_a != ptr_b)
	{
		throw std::runtime_error(str);
	}
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#pragma once

template <typename T>
int cmpEq(T a, T b)
{
	return a != b;
}

template <typename T, typename E>
int cmpEq(T a, E b)
{
	return a != b;
}

#define ASSERT_EQ(a, b) if (cmpEq(a,b) == 1) return 1;

int pass()
{
	return 0;
}

int fail()
{
	return 1;
}

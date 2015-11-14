/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/types/BoolType.h>

const int BOOL_WIDTH = 32;

BoolType::BoolType()
: IntType(BOOL_WIDTH)
{
	// Do nothing.
}

std::string BoolType::getSignature() const
{
	return "b";
}

BoolType* BoolType::get()
{
	auto defined = getDefined("b");
	if (defined != nullptr)
	{
		return dynamic_cast<BoolType*>(defined);
	}
	
	BoolType* ty = new BoolType();
	define("b", ty);
	
	return ty;
}

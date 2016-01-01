/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

/// Defines some comparision between two items,
/// where one item is the source and the other item is the target.
enum Comparison
{
	/// Indicates that the two items are equal.
	EQUAL,
	
	/// Indicates that the source is of lesser precedence than the target.
	LOWER_PRECEDENCE,
	
	/// Indicates that the source is of greater precedence than the target.
	HIGHER_PRECEDENCE,
	
	/// Indicates that the source and target cannot be compared.
	INCOMPATIBLE
};

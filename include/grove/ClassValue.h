/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"
#include "Accessible.h"

/**
 * Represents an instance of a class or a pointer to an instance.
 */
class ClassValue : public Expression, public Accessible
{
	
};
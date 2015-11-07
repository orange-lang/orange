/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Expression.h>

llvm::Value* Expression::getValue() const
{
	return m_value;
}

void Expression::setValue(llvm::Value *value)
{
	m_value = value;
}

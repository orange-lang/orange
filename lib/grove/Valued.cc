/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Valued.h>


llvm::Value* Valued::getPointer() const
{
	return nullptr;
}

bool Valued::hasPointer() const
{
	return false;
}

llvm::Value* Valued::getSize() const
{
	return m_size;
}

llvm::Value* Valued::getValue() const
{
	return m_value;
}

void Valued::setValue(llvm::Value *newValue)
{
	m_value = newValue;
}
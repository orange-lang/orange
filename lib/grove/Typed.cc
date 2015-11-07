/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Typed.h>
#include <grove/types/Type.h>

Type* Typed::getType() const
{
	return m_type;
}

llvm::Type* Typed::getLLVMType() const
{
	if (m_type == nullptr)
	{
		return nullptr;
	}
	
	return getType()->getLLVMType();
}

void Typed::setType(Type* type)
{
	m_type = type;
}
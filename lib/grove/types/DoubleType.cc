/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/DoubleType.h>
#include <llvm/IR/Type.h>

DoubleType::DoubleType()
{
	m_type = llvm::Type::getDoubleTy(*m_context);
}

std::string DoubleType::getSignature() const
{
	return "F";
}

bool DoubleType::isPODTy() const
{
	return true;
}

bool DoubleType::isDoubleTy() const
{
	return true;
}

bool DoubleType::isFloatingPointTy() const
{
	return true;
}

BasicType DoubleType::PODTy() const
{
	return DOUBLE;
}

DoubleType* DoubleType::get()
{
	auto defined = getDefined("F");
	if (defined != nullptr)
	{
		return dynamic_cast<DoubleType*>(defined);
	}
	
	DoubleType* ty = new DoubleType();
	define("F", ty);
	
	return ty;
}
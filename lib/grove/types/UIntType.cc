/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/UIntType.h>
#include <llvm/IR/Type.h>

UIntType::UIntType(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);
}

std::string UIntType::getSignature() const
{
	std::stringstream ss;
	ss << "I." << m_width;
	return ss.str();
}

bool UIntType::isPODTy() const
{
	return true;
}

bool UIntType::isSigned() const
{
	return false;
}

bool UIntType::isIntTy() const
{
	return true;
}

BasicType UIntType::PODTy() const
{
	switch (m_width)
	{
		case 8:
			return UINT8;
		case 16:
			return UINT16;
		case 32:
			return UINT32;
		case 64:
			return UINT64;
		default:
			return OTHER;
	}
}

UIntType* UIntType::get(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	std::stringstream ss;
	ss << "I." << width;
	
	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return dynamic_cast<UIntType*>(defined);
	}
	
	UIntType* ty = new UIntType(width);
	define(ss.str(), ty);
	
	return ty;
}
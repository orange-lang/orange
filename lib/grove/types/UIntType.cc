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
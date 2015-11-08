/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/IntType.h>
#include <llvm/IR/Type.h>

IntType::IntType(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);
}

std::string IntType::getSignature() const
{
	std::stringstream ss;
	ss << "i." << m_width;
	return ss.str();
}

IntType* IntType::get(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	std::stringstream ss;
	ss << "i." << width;
	
	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return dynamic_cast<IntType*>(defined);
	}
	
	IntType* ty = new IntType(width);
	define(ss.str(), ty);
	
	return ty;
}
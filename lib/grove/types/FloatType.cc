/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/FloatType.h>
#include <llvm/IR/Type.h>

FloatType::FloatType()
{
	m_type = llvm::Type::getFloatTy(*m_context);
}

std::string FloatType::getSignature() const
{
	return "f";
}

FloatType* FloatType::get()
{
	auto defined = getDefined("f");
	if (defined != nullptr)
	{
		return dynamic_cast<FloatType*>(defined);
	}
	
	FloatType* ty = new FloatType();
	define("f", ty);
	
	return ty;
}
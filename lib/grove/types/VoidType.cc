/*
 ** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/types/VoidType.h>
#include <llvm/IR/Type.h>

VoidType::VoidType()
: Type(false)
{
	m_type = (llvm::Type *)llvm::Type::getVoidTy(*m_context);
}

std::string VoidType::getString() const
{
	return "void";
}

std::string VoidType::getSignature() const
{
	return "v";
}

bool VoidType::isPODTy() const
{
	return true;
}

bool VoidType::isVoidTy() const
{
	return true;
}

BasicType VoidType::PODTy() const
{
	return TYVOID;
}

VoidType* VoidType::get()
{
	auto defined = getDefined("v");
	if (defined != nullptr)
	{
		return defined->as<VoidType*>();
	}

	VoidType* ty = new VoidType();
	define("v", ty);

	return ty;
}

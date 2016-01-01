/*
 ** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/types/VoidType.h>
#include <llvm/IR/Type.h>

Orange::VoidType::VoidType()
: Type(false)
{
	m_type = (llvm::Type *)llvm::Type::getVoidTy(*m_context);
}

std::string Orange::VoidType::getString() const
{
	return "void";
}

std::string Orange::VoidType::getSignature() const
{
	return "v";
}

bool Orange::VoidType::isPODTy() const
{
	return true;
}

bool Orange::VoidType::isVoidTy() const
{
	return true;
}

BasicType Orange::VoidType::PODTy() const
{
	return TYVOID;
}

Orange::VoidType* Orange::VoidType::get(Module* mod)
{
	auto defined = getDefined(mod, "v");
	if (defined != nullptr)
	{
		return defined->as<VoidType*>();
	}

	VoidType* ty = new VoidType();
	define(mod, "v", ty);

	return ty;
}

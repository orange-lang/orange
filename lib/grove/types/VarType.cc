/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/VarType.h>
#include <llvm/IR/Type.h>

VarType::VarType()
{
	m_type = (llvm::Type *)llvm::Type::getVoidTy(*m_context);
}

std::string VarType::getSignature() const
{
	return "V";
}

bool VarType::isVarTy() const
{
	return true;
}

VarType* VarType::get()
{
	auto defined = getDefined("V");
	if (defined != nullptr)
	{
		return defined->as<VarType*>();
	}
	
	VarType* ty = new VarType();
	define("V", ty);
	
	return ty;
}
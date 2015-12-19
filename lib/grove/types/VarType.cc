/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/VarType.h>
#include <llvm/IR/Type.h>

VarType::VarType(bool isConst)
: Type(isConst)
{
	m_type = (llvm::Type *)llvm::Type::getVoidTy(*m_context);
}

std::string VarType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "var";
	return ss.str();
}

std::string VarType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
	ss << "A";
	
	return ss.str();
}

bool VarType::isVarTy() const
{
	return true;
}

Type* VarType::getConst() const
{
	return VarType::get(getModule(), true);
}

VarType* VarType::get(Module* mod, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "V";
	
	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<VarType*>();
	}
	
	VarType* ty = new VarType(isConst);
	define(mod, ss.str(), ty);
	
	return ty;
}
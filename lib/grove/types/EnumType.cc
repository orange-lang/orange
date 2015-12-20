/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/EnumType.h>
#include <grove/types/UIntType.h>
#include <grove/types/IntType.h>

#include <grove/exceptions/fatal_error.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>

EnumType::EnumType(const Type* contained, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}
	
	m_contained = contained;
	m_type = m_contained->getLLVMType();
	
	copyCasts(typeid(*contained));
}

std::string EnumType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "enum<" << m_contained->getString() << ">";
	return ss.str();
}

std::string EnumType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst()) {
		ss << getConstIdentifier();
	}
	
	ss << "e" << m_contained->getSignature();
	
	return ss.str();
}

bool EnumType::isSigned() const
{
	return getBaseTy()->isSigned();
}

const Type* EnumType::getBaseTy() const
{
	return m_contained;
}

const Type* EnumType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

const Type* EnumType::getConst() const
{
	return EnumType::get(getModule(), m_contained, true);
}

EnumType* EnumType::get(Module* mod, const Type *contained, bool isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}
	
	if (contained->isVoidTy())
	{
		throw fatal_error("cannot create enum of type void");
	}
	
	if (contained->isVarTy())
	{
		throw fatal_error("cannot create enum of type var");
	}
	
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "e" << contained->getSignature();
	
	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<EnumType *>();
	}
	
	EnumType* ty = new EnumType(contained, isConst);
	define(mod, ss.str(), ty);
	
	return ty;
}

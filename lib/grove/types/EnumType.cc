/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/types/EnumType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>

#include <grove/types/UIntType.h>
#include <grove/types/IntType.h>

EnumType::EnumType(Type* contained, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}
	
	m_contained = contained;
	m_type = m_contained->getLLVMType();
	
	copyCasts(typeid(*contained));
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

Type* EnumType::getBaseTy() const
{
	return m_contained;
}

Type* EnumType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

Type* EnumType::getConst() const
{
	return EnumType::get(m_contained, true);
}

EnumType* EnumType::get(Type *contained, bool isConst)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}
	
	if (contained->isVoidTy())
	{
		throw std::invalid_argument("cannot get pointer to void");
	}
	
	if (contained->isVarTy())
	{
		throw std::invalid_argument("cannot get pointer to var");
	}
	
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "e" << contained->getSignature();
	
	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return defined->as<EnumType *>();
	}
	
	EnumType* ty = new EnumType(contained, isConst);
	define(ss.str(), ty);
	
	return ty;
}

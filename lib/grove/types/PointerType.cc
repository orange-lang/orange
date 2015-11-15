/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/PointerType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>

#include <grove/types/UIntType.h>
#include <grove/types/IntType.h>

PointerType::PointerType(Type* contained)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}
	
	m_contained = contained;
	m_type = m_contained->getLLVMType()->getPointerTo();
	
	defineCast(typeid(IntType), llvm::Instruction::CastOps::IntToPtr);
	defineCast(typeid(UIntType), llvm::Instruction::CastOps::IntToPtr);
}

std::string PointerType::getSignature() const
{
	return m_contained->getSignature() + "p";
}

bool PointerType::isSigned() const
{
	return true;
}


bool PointerType::isPointerTy() const
{
	return true;
}

Type* PointerType::getBaseTy()
{
	return m_contained;
}

Type* PointerType::getRootTy()
{
	return getBaseTy()->getRootTy();
}

PointerType* PointerType::get(Type *contained)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}
	
	std::string signature = contained->getSignature() + "p";
	
	auto defined = getDefined(signature);
	if (defined != nullptr)
	{
		return dynamic_cast<PointerType *>(defined);
	}
	

	PointerType* ty = new PointerType(contained);
	define(signature, ty);
	
	return ty;
}
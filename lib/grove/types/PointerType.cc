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

PointerType::PointerType(Type* contained, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}

	m_contained = contained;
	m_type = m_contained->getLLVMType()->getPointerTo();

	defineCast(typeid(IntType), llvm::Instruction::CastOps::PtrToInt);
	defineCast(typeid(UIntType), llvm::Instruction::CastOps::PtrToInt);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::BitCast);
}

std::string PointerType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst()) {
		ss << "U";
	}
	
	ss << "p" << m_contained->getSignature();
	
	return ss.str();
}

bool PointerType::isSigned() const
{
	return true;
}


bool PointerType::isPointerTy() const
{
	return true;
}

Type* PointerType::getBaseTy() const
{
	return m_contained;
}

Type* PointerType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

Type* PointerType::getConst() const
{
	return PointerType::get(m_contained, true);
}

PointerType* PointerType::get(Type *contained, bool isConst)
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

	std::string signature = "p" + contained->getSignature();
	
	if (isConst)
	{
		signature += "!";
	}

	auto defined = getDefined(signature);
	if (defined != nullptr)
	{
		return defined->as<PointerType *>();
	}

	PointerType* ty = new PointerType(contained, isConst);
	define(signature, ty);

	return ty;
}

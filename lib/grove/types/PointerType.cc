/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/PointerType.h>
#include <grove/types/UIntType.h>
#include <grove/types/IntType.h>

#include <grove/exceptions/fatal_error.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>

PointerType::PointerType(Type* contained, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}

	m_contained = contained;

	defineCast(typeid(IntType), llvm::Instruction::CastOps::PtrToInt);
	defineCast(typeid(UIntType), llvm::Instruction::CastOps::PtrToInt);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::BitCast);
}

llvm::Type* PointerType::getLLVMType() const
{
	return m_contained->getLLVMType()->getPointerTo();
}

std::string PointerType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << m_contained->getString() << "*";
	return ss.str();
}

std::string PointerType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst()) {
		ss << getConstIdentifier();
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
	return PointerType::get(m_module, m_contained, true);
}

PointerType* PointerType::get(Module* mod, Type *contained, bool isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}
	
	if (contained->isVoidTy())
	{
		throw fatal_error("cannot get pointer to type void");
	}
	
	if (contained->isVarTy())
	{
		throw fatal_error("cannot get pointer to type var");
	}

	std::stringstream ss;

	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "p" << contained->getSignature();
	
	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<PointerType *>();
	}

	PointerType* ty = new PointerType(contained, isConst);
	define(mod, ss.str(), ty);

	return ty;
}

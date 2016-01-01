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

Orange::PointerType::PointerType(const Type* contained, bool isConst)
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

const Orange::Type* Orange::PointerType::copyType() const
{
	return Orange::PointerType::get(getModule(), m_contained->copyType(),
							isConst());
}

bool Orange::PointerType::matches(const Type *ty) const
{
	// If our contained is a node type, and
	// we're looking at a pointer type that contains a node
	// type, let's compare those instead.
	if (m_contained->isNodeTy() && ty->isPointerTy() &&
		ty->getBaseTy()->isNodeTy())
	{
		// Compare the reference types...
		return m_contained->matches(ty->getBaseTy());
	}
	
	
	return Type::matches(ty);
}

llvm::Type* Orange::PointerType::getLLVMType() const
{
	if (m_contained->getLLVMType()->isVoidTy())
	{
		throw fatal_error("Getting a pointer to a void type");
	}
	
	return m_contained->getLLVMType()->getPointerTo();
}

std::string Orange::PointerType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << m_contained->getString() << "*";
	return ss.str();
}

std::string Orange::PointerType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst()) {
		ss << getConstIdentifier();
	}
	
	ss << "p" << m_contained->getSignature();
	
	return ss.str();
}

bool Orange::PointerType::isSigned() const
{
	return true;
}

bool Orange::PointerType::isPointerTy() const
{
	return true;
}

const Orange::Type* Orange::PointerType::getBaseTy() const
{
	return m_contained;
}

const Orange::Type* Orange::PointerType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

const Orange::Type* Orange::PointerType::getConst() const
{
	return Orange::PointerType::get(getModule(), m_contained, true);
}

Orange::PointerType* Orange::PointerType::get(Module* mod,
											  const Orange::Type* contained,
                							  bool isConst)
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

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/Type.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include <grove/Module.h>
#include <grove/types/PointerType.h>

std::map<std::string, Type*> Type::m_defined;

bool Type::isSigned() const
{
	return false;
}

bool Type::isPODTy() const
{
	return false;
}

bool Type::isArrayTy() const
{
	return false;
}

bool Type::isDoubleTy() const
{
	return false;
}

bool Type::isFloatTy() const
{
	return false;
}

bool Type::isFloatingPointTy() const
{
	return false;
}

bool Type::isFunctionTy() const
{
	return false;
}

bool Type::isIntTy() const
{
	return false;
}

bool Type::isPointerTy() const
{
	return false;
}

bool Type::isVoidTy() const
{
	return false;
}

BasicType Type::PODTy() const
{
	return OTHER;
}

Type* Type::getPointerTo()
{
	return PointerType::get((Type *)this);
}

Type* Type::getBaseTy()
{
	return this;
}

Type* Type::getRootTy()
{
	return this;
}

Type* Type::getDefined(std::string signature)
{
	auto it = m_defined.find(signature);
	
	if (it == m_defined.end())
	{
		return nullptr;
	}
	
	return it->second;
}

void Type::define(std::string signature, Type *ty)
{
	if (getDefined(signature) != nullptr)
	{
		throw std::invalid_argument("signature is already defined.");
	}
	
	if (ty == nullptr)
	{
		throw std::invalid_argument("ty must not be null.");
	}
	
	m_defined[signature] = ty;
}

Type::Type()
{
	m_context = & llvm::getGlobalContext();
	m_type = llvm::Type::getVoidTy(*m_context);
}

std::string Type::getSignature() const
{
	throw std::runtime_error("Type::getSignature shouldn't be called.");
}

llvm::Type* Type::getLLVMType() const
{
	return m_type;
}
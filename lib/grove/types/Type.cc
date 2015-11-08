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

std::map<std::string, Type*> Type::m_defined;

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
}

bool Type::isSigned() const
{
	return false;
}

std::string Type::getSignature() const
{
	throw std::runtime_error("Type::getSignature shouldn't be called.");
}

llvm::Type* Type::getLLVMType() const
{
	return llvm::Type::getVoidTy(*m_context);
}
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
#include <util/assertions.h>

std::map<std::string, Type*> Type::m_defined;
std::map<TypeTuple, int> Type::m_cast_map;
std::map<TypeTuple, TypeCallback> Type::m_cast_func_map;

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

bool Type::isVarTy() const
{
	return false;
}

bool Type::isConst() const
{
	return m_const;
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

Type* Type::getConst()
{
	throw std::runtime_error("Cannot get const of this type");
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

unsigned int Type::getIntegerBitWidth() const
{
	return 0;
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

void Type::defineCast(const std::type_info &to, TypeCallback cb)
{
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_func_map[tuple] = cb;
}

void Type::defineCast(const std::type_info &to, int cast)
{
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_map[tuple] = cast;
}
std::string Type::getSignature() const
{
	throw std::runtime_error("Type::getSignature shouldn't be called.");
}

int Type::castOperation(Type *to)
{
	if (this == to)
	{
		return 0;
	}
	
	TypeTuple key(typeid(*this).hash_code(), typeid(*to).hash_code());
	
	// Search for callbacks first.
	auto it_cb = m_cast_func_map.find(key);
	if (it_cb != m_cast_func_map.end())
	{
		return it_cb->second(this, to);
	}
	
	auto it = m_cast_map.find(key);
	if (it == m_cast_map.end())
	{
		throw std::invalid_argument("no cast defined");
	}
	
	return it->second;
}

llvm::Type* Type::getLLVMType() const
{
	return m_type;
}

Comparison Type::compare(Type *source, Type *target)
{
	assertExists(source, "Source type must exist");
	assertExists(target, "Target type must exist");
	
	if (source == target)
	{
		return Comparison::EQUAL;
	}
	
	// Only compare the precedence of two POD types.
	bool bothPOD = source->isPODTy() && target->isPODTy();
	if (bothPOD == false)
	{
		return Comparison::INCOMPATIBLE;
	}
	
	if (source->PODTy() < target->PODTy())
	{
		return Comparison::HIGHER_PRECEDENCE;
	}
	else if (source->PODTy() == target->PODTy())
	{
		return Comparison::EQUAL;
	}
	else
	{
		return Comparison::LOWER_PRECEDENCE;
	}
}

Type::Type(bool isConst)
{
	m_context = & llvm::getGlobalContext();
	m_const = isConst;
	m_type = llvm::Type::getVoidTy(*m_context);
}

Type::~Type()
{
	// Do nothing.
}

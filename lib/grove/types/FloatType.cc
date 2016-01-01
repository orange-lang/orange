/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/FloatType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include <grove/types/UIntType.h>
#include <grove/types/IntType.h>
#include <grove/types/DoubleType.h>

Orange::FloatType::FloatType(bool isConst)
: Type(isConst)
{
	m_type = llvm::Type::getFloatTy(*m_context);

	defineCast(typeid(UIntType), llvm::Instruction::CastOps::FPToUI);
	defineCast(typeid(IntType), llvm::Instruction::CastOps::FPToSI);
	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::FPExt);
}

std::string Orange::FloatType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "float";
	return ss.str();
}

std::string Orange::FloatType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
	ss << "f";
	
	return ss.str();
}

bool Orange::FloatType::isPODTy() const
{
	return true;
}

bool Orange::FloatType::isFloatTy() const
{
	return true;
}

bool Orange::FloatType::isFloatingPointTy() const
{
	return true;
}

BasicType Orange::FloatType::PODTy() const
{
	return TYFLOAT;
}

Orange::Type* Orange::FloatType::getConst() const
{
	return FloatType::get(getModule(), true);
}

Orange::FloatType* Orange::FloatType::get(Module* mod, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "f";
	
	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<FloatType*>();
	}

	FloatType* ty = new FloatType(isConst);
	define(mod, ss.str(), ty);

	return ty;
}

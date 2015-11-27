/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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

FloatType::FloatType(bool isConst)
: Type(isConst)
{
	m_type = llvm::Type::getFloatTy(*m_context);

	defineCast(typeid(UIntType), llvm::Instruction::CastOps::FPToUI);
	defineCast(typeid(IntType), llvm::Instruction::CastOps::FPToSI);
	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::FPExt);
}

std::string FloatType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "float";
	return ss.str();
}

std::string FloatType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
	ss << "f";
	
	return ss.str();
}

bool FloatType::isPODTy() const
{
	return true;
}

bool FloatType::isFloatTy() const
{
	return true;
}

bool FloatType::isFloatingPointTy() const
{
	return true;
}

BasicType FloatType::PODTy() const
{
	return TYFLOAT;
}

Type* FloatType::getConst() const
{
	return FloatType::get(true);
}

FloatType* FloatType::get(bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "f";
	
	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return defined->as<FloatType*>();
	}

	FloatType* ty = new FloatType(isConst);
	define(ss.str(), ty);

	return ty;
}

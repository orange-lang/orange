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

FloatType::FloatType()
{
	m_type = llvm::Type::getFloatTy(*m_context);
	
	defineCast(typeid(UIntType), llvm::Instruction::CastOps::FPToUI);
	defineCast(typeid(IntType), llvm::Instruction::CastOps::FPToSI);
	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::FPExt);
}

std::string FloatType::getSignature() const
{
	return "f";
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
	return FLOAT;
}

FloatType* FloatType::get()
{
	auto defined = getDefined("f");
	if (defined != nullptr)
	{
		return dynamic_cast<FloatType*>(defined);
	}
	
	FloatType* ty = new FloatType();
	define("f", ty);
	
	return ty;
}
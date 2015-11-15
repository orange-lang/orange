/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/IntType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/IntType.h>
#include <grove/types/PointerType.h>

IntType::IntType(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	m_width = width;
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);
	
	defineCast(typeid(UIntType), llvm::Instruction::CastOps::SExt);
	defineCast(typeid(IntType), llvm::Instruction::CastOps::SExt);
	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::FPToSI);
	defineCast(typeid(FloatType), llvm::Instruction::CastOps::FPToSI);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::PtrToInt);
}

std::string IntType::getSignature() const
{
	std::stringstream ss;
	ss << "i." << m_width;
	return ss.str();
}

bool IntType::isPODTy() const
{
	return true;
}

bool IntType::isSigned() const
{
	return true;
}

bool IntType::isIntTy() const
{
	return true;
}

BasicType IntType::PODTy() const
{
	switch (m_width)
	{
		case 8:
			return INT8;
		case 16:
			return INT16;
		case 32:
			return INT32;
		case 64:
			return INT64;
		default:
			return OTHER;
	}
}

IntType* IntType::get(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	std::stringstream ss;
	ss << "i." << width;
	
	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return dynamic_cast<IntType*>(defined);
	}
	
	IntType* ty = new IntType(width);
	define(ss.str(), ty);
	
	return ty;
}
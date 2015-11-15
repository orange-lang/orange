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
#include <grove/types/BoolType.h>
#include <grove/types/PointerType.h>

static int IntToInt(Type* f, Type* t)
{
	auto from = dynamic_cast<IntType *>(f);
	auto to = dynamic_cast<IntType *>(t);
	
	if (from->getWidth() > to->getWidth())
	{
		return llvm::Instruction::CastOps::Trunc;
	}
	else if (from->getWidth() == to->getWidth())
	{
		return 0;
	}
	else
	{
		return llvm::Instruction::CastOps::SExt;
    }
}

static int IntToUInt(Type* f, Type* t)
{
	auto from = dynamic_cast<IntType *>(f);
	auto to = dynamic_cast<UIntType *>(t);
	
	if (from->getWidth() > to->getWidth())
	{
		return llvm::Instruction::CastOps::Trunc;
	}
	else if (from->getWidth() == to->getWidth())
	{
		return 0;
	}
	else
	{
		return llvm::Instruction::CastOps::SExt;
	}
}


IntType::IntType(unsigned int width)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}
	
	m_width = width;
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);
	
	defineCast(typeid(IntType), IntToInt);
	defineCast(typeid(BoolType), IntToUInt);
	defineCast(typeid(UIntType), IntToUInt);

	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::SIToFP);
	defineCast(typeid(FloatType), llvm::Instruction::CastOps::SIToFP);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::IntToPtr);
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

unsigned int IntType::getWidth() const
{
	return m_width;
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
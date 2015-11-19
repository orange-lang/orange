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
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/BoolType.h>
#include <grove/types/PointerType.h>

#include <grove/ASTNode.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

static int IntToInt(Type* f, Type* t)
{
	auto from = f->as<IntType *>();
	auto to = t->as<IntType *>();

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
	auto from = f->as<IntType *>();
	auto to = t->as<UIntType *>();

	if (from->getWidth() > to->getIntegerBitWidth())
	{
		return llvm::Instruction::CastOps::Trunc;
	}
	else if (from->getIntegerBitWidth() == to->getIntegerBitWidth())
	{
		return 0;
	}
	else
	{
		return llvm::Instruction::CastOps::SExt;
	}
}

static llvm::Value* BoolCast(void* irBuilder, llvm::Value* val, Type* from,
							 Type* to)
{
	assertExists(irBuilder, "irbuilder must exist");
	assertExists(val, "val must exist");
	assertExists(from, "from must exist");
	assertExists(to, "to must exist");
	
	IRBuilder* IRB = (IRBuilder *)irBuilder;
	
	auto zero = llvm::ConstantInt::get(from->getLLVMType(), 0, true);
	assertEqual(zero, val, "Could not create bool cast");
	
	return IRB->CreateICmpNE(val, zero);
}

IntType::IntType(unsigned int width, bool isConst)
: Type(isConst)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}

	m_width = width;
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);

	defineCast(typeid(IntType), IntToInt);
	defineCast(typeid(UIntType), IntToUInt);

	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::SIToFP);
	defineCast(typeid(FloatType), llvm::Instruction::CastOps::SIToFP);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::IntToPtr);
	
	defineCast(typeid(BoolType), IntToUInt, BoolCast);
	
}

unsigned int IntType::getIntegerBitWidth() const
{
	return m_width;
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

Type* IntType::getConst() const
{
	return IntType::get(m_width, true);
}

IntType* IntType::get(unsigned int width, bool isConst)
{
	if (width == 0)
	{
		throw std::invalid_argument("width must not be 0.");
	}

	std::stringstream ss;
	ss << "i." << width;
	
	if (isConst)
	{
		ss << "!";
	}

	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return defined->as<IntType*>();
	}

	IntType* ty = new IntType(width, isConst);
	define(ss.str(), ty);

	return ty;
}

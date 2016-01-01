/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/IntType.h>
#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/BoolType.h>
#include <grove/types/PointerType.h>

#include <grove/ASTNode.h>
#include <grove/Valued.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

static int IntToInt(const Orange::Type* from, const Orange::Type* to)
{
	if (from->getIntegerBitWidth() > to->getIntegerBitWidth())
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

static int IntToUInt(const Orange::Type* from, const Orange::Type* to)
{
	if (from->getIntegerBitWidth() > to->getIntegerBitWidth())
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

static llvm::Value* BoolCast(void* irBuilder, Valued* val,
							 const Orange::Type* from, const Orange::Type* to)
{
	assertExists(irBuilder, "irbuilder must exist");
	assertExists(val, "val must exist");
	assertExists(from, "from must exist");
	assertExists(to, "to must exist");
	
	auto llvm_val = val->getValue();
	assertExists(llvm_val, "valued didn't have value");
	
	LLVMBuilder* IRB = (LLVMBuilder *)irBuilder;
	
	auto zero = llvm::ConstantInt::get(from->getLLVMType(), 0, true);
	assertEqual(zero, llvm_val, "Could not create bool cast");
	
	return IRB->CreateICmpNE(llvm_val, zero);
}

Orange::IntType::IntType(unsigned int width, bool isConst)
: Type(isConst)
{
	if (width == 0)
	{
		throw fatal_error("tried to create an int with a width of 0");
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

unsigned int Orange::IntType::getIntegerBitWidth() const
{
	return m_width;
}


std::string Orange::IntType::getSignature(unsigned int width, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	switch (width)
	{
		case 1:
			ss << "b";
			break;
		case 8:
			ss << "c";
			break;
		case 16:
			ss << "s";
			break;
		case 32:
			ss << "i";
			break;
		case 64:
			ss << "l";
			break;
		default:
			ss << width << "i";
			break;
	}
	
	return ss.str();
}

std::string Orange::IntType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "int" << m_width;
	return ss.str();
}

std::string Orange::IntType::getSignature() const
{
	return getSignature(m_width, isConst());
}

bool Orange::IntType::isPODTy() const
{
	return true;
}

bool Orange::IntType::isSigned() const
{
	return true;
}

bool Orange::IntType::isIntTy() const
{
	return true;
}

unsigned int Orange::IntType::getWidth() const
{
	return m_width;
}

BasicType Orange::IntType::PODTy() const
{
	switch (m_width)
	{
		case 8:
			return TYINT8;
		case 16:
			return TYINT16;
		case 32:
			return TYINT32;
		case 64:
			return TYINT64;
		default:
			return TYOTHER;
	}
}

Orange::Type* Orange::IntType::getConst() const
{
	return IntType::get(getModule(), m_width, true);
}

Orange::IntType* Orange::IntType::get(Module* mod, unsigned int width,
									  bool isConst)
{
	if (width == 0)
	{
		throw fatal_error("tried to create an int with a width of 0");
	}

	auto sig = getSignature(width, isConst);
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<IntType*>();
	}

	IntType* ty = new IntType(width, isConst);
	define(mod, sig, ty);

	return ty;
}

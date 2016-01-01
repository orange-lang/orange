/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/IntType.h>
#include <grove/types/BoolType.h>
#include <grove/types/PointerType.h>

#include <grove/ASTNode.h>
#include <grove/Valued.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

static int UIntToInt(const Orange::Type* from, const Orange::Type* to)
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
		return llvm::Instruction::CastOps::ZExt;
	}
}

static int UIntToUInt(const Orange::Type* from, const Orange::Type* to)
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
		return llvm::Instruction::CastOps::ZExt;
	}
}

static llvm::Value* BoolCast(void* irBuilder, Valued* val,
							 const Orange::Type* from, const Orange::Type* to)
{
	assertExists(irBuilder, "irbuilder must exist");
	assertExists(val, "val must exist");
	assertExists(from, "from must exist");
	assertExists(to, "to must exist");
	
	LLVMBuilder* IRB = (LLVMBuilder *)irBuilder;
	
	auto llvm_val = val->getValue();
	assertExists(llvm_val, "llvm_val is nullptr");
	
	auto zero = llvm::ConstantInt::get(from->getLLVMType(), 0, false);
	assertEqual(zero, llvm_val, "Could not create bool cast");
	
	return IRB->CreateICmpNE(llvm_val, zero);
}

Orange::UIntType::UIntType(unsigned int width, bool isConst)
: Type(isConst)
{
	if (width == 0)
	{
		throw fatal_error("trying to create uint with width of 0");
	}
	
	m_width = width;
	m_type = (llvm::Type *)llvm::Type::getIntNTy(*m_context, width);
	
	defineCast(typeid(UIntType), UIntToUInt);
	defineCast(typeid(IntType), UIntToInt);
	
	defineCast(typeid(DoubleType), llvm::Instruction::CastOps::UIToFP);
	defineCast(typeid(FloatType), llvm::Instruction::CastOps::UIToFP);
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::IntToPtr);
	
	defineCast(typeid(BoolType), UIntToUInt, BoolCast);
}

std::string Orange::UIntType::getSignature(unsigned int width, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	switch (width)
	{
		case 1:
			ss << "B";
			break;
		case 8:
			ss << "C";
			break;
		case 16:
			ss << "S";
			break;
		case 32:
			ss << "I";
			break;
		case 64:
			ss << "L";
			break;
		default:
			ss << width << "I";
			break;
	}
	
	return ss.str();
}

std::string Orange::UIntType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "uint" << m_width;
	return ss.str();
}

std::string Orange::UIntType::getSignature() const
{
	return getSignature(m_width, isConst());
}

bool Orange::UIntType::isPODTy() const
{
	return true;
}

bool Orange::UIntType::isSigned() const
{
	return false;
}

bool Orange::UIntType::isIntTy() const
{
	return true;
}

unsigned int Orange::UIntType::getIntegerBitWidth() const
{
	return m_width;
}

BasicType Orange::UIntType::PODTy() const
{
	switch (m_width)
	{
		case 1:
			return TYUINT1;
		case 8:
			return TYUINT8;
		case 16:
			return TYUINT16;
		case 32:
			return TYUINT32;
		case 64:
			return TYUINT64;
		default:
			return TYOTHER;
	}
}

Orange::Type* Orange::UIntType::getConst() const
{
	return UIntType::get(getModule(), m_width, true);
}

Orange::UIntType* Orange::UIntType::get(Module* mod, unsigned int width,
										bool isConst)
{
	if (width == 0)
	{
		throw fatal_error("trying to create uint with width of 0");
	}

	auto sig = getSignature(width, isConst);
	
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return dynamic_cast<UIntType*>(defined);
	}
	
	UIntType* ty = new UIntType(width, isConst);
	define(mod, sig, ty);
	
	return ty;
}
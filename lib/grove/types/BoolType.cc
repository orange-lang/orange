/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/types/BoolType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/IntType.h>
#include <grove/types/PointerType.h>

const int BOOL_WIDTH = 1;

static int BoolToInt(const Orange::Type* f, const Orange::Type* t)
{
	auto from = f->as<BoolType*>();
	auto to = t->as<IntType*>();

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

static int BoolToUInt(const Orange::Type* f, const Orange::Type* t)
{
	auto from = f->as<BoolType*>();
	auto to = t->as<UIntType*>();

	if (from->Type::getIntegerBitWidth() > to->getIntegerBitWidth())
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

BoolType::BoolType(bool isConst)
: UIntType(BOOL_WIDTH, isConst)
{
	defineCast(typeid(IntType), BoolToInt);
	defineCast(typeid(UIntType), BoolToUInt);
}

std::string BoolType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "bool";
	
	return ss.str();
}

std::string BoolType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
	ss << "b";
	
	return ss.str();
}

Orange::Type* BoolType::getConst() const
{
	return BoolType::get(getModule(), true);
}

bool BoolType::isBoolTy() const
{
	return true;
}

bool BoolType::isIntTy() const
{
	return false; 
}

BoolType* BoolType::get(Module* mod, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << "U";
	}
	
	ss << "b";
	
	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<BoolType*>();
	}

	BoolType* ty = new BoolType(isConst);
	define(mod, ss.str(), ty);

	return ty;
}

/*
 ** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <libast/types/BoolType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include <libast/types/UIntType.h>
#include <libast/types/DoubleType.h>
#include <libast/types/FloatType.h>
#include <libast/types/IntType.h>
#include <libast/types/PointerType.h>

const int BOOL_WIDTH = 1;

static int BoolToInt(const Orange::Type* f, const Orange::Type* t)
{
	auto from = f->as<Orange::BoolType*>();
	auto to = t->as<Orange::IntType*>();

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
	auto from = f->as<Orange::BoolType*>();
	auto to = t->as<Orange::UIntType*>();

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

Orange::BoolType::BoolType(bool isConst)
: UIntType(BOOL_WIDTH, isConst)
{
	defineCast(typeid(IntType), BoolToInt);
	defineCast(typeid(UIntType), BoolToUInt);
}

std::string Orange::BoolType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << "bool";
	
	return ss.str();
}

std::string Orange::BoolType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
	ss << "b";
	
	return ss.str();
}

Orange::Type* Orange::BoolType::getConst() const
{
	return BoolType::get(getModule(), true);
}

bool Orange::BoolType::isBoolTy() const
{
	return true;
}

bool Orange::BoolType::isIntTy() const
{
	return false; 
}

Orange::BoolType* Orange::BoolType::get(Module* mod, bool isConst)
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

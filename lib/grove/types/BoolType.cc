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

static int BoolToInt(Type* f, Type* t)
{
	auto from = f->as<BoolType*>();
	auto to = t->as<IntType*>();

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
		return llvm::Instruction::CastOps::ZExt;
	}
}

static int BoolToUInt(Type* f, Type* t)
{
	auto from = f->as<BoolType*>();
	auto to = t->as<UIntType*>();

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
		return llvm::Instruction::CastOps::ZExt;
	}
}

BoolType::BoolType()
: UIntType(BOOL_WIDTH)
{
	defineCast(typeid(IntType), BoolToInt);
	defineCast(typeid(UIntType), BoolToUInt);
}

std::string BoolType::getSignature() const
{
	return "b";
}

BoolType* BoolType::get()
{
	auto defined = getDefined("b");
	if (defined != nullptr)
	{
		return defined->as<BoolType*>();
	}

	BoolType* ty = new BoolType();
	define("b", ty);

	return ty;
}

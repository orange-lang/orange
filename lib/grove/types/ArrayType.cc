/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/ArrayType.h>
#include <grove/types/PointerType.h>

#include <grove/Valued.h>
#include <grove/ASTNode.h>
#include <grove/Expression.h>
#include <grove/Value.h>

#include <util/llvmassertions.h>
#include <util/assertions.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>


static llvm::Value* PointerCast(void* irBuilder, Valued* val, Type* from,
							 Type* to)
{
	assertExists(irBuilder, "irbuilder must exist");
	assertExists(val, "val must exist");
	assertExists(from, "from must exist");
	assertExists(to, "to must exist");
	
	auto llvm_val = val->getPointer();
	assertExists(llvm_val, "valued didn't have pointer");
	
	IRBuilder* IRB = (IRBuilder *)irBuilder;
	
	return IRB->CreateBitCast(llvm_val, to->getLLVMType());
}

ArrayType::ArrayType(Type* contained, unsigned int size, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}

	m_contained = contained;
	m_size = size;

	m_type = llvm::ArrayType::get(m_contained->getLLVMType(), m_size);
	
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::BitCast,
			   	PointerCast);
}

std::string ArrayType::getSignature() const
{
	std::stringstream ss;
	ss << m_size << m_contained->getSignature();
	return ss.str();
}

bool ArrayType::isSigned() const
{
	return m_contained->isSigned();
}

bool ArrayType::isArrayTy() const
{
	return true;
}

Type* ArrayType::getBaseTy() const
{
	return m_contained;
}

Type* ArrayType::getRootTy() const
{
	return m_contained->getRootTy();
}

Type* ArrayType::getConst() const
{
	return ArrayType::get(m_contained, m_size, true);
}

ArrayType* ArrayType::get(Type* contained, Expression* expr, bool isConst)
{
	if (expr->isConstant() == false)
	{
		throw std::invalid_argument("cannot use non-constant expr for type");
	}
	
	if (expr->getType()->isIntTy() == false)
	{
		throw std::invalid_argument("array size can only be defined with an integer");
	}
	
	if (dynamic_cast<Value *>(expr) == nullptr)
	{
		throw std::invalid_argument("Don't know how to handle this");
	}
	
	Value* v = dynamic_cast<Value *>(expr);
	unsigned int size = 0;
	
	if (expr->getType()->isSigned())
	{
		size = v->getInt();
	}
	else
	{
		size = v->getUInt();
	}
	
	return get(contained, size, isConst);
}

ArrayType* ArrayType::get(Type *contained, unsigned int size, bool isConst)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be nullptr");
	}

	std::stringstream ss;
	ss << size << contained->getSignature();
	
	if (isConst)
	{
		ss << "U";
	}

	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return defined->as<ArrayType *>();
	}

	ArrayType* ty = new ArrayType(contained, size, isConst);
	define(ss.str(), ty);

	return ty;
}

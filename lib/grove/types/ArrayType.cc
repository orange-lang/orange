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

#include <grove/exceptions/fatal_error.h>

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
	
	LLVMBuilder* IRB = (LLVMBuilder *)irBuilder;
	
	return IRB->CreateBitCast(llvm_val, to->getLLVMType());
}

ArrayType::ArrayType(Type* contained, unsigned int size, bool isConst)
: Type(isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}

	m_contained = contained;
	m_size = size;

	m_type = llvm::ArrayType::get(m_contained->getLLVMType(), m_size);
	
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::BitCast,
			   	PointerCast);
}

std::string ArrayType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << m_contained->getString();
	ss << "[" << m_size << "]";
	
	return ss.str();
}

std::string ArrayType::getSignature() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << getConstIdentifier();
	}
	
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
	return ArrayType::get(getModule(), m_contained, m_size, true);
}

ArrayType* ArrayType::get(Module* mod, Type *contained, unsigned int size,
						  bool isConst)
{
	if (contained == nullptr)
	{
		throw fatal_error("contained was null");
	}

	std::stringstream ss;
	ss << size << contained->getSignature();
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}

	auto defined = getDefined(mod, ss.str());
	if (defined != nullptr)
	{
		return defined->as<ArrayType *>();
	}

	ArrayType* ty = new ArrayType(contained, size, isConst);
	define(mod, ss.str(), ty);

	return ty;
}

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ArrayValue.h>

#include <grove/types/Type.h>
#include <grove/types/ArrayType.h>

#include <util/llvmassertions.h>
#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

ASTNode* ArrayValue::copy() const
{
	return new ArrayValue(copyVector(getElements()));
}

std::vector<Expression *> ArrayValue::getElements() const
{
	return m_elements;
}

llvm::Value* ArrayValue::castTo(Type* ty) const
{
	assertExists(ty, "type must exist.");
	assertExists(getType(), "expression does not have a type.");
	
	// If casting to a pointer, use the pointer for the cast.
	auto use_val = getValue();
	if (ty->isPointerTy())
	{
		use_val = getPointer();
	}
	
	return getType()->cast(IRBuilder(), use_val, ty);
}

void ArrayValue::resolve()
{
	// Find the highest precedence type in retStmts.
	auto highest = getElements()[0]->getType();
	assertExists(highest, "Array element missing type");
	
	for (int i = 1; i < getElements().size(); i++)
	{
		auto cmp_ty = getElements().at(i)->getType();
		assertExists(cmp_ty, "Array element missing type");
		
		switch (Type::compare(highest, cmp_ty)) {
			case LOWER_PRECEDENCE:
				highest = cmp_ty;
				break;
			case INCOMPATIBLE:
				throw std::invalid_argument("Incompatible array elements");
			default:
				break;
		}
	}
	
	setType(ArrayType::get(highest, getElements().size()));
}

void ArrayValue::build()
{
	// Build all elements
	for (auto element : getElements())
	{
		element->build();
	}
	
	auto val = IRBuilder()->CreateAlloca(getType()->getLLVMType());
	
	if (isConstant())
	{
		std::vector<llvm::Constant *> consts;
		
		for (auto element : getElements())
		{
			auto ele = element->castTo(getType()->getBaseTy());
			assertExists(ele, "Element couldn't be casted");
			
			if (llvm::isa<llvm::Constant>(ele) == false)
			{
				throw std::runtime_error("element was not a constant");
			}
				
			consts.push_back((llvm::Constant *)ele);
		}
		
		auto array_ty = (llvm::ArrayType *)getType()->getLLVMType();
		auto store = llvm::ConstantArray::get(array_ty, consts);
		IRBuilder()->CreateStore(store, val);
	}
	else
	{
		for (unsigned int i = 0; i < getElements().size(); i++)
		{
			auto ele = getElements().at(i);
			auto ele_val = ele->castTo(getType()->getBaseTy());
			assertExists(ele_val, "Element couldn't be casted");
			
			auto gep = IRBuilder()->CreateConstInBoundsGEP2_64(val, 0, i);
			
			assertEqual<VAL,PTR>(ele_val, gep, "Types not matching!");
			IRBuilder()->CreateStore(ele_val, gep);
		}
	}
	
	setValue(val);
}

bool ArrayValue::hasPointer() const
{
	return false;
}

llvm::Value* ArrayValue::getPointer() const
{
	return m_value;
}

llvm::Value* ArrayValue::getValue() const
{
//	return m_value;
	return IRBuilder()->CreateLoad(m_value);
}

bool ArrayValue::isConstant() const
{
	for (auto element : getElements())
	{
		if (element->getType()->isArrayTy())
		{
			return false;
		}
		
		if (element->isConstant() == false)
		{
			return false;
		}
	}
	
	return true;
}

ArrayValue::ArrayValue(std::vector<Expression *> elements)
{
	if (elements.size() == 0)
	{
		throw std::invalid_argument("Arrays must have at least 1 element.");
	}
	
	for (auto element : elements)
	{
		addChild(element, true);
	}
	
	m_elements = elements;
}
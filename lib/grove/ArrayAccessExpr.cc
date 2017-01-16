/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ArrayAccessExpr.h>
#include <grove/Module.h>

#include <grove/exceptions/invalid_type_error.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

ASTNode* ArrayAccessExpr::copy() const
{
	auto array_copy = getArray()->copy()->as<Expression *>();
	auto idx_copy = getIndex()->copy()->as<Expression *>();
	return new ArrayAccessExpr(array_copy, idx_copy);
}

Expression* ArrayAccessExpr::getArray() const
{
	return m_array;
}

Expression* ArrayAccessExpr::getIndex() const
{
	return m_idx;
}

void ArrayAccessExpr::resolve()
{
	auto array_ty = getArray()->getType();
	assertExists(array_ty, "Array has no type");
	
	bool valid = array_ty->isArrayTy() || array_ty->isPointerTy();
	if (valid == false)
	{
		throw invalid_type_error(this, "cannot access element of non-array type",
								 array_ty);
	}
	
	auto idx_ty = getIndex()->getType();
	assertExists(idx_ty, "Index has no type");
	
	if (idx_ty->isIntTy() == false)
	{
		throw invalid_type_error(this, "cannot get index of array using type",
								 idx_ty);
	}
	
	setType(array_ty->getBaseTy());
}

bool ArrayAccessExpr::hasPointer() const
{
	return true;
}

llvm::Value* ArrayAccessExpr::getPointer() const
{
	return m_value;
}

llvm::Value* ArrayAccessExpr::getValue() const
{
	return IRBuilder()->CreateLoad(m_value);
}

void ArrayAccessExpr::build()
{
	getArray()->build();
	getIndex()->build();
	
	llvm::Value* vArray = nullptr;
	if (getArray()->hasPointer() && getArray()->getType()->isArrayTy())
	{
		vArray = getArray()->getPointer();
	}
	else
	{
		vArray = getArray()->getValue();
	}
	
	auto vIndex = getIndex()->getValue();
	
	assertExists(vArray, "Array generated no value");
	assertExists(vIndex, "Index generated no value");
	
	std::vector<llvm::Value *> indices;
	
	if (getArray()->getType()->isArrayTy() &&
		getArray()->getType()->isVariadiclySized() == false)
	{
		auto& ctx = getModule()->getLLVMContext();
		auto idx = llvm::ConstantInt::get(llvm::Type::getInt64Ty(ctx), 0);
		indices.push_back(idx);
	}
	
	indices.push_back(vIndex);
	
	setValue(IRBuilder()->CreateInBoundsGEP(vArray, indices));
}

ArrayAccessExpr::ArrayAccessExpr(Expression* array, Expression* idx)
{
	m_array = array;
	m_idx = idx;
	
	addChild(m_array, true);
	addChild(m_idx, true);
}
/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/SizeofExpr.h>
#include <grove/Module.h>
#include <grove/Valued.h>

#include <grove/types/Type.h>
#include <grove/types/UIntType.h>

#include <grove/exceptions/invalid_type_error.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <util/assertions.h>

ASTNode* SizeofExpr::copy() const
{
	if (getTypeArg() != nullptr)
	{
		return new SizeofExpr(getTypeArg());
	}
	else
	{
		auto expr_copy = getExpressionArg()->copy()->as<Expression *>();
		return new SizeofExpr(expr_copy);
	}
}

Expression* SizeofExpr::getExpressionArg() const
{
	return m_expression_arg;
}

Type* SizeofExpr::getTypeArg() const
{
	return m_type_arg;
}

void SizeofExpr::resolve()
{
	if (getTypeArg() != nullptr && getTypeArg()->isVariadiclySized())
	{
		for (auto size : getTypeArg()->getVariadicSizes())
		{
			if (size->getType()->isIntTy() == false)
			{
				throw invalid_type_error(size, "cannot create variadic array "
										 "with size of type", size->getType());
			}
		}
	}
}

void SizeofExpr::build()
{
	auto target = getModule()->getLLVMModule()->getDataLayout();
	
	llvm::Value* val = nullptr;
	
	if (getTypeArg() != nullptr)
	{
		auto sz = target->getTypeAllocSize(getTypeArg()->getLLVMType());
		val = llvm::ConstantInt::get(getType()->getLLVMType(), sz, false);
		
		if (getTypeArg()->isVariadiclySized())
		{
			for (auto s : getTypeArg()->getVariadicSizes())
			{
				s->build();
				auto s_val = s->castTo(UIntType::get(64));
				
				val = IRBuilder()->CreateMul(val, s_val);
			}
		}
	}
	else
	{
		auto ty = getExpressionArg()->getType()->getLLVMType();
		auto sz = target->getTypeAllocSize(ty);
		val = llvm::ConstantInt::get(getType()->getLLVMType(), sz, false);
		
		if (getExpressionArg()->ASTNode::is<Valued *>())
		{
			auto valued = getExpressionArg()->ASTNode::as<Valued *>();
			auto ele_sz = valued->getSize();
			
			if (ele_sz != nullptr)
			{
				val = IRBuilder()->CreateMul(val, ele_sz);
			}
		}
	}
	
	setValue(val);
}

SizeofExpr::SizeofExpr(Type* typeArg)
{
	assertExists(typeArg, "typeArg cannot be null");
	
	m_type_arg = typeArg;
	
	if (typeArg->isVariadiclySized())
	{
		for (auto s : typeArg->getVariadicSizes())
		{
			addChild(s, true);
		}
	}
	
	setType(UIntType::get(64));
}

SizeofExpr::SizeofExpr(Expression* expr)
{
	m_expression_arg = expr;
	
	addChild(m_expression_arg, true);
	
	setType(UIntType::get(64));
}

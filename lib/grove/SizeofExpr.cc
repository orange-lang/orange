/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
#include <grove/types/NodeType.h>

#include <grove/exceptions/invalid_type_error.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <util/assertions.h>

ASTNode* SizeofExpr::copy() const
{
	return new SizeofExpr(*this);
}

std::vector<ObjectBase**> SizeofExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase**)&m_expression_arg
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> SizeofExpr::getMemberLists()
{
	return defMemberLists();
}

Expression* SizeofExpr::getExpressionArg() const
{
	return m_expression_arg;
}

const Orange::Type* SizeofExpr::getTypeArg() const
{
	return m_type_arg;
}

void SizeofExpr::resolve()
{
	setType(Orange::UIntType::get(getModule(), 64));
	
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
				auto s_val = s->castTo(Orange::UIntType::get(getModule(), 64));
				
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

SizeofExpr::SizeofExpr(const Orange::Type* typeArg)
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
}

SizeofExpr::SizeofExpr(Expression* expr)
{
	m_expression_arg = expr;
	
	addChild(m_expression_arg, true);
}

SizeofExpr::SizeofExpr(const SizeofExpr& other)
{
	if (other.m_expression_arg != nullptr)
	{
		m_expression_arg = (Expression *)other.m_expression_arg->copy();
	}
	else if (other.m_type_arg != nullptr)
	{
		m_type_arg = other.m_type_arg->copyType();
	}
	
	addChild(m_expression_arg);
	
	if (m_type_arg)
	{
		if (m_type_arg->isVariadiclySized())
		{
			for (auto s : m_type_arg->getVariadicSizes())
			{
				addChild(s, true);
			}
		}
		
		if (m_type_arg->is<NodeType *>())
		{
			addChild(m_type_arg->as<NodeType *>());
		}
	}
	
	other.defineCopy(this);
}
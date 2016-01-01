/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/TernaryExpr.h>
#include <grove/Function.h>
#include <grove/Module.h>

#include <grove/types/Type.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

ASTNode* TernaryExpr::copy() const
{
	return new TernaryExpr(*this);
}

std::vector<ObjectBase**> TernaryExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase**)&m_condition,
		(ObjectBase**)&m_true_val,
		(ObjectBase**)&m_false_val
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> TernaryExpr::getMemberLists()
{
	return defMemberLists();
}

Expression* TernaryExpr::getCondition() const
{
	return m_condition;
}

Expression* TernaryExpr::getTrueVal() const
{
	return m_true_val;
}

Expression* TernaryExpr::getFalseVal() const
{
	return m_false_val;
}

void TernaryExpr::resolve()
{
	auto cond_ty = getCondition()->getType();
	auto true_ty = getTrueVal()->getType();
	auto false_ty = getFalseVal()->getType();
	
	assertExists(cond_ty, "condition has no type");
	assertExists(true_ty, "true expression has no type");
	assertExists(false_ty, "false expression has no type");
	
	if (cond_ty->isBoolTy() == false)
	{
		throw code_error(getCondition(), [cond_ty]() -> std::string
			{
				std::stringstream ss;
				ss << "condition of ternary expression is "
				   << cond_ty->getString() << ", expected boolean";
				
				return ss.str();
			});
	}
	
	if (true_ty != false_ty)
	{
		throw code_error(getCondition(), [true_ty, false_ty]() -> std::string
		{
			std::stringstream ss;
			ss << "expressions in ternary statements do not match types "
			   << "(" << true_ty->getString() << " and "
			   << false_ty->getString() << ")";
			
			return ss.str();
		});
	}
	
	setType(true_ty);
}

void TernaryExpr::build()
{
	// Setup blocks
	auto parent_func = findParent<Function *>();
	auto llvm_func = parent_func->getLLVMFunction();
	auto& ctx = getModule()->getLLVMContext();
	
	auto true_block = llvm::BasicBlock::Create(ctx, "trueval", llvm_func,
											   parent_func->getExit());
	auto false_block = llvm::BasicBlock::Create(ctx, "falseval", llvm_func,
												parent_func->getExit());
	auto continue_block = llvm::BasicBlock::Create(ctx, "continue", llvm_func,
												   parent_func->getExit());

	getCondition()->build();
	
	auto vCondition = getCondition()->getValue();
	assertExists(vCondition, "condition generated no value");
	
	auto val = IRBuilder()->CreateAlloca(getType()->getLLVMType());
	IRBuilder()->CreateCondBr(vCondition, true_block, false_block);
	
	IRBuilder()->SetInsertPoint(true_block);
	getTrueVal()->build();
	assertExists(getTrueVal()->getValue(), "true expr generated no value");
	IRBuilder()->CreateStore(getTrueVal()->getValue(), val);
	IRBuilder()->CreateBr(continue_block);
	
	IRBuilder()->SetInsertPoint(false_block);
	getFalseVal()->build();
	assertExists(getFalseVal()->getValue(), "false expr generated no value");
	IRBuilder()->CreateStore(getFalseVal()->getValue(), val);
	IRBuilder()->CreateBr(continue_block);
	
	IRBuilder()->SetInsertPoint(continue_block);
	
	setValue(IRBuilder()->CreateLoad(val));
}

TernaryExpr::TernaryExpr(Expression* condition, Expression* trueval,
						 Expression* falseval)
{
	m_condition = condition;
	m_true_val = trueval;
	m_false_val = falseval;
	
	addChild(condition, true);
	addChild(trueval, true);
	addChild(falseval, true);
}

TernaryExpr::TernaryExpr(const TernaryExpr& other)
{
	m_condition = (Expression *)other.m_condition->copy();
	m_true_val = (Expression *)other.m_true_val->copy();
	m_false_val = (Expression *)other.m_false_val->copy();
	
	addChild(m_condition, true);
	addChild(m_true_val, true);
	addChild(m_false_val, true);
	
	other.defineCopy(this);
}
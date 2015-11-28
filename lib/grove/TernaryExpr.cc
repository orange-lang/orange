/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
	auto condition_copy = getCondition()->copy()->as<Expression *>();
	auto true_val_copy = getTrueVal()->copy()->as<Expression *>();
	auto false_val_copy = getFalseVal()->copy()->as<Expression *>();
	
	return new TernaryExpr(condition_copy, true_val_copy, false_val_copy);
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

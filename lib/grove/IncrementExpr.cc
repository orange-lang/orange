/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/IncrementExpr.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

Expression* IncrementExpr::getExpression() const
{
	return m_expr;
}

ASTNode* IncrementExpr::copy() const
{
	auto expr = m_expr->copy()->as<Expression *>();
	return new IncrementExpr(expr, m_delta, m_preincrement);
}

int IncrementExpr::getDelta() const
{
	return m_delta;
}

bool IncrementExpr::isPreIncrement() const
{
	return m_preincrement == true;
}

bool IncrementExpr::isPostIncrement() const
{
	return m_preincrement == false;
}

void IncrementExpr::resolve()
{
	auto ty = getExpression()->getType();
	assertExists(ty, "Expression has no type.");
	
	if (ty->isIntTy() == false && ty->isFloatingPointTy() == false)
	{
		throw std::runtime_error("cannot increment type");
	}
	
	if (getExpression()->hasPointer() == false)
	{
		throw std::runtime_error("expression is not an lvalue");
	}
	
	setType(ty);
}

void IncrementExpr::build()
{
	getExpression()->build();
	
	auto ptr = getExpression()->getPointer();
	auto val = getExpression()->getValue();
	auto ty = getExpression()->getType();
	
	assertExists(ptr, "Expression has no pointer");
	assertExists(val, "Expression generated no value");
	
	llvm::Value* newVal = nullptr;
	if (ty->isIntTy())
	{
		auto delta = llvm::ConstantInt::get(ty->getLLVMType(), getDelta());
    	newVal = IRBuilder()->CreateAdd(val, delta);
	}
	else if (ty->isFloatingPointTy())
	{
		auto delta = llvm::ConstantFP::get(ty->getLLVMType(), (double)getDelta());
    	newVal = IRBuilder()->CreateFAdd(val, delta);
	}
	
	IRBuilder()->CreateStore(newVal, ptr);
	
	if (isPreIncrement())
	{
		setValue(newVal);
	}
	else
	{
		setValue(val);
	}
}

IncrementExpr::IncrementExpr(Expression* expr, int delta, bool preincrement)
{
	assertExists(expr, "Expr cannot be null");
	
	m_preincrement = preincrement;
	m_expr = expr;
	m_delta = delta;
	
	addChild(expr);
}


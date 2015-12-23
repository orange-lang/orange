/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/DerefExpr.h>

#include <grove/types/Type.h>

#include <grove/exceptions/invalid_type_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

ASTNode* DerefExpr::copy() const
{
	return new DerefExpr(*this);
}

Expression* DerefExpr::getExpression() const
{
	return m_expression;
}

bool DerefExpr::hasPointer() const
{
	return true;
}

llvm::Value* DerefExpr::getPointer() const
{
	return m_expression->getValue();
}

void DerefExpr::resolve()
{
	auto ty = getExpression()->getType();
	assertExists(ty, "Expression has no type");
	
	if (ty->isPointerTy() == false)
	{
		throw invalid_type_error(getExpression(), "can not dereference non-"
								 "pointer type", ty);
	}
	
	setType(ty->getBaseTy());
}

void DerefExpr::build()
{
	getExpression()->build();
	
	auto val = getExpression()->getValue();
	assertExists(val, "Expression has no value.");
	
	setValue(IRBuilder()->CreateLoad(val));
}

DerefExpr::DerefExpr(Expression* expr)
{
	m_expression = expr;
	addChild(m_expression, true);
}

DerefExpr::DerefExpr(const DerefExpr& other)
{
	m_expression = (Expression *)other.m_expression->copy();
	addChild(m_expression, true);
	
	other.defineCopy(this);
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/NegativeExpr.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

Expression* NegativeExpr::getExpression() const
{
	return m_expr;
}

void NegativeExpr::resolve()
{
	auto ty = getExpression()->getType();
	
	if (ty->isPODTy() == false)
	{
		throw std::invalid_argument("can only negate a value that's numeric");
	}
	else if (ty->isIntTy() && ty->isSigned() == false)
	{
		throw std::invalid_argument("cannot negate an unsigned integer.");
	}
	else if (ty->isVoidTy())
	{
		throw std::invalid_argument("cannot negate a void value.");
	}
	
	setType(ty);
}

void NegativeExpr::build()
{
	getExpression()->build();
	assertExists(getExpression()->getValue(), "expression has no value.");
	
	llvm::Value* val = nullptr;
	
	if (getExpression()->getType()->isFloatingPointTy())
	{
		val = IRBuilder()->CreateFNeg(getExpression()->getValue());
	}
	else
	{
		val = IRBuilder()->CreateNeg(getExpression()->getValue());
	}
	
	setValue(val);
}

NegativeExpr::NegativeExpr(Expression* expr)
{
	assertExists(expr, "expr cannot be nullptr.");
	m_expr = expr;
	
	addChild(expr);
}
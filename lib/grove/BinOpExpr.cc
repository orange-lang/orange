/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpExpr.h>
#include <util/assertions.h>
#include <grove/types/Type.h>

bool BinOpExpr::areTypesCompatible() const
{
	if (getLHS()->getType() == getRHS()->getType())
	{
		return true;
	}
	
	// If they're not the same type, determine if we can
	// cast them.
	return areTypesCastable();
}

bool BinOpExpr::areTypesCastable() const
{
	return getLHS()->getType()->isPODTy() && getRHS()->getType()->isPODTy();
}

bool BinOpExpr::requiresCast() const
{
	return getLHS()->getType() != getRHS()->getType();
}

bool BinOpExpr::isFloatingPointOperation() const
{
	return getLHS()->getType()->isFloatingPointTy() ||
    	getRHS()->getType()->isFloatingPointTy();
}

bool BinOpExpr::areOperandsSigned() const
{
	return getLHS()->getType()->isSigned() ||
    	getRHS()->getType()->isSigned();
}

Expression* BinOpExpr::getLHS() const
{
	return m_LHS;
}

Expression* BinOpExpr::getRHS() const
{
	return m_RHS;
}

std::string BinOpExpr::getOperator() const
{
	return m_operator;
}

void BinOpExpr::resolve()
{
	if (areTypesCompatible())
	{
		throw std::invalid_argument("LHS is not compatible with RHS");
	}
}

BinOpExpr::BinOpExpr(Expression* LHS, std::string op, Expression* RHS)
{
	assertExists(LHS, "LHS must not be null.");
	assertExists(RHS, "RHS must not be null.");
	
	if (op == "")
	{
		throw std::invalid_argument("op must not be empty");
	}
	
	m_LHS = LHS;
	m_operator = op;
	m_RHS = RHS;
	
	addChild(LHS);
	addChild(RHS);
}
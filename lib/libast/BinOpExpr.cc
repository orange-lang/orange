/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/BinOpExpr.h>

#include <libast/types/Type.h>

#include <libast/exceptions/binop_error.h>
#include <libast/exceptions/fatal_error.h>

#include <util/assertions.h>

std::vector<ObjectBase**> BinOpExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_LHS,
		(ObjectBase **)&m_RHS
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> BinOpExpr::getMemberLists()
{
	return defMemberLists();
}

bool BinOpExpr::areTypesCompatible() const
{
	if (getLHS()->getType() == getRHS()->getType())
	{
		return true;
	}
	
	if (getLHS()->getType() && getRHS()->getType()
		&& getLHS()->matchesType(getRHS()->getType()))
	{	
		return true;
	}
	
	// If they're not the same type, determine if we can
	// cast them.
	return areTypesCastable();
}

bool BinOpExpr::areTypesCastable() const
{
	if (getLHS()->getType()->isPODTy() && getRHS()->getType()->isPODTy())
	{
		return true;
	}
	
	if ((getLHS()->getType()->isPointerTy() && getRHS()->getType()->isIntTy()) ||
		(getLHS()->getType()->isIntTy() && getRHS()->getType()->isPointerTy()))
	{
		return true;
	}
		
	
	return false;
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

OString BinOpExpr::getOperator() const
{
	return m_operator;
}

void BinOpExpr::resolve()
{
	if (areTypesCompatible() == false)
	{
		throw binop_error(&m_operator, getLHS()->getType(), getOperator(),
						  getRHS()->getType());
	}
}

BinOpExpr::BinOpExpr(Expression* LHS, OString op, Expression* RHS)
{
	assertExists(LHS, "LHS must not be null.");
	assertExists(RHS, "RHS must not be null.");
	
	if (op == "")
	{
		throw fatal_error("op must not be empty");
	}
	
	m_LHS = LHS;
	m_operator = op;
	m_RHS = RHS;
	
	addChild(LHS);
	addChild(RHS);
}
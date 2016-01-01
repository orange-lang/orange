/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ReferenceExpr.h>

#include <grove/types/Type.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

ASTNode* ReferenceExpr::copy() const
{
	return new ReferenceExpr(*this);
}

std::vector<ObjectBase**> ReferenceExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_expression
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> ReferenceExpr::getMemberLists()
{
	return defMemberLists();
}

Expression* ReferenceExpr::getExpression() const
{
	return m_expression;
}

void ReferenceExpr::resolve()
{
	auto ty = getExpression()->getType();
	assertExists(ty, "Expression has no type");
	
	if (getExpression()->hasPointer() == false && ty->isFunctionTy() == false)
	{
		throw code_error(getExpression(), []() -> std::string
			{
				return "cannot get a pointer to expression that is not an "
    				"lvalue";
			});
	}
	
	if (getExpression()->transferrable())
	{
		throw code_error(getExpression(), []() -> std::string
		{
			return "cannot get a pointer to a temporary expression";
		});
	}

	if (ty->isFunctionTy())
	{
		setType(ty->getPointerTo());
	}
	else
	{
    	setType(ty->getPointerTo());
	}
}

void ReferenceExpr::build()
{
	getExpression()->build();
	
	if (getExpression()->getType()->isFunctionTy())
	{
		setValue(getExpression()->getValue());
	}
	else
	{
		auto val = getExpression()->getPointer();
		assertExists(val, "Expression's pointer is null");
	
		setValue(val);
	}
}

ReferenceExpr::ReferenceExpr(Expression* expr)
{
	m_expression = expr;
	addChild(expr, true);
}


ReferenceExpr::ReferenceExpr(const ReferenceExpr& other)
{
	m_expression = (Expression *)other.m_expression->copy();
	addChild(m_expression, true);
	
	other.defineCopy(this);
}
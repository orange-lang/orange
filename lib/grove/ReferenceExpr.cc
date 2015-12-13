/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
	return new ReferenceExpr(getExpression()->copy()->as<Expression *>());
}

Expression* ReferenceExpr::getExpression() const
{
	return m_expression;
}

void ReferenceExpr::resolve()
{
	if (getExpression()->hasPointer() == false)
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
	
	auto ty = getExpression()->getType();
	assertExists(ty, "Expression has no type");
	
	setType(ty->getPointerTo());
}

void ReferenceExpr::build()
{
	auto val = getExpression()->getPointer();
	assertExists(val, "Expression's pointer is null");
	
	setValue(val);
}

ReferenceExpr::ReferenceExpr(Expression* expr)
{
	m_expression = expr;
	addChild(expr, true);
}

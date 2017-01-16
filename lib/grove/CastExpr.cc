/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CastExpr.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

ASTNode* CastExpr::copy() const
{
	return new CastExpr(getType(), getExpression()->copy()->as<Expression *>());
}

Expression* CastExpr::getExpression() const
{
	return m_expression;
}

void CastExpr::resolve()
{
	auto old_ty = getExpression()->getType();
	assertExists(old_ty, "Expression has no type");
	
	/// If this function throws an error, a cast isn't defined.
	old_ty->castOperation(getType());
}

void CastExpr::build()
{
	getExpression()->build();
	
	auto val = getExpression()->getValue();
	assertExists(val, "Expression didn't generate a value");
	
	auto casted = getExpression()->castTo(getType());
	assertExists(casted, "Cast failed");
	
	setValue(casted);
}

CastExpr::CastExpr(Type* ty, Expression* expr)
{
	m_type = ty;
	m_expression = expr;
	
	addChild(m_expression, true);
}
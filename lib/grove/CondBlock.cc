/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CondBlock.h>
#include <grove/Expression.h>

#include <grove/types/Type.h>

#include <grove/exceptions/invalid_type_error.h>

#include <util/assertions.h>

ASTNode* CondBlock::copy() const
{
	auto clone = new CondBlock(m_expr->copy()->as<Expression *>(), m_invert);
	clone->copyStatements(this);
	return clone;
}

void CondBlock::resolve()
{
	assertExists(getExpression()->getType(), "Expression has no type!");
	
	if (getExpression()->getType()->isBoolTy() == false)
	{
		throw invalid_type_error(getExpression(), "expression of condition was "
								 "non-boolean type", getExpression()->getType());
	}
}

Expression* CondBlock::getExpression() const
{
	return m_expr;
}

bool CondBlock::invertCondition() const
{
	return m_invert;
}

CondBlock::CondBlock(Expression* expr, bool invert)
{
	assertExists(expr, "Expression can not be null!");
	
	m_expr = expr;
	m_invert = invert;
	
	addChild(m_expr);
}

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CondBlock.h>
#include <grove/Expression.h>
#include <grove/types/Type.h>
#include <util/assertions.h>

void CondBlock::resolve()
{
	assertExists(getExpression()->getType(), "Expression has no type!");
	
	if (getExpression()->getType()->isBoolTy() == false)
	{
		throw std::invalid_argument("expression must be a boolean");
	}
}

Expression* CondBlock::getExpression() const
{
	return m_expr;
}

CondBlock::CondBlock(Expression* expr)
{
	assertExists(expr, "Expression can not be null!");
	
	m_expr = expr;
	addChild(m_expr);
}

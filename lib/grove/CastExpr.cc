/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
	return new CastExpr(*this);
}

std::vector<ObjectBase**> CastExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_expression
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> CastExpr::getMemberLists()
{
	return defMemberLists();
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

CastExpr::CastExpr(const Type* ty, Expression* expr)
{
	setType(ty);
	m_expression = expr;
	
	addChild(m_expression, true);
}

CastExpr::CastExpr(const CastExpr& other)
{
	setType(other.m_type->copyType());
	m_expression = (Expression *)other.m_expression->copy();
	
	addChild(m_expression, true);
	
	other.defineCopy(this);
}
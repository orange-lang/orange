/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/AccessExpr.h>

#include <util/assertions.h>

ASTNode* AccessExpr::copy() const
{
	auto lhs_copy = getLHS()->copy()->as<Expression *>();
	return new AccessExpr(lhs_copy, getName());
}

Expression* AccessExpr::getLHS() const
{
	return m_LHS;
}

std::string AccessExpr::getName() const
{
	return m_name;
}

Expression* AccessExpr::getAccessed() const
{
	return m_accessed;
}

void AccessExpr::resolve()
{
	auto a_lhs = getLHS()->ASTNode::as<Accessible *>();
	m_accessed = a_lhs->access(getName(), nullptr);
	assertExists(m_accessed, "No member found");
	
	setType(m_accessed->getType());
}

void AccessExpr::build()
{
	getLHS()->build();
	
	setValue(getAccessed()->getValue());
}

bool AccessExpr::isAccessible() const
{
	return (getAccessed()->ASTNode::is<Accessible *>() &&
			getAccessed()->ASTNode::as<Accessible *>()->isAccessible());
}

Expression* AccessExpr::access(std::string name, Type* hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	return getAccessed()->ASTNode::as<Accessible *>()->access(name, hint);
}

AccessExpr::AccessExpr(Expression* LHS, std::string name)
{
	if (name == "")
	{
		throw std::runtime_error("name must not be empty");
	}
	
	m_LHS = LHS;
	m_name = name;
	
	addChild(m_LHS, true);
}
/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/AccessExpr.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/code_error.h>

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

OString AccessExpr::getName() const
{
	return m_name;
}

Expression* AccessExpr::getAccessed() const
{
	return m_accessed;
}

void AccessExpr::resolve()
{
	if (isAccessible() == false)
	{
		throw code_error(m_LHS, []() -> std::string
			{
				return "object is not accessible.";
			});
	}
	
	auto a_lhs = getLHS()->ASTNode::as<Accessible *>();
	m_accessed = a_lhs->access(getName(), nullptr);
	
	if (m_accessed == nullptr)
	{
		auto name = getName();
		throw code_error(m_LHS, [name] () -> std::string
			{
				std::stringstream ss;
				ss << "object does not have accessible member named " <<
					name.str();
				return ss.str();
			});
	}
	
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

Expression* AccessExpr::access(OString name, Type* hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	return getAccessed()->ASTNode::as<Accessible *>()->access(name, hint);
}

AccessExpr::AccessExpr(Expression* LHS, OString name)
{
	if (name == "")
	{
		throw fatal_error("name must not be empty");
	}
	
	m_LHS = LHS;
	m_name = name;
	
	addChild(m_LHS, true);
}
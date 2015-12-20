/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/AccessExpr.h>
#include <grove/Module.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

ASTNode* AccessExpr::copy() const
{
	auto lhs_copy = getLHS()->copy()->as<Expression *>();
	auto copy = new AccessExpr(lhs_copy, getName());
	defineCopy(copy);
	return copy;
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

bool AccessExpr::hasPointer() const
{
	return m_accessed->hasPointer();
}

llvm::Value* AccessExpr::getPointer() const
{
	return m_accessed->getPointer();
}

void AccessExpr::resolve()
{
	getModule()->beginCopy();
	
	if (getLHS()->ASTNode::is<Accessible *>() == false ||
		getLHS()->ASTNode::as<Accessible *>()->isAccessible() == false)
	{
		throw code_error(m_LHS, []() -> std::string
			{
				return "object is not accessible.";
			});
	}
	
	auto a_lhs = getLHS()->ASTNode::as<Accessible *>();
	m_accessed = a_lhs->access(getName(), getLHS());
	
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
	
	addChild(m_accessed);
	getModule()->findDependencies(m_accessed);
	getModule()->resolve(m_accessed);
	
	setType(m_accessed->getType());
	
	getModule()->endCopy();
}

void AccessExpr::build()
{
	getLHS()->build();
	getAccessed()->build();
	
	setValue(getAccessed()->getValue());
}

bool AccessExpr::isAccessible() const
{
	return (getAccessed()->ASTNode::is<Accessible *>() &&
			getAccessed()->ASTNode::as<Accessible *>()->isAccessible());
}

Expression* AccessExpr::access(OString name, const ASTNode* hint) const
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
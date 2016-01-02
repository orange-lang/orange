/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/AccessExpr.h>
#include <grove/Module.h>
#include <grove/IDReference.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

ASTNode* AccessExpr::copy() const
{
	return new AccessExpr(*this);
}

std::vector<ObjectBase**> AccessExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_LHS,
		(ObjectBase **)&m_accessed
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> AccessExpr::getMemberLists()
{
	return defMemberLists();
}

ASTNode* AccessExpr::getLHS() const
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

bool AccessExpr::accessingThis() const
{
	return (getLHS()->is<IDReference *>() &&
			getLHS()->as<IDReference *>()->getName() == "this");
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
	
	m_accessed->setLocation(getLocation());
	addChild(m_accessed);
	getModule()->process(m_accessed);
	
	setType(m_accessed->getType());
	
	getModule()->endCopy();
}

void AccessExpr::build()
{
	getModule()->build(getLHS());
	getModule()->build(getAccessed());
	
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

AccessExpr::AccessExpr(ASTNode* LHS, OString name)
{
	if (name == "")
	{
		throw fatal_error("name must not be empty");
	}
	
	m_LHS = LHS;
	m_name = name;
	
	addChild(m_LHS, true);
}

AccessExpr::AccessExpr(const AccessExpr& other)
{
	m_LHS = (Expression *)other.m_LHS->copy();
	m_name = other.m_name;
	
	addChild(m_LHS, true);
	
	other.defineCopy(this);
}
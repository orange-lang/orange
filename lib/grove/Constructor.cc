/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Constructor.h>
#include <grove/ClassDecl.h>
#include <grove/Parameter.h>

#include <grove/types/Type.h>
#include <grove/types/ReferenceType.h>

#include <util/assertions.h>
#include <util/copy.h>

ClassDecl* Constructor::getClass() const
{
	return m_class;
}

ClassMethod* Constructor::getMethod() const
{
	return m_method;
}

ASTNode* Constructor::copy() const
{
	return new Constructor(*this);
}

std::vector<ObjectBase**> Constructor::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> Constructor::getMemberLists()
{
	return defMemberLists();
}

Genericable* Constructor::createInstance(const Type *type)
{
	if (getClass()->isGeneric() && getMethod() == nullptr)
	{
		throw fatal_error("Generic class can't use a default constructor");
	}
	
	if (getClass()->isGeneric())
	{
		throw fatal_error("Need to create a instance for generic class now");
	}
	
	return Function::createInstance(type);
}

Constructor::Constructor(ClassDecl* theClass, ClassMethod* method,
						 OString name, std::vector<Parameter *> params)
: Function(name, params)
{
	assertExists(theClass, "Constructor created with no class");
	m_class = theClass;
	m_method = method;
}

Constructor::Constructor(const Constructor& other)
: Function(other.m_name, copyVector(other.getParams()))
{
	m_class = other.getClass();
	
	other.defineCopy(this);
}
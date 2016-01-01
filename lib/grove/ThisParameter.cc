/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ThisParameter.h>
#include <grove/ClassDecl.h>
#include <grove/Module.h>

#include <grove/types/Type.h>
#include <grove/types/VoidType.h>
#include <grove/types/NodeType.h>

#include <util/assertions.h>

std::vector<ObjectBase **> ThisParameter::getMemberNodes()
{
	auto list = Parameter::getMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_class
	});
	return list;
}

ASTNode* ThisParameter::copy() const
{
	return new ThisParameter(*this);
}

void ThisParameter::findDependencies()
{
	Parameter::findDependencies();
	addDependency(m_class);
}

void ThisParameter::resolve()
{
	auto ty = m_class->getRefTy();
	setType(ty->getPointerTo());
	
	if (ty->is<NodeType *>())
	{
		getModule()->process(ty->as<NodeType *>());
	}
	
	Parameter::resolve();
}

ThisParameter::ThisParameter(ClassDecl* theClass)
: Parameter(Orange::VoidType::get(theClass->getModule()), "this")
{
	m_class = theClass;
	assertExists(m_class, "Created ThisParameter without a class");
}

ThisParameter::ThisParameter(const ThisParameter& other)
: Parameter(other)
{
	m_class = other.getModule()->tryGetCopy(other.m_class)->as<ClassDecl*>();
}
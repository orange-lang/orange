/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ClassMethod.h>
#include <grove/ClassDecl.h>
#include <grove/Parameter.h>
#include <grove/ThisParameter.h>
#include <grove/Module.h>
#include <grove/BinOpAssign.h>
#include <grove/AccessExpr.h>
#include <grove/MemberVarDecl.h>

#include <grove/types/Type.h>
#include <grove/types/ReferenceType.h>

#include <util/assertions.h>
#include <util/copy.h>

bool ClassMethod::usableFrom(const ASTNode *from) const
{
	if (getProtectionLevel() == ProtectionLevel::PROTECTION_PUBLIC)
	{
		return true;
	}
	
	return (m_class == from->findParent<ClassDecl*>());
}

ProtectionLevel ClassMethod::defaultProtectionLevel() const
{
	return ProtectionLevel::PROTECTION_PUBLIC;
}

void ClassMethod::initialize()
{
	if (getStatic() == false && m_this_param == nullptr)
	{
    	addThisParam();
	}
}

void ClassMethod::findDependencies()
{
	Function::findDependencies();
	
	addDependency(m_class);
}

bool ClassMethod::isConstructor() const
{
	return getName() == m_class->getName();
}

ASTNode* ClassMethod::copy() const
{
	return new ClassMethod(*this);
}

std::vector<ObjectBase**> ClassMethod::getMemberNodes()
{
	auto list = Function::getMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_class,
		(ObjectBase **)&m_this_param
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> ClassMethod::getMemberLists()
{
	return Function::getMemberLists();
}

ClassDecl* ClassMethod::getClass() const
{
	return m_class;
}

Parameter* ClassMethod::getThisParam() const
{
	return m_this_param;
}

void ClassMethod::addThisParam()
{
	m_this_param = new ThisParameter(m_class);
	if (m_params.size() == 0)
	{
		addChild(m_this_param, 0);
	}
	else
	{
		addChild(m_this_param, m_params.at(0), 0);
	}
	
	m_params.insert(m_params.begin(), m_this_param);
}

BinOpAssign* ClassMethod::getInitializerForMember(MemberVarDecl *member) const
{
	auto assigns = findChildren<BinOpAssign *>();
	for (auto assign : assigns)
	{
		getModule()->findDependencies(assign);
		
		// We need to know if this BinOpAssign is assigning to our
		// member. Unfortunately, it may be an AccessExpr (via this.[name])
		// The AccessExpr doesn't know what it is actually accessing
		// by the time findDependencies is called, as a lot of accessing
		// can only be determined during resolve of non-generics.
		//
		// Given that, we have to manually check to see if the assign's
		// LHS is an AccessExpr, and if it's accessing this.memberName
		if (assign->getLHS()->is<AccessExpr *>() == true &&
			(assign->getLHS()->as<AccessExpr *>()->accessingThis() == false ||
			 assign->getLHS()->as<AccessExpr *>()->getName() !=
				member->getName()))
		{
			continue;
		}
		else if (assign->getLHS()->is<AccessExpr *>() == false &&
				 assign->dependsOn(member) == false)
		{
			continue;
		}
		
		return assign;
	}
	
	return nullptr;
}

ClassMethod::ClassMethod(OString name, ClassDecl* theClass,
						 std::vector<Parameter *> params)
: Function(name, params)
{
	assertExists(theClass, "ClassMethod created with no class");
	m_class = theClass;
}

ClassMethod::ClassMethod(const ClassMethod& other)
: Function(other)
{
	if (other.getStatic() == false)
	{
    	m_this_param = getParams().at(0);
	}
	
	m_class = other.getModule()->tryGetCopy(other.m_class)->as<ClassDecl *>();
}
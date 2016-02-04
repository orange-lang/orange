/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/ClassMethod.h>
#include <libast/ClassDecl.h>
#include <libast/Parameter.h>
#include <libast/ThisParameter.h>
#include <libast/Module.h>
#include <libast/BinOpAssign.h>
#include <libast/AccessExpr.h>
#include <libast/MemberVarDecl.h>
#include <libast/IDReference.h>
#include <libast/ExpressionCall.h>
#include <libast/SuperCall.h>

#include <libast/types/Type.h>

#include <libast/exceptions/code_error.h>

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

ExpressionCall* ClassMethod::getSuperCtorCall() const
{
	ExpressionCall* ctor_call = nullptr;
	for (auto stmt : getStatements())
	{
		if (stmt->is<SuperCall*>())
		{
			if (ctor_call != nullptr)
			{
				throw code_error(stmt, ctor_call, []() -> std::string
								 {
									 return "A constructor can only call a "
									 "parents constructor once";
								 });
			}
			
			ctor_call = stmt->as<SuperCall *>();
		}
	}
	
	return ctor_call;
}

void ClassMethod::findDependencies()
{
	Function::findDependencies();
}

void ClassMethod::resolve()
{
	if (isConstructor() && getClass()->getParentClass())
	{
		auto ctor_call = getSuperCtorCall();
		if (ctor_call == nullptr &&
			getClass()->getParentClass()->hasDefaultCtor() == false)
		{
			throw code_error(this, []() -> std::string
							 {
								 return "Class constructor must explicitly "
								 "call a constructor of parent class that "
								 "has no default constructor";
							 });
		}
		else if (ctor_call == nullptr &&
				 getClass()->getParentClass()->getDefaultCtor())
		{
			auto ctor = getClass()->getParentClass()->getDefaultCtor();
			
			std::vector<Expression *> params;
			params.push_back(new IDReference("this"));
			
			auto ctor_call = new ExpressionCall(ctor, params);
			
			if (getStatements().size() == 0)
			{
				addStatement(ctor_call);
			}
			else
			{
				addStatement(ctor_call, getStatements().at(0), 0);
			}
			
			getModule()->process(ctor_call);
		}
	}
	
	Function::resolve();
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

bool ClassMethod::isGeneric() const
{
	return Function::isGeneric() || m_class->isGeneric();
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
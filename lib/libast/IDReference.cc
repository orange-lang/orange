/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/IDReference.h>
#include <libast/Valued.h>
#include <libast/Named.h>
#include <libast/Typed.h>
#include <libast/Function.h>
#include <libast/MemberVarDecl.h>
#include <libast/MemberAccess.h>
#include <libast/ClassDecl.h>
#include <libast/ClassMethod.h>
#include <libast/Module.h>

#include <libast/exceptions/undefined_error.h>
#include <libast/exceptions/fatal_error.h>

#include <util/assertions.h>

OString IDReference::getName() const
{
	return m_name;
}

ASTNode* IDReference::copy() const
{
	return new IDReference(*this);
}

void IDReference::findDependencies()
{
	auto ref = findNamed(getName(), nullptr);
	
	if (ref == nullptr)
	{
		throw undefined_error(&m_name, m_name);
	} 
	else if (ref->as<ASTNode *>()->findParent<Function *>() !=
			 findParent<Function *>())
	{
		throw undefined_error(&m_name, m_name);
	}
	else
	{
		setNode(ref->as<ASTNode *>());
	}
	
	addDependency(getNode()->as<ASTNode *>());
}


IDReference::IDReference(OString name)
{
	if (name == "")
	{
		throw fatal_error("name for id reference was null");
	}

	m_name = name;
}

IDReference::IDReference(const IDReference& other)
{
	m_name = other.m_name;
	other.defineCopy(this);
}
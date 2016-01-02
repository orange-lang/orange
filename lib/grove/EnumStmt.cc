/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/EnumStmt.h>
#include <grove/Value.h>
#include <grove/Module.h>

#include <grove/types/Type.h>
#include <grove/types/EnumType.h>

#include <grove/exceptions/already_defined_error.h>

#include <util/assertions.h>

ASTNode* EnumStmt::copy() const
{
	return new EnumStmt(*this);
}

std::vector<ObjectBase**> EnumStmt::getMemberNodes()
{
	auto list = defMemberNodes();
	
	auto values = std::vector<ObjectBase **>();
	for (auto vp : m_members)
	{
		values.push_back((ObjectBase **)&vp.val);
	}
	
	list.insert(list.end(), values.begin(), values.end());
	return list;
}

std::vector<std::vector<ObjectBase *>*> EnumStmt::getMemberLists()
{
	return defMemberLists();
}

void EnumStmt::resolve()
{
	SearchSettings settings;
	settings.createGeneric = false;
	settings.includeLimit = false;
	
	auto named = findNamed(getName(), nullptr, settings);
	if (named != nullptr && named != this)
	{
		auto base = named->as<CodeBase *>();
		throw already_defined_error(&m_name, base, m_name, false);
	}
}

void EnumStmt::build()
{
	for (auto pair : m_members)
	{
		getModule()->build(pair.val);
	}
}

bool EnumStmt::isAccessible() const
{
	return true;
}

Expression* EnumStmt::access(OString name, const ASTNode* hint) const
{
	auto it = std::find_if(m_members.begin(), m_members.end(),
		[name] (EnumValPair pair) -> bool
		{
			return pair.name == name;
	   	});
	
	if (it == m_members.end())
	{
		return nullptr;
	}
	else
	{
		return (Expression *)it->val->copy();
	}
}

void EnumStmt::addMember(OString name, Value *val)
{
	auto it = std::find_if(m_members.begin(), m_members.end(),
		[name] (EnumValPair pair) -> bool
		{
		   return pair.name == name;
		});
	
	if (it != m_members.end())
	{
		throw already_defined_error(&name, &it->name, name);
	}
	
	if (val != nullptr)
	{
    	val->convert(getType()->getBaseTy());
		
		m_members.push_back(EnumValPair(name, val));
		
		addChild(val, true);
	}
	else if (m_members.size() > 0)
	{
		// Get the next value
		auto pval = m_members.back().val;
		auto nval = pval->addDelta(1);
		
		m_members.push_back(EnumValPair(name, nval));
		
		addChild(nval, true);
	}
	else
	{
		// Get the first val, starting at 0
		auto fval = new Value("0", getType()->getBaseTy());
		m_members.push_back(EnumValPair(name, fval));
		
		addChild(fval, true);	
	}
	
}

EnumStmt::EnumStmt(OString name, Module* mod, const Orange::Type* baseType)
{
	m_name = name;
	
	assertExists(baseType, "baseType cannot be nullptr");
	
	if (baseType->isIntTy() == false)
	{
		throw code_error(&name, [name]() -> std::string
			{
				std::stringstream ss;
				ss << "expected internal type of enum " << name.str()
				   << " to be an integer type";
				
				return ss.str();
			});
	}

	m_base_type = baseType;
	setType(Orange::EnumType::get(mod, m_base_type, false));
}

EnumStmt::EnumStmt(const EnumStmt& other)
{
	m_name = other.m_name;
	m_base_type = other.m_base_type->copyType();
	setType(Orange::EnumType::get(other.getModule(), m_base_type, false));
	
	for (auto pair : m_members)
	{
		addMember(pair.name, (Value *)pair.val->copy());
	}
	
	other.defineCopy(this);
}
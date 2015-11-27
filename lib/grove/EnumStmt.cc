/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/EnumStmt.h>
#include <grove/Value.h>

#include <grove/types/Type.h>
#include <grove/types/EnumType.h>

#include <grove/exceptions/already_defined_error.h>

#include <util/assertions.h>

ASTNode* EnumStmt::copy() const
{
	auto copied_enum = new EnumStmt(getName(), getType()->getBaseTy());
	
	for (auto pair : m_members)
	{
		auto copied_val = pair.val->copy()->as<Value *>();
		copied_enum->addMember(pair.name, copied_val);
	}
	
	return copied_enum;
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
		pair.val->build();
	}
}

bool EnumStmt::isAccessible() const
{
	return true;
}

Expression* EnumStmt::access(OString name, Type *hint) const
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
		return it->val;
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

EnumStmt::EnumStmt(OString name, Type* baseType)
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
	
	setType(EnumType::get(baseType, false));
}
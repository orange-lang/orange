/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/ReferenceType.h>

#include <grove/Typed.h>
#include <grove/Named.h>
#include <grove/TypeProvider.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

OString ReferenceType::getName() const
{
	return m_name;
}

void ReferenceType::resolve()
{
	SearchSettings settings;
	settings.filter = [] (Named *named)
	{
		return named->is<TypeProvider *>();
	};
	
	auto named = findNamed(m_name, nullptr, settings);
	if (named == nullptr)
	{
		auto name = m_name;
		throw code_error(this, [name] () -> std::string
			{
				std::stringstream ss;
				ss << "no type named " << name.str() << " found";
				return ss.str();
			});
	}
	
	assertExists(named->as<Typed *>()->getType(), "node has no type");
	m_type = named->as<Typed *>()->getType()->getLLVMType();
	m_reference = named->as<ASTNode *>();
}

ReferenceType::ReferenceType(OString name)
: NodeType(false)
{
	if (name == "")
	{
		throw fatal_error("name for ReferenceType was empty");
	}
	
	m_name = name;
}
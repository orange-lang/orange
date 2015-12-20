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
#include <grove/ClassDecl.h>
#include <grove/CtorCall.h>
#include <grove/Module.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

OString ReferenceType::getName() const
{
	return m_name;
}

const Type* ReferenceType::getComparisonTy() const
{
	return m_ref_type;
}

std::string ReferenceType::getString() const
{
	return m_name;
}

std::string ReferenceType::getSignature() const
{
	if (m_ref_type == nullptr)
	{
		std::stringstream ss;
    	ss << this;
    	return ss.str();
	}
	else
	{
		return m_ref_type->getSignature();
	}
}

Module* ReferenceType::getModule() const
{
	if (Type::m_module != nullptr)
	{
		return Type::m_module;
	}
	
	if (m_reference != nullptr)
	{
		return m_reference->getModule();
	}
	
	return nullptr;
}

ASTNode* ReferenceType::getReference() const
{
	return m_reference;
}

void ReferenceType::findReference()
{
	SearchSettings settings;
	settings.includeLimit = false;
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
	
	m_reference = named->as<ASTNode *>();
}

void ReferenceType::findDependencies()
{
	if (m_reference == nullptr)
	{
		findReference();
	}
	
	addDependency(m_reference);
}

void ReferenceType::resolve()
{
	if (m_reference == nullptr)
	{
		findReference();
	}
	
	assertExists(m_reference, "reference has no value");
	
	if (m_ref_type == nullptr)
	{
		auto typed = m_reference->as<Typed *>();
    	assertExists(typed->getType(), "node has no type");
    	m_ref_type = typed->getType();
    	m_type = m_ref_type->getLLVMType();
	}
	
	if (m_type == nullptr)
	{
		throw fatal_error("Never got type for ReferenceType!");
	}
		
	Type::m_module = ASTNode::getModule();
}

bool ReferenceType::canInitializeVar() const
{
	return m_reference->is<ClassDecl *>();
}

Expression* ReferenceType::initializeVar() const
{
	if (canInitializeVar() == false)
	{
		return nullptr;
	}
	
	auto class_decl = m_reference->as<ClassDecl *>();
	if (class_decl->hasDefaultCtor() == false)
	{
		return nullptr;
	}
	
	return new CtorCall(m_name, std::vector<Expression *>());
}

ASTNode* ReferenceType::copy() const
{
	ASTNode* clone = nullptr;
	
	if (m_name != "")
	{
		clone = new ReferenceType(m_name);
	}
	else
	{
		const ASTNode* reference = nullptr;
		if (getModule()->hasCopy(m_reference))
		{
			reference = getModule()->getCopy(m_reference);
		}
		else
		{
			reference = m_reference;
		}
		
		if (m_sticky_ref_type)
		{
			clone = new ReferenceType(reference, m_ref_type);
		}
		else
		{
			clone = new ReferenceType(reference);
		}
	}
	
	defineCopy(clone);
	return clone;
}

const Type* ReferenceType::copyType() const
{
	return copy()->as<Type *>();
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

ReferenceType::ReferenceType(const ASTNode* reference)
: NodeType(false)
{
	assertExists(reference, "reference for ReferenceType was emtpy");
	m_reference = (ASTNode *)reference;
	m_location = reference->getLocation();
}

ReferenceType::ReferenceType(const ASTNode* reference, const Type* refType)
: NodeType(false)
{
	assertExists(reference, "reference for ReferenceType was emtpy");
	m_reference = (ASTNode *)reference;
	m_location = reference->getLocation();
	
	assertExists(refType, "refType for ReferenceType was empty");
	m_ref_type = refType;
	m_type = m_ref_type->getLLVMType();
	
	m_sticky_ref_type = true;
}


/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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

const Orange::Type* ReferenceType::getComparisonTy() const
{
	if (Typed::m_type == nullptr)
	{
		return this;
	}
	
	return Typed::m_type;
}

std::string ReferenceType::getString() const
{
	if (Typed::m_type != nullptr)
	{
		return Typed::m_type->getString();
	}
	
	return m_name;
}

std::string ReferenceType::getSignature() const
{
	std::stringstream ss;
	ss << "R" << this;
	return ss.str();
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

bool ReferenceType::hasReference() const
{
	return true;
}

ASTNode* ReferenceType::getReference() const
{
	return m_reference;
}

void ReferenceType::findReference()
{
	SearchSettings settings;
	settings.includeLimit = false;
	settings.createGeneric = false;
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

bool ReferenceType::isAccessible() const
{
	return getReference() && getReference()->is<Accessible *>() &&
		getReference()->as<Accessible*>()->isAccessible();
}
	
Expression* ReferenceType::access(OString name, const ASTNode* hint) const
{
	if (isAccessible() == false) return nullptr;
	return getReference()->as<Accessible*>()->access(name, hint);
}

void ReferenceType::initialize()
{
	if (m_reference == nullptr)
	{
		findReference();
	}
}

void ReferenceType::findDependencies()
{
	addDependency(m_reference);
}

void ReferenceType::resolve()
{
	assertExists(m_reference, "reference has no value");
	
	if (Typed::m_type == nullptr)
	{
		auto typed = m_reference->as<Typed *>();
    	assertExists(typed->getType(), "node has no type");
		setType(typed->getType());
	}
	
	if (Type::m_type == nullptr)
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
			clone = new ReferenceType(reference, Typed::m_type);
		}
		else
		{
			clone = new ReferenceType(reference);
		}
	}
	
	defineCopy(clone);
	return clone;
}

std::vector<ObjectBase**> ReferenceType::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_reference
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> ReferenceType::getMemberLists()
{
	return defMemberLists();
}

const Orange::Type* ReferenceType::copyType() const
{
	return copy()->as<Type *>();
}

void ReferenceType::setType(const Orange::Type* ty)
{
	if (ty->is<ReferenceType *>())
	{
		throw fatal_error("Trying to create a reference to a reference");
	}
	
	Typed::setType(ty);
	
	Type::m_type = Typed::m_type->getLLVMType();
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

ReferenceType::ReferenceType(const ASTNode* reference,
							 const Orange::Type* refType)
: NodeType(false)
{
	assertExists(reference, "reference for ReferenceType was emtpy");
	m_reference = (ASTNode *)reference;
	m_location = reference->getLocation();
	
	assertExists(refType, "refType for ReferenceType was empty");
	setType(refType);
	
	m_sticky_ref_type = true;
}


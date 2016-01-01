/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/ClassType.h>

#include <llvm/IR/DerivedTypes.h>

ClassType::ClassType(const OString& name, std::vector<const Type *> members)
: Type(false), m_name(name)
{
	m_members = members;
	
	std::vector<llvm::Type*> elements;
	for (auto member : m_members)
	{
		elements.push_back(member->getLLVMType());
	}
	
	m_type = llvm::StructType::create(*m_context, elements, m_name.str());
}

const Orange::Type* ClassType::copyType() const
{
	std::vector<const Orange::Type*> members;
	for (auto& member : m_members)
	{
		members.push_back(member->copyType());
	}
	
	return ClassType::get(getModule(), m_name, members);
}

std::string ClassType::getSignature(const OString& name,
									const std::vector<const Type *> members)
{
	std::stringstream ss;
	ss << "T" << members.size();
	for (auto member : members)
	{
		ss << member->getSignature();
	}
	return ss.str();
}

bool ClassType::isClassTy() const
{
	return true;
}

bool ClassType::isAggTy() const
{
	return true;
}

const Orange::Type* ClassType::replaceMember(const Orange::Type* member,
											 const Orange::Type* with)
const
{
	std::vector<const Type*> new_members;
	for (auto old_member : m_members)
	{
		if (old_member == member)
		{
			new_members.push_back(with);
		}
		else
		{
			new_members.push_back(old_member);
		}
	}
	
	return ClassType::get(m_module, m_name, new_members);
}

std::vector<const Orange::Type*> ClassType::getMemberTys() const
{
	return m_members;
}

std::string ClassType::getString() const
{
	std::stringstream ss;
	ss << "class<";
	
	for (unsigned int i = 0; i < m_members.size(); i++)
	{
		ss << m_members.at(i)->getString();
		
		if (i + 1 < m_members.size())
		{
			ss << ", ";
		}
	}
	
	ss << ">";
	return ss.str();
}

std::string ClassType::getSignature() const
{
	return getSignature(m_name, m_members);
}

ClassType* ClassType::get(Module* mod, const OString& name,
						  std::vector<const Type *> members)
{
	auto full_name = "class." + name;
	
	for (auto member : members)
	{
		if (member == nullptr)
		{
			throw fatal_error("class type created with null member");
		}
		else if (member->isVoidTy())
		{
			throw fatal_error("class type created with void member");
		}
		else if (member->isVarTy())
		{
			throw fatal_error("class type created with var member");
		}
	}
	
	auto sig = getSignature(full_name, members);
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<ClassType *>();
	}
	
	ClassType* ty = new ClassType(full_name, members);
	define(mod, sig, ty);
	
	return ty;
}
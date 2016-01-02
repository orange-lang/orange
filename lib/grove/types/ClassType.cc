/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/ClassType.h>

#include <grove/ClassDecl.h>

#include <llvm/IR/DerivedTypes.h>

Orange::ClassType::ClassType(ClassDecl* the_class, std::vector<const Type *> members)
: Type(false), m_class(the_class)
{
	m_members = members;
	
	std::vector<llvm::Type*> elements;
	for (auto member : m_members)
	{
		elements.push_back(member->getLLVMType());
	}
	
	m_type = llvm::StructType::create(*m_context, elements,
									  the_class->getName().str());
}

const Orange::Type* Orange::ClassType::copyType() const
{
	std::vector<const Orange::Type*> members;
	for (auto& member : m_members)
	{
		members.push_back(member->copyType());
	}
	
	return ClassType::get(getModule(), m_class, members);
}

std::string Orange::ClassType::getSignature(const ClassDecl* the_class,
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

bool Orange::ClassType::isClassTy() const
{
	return true;
}

bool Orange::ClassType::isAggTy() const
{
	return true;
}

const Orange::Type* Orange::ClassType::replaceMember(const Orange::Type* member,
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
	
	return ClassType::get(m_module, m_class, new_members);
}

std::vector<const Orange::Type*> Orange::ClassType::getMemberTys() const
{
	return m_members;
}

std::string Orange::ClassType::getString() const
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

std::string Orange::ClassType::getSignature() const
{
	return getSignature(m_class, m_members);
}

Orange::ClassType* Orange::ClassType::get(Module* mod, ClassDecl* the_class,
						  std::vector<const Type *> members)
{
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
	
	auto sig = getSignature(the_class, members);
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<ClassType *>();
	}
	
	ClassType* ty = new ClassType(the_class, members);
	define(mod, sig, ty);
	
	return ty;
}
/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/ClassType.h>

#include <libast/ClassDecl.h>
#include <libast/Valued.h>

#include <llvm/IR/DerivedTypes.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>

static llvm::Value* ClassCast(void* irBuilder, Valued* val,
							  const Orange::Type* from,
							  const Orange::Type* to)
{
	if (val->hasPointer() == false)
	{
		throw fatal_error("Should not have got here");
	}
	
	LLVMBuilder* IRB = (LLVMBuilder *)irBuilder;
	auto cast = IRB->CreateBitCast(val->getPointer(),
								   to->getLLVMType()->getPointerTo());
	return IRB->CreateLoad(cast);
}

Orange::ClassType::ClassType(ClassDecl* the_class)
: Type(false), m_class(the_class)
{
	std::stringstream name;
	name << "class." << the_class->getName().str();
	
	m_type = llvm::StructType::create(*m_context, name.str());
	m_opaque = true;
	
	defineCast(typeid(ClassType), llvm::Instruction::CastOps::BitCast,
			   ClassCast);
}

Orange::ClassType::ClassType(ClassDecl* the_class,
							 std::vector<const Type *> members)
: Type(false), m_class(the_class)
{
	m_members = members;
	
	std::vector<llvm::Type*> elements;
	for (auto member : m_members)
	{
		elements.push_back(member->getLLVMType());
	}
	
	std::stringstream name;
	name << "class." << the_class->getName().str();
	
	m_type = llvm::StructType::create(*m_context, elements,
									  name.str());
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
									const std::vector<const Type *> members,
									bool opaque)
{
	std::stringstream ss;
	
	if (opaque)
	{
		ss << "O" << the_class;
	}
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

bool Orange::ClassType::hasReference() const
{
	return true;
}

ASTNode* Orange::ClassType::getReference() const
{
	return m_class;
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

void Orange::ClassType::specifyMembers(std::vector<const Type *> members)
{
	if (m_opaque == false)
	{
		throw fatal_error("Type is not opaque");
	}
	
	m_members = members;
	
	std::vector<llvm::Type*> elements;
	for (auto member : m_members)
	{
		elements.push_back(member->getLLVMType());
	}
	
	auto struct_ty = (llvm::StructType *)m_type;
	struct_ty->setBody(elements);
}

std::vector<const Orange::Type*> Orange::ClassType::getMemberTys() const
{
	return m_members;
}

std::string Orange::ClassType::getString() const
{
	return m_class->getName();
}

std::string Orange::ClassType::getSignature() const
{
	return getSignature(m_class, m_members, m_opaque);
}

Orange::ClassType* Orange::ClassType::get(Module* mod, ClassDecl* the_class)
{
	std::vector<const Type*> members;
	
	auto sig = getSignature(the_class, members, true);
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<ClassType *>();
	}
	
	ClassType* ty = new ClassType(the_class);
	define(mod, sig, ty);
	
	return ty;
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
	
	auto sig = getSignature(the_class, members, false);
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<ClassType *>();
	}
	
	ClassType* ty = new ClassType(the_class, members);
	define(mod, sig, ty);
	
	return ty;
}
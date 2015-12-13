/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/MemberAccess.h>
#include <grove/MemberVarDecl.h>
#include <grove/ClassDecl.h>
#include <grove/Valued.h>
#include <grove/ASTNode.h>
#include <grove/Module.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

ASTNode* MemberAccess::copy() const
{
	return new MemberAccess(m_class, m_valued, m_name);
}

const ClassDecl* MemberAccess::getClass() const
{
	return m_class;
}

const Valued* MemberAccess::getValued() const
{
	return m_valued;
}

const MemberVarDecl* MemberAccess::getMember() const
{
	return m_member;
}

const OString& MemberAccess::getName() const
{
	return m_name;
}

bool MemberAccess::hasPointer() const
{
	return true;
}

llvm::Value* MemberAccess::getPointer() const
{
	return m_value;
}

llvm::Value* MemberAccess::getValue() const
{
	return IRBuilder()->CreateLoad(m_value);
}

bool MemberAccess::isAccessible() const
{
	return m_member->isAccessible();
}

Expression* MemberAccess::access(OString name, const ASTNode *hint) const
{
	return m_member->access(name, this);
}

void MemberAccess::findDependencies()
{
	ASTNode::findDependencies();
	
	addDependency((ASTNode *)m_class);
	addDependency(m_member);
	addDependency(m_valued->as<ASTNode *>());
}

void MemberAccess::resolve()
{
	setType(m_member->getType());
}

void MemberAccess::build()
{
	auto offset = getMember()->getOffset();
	
	std::vector<llvm::Value *> offsets;
	offsets.push_back(llvm::ConstantInt::get(getModule()->getLLVMContext(),
											 llvm::APInt(32, 0)));
	offsets.push_back(llvm::ConstantInt::get(getModule()->getLLVMContext(),
											 llvm::APInt(32, offset)));
	
	m_value = IRBuilder()->CreateInBoundsGEP(m_valued->getPointer(), offsets);
}

MemberAccess::MemberAccess(const ClassDecl* classDecl, Valued* valued,
						   const OString& name)
: m_name(name)
{
	if (name == "")
	{
		throw fatal_error("MemberAccess ctor called with empty name");
	}
	
	assertExists(classDecl, "MemberAccess ctor called with no ClassDecl");
	assertExists(valued, "MemberAccess ctor called with no Valued");
	
	m_class = classDecl;
	m_valued = valued;
	m_member = m_class->getMember(name);
	
	if (m_member == nullptr)
	{
		throw code_error((ASTNode *)classDecl,
			[&name, classDecl] () -> std::string
			{
				std::stringstream ss;
				ss << "Object of class " << classDecl->getName().str()
				   << " has no member " << name.str();
				return ss.str();
			});
	}
}

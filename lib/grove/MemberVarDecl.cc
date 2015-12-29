/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/MemberVarDecl.h>
#include <grove/ClassDecl.h>
#include <grove/Expression.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

ProtectionLevel MemberVarDecl::defaultProtectionLevel() const
{
	return ProtectionLevel::PROTECTION_PUBLIC;
}

ASTNode* MemberVarDecl::copy() const
{
	return new MemberVarDecl(*this);
}

llvm::Value* MemberVarDecl::getValue() const
{
	throw fatal_error("MemberVarDecl::getValue used directly!");
}

llvm::Value* MemberVarDecl::getPointer() const
{
	throw fatal_error("MemberVarDecl::getPointer used directly!");
}

unsigned int MemberVarDecl::getOffset() const
{
	auto parentClass = findParent<ClassDecl *>();
	assertExists(parentClass, "couldn't find a parent class for "
				 "MemberVarDecl");
	
	auto&& members = parentClass->getMembers();
	auto it = std::find(members.begin(), members.end(), this);

	if (it == members.end())
	{
		throw fatal_error("couldn't find member's offset in parent");
	}
	
	return (unsigned int)std::distance(members.begin(), it);
}

void MemberVarDecl::build()
{
	// Do nothing.
}

MemberVarDecl::MemberVarDecl(const Type* type, OString name,
							 Expression* expression)
: VarDecl(type, name, expression)
{
	// Do nothing.
}

MemberVarDecl::MemberVarDecl(const MemberVarDecl& other)
: VarDecl(other.m_type->copyType(), other.m_name,
		  (Expression *)other.getExpression()->copy())
{
	other.defineCopy(this);
}
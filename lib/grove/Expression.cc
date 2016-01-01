/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Expression.h>
#include <grove/types/Type.h>
#include <util/assertions.h>

#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>

llvm::Value* Expression::castTo(const Orange::Type *ty) const
{
	assertExists(ty, "type must exist.");
	assertExists(getType(), "expression does not have a type.");
	
	return getType()->cast(IRBuilder(), (Valued *)this, ty);
}

llvm::Value* Expression::castTo(Expression *expr) const
{
	assertExists(expr, "expr must exist.");
	
	auto expr_ty = expr->getType();
	return castTo(expr_ty);
}

ASTNode* Expression::copy() const
{
	throw fatal_error("Cannot copy generic Expression");
	return nullptr;
}

std::vector<ObjectBase**> Expression::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> Expression::getMemberLists()
{
	return defMemberLists();
}

bool Expression::isConstant() const
{
	return false;
}
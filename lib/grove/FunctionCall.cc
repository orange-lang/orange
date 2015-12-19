/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/FunctionCall.h>
#include <grove/Named.h>

#include <grove/types/Type.h>
#include <grove/types/FunctionType.h>
#include <grove/types/IntType.h>
#include <grove/types/UIntType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/VarType.h>
#include <grove/types/ArrayType.h>
#include <grove/types/PointerType.h>

#include <grove/exceptions/undefined_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

OString FunctionCall::getName() const
{
	return m_name;
}

FunctionType* FunctionCall::expectedFunctionTy() const
{
	auto ty_list = std::vector<Type *>();
	for (auto arg : m_args)
	{
		// Cast arrays to pointers so we can pass-by-reference
		if (arg->getType()->isArrayTy())
		{
			ty_list.push_back(PointerType::get(getModule(),
											   arg->getType()->getBaseTy()));
			continue;
		}
		
		ty_list.push_back(arg->getType());
	}
	
	// Put a wildcard on the return type.
	return FunctionType::get(getModule(), VarType::get(getModule()), ty_list);
}

ASTNode* FunctionCall::copy() const
{
	return new FunctionCall(getName(), copyVector(getArgs()));
}

void FunctionCall::findDependencies()
{
	ASTNode::findDependencies();
	
	auto named = findAllNamed(getName());
	for (auto n : named)
	{
		addDependency(n->as<ASTNode *>());
	}
}

void FunctionCall::findNode()
{
	auto def = findNamed(getName(), expectedFunctionTy());
	if (def == nullptr)
	{
		throw undefined_error(&m_name, m_name);
	}
	
	// Determine type
	setExpr(def->as<ASTNode *>());
}

void FunctionCall::resolve()
{
	if (getExpr() == nullptr)
	{
		findNode();
	}
	
	ExpressionCall::resolve();
}

FunctionCall::FunctionCall(OString name, std::vector<Expression *> args)
: ExpressionCall(args)
{
	if (name == "")
	{
		throw fatal_error("name of function call was empty");
	}

	m_name = name;
}

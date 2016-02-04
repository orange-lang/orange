/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/FunctionCall.h>
#include <libast/Named.h>
#include <libast/Function.h>
#include <libast/ExternFunction.h>
#include <libast/VarDecl.h>

#include <libast/types/Type.h>
#include <libast/types/FunctionType.h>
#include <libast/types/IntType.h>
#include <libast/types/UIntType.h>
#include <libast/types/DoubleType.h>
#include <libast/types/VarType.h>
#include <libast/types/ArrayType.h>
#include <libast/types/PointerType.h>

#include <libast/exceptions/undefined_error.h>
#include <libast/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

OString FunctionCall::getName() const
{
	return m_name;
}

ASTNode* FunctionCall::copy() const
{
	return new FunctionCall(*this);
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
	SearchSettings settings;
	settings.filter = [this](Named* named) -> bool
	{
		if (named->is<ExternFunction *>() == true ||
			named->is<VarDecl *>())
		{
			return true;
		}
		
		if (named->is<Function *>() == false)
		{
			return false;
		}
		
		auto func = named->as<Function *>();
		return func->getParams().size() == this->getArgs().size();
	};
	
	auto def = findNamed(getName(), expectedFunctionTy(), settings);
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

FunctionCall::FunctionCall(const FunctionCall& other)
: ExpressionCall(copyVector(other.getArgs()))
{
	m_name = other.m_name;
	other.defineCopy(this);
}
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
#include <util/assertions.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

std::string FunctionCall::getName() const
{
	return m_name;
}

std::vector<Expression *> FunctionCall::getArgs() const
{
	return m_args;
}

llvm::Function* FunctionCall::getFunction() const
{
	// Determine type
	auto named = dynamic_cast<Valued *>(findNamed(getName()));
	assertExists(named, "Couldn't find function");
	
	auto value = named->getValue();
	
	if (llvm::isa<llvm::Function>(value) == false)
	{
		throw std::invalid_argument("Object did not contain a function");
	}
	
	return (llvm::Function *)value;
}

void FunctionCall::resolve()
{
	// Determine type
	auto named = dynamic_cast<Typed *>(findNamed(getName()));
	assertExists(named, "Couldn't find function");
	
	auto ty = named->getType();
	if (ty == nullptr || ty->isFunctionTy() == false)
	{
    	assertExists(ty, "Object isn't a function.");
	}
	
	auto func_ty = dynamic_cast<FunctionType*>(ty);
	setType(func_ty->getReturnTy());
}

void FunctionCall::build()
{
	for (auto arg : m_args)
	{
		arg->build();
	}
	
	IRBuilder()->CreateCall(getFunction());
}

FunctionCall::FunctionCall(std::string name, std::vector<Expression *> args)
{
	if (name == "")
	{
		throw std::invalid_argument("name cannot be empty");
	}
	
	for (auto arg : args)
	{
		addChild(arg, true);
	}
	
	m_name = name;
	m_args = args;
}
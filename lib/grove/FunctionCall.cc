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

FunctionType* FunctionCall::getFunctionTy() const
{
	auto named = dynamic_cast<Typed *>(findNamed(getName()));
	assertExists(named, "Couldn't find function");
	
	auto ty = named->getType();
	if (ty == nullptr || ty->isFunctionTy() == false)
	{
		assertExists(ty, "Object isn't a function.");
	}
	
	auto func_ty = dynamic_cast<FunctionType*>(ty);
	return func_ty;
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
	
	if (m_args.size() != func_ty->getArgs().size())
	{
		throw std::invalid_argument("function args != caller args");
	}
	
	setType(func_ty->getReturnTy());
}

void FunctionCall::build()
{
	std::vector<llvm::Value *> llvm_args;
	
	auto func_ty = getFunctionTy();
	for (unsigned int i = 0; i < m_args.size(); i++)
	{
		auto param_ty = func_ty->getArgs()[i];
		
		auto arg = m_args[i];
		arg->build();
	
		// Cast the argument if it doesn't match the parameter.
		if (arg->getType() != param_ty)
		{
			llvm_args.push_back(arg->castTo(param_ty));
		}
		else
		{
			llvm_args.push_back(arg->getValue());
		}
	}
	
	auto res = IRBuilder()->CreateCall(getFunction(), llvm_args);
	setValue(res);
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
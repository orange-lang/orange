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

#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

OString FunctionCall::getName() const
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
	auto valued = findNamed(getName(), expectedFunctionTy())->as<Valued *>();
	auto value = valued->getValue();
	assertExists(value, "value did not exist");

	if (llvm::isa<llvm::Function>(value) == false)
	{
		throw std::invalid_argument("Object did not contain a function");
	}

	return (llvm::Function *)value;
}

FunctionType* FunctionCall::getFunctionTy() const
{
	auto typed = findNamed(getName(), expectedFunctionTy())->as<Typed *>();
	auto ty = typed->getType();

	if (ty == nullptr || ty->isFunctionTy() == false)
	{
		assertExists(ty, "Object isn't a function.");
	}

	return ty->as<FunctionType*>();
}

FunctionType* FunctionCall::expectedFunctionTy() const
{
	auto ty_list = std::vector<Type *>();
	for (auto arg : m_args)
	{
		// Cast arrays to pointers so we can pass-by-reference
		if (arg->getType()->isArrayTy())
		{
			ty_list.push_back(PointerType::get(arg->getType()->getBaseTy()));
			continue;
		}
		
		ty_list.push_back(arg->getType());
	}
	
	// Put a wildcard on the return type.
	return FunctionType::get(VarType::get(), ty_list);
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

void FunctionCall::resolve()
{
	auto def = findNamed(getName(), expectedFunctionTy());
	if (def == nullptr)
	{
		throw undefined_error(&m_name, m_name);
	}
	
	// Determine type
	auto typed = def->as<Typed *>();
	auto ty = typed->getType();

	if (ty == nullptr || ty->isFunctionTy() == false)
	{
    	assertExists(ty, "Object isn't a function.");
	}

	auto func_ty = ty->as<FunctionType*>();

	if (!func_ty->isVarArg() && m_args.size() != func_ty->getArgs().size())
	{
		throw std::invalid_argument("function args != caller args");
	}
	else if (func_ty->isVarArg() && m_args.size() < func_ty->getArgs().size())
	{
		throw std::invalid_argument("not enough arguments to call vaarg func");
	}

	setType(func_ty->getReturnTy());
}

void FunctionCall::build()
{
	std::vector<llvm::Value *> llvm_args;

	auto func_ty = getFunctionTy();
	auto num_args = func_ty->getArgs().size();
	
	for (unsigned int i = 0; i < num_args; i++)
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
	
	// Add remaining arguments if it is vaarg.
	for (unsigned int i = num_args; i < m_args.size(); i++)
	{
		auto arg = m_args[i];
		arg->build();
		
		auto arg_ty = arg->getType();
		
		// To meet with C calling conventials, arugments that are in the
		// "variable argument" section of the argument list are upcasted
		// in certain conditions:
		// 	- integers lower than 32 bits are casted to int32
		// 	- floats are casted to doubles.
		if (arg_ty->isIntTy() && arg_ty->getIntegerBitWidth() < 32)
		{
			if (arg_ty->isSigned())
			{
    			llvm_args.push_back(arg->castTo(IntType::get(32)));
			}
			else
			{
    			llvm_args.push_back(arg->castTo(UIntType::get(32)));
			}
		}
		else if (arg_ty->isFloatTy())
		{
			llvm_args.push_back(arg->castTo(DoubleType::get()));
		}
		else
		{
			llvm_args.push_back(arg->getValue());
		}
	}

	auto res = IRBuilder()->CreateCall(getFunction(), llvm_args);
	setValue(res);
}

FunctionCall::FunctionCall(OString name, std::vector<Expression *> args)
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

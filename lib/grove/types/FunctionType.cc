/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/FunctionType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

FunctionType::FunctionType(Type* retType, std::vector<Type*> args, bool vaarg)
: Type(false)
{
	if (retType == nullptr)
	{
		throw std::invalid_argument("retType must not be null.");
	}

	for (auto arg : args)
	{
		if (arg == nullptr)
		{
			throw std::invalid_argument("must args must not be null.");
		}
	}

	m_ret_type = retType;
	m_args = args;

	std::vector<llvm::Type *> params;
	for (auto ty : args)
	{
		params.push_back(ty->getLLVMType());
	}
	
	m_var_arg = vaarg;

	m_type = llvm::FunctionType::get(retType->getLLVMType(), params, vaarg);
}

std::string FunctionType::getSignature(Type* retType, std::vector<Type*> args,
									   bool vaarg)
{
	if (retType == nullptr)
	{
		throw std::invalid_argument("retType must not be null.");
	}

	std::stringstream ss;
	ss << "_" << retType->getSignature();

	for (unsigned int i = 0; i < args.size(); i++)
	{
		if (args[i] == nullptr)
		{
			throw std::invalid_argument("every argument must not be null");
		}

		ss << args[i]->getSignature();
	}
	
	if (vaarg)
	{
		ss << "$";
	}

	return ss.str();
}

std::string FunctionType::getSignature() const
{
	return FunctionType::getSignature(m_ret_type, m_args, m_var_arg);
}

bool FunctionType::isSigned() const
{
	return getReturnTy()->isSigned();
}

bool FunctionType::isFunctionTy() const
{
	return true;
}

bool FunctionType::isVarArg() const
{
	return m_var_arg;
}

Type* FunctionType::getBaseTy() const
{
	return m_ret_type;
}

Type* FunctionType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

Type* FunctionType::getReturnTy() const
{
	return m_ret_type;
}

std::vector<Type *> FunctionType::getArgs() const
{
	return m_args;
}

FunctionType* FunctionType::get(Type *retType, std::vector<Type *> args,
								bool vaarg)
{
	if (retType == nullptr)
	{
		throw std::invalid_argument("retType must not be null.");
	}

	for (auto arg : args)
	{
		if (arg == nullptr)
		{
			throw std::invalid_argument("must args must not be null.");
		}
	}

	std::string signature = getSignature(retType, args, vaarg);
	auto defined = getDefined(signature);

	if (defined != nullptr)
	{
		return defined->as<FunctionType *>();
	}

	auto ty = new FunctionType(retType, args, vaarg);
	define(signature, ty);

	return ty;
}

/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/FunctionType.h>

#include <libast/exceptions/fatal_error.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

Orange::FunctionType::FunctionType(const Type* retType,
								   std::vector<const Type*> args, bool vaarg)
: Type(false)
{
	if (retType == nullptr)
	{
		throw fatal_error("retType was null");
	}

	for (auto arg : args)
	{
		if (arg == nullptr)
		{
    		throw fatal_error("argument in args was null");
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
	
	for (auto ty : args)
	{
		if (ty->isVarTy())
		{
			m_type = llvm::Type::getVoidTy(*m_context);
			return;
		}
	}

	m_type = llvm::FunctionType::get(retType->getLLVMType(), params, vaarg);
}

llvm::Type* Orange::FunctionType::getLLVMType() const
{
	std::vector<llvm::Type *> params;
	for (auto ty : m_args)
	{
		params.push_back(ty->getLLVMType());
	}
	
	return llvm::FunctionType::get(m_ret_type->getLLVMType(), params,
								   m_var_arg);
}

const Orange::Type* Orange::FunctionType::copyType() const
{
	std::vector<const Orange::Type*> args;
	for (auto& arg : m_args)
	{
		args.push_back(arg->copyType());
	}
	
	return Orange::FunctionType::get(getModule(), m_ret_type->copyType(),
							 args, m_var_arg);
}

std::string Orange::FunctionType::getString() const
{
	std::stringstream ss;
	ss << "def(";
	
	for (unsigned int i = 0; i < m_args.size(); i++)
	{
		ss << m_args[i]->getString();
		
		if (i + 1 < m_args.size())
		{
			ss << ", ";
		}
	}
	
	ss << ") ->" << m_ret_type->getString();
	return ss.str();
}

std::string Orange::FunctionType::getSignature(const Orange::Type* retType,
									   std::vector<const Orange::Type*> args,
									   bool vaarg)
{
	if (retType == nullptr)
	{
		throw fatal_error("retType was null");
	}

	std::stringstream ss;
	ss << retType->getSignature();

	for (unsigned int i = 0; i < args.size(); i++)
	{
		if (args[i] == nullptr)
		{
    		throw fatal_error("argument in args was null");
		}

		ss << args[i]->getSignature();
	}
	
	if (args.size() == 0)
	{
		ss << "v";
	}
	
	if (vaarg)
	{
		ss << "V";
	}

	return ss.str();
}

std::string Orange::FunctionType::getSignature() const
{
	return Orange::FunctionType::getSignature(m_ret_type, m_args, m_var_arg);
}

bool Orange::FunctionType::isSigned() const
{
	return getReturnTy()->isSigned();
}

bool Orange::FunctionType::isFunctionTy() const
{
	return true;
}

bool Orange::FunctionType::isVarArg() const
{
	return m_var_arg;
}

const Orange::Type* Orange::FunctionType::getBaseTy() const
{
	return m_ret_type;
}

const Orange::Type* Orange::FunctionType::getRootTy() const
{
	return getBaseTy()->getRootTy();
}

const Orange::Type* Orange::FunctionType::getReturnTy() const
{
	return m_ret_type;
}

std::vector<const Orange::Type *> Orange::FunctionType::getArgs() const
{
	return m_args;
}

Orange::FunctionType* Orange::FunctionType::get(Module* mod,
												const Orange::Type* retType,
												std::vector<const Orange::Type *> args,
												bool vaarg)
{
	if (retType == nullptr)
	{
		throw fatal_error("retType was null");
	}

	for (auto arg : args)
	{
		if (arg == nullptr)
		{
    		throw fatal_error("argument in args was null");
		}
		
		if (arg->getLLVMType()->isVoidTy() && arg->isVarTy() == false)
		{
			throw fatal_error("adding void argument to function");
		}
	}

	std::string signature = getSignature(retType, args, vaarg);
	auto defined = getDefined(mod, signature);

	if (defined != nullptr)
	{
		return defined->as<FunctionType *>();
	}

	auto ty = new FunctionType(retType, args, vaarg);
	define(mod, signature, ty);

	return ty;
}

/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ExternFunction.h>
#include <grove/Parameter.h>
#include <grove/Module.h>

#include <grove/types/FunctionType.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

std::vector<const Type *> ExternFunction::getParamTys() const
{
	std::vector<const Type *> tys;
	
	for (auto param : getParams())
	{
		tys.push_back(param->getType());
	}
	
	return tys;
}

std::vector<Parameter *> ExternFunction::getParams() const
{
	return m_params;
}

ASTNode* ExternFunction::copy() const
{
	return new ExternFunction(getName(), copyVector(getParams()),
							  m_ret_type->copyType(), m_vararg);
}

void ExternFunction::resolve()
{
	setType(FunctionType::get(getModule(), m_ret_type, getParamTys(),
							  m_vararg));
}

void ExternFunction::build()
{
	auto func_ty = (llvm::FunctionType *)getType()->getLLVMType();
	auto linkage = llvm::Function::ExternalLinkage;
	
	auto func = llvm::Function::Create(func_ty, linkage, getName().str(),
									   getModule()->getLLVMModule());
	
	setValue(func);
}

ExternFunction::ExternFunction(OString name, std::vector<Parameter *> params,
							   const Type* retType, bool vararg)
{
	if (name == "")
	{
		throw fatal_error("name of function was empty");
	}
	
	for (auto param : params)
	{
		assertExists(param, "Param must not be null");
		assertExists(param->getType(), "Param must have type.");
	}
	
	assertExists(retType, "return type must exist");
	
	m_name = name;
	m_params = params;
	m_ret_type = retType;
	m_vararg = vararg;
	
}
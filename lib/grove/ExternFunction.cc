/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/FunctionType.h>

#include <grove/ExternFunction.h>
#include <grove/Parameter.h>
#include <util/assertions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <grove/Module.h>


std::vector<Type *> ExternFunction::getParamTys() const
{
	std::vector<Type *> tys;
	
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

void ExternFunction::build()
{
	auto func_ty = (llvm::FunctionType *)getType()->getLLVMType();
	auto linkage = llvm::Function::ExternalLinkage;
	
	auto func = llvm::Function::Create(func_ty, linkage, getName(),
									   getModule()->getLLVMModule());
	
	setValue(func);
}

ExternFunction::ExternFunction(std::string name, std::vector<Parameter *> params,
							   Type* retType, bool vararg)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be empty.");
	}
	
	for (auto param : params)
	{
		assertExists(param, "Param must not be null");
		assertExists(param->getType(), "Param must have type.");
	}
	
	assertExists(retType, "return type must exist");
	
	m_name = name;
	m_params = params;
	
	setType(FunctionType::get(retType, getParamTys(), vararg));
}
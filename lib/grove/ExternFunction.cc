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

std::vector<const Orange::Type *> ExternFunction::getParamTys() const
{
	std::vector<const Orange::Type *> tys;
	
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
	return new ExternFunction(*this);
}

std::vector<ObjectBase**> ExternFunction::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> ExternFunction::getMemberLists()
{
	auto list = defMemberLists();
	list.insert(list.end(), {
		(std::vector<ObjectBase *>*)&m_params
	});
	return list;
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
							   const Orange::Type* retType, bool vararg)
{
	if (name == "")
	{
		throw fatal_error("name of function was empty");
	}
	
	for (auto param : params)
	{
		assertExists(param, "Param must not be null");
		assertExists(param->getType(), "Param must have type.");
		addChild(param, true);
	}
	
	assertExists(retType, "return type must exist");
	
	m_name = name;
	m_params = params;
	m_ret_type = retType;
	m_vararg = vararg;
}

ExternFunction::ExternFunction(const ExternFunction& other)
{
	m_name = other.m_name;
	m_params = copyVector(other.getParams());
	m_ret_type = other.m_ret_type->copyType();
	m_vararg = other.m_vararg;
	
	for (auto& param : m_params)
	{
		addChild(param, true);
	}
	
	other.defineCopy(this);
}


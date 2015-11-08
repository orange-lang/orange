/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Function.h>
#include <grove/Module.h>
#include <grove/types/Type.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

std::string Function::getName() const
{
	return m_name;
}

llvm::BasicBlock* Function::getEntry() const
{
	return m_entry;
}

llvm::BasicBlock* Function::getExit() const
{
	return m_exit;
}

void Function::build()
{
	if (getType() == nullptr)
	{
		throw std::runtime_error("No type has been assigned to this function.");
	}
	
	auto llvm_ty = static_cast<llvm::FunctionType *>(getType()->getLLVMType());
	
	if (llvm_ty->isFunctionTy() == false)
	{
		throw std::runtime_error("Function's type was _not_ a function!");
	}
	
	auto linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
	auto func = llvm::Function::Create(llvm_ty, linkage, m_name,
									   getModule()->getLLVMModule());
	
	m_entry = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									   "entry", func);
	
	m_exit = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									  "exit", func);

	
	/// @todo run optimization on function
}

Function::Function(ASTNode* parent, std::string name)
: Block(parent)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	m_name = name;
}

Function::Function(Module* module, std::string name)
: Block(module)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	m_name = name;
}
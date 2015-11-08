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
#include <grove/types/FunctionType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <util/assertions.h>

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

llvm::Value* Function::getRetValue() const
{
	return m_ret_value;
}

Type* Function::getReturnType()
{
	auto ty = dynamic_cast<FunctionType *>(getType());
	if (ty == nullptr)
	{
		throw std::runtime_error("Function does not have a function type.");
	}
	
	return ty->getReturnType();
}

bool Function::isVoidFunction()
{
	auto retType = getReturnType();
	if (retType == nullptr)
	{
		throw std::runtime_error("Couldn't get function type.");
	}
	
	return retType->getLLVMType()->isVoidTy();
}

void Function::build()
{
	assertExists(getType(), "No type has been assigned to this function.");
	
	auto func_ty = dynamic_cast<FunctionType *>(getType());
	assertExists(func_ty, "Function's type was not a function.");
	
	auto llvm_ty = static_cast<llvm::FunctionType *>(getType()->getLLVMType());
	
	auto linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
	auto func = llvm::Function::Create(llvm_ty, linkage, m_name,
									   getModule()->getLLVMModule());
	
	
	auto stored_insert = IRBuilder()->GetInsertBlock();
	
	m_entry = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									   "entry", func);
	IRBuilder()->SetInsertPoint(getEntry());
	
	if (isVoidFunction() == false)
	{
		auto ret_ty = getReturnType()->getLLVMType();
		m_ret_value = IRBuilder()->CreateAlloca(ret_ty);
	}
	
	if (isRootNode() == true)
	{
		auto ret_ty = getReturnType()->getLLVMType();
		auto default_ret = llvm::ConstantInt::get(ret_ty, 0, true);
		
		IRBuilder()->CreateStore(default_ret, getRetValue());
	}
	
	m_exit = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									  "exit", func);
	
	for (auto stmt : getStatements())
	{
		stmt->build();
	}
	
	/// If we're missing a terminator, jump to exit.
	if (IRBuilder()->GetInsertBlock()->getTerminator() == nullptr)
	{
		IRBuilder()->CreateBr(getExit());
	}
	
	IRBuilder()->SetInsertPoint(getExit());
	
	if (isVoidFunction() == false)
	{
		auto ret_load = IRBuilder()->CreateLoad(m_ret_value);
		IRBuilder()->CreateRet(ret_load);
	}
	else
	{
		IRBuilder()->CreateRetVoid();
	}
	
	/// @todo run optimization on function
	
	if (stored_insert != nullptr)
	{
    	IRBuilder()->SetInsertPoint(stored_insert);
	}
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
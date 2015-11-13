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
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Codegen/Passes.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Transforms/Scalar.h>
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

void Function::createReturn()
{
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
}

Type* Function::getReturnType()
{
	auto ty = getType();
	if (ty == nullptr || ty->isFunctionTy() == false)
	{
		throw std::runtime_error("Function does not have a function type.");
	}
	
	return ty->getBaseTy();
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

void Function::createFunction()
{
	auto llvm_ty = (llvm::FunctionType *)(getType()->getLLVMType());
	
	auto linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
	m_function = llvm::Function::Create(llvm_ty, linkage, m_name,
									   getModule()->getLLVMModule());
	
	
	m_entry = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									   "entry", m_function);
	m_exit = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									  "exit", m_function);
}

void Function::setupFunction()
{
	IRBuilder()->SetInsertPoint(getEntry());
	
	if (isVoidFunction() == false)
	{
		auto ret_ty = getReturnType()->getLLVMType();
		m_ret_value = IRBuilder()->CreateAlloca(ret_ty);
	}
}

void Function::optimize()
{
	llvm::legacy::FunctionPassManager FPM(getModule()->getLLVMModule());
	FPM.add(llvm::createBasicAliasAnalysisPass());
	FPM.add(llvm::createPromoteMemoryToRegisterPass());
	FPM.add(llvm::createInstructionCombiningPass());
	FPM.add(llvm::createReassociatePass());
	FPM.add(llvm::createGVNPass());
	FPM.add(llvm::createCFGSimplificationPass());

	FPM.run(*m_function);
}

void Function::build()
{
	// Save point.
	auto stored_insert = IRBuilder()->GetInsertBlock();
	
	createFunction();
	setupFunction();
	
	for (auto stmt : getStatements())
	{
		if (stmt->is<Statement *>() && stmt->as<Statement *>()->isTerminator())
		{
			break;
		}
		
		stmt->build();
	}
	
	createReturn();
	optimize();
	
	// Restore point.
	if (stored_insert != nullptr)
	{
    	IRBuilder()->SetInsertPoint(stored_insert);
	}
}

Function::Function(std::string name)
: Block()
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
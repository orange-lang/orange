/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Function.h>
#include <grove/Module.h>
#include <grove/ReturnStmt.h>
#include <grove/Parameter.h>
#include <grove/types/Type.h>
#include <grove/types/FunctionType.h>
#include <grove/types/VoidType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Codegen/Passes.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Transforms/Scalar.h>
#include <util/assertions.h>
#include <util/copy.h>

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

llvm::Function* Function::getLLVMFunction() const
{
	return m_function;
}

std::vector<Type *> Function::getParamTys() const
{
	std::vector<Type *> tys;
	
	for (auto param : getParams())
	{
		auto ty = param->getType();
		assertExists(ty, "Param did not have a type!");
		
		tys.push_back(ty);
	}
	
	return tys;
}

std::vector<Parameter *> Function::getParams() const
{
	return m_params;
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

void Function::setReturnType(Type *ty)
{
	m_ret_type = ty;
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

bool Function::isGeneric() const
{
	for (auto ty : getParamTys())
	{
		if (ty->isVarTy())
		{
			return true;
		}
	}
	
	return false;
}

Genericable* Function::createInstance(Type *type)
{
	if (isGeneric() == false)
	{
		throw std::runtime_error("Cannot create instance of non-generic");
	}
	
	assertExists(type, "Type cannot be null");
	
	auto func_ty = type->as<FunctionType *>();
	auto clone = copy()->as<Function *>();
	
	if (func_ty->getArgs().size() != clone->getParams().size())
	{
		throw std::runtime_error("params in type doesn't match function");
	}
	
	for (int i = 0; i < clone->getParams().size(); i++)
	{
		auto param = clone->m_params[i];
		auto ty = param->getType();
		auto new_ty = func_ty->getArgs()[i];
		
		// Don't change type of non-var arguments
		if (ty->isVarTy() == false)
		{
			continue;
		}
		
		param->setType(new_ty);
	}
	
	if (clone->isGeneric())
	{
		throw std::runtime_error("instance is still generic!");
	}
	
	m_instances.push_back(clone);
	getParent()->addChild(clone);
	
	return clone;
}


bool Function::matchesType(Type *type) const
{
	if (isGeneric())
	{
		return true;
	}
	
	auto arg_ty = type->as<FunctionType *>();
	auto match_ty = getType()->as<FunctionType *>();
	
	// Match return types
	if (arg_ty->getReturnTy()->matches(match_ty->getReturnTy()) == false)
	{
		return false;
	}
	
	// Match argument length
	if (arg_ty->getArgs().size() != match_ty->getArgs().size())
	{
		return false;
	}
	
	// Match arguments
	for (unsigned int i = 0; i < arg_ty->getArgs().size(); i++)
	{
		auto their_arg = arg_ty->getArgs()[i];
		auto our_arg = arg_ty->getArgs()[i];
		
		if (their_arg->matches(our_arg) == false)
		{
			return false;
		}
	}
	
	return true;
}

ASTNode* Function::copy() const
{
	auto func = new Function(getModule(), getName(), copyVector(getParams()));
	func->copyStatements(this);
	return func;
}

void Function::resolve()
{
	// If we already have a type, return.
	if (getType() != nullptr)
	{
		return;
	}
	
	if (isGeneric())
	{
		throw std::runtime_error("Don't know how to handle generic funcs");
	}
	
	if (m_ret_type != nullptr)
	{
		setType(FunctionType::get(m_ret_type, getParamTys()));
		return;
	}
	
	auto retStmts = findChildren<ReturnStmt *>();
	
	if (retStmts.size() == 0)
	{
		setType(FunctionType::get(VoidType::get(), getParamTys()));
	}
	else
	{
		// Find the highest precedence type in retStmts.
		auto highest = retStmts[0]->getType();
		assertExists(highest, "Return statement missing type");
		
		for (int i = 1; i < retStmts.size(); i++)
		{
			auto cmp_ty = retStmts[i]->getType();
    		assertExists(cmp_ty, "Return statement missing type");
			
			switch (Type::compare(highest, cmp_ty)) {
				case LOWER_PRECEDENCE:
					highest = cmp_ty;
					break;
				case INCOMPATIBLE:
					throw std::invalid_argument("Found incompatible return statements");
				default:
					break;
			}
		}
		
		setType(FunctionType::get(highest, getParamTys()));
	}
}

void Function::createFunction()
{
	assertExists(getType(), "Function does not have a type.");
	
	auto llvm_ty = (llvm::FunctionType *)(getType()->getLLVMType());
	
	auto linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
	m_function = llvm::Function::Create(llvm_ty, linkage, m_name,
									   getModule()->getLLVMModule());
	
	// Set argument names
	auto arg_it = m_function->arg_begin();
	for (unsigned int i = 0; i < m_params.size(); i++, arg_it++)
	{
		arg_it->setName(m_params[i]->getName());
	}
	
	m_entry = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									   "entry", m_function);
	m_exit = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
									  "exit", m_function);
	
	setValue(m_function);
}

void Function::setupFunction()
{
	IRBuilder()->SetInsertPoint(getEntry());
	
	// Create our parameters.
	auto arg_it = getLLVMFunction()->arg_begin();
	for (unsigned int i = 0; i < getParams().size(); i++, arg_it++)
	{
		auto param = getParams()[i];
		
		auto ty = param->getType()->getLLVMType();
		auto alloc = IRBuilder()->CreateAlloca(ty);
		
		IRBuilder()->CreateStore(arg_it, alloc);
		param->setValue(alloc);
	}
	
	if (isVoidFunction() == false)
	{
		auto ret_ty = getReturnType()->getLLVMType();
		m_ret_value = IRBuilder()->CreateAlloca(ret_ty);
	}
}

void Function::optimize()
{
	llvm::legacy::FunctionPassManager FPM(getModule()->getLLVMModule());
	FPM.add(llvm::createVerifierPass(true));
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
	if (isGeneric())
	{
		for (auto inst : m_instances)
		{
			inst->as<Function *>()->build();
		}
		
		return;
	}
	
	// Save point.
	auto stored_insert = IRBuilder()->GetInsertBlock();
	
	createFunction();
	setupFunction();
	buildStatements();
	createReturn();
	optimize();
	
	// Restore point.
	if (stored_insert != nullptr)
	{
    	IRBuilder()->SetInsertPoint(stored_insert);
	}
}

bool Function::isTerminator() const
{
	return false;
}

Function::Function(std::string name, std::vector<Parameter *> params)
: Block()
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	for (auto param : params)
	{
		addChild(param, true);
	}
	
	m_name = name;
	m_params = params;
}

Function::Function(Module* module, std::string name,
				   std::vector<Parameter *> params)
: Block(module)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	for (auto param : params)
	{
		addChild(param, true);
	}
	
	m_name = name;
	m_params = params;
}
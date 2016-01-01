/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Function.h>
#include <grove/Module.h>
#include <grove/Builder.h>
#include <grove/ReturnStmt.h>
#include <grove/Parameter.h>

#include <grove/types/Type.h>
#include <grove/types/FunctionType.h>
#include <grove/types/VoidType.h>
#include <grove/types/VarType.h>
#include <grove/types/PointerType.h>

#include <grove/exceptions/already_defined_sig_error.h>
#include <grove/exceptions/invalid_type_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/copy.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/CodeGen/Passes.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Transforms/Scalar.h>

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

Parameter* Function::getParam(std::string name) const
{
	for (auto& param : getParams())
	{
		if (param->getName() == name)
		{
			return param;
		}
	}
	
	return nullptr;
}

std::vector<const Orange::Type *> Function::getParamTys() const
{
	std::vector<const Orange::Type *> tys;
	
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

OString Function::getMangledName() const
{
	std::stringstream ss;
	ss << "_O" << getName().str().size() << getName().str();
	ss << getType()->getSignature();
	
	return ss.str();
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

const Orange::Type* Function::getReturnType() const
{
	auto ty = getType();
	if (ty == nullptr || ty->isFunctionTy() == false)
	{
		throw fatal_error("function not assigned a function type.");
	}
	
	return ty->getBaseTy();
}

void Function::setReturnType(const Orange::Type* ty)
{
	m_ret_type = ty;
}

bool Function::isVoidFunction() const
{
	auto retType = getReturnType();
	if (retType == nullptr)
	{
		throw fatal_error("Couldn't get type of function");
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
	
	if (findParent<Genericable *>() &&
		findParent<Genericable *>()->isGeneric())
	{
		return true;
	}
	
	return false;
}

Genericable* Function::createInstance(const Orange::Type *type)
{
	if (isGeneric() == false)
	{
		throw fatal_error("Cannot call createInstance on non-generic function");
	}
	
	assertExists(type, "Type cannot be null");
	
	auto func_ty = type->as<Orange::FunctionType *>();
	
	getModule()->beginCopy();
	
	auto clone = copy()->as<Function *>();
	
	getModule()->endCopy();
	
	if (func_ty->getArgs().size() != clone->getParams().size())
	{
		throw fatal_error("params in type doesn't match function");
	}
	
	for (unsigned int i = 0; i < clone->getParams().size(); i++)
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
		throw fatal_error("instance is still a generic!");
	}
	
	clone->m_instance_of = this;
	
	m_instances.push_back(clone);
	getParent()->addChild(clone);
	
	return clone;
}


bool Function::matchesType(const Orange::Type* type) const
{
	auto arg_ty = type->as<Orange::FunctionType *>();
	auto param_tys = getParamTys();
	
	// Match argument length
	if (arg_ty->getArgs().size() != param_tys.size())
	{
		return false;
	}
	
	// Match arguments
	for (unsigned int i = 0; i < arg_ty->getArgs().size(); i++)
	{
		auto their_arg = arg_ty->getArgs()[i];
		auto our_arg = param_tys[i];
		
		// If we're an instance, we only want to match types
		// that were generic from our parent, since arg casting
		// may have occured. This partial type matching won't
		// affect multiple matches, since an exact match has to
		// occur if multiple nodes are found with the same name.
		if (isInstance())
		{
			auto instance = getInstanceParent()->as<Function *>();
			// If parameter i of our parent isn't var, continue.
			auto parent_arg = instance->getParamTys().at(i);
			if (parent_arg->isVarTy() == false)
			{
				continue;
			}
		}
		
		if (their_arg->matches(our_arg) == false)
		{
			return false;
		}
	}
	
	return true;
}

ASTNode* Function::copy() const
{
	return new Function(*this);
}

std::vector<ObjectBase**> Function::getMemberNodes()
{
	return Block::getMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> Function::getMemberLists()
{
	auto list = Block::getMemberLists();
	list.insert(list.end(), {
		(std::vector<ObjectBase *>*)&m_params
	});
	return list;
}

void Function::findDependencies()
{
	// Find all return statements that don't depend on this function.
	auto retStmts = findChildren<ReturnStmt *>();
	
	bool found_ret = false;
	
	for (auto ret : retStmts)
	{
		if (ret->dependsOn(this) == true)
		{
			continue;
		}
		
		if (isInstance() &&
			ret->dependsOn(getInstanceParent()->as<Function*>()))
		{
			continue;
		}
		
		addDependency(ret);
		found_ret = true;
	}
	
	for (auto param : getParams())
	{
		addDependency(param);
	}
	
	if (retStmts.size() > 0 && found_ret == false)
	{
		throw fatal_error("could not determine return type for function");
	}
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
		// We need to resolve our parameters just in case they need it 
		for (auto param : getParams())
		{
			getModule()->resolve(param);
		}
		
		setType(Orange::FunctionType::get(getModule(),
										  Orange::VarType::get(getModule()),
										  getParamTys()));
		
		auto search_settings = SearchSettings();
		search_settings.forceTypeMatch = true;
		search_settings.createGeneric = false;
		search_settings.filter = [this](Named* named) -> bool
		{
			if (named->is<Function *>())
			{
				auto func = named->as<Function *>();
				return func->getInstanceParent() != this &&
					getInstanceParent() != func;
			}
			
			return true;
		};
		
		auto found = findNamed(getName(), getType(), search_settings);
		if (found != nullptr)
		{
			auto base = found->as<CodeBase *>();
			throw already_defined_sig_error(&m_name, base, m_name);
		}
		
		return;
	}
	
	for (auto param : m_params)
	{
		if (param->getType()->isArrayTy())
		{
			auto ty = param->getType();
			param->setType(Orange::PointerType::get(getModule(),
													ty->getRootTy()));
		}
	}
	
	if (m_ret_type != nullptr)
	{
		setType(Orange::FunctionType::get(getModule(), m_ret_type,
										  getParamTys()));
		return;
	}
	
	// Get return statements this function depends on.
	std::vector<ReturnStmt *> retStmts;
	for (auto dep : getDependencies())
	{
		if (dep->is<ReturnStmt *>())
		{
			retStmts.push_back(dep->as<ReturnStmt *>());
		}
	}
	
	if (retStmts.size() == 0)
	{
		setType(Orange::FunctionType::get(getModule(),
										  Orange::VoidType::get(getModule()),
										  getParamTys()));
	}
	else
	{
		// Find the highest precedence type in retStmts.
		auto highest = retStmts[0]->getType();
		assertExists(highest, "Return statement missing type");
		
		for (unsigned int i = 1; i < retStmts.size(); i++)
		{
			auto cmp_ty = retStmts[i]->getType();
    		assertExists(cmp_ty, "Return statement missing type");
			
			switch (Orange::Type::compare(highest, cmp_ty)) {
				case LOWER_PRECEDENCE:
					highest = cmp_ty;
					break;
				case INCOMPATIBLE:
					throw invalid_type_error(retStmts[i], "function has "
											 "multiple return statements that "
											 "are incompatible with return "
											 "statement of type", cmp_ty);
				default:
					break;
			}
		}
		
		setType(Orange::FunctionType::get(getModule(), highest, getParamTys()));
	}
	
	auto search_settings = SearchSettings();
	search_settings.forceTypeMatch = true;
	
	if (isInstance() == false)
	{
		auto found = findNamed(getName(), getType(), search_settings);
		if (found != nullptr)
		{
			throw already_defined_sig_error(&m_name, found->as<CodeBase *>(),
											m_name);
		}
	}
}

void Function::createFunction()
{
	assertExists(getType(), "Function does not have a type.");
	
	auto llvm_ty = (llvm::FunctionType *)(getType()->getLLVMType());
	
	auto linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
	m_function = llvm::Function::Create(llvm_ty, linkage, getMangledName().str(),
									   getModule()->getLLVMModule());
	
	// Set argument names
	auto arg_it = m_function->arg_begin();
	for (unsigned int i = 0; i < m_params.size(); i++, arg_it++)
	{
		arg_it->setName(m_params[i]->getName().str());
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
	if (getModule()->getBuilder()->getDebug())
	{
		m_function->dump();
	}
	
	
	// Validate all blocks have terminators.
	auto it = m_function->getBasicBlockList().begin();
	for ( ; it != m_function->getBasicBlockList().end(); it++)
	{
		if (it->getTerminator() == nullptr)
		{
			throw fatal_error("block is missing terminator");
		}
	}
	
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

Function::Function(OString name, std::vector<Parameter *> params)
: Block()
{
	if (name == "")
	{
		throw fatal_error("name of function was empty");
	}
	
	for (auto param : params)
	{
		addChild(param, true);
	}
	
	m_name = name;
	m_params = params;
}

Function::Function(Module* module, OString name,
				   std::vector<Parameter *> params)
: Block(module)
{
	if (name == "")
	{
		throw fatal_error("name of function was empty");
	}
	
	for (auto param : params)
	{
		addChild(param, true);
	}
	
	m_name = name;
	m_params = params;
}

Function::Function(const Function& other)
{
	m_name = other.m_name;
	m_params = copyVector(other.getParams());
	
	for (auto& param : m_params)
	{
		addChild(param, true);
	}
	
	copyStatements(&other);
	other.defineCopy(this);
}
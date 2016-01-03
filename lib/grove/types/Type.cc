/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/Type.h>
#include <grove/types/PointerType.h>

#include <grove/exceptions/fatal_error.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include <grove/Module.h>
#include <grove/Valued.h>
#include <grove/ASTNode.h>
#include <grove/Expression.h>
#include <grove/Value.h>

#include <util/assertions.h>

std::map<std::tuple<Module *, std::string>, Orange::Type*>
    Orange::Type::m_defined;
std::map<TypeTuple, TypeCast> Orange::Type::m_cast_map;
std::map<TypeTuple, TypeCallback> Orange::Type::m_cast_ty_map;

void Orange::Type::clear(Module *mod)
{
	std::map<std::tuple<Module *, std::string>, Orange::Type*> copy;
	
	for (auto& pair : m_defined)
	{
		if (std::get<0>(pair.first) != mod)
		{
			copy[pair.first] = pair.second;
			continue;
		}
		
		delete pair.second;
	}
	
	m_defined = copy;
}

std::string Orange::Type::getConstIdentifier()
{
	return "U";
}

Module* Orange::Type::getModule() const
{
	return m_module;
}

void Orange::Type::copyCasts(const std::type_info &of)
{
	for (auto pair : m_cast_map)
	{
		if (std::get<0>(pair.first) != of.hash_code())
		{
			continue;
		}
		
		TypeTuple tup(typeid(*this).hash_code(), std::get<1>(pair.first));
		m_cast_map[tup] = pair.second;
	}
	
	for (auto pair : m_cast_ty_map)
	{
		if (std::get<0>(pair.first) != of.hash_code())
		{
			continue;
		}
		
		TypeTuple tup(typeid(*this).hash_code(), std::get<1>(pair.first));
		m_cast_ty_map[tup] = pair.second;
	}
}

std::string Orange::Type::getString() const
{
	throw fatal_error("Type::getString not overriden for type");
}

bool Orange::Type::isSigned() const
{
	return false;
}

bool Orange::Type::isPODTy() const
{
	return false;
}

bool Orange::Type::isArrayTy() const
{
	return false;
}

bool Orange::Type::isDoubleTy() const
{
	return false;
}

bool Orange::Type::isFloatTy() const
{
	return false;
}

bool Orange::Type::isFloatingPointTy() const
{
	return false;
}

bool Orange::Type::isFunctionTy() const
{
	return false;
}

bool Orange::Type::isIntTy() const
{
	return false;
}

bool Orange::Type::isBoolTy() const
{
	return false;
}

bool Orange::Type::isPointerTy() const
{
	return false;
}

bool Orange::Type::isVoidTy() const
{
	return false;
}

bool Orange::Type::isVarTy() const
{
	return false;
}

bool Orange::Type::isClassTy() const
{
	return false;
}

bool Orange::Type::isNodeTy() const
{
	return false;
}

bool Orange::Type::isFutureTy() const
{
	return false;
}

bool Orange::Type::isAggTy() const
{
	return false;
}

bool Orange::Type::hasReference() const
{
	return false;
}

ASTNode* Orange::Type::getReference() const
{
	return nullptr;
}

bool Orange::Type::isConst() const
{
	return m_const;
}

BasicType Orange::Type::PODTy() const
{
	return TYOTHER;
}

const Orange::Type* Orange::Type::getPointerTo() const
{
	if (isVarTy())
	{
		return this;
	}
	
	return PointerType::get(getModule(), (Type *)this);
}

const Orange::Type* Orange::Type::getBaseTy() const
{
	return (Type *)this;
}

const Orange::Type* Orange::Type::getRootTy() const
{
	return (Type *)this;
}

const Orange::Type* Orange::Type::getConst() const
{
	throw fatal_error("getConst not overriden for type");
}

bool Orange::Type::matches(const Orange::Type *ty) const
{
	bool does_match = ty == this || ty->isVarTy() || this->isVarTy() ||
		this->getBaseTy()->isVarTy() || ty->getBaseTy()->isVarTy();
	
	if (does_match == false && ty->getComparisonTy() != ty)
	{
		return matches((Type *)ty->getComparisonTy());
	}
	else if (does_match == false && getComparisonTy() != this)
	{
		return getComparisonTy()->matches(ty);
	}
	
	return does_match;
}

Orange::Type* Orange::Type::getDefined(Module* mod, std::string signature)
{
	auto it = m_defined.find(std::make_tuple(mod, signature));
	
	if (it == m_defined.end())
	{
		return nullptr;
	}
	
	return it->second;
}

const Orange::Type* Orange::Type::replaceMember(const Orange::Type* member,
												const Orange::Type* with) const
{
	return this;
}

std::vector<const Orange::Type*> Orange::Type::getMemberTys() const
{
	return std::vector<const Orange::Type*>();
}

unsigned int Orange::Type::getIntegerBitWidth() const
{
	return 0;
}

void Orange::Type::define(Module* mod, std::string signature, Orange::Type *ty)
{
	assertExists(mod, "Mod cannot be nullptr");
	
	if (getDefined(mod, signature) != nullptr)
	{
		throw fatal_error("trying to redefine a signature");
	}
	
	if (ty == nullptr)
	{
		throw fatal_error("ty was null");
	}
	
	m_defined[std::make_tuple(mod, signature)] = ty;
	ty->m_module = mod;
}

void Orange::Type::defineCast(const std::type_info &to, TypeCallback cb)
{
	TypeCast tc = [cb](void* build, Valued* val,
					   const Orange::Type* from,
					   const Orange::Type* to) -> llvm::Value*
	{
		assertExists(build, "build must exist");
		assertExists(from, "from must exist");
		assertExists(to, "to must exist");
		
		IRBuilder* IRB = (IRBuilder *)build;
		
		auto llvm_val = val->getValue();
		assertExists(llvm_val, "value must exist");
		
		auto op = (llvm::Instruction::CastOps)cb(from, to);
		if (op == NO_CAST)
		{
			return llvm_val;
		}
		
		auto casted = IRB->CreateCast(op, llvm_val, to->getLLVMType());
		assertExists(casted, "cast returned nullptr");
		
		return casted;
	};
	
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_map[tuple] = tc;
	m_cast_ty_map[tuple] = cb;
}

void Orange::Type::defineCast(const std::type_info &to, int cast)
{
	TypeCallback cb = [cast](const Orange::Type*, const Orange::Type*) -> int
	{
		return cast;
	};
	
	TypeCast tc = [cb](void* build, Valued* val,
					   const Orange::Type* from,
					   const Orange::Type* to) -> llvm::Value*
	{
		assertExists(build, "build must exist");
		assertExists(from, "from must exist");
		assertExists(to, "to must exist");
		
		IRBuilder* IRB = (IRBuilder *)build;
		
		auto llvm_val = val->getValue();
		assertExists(llvm_val, "value must exist");
		
		auto op = (llvm::Instruction::CastOps)cb(from, to);
		if (op == NO_CAST)
		{
			return llvm_val;
		}
		
		auto casted = IRB->CreateCast(op, llvm_val, to->getLLVMType());
		assertExists(casted, "cast returned nullptr");
		
		return casted;
	};
	
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_map[tuple] = tc;
	m_cast_ty_map[tuple] = cb;
}

void Orange::Type::defineCast(const std::type_info &to, TypeCallback cb,
							  TypeCast func)
{
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_map[tuple] = func;
	m_cast_ty_map[tuple] = cb;
}

void Orange::Type::defineCast(const std::type_info& to, int cast, TypeCast func)
{
	TypeTuple tuple(typeid(*this).hash_code(), to.hash_code());
	m_cast_map[tuple] = func;
	m_cast_ty_map[tuple] = [cast](const Orange::Type*,
								  const Orange::Type*) -> int
	{
		return cast;
	};
}

std::string Orange::Type::getSignature() const
{
	throw fatal_error("Orange::Type::getSignature not overriden");
}

int Orange::Type::castOperation(const Orange::Type *to) const
{
	if (this == to)
	{
		return 0;
	}
	
	TypeTuple key(typeid(*this).hash_code(), typeid(*to).hash_code());
	
	// Search for callbacks first.
	auto it_cb = m_cast_ty_map.find(key);
	if (it_cb == m_cast_ty_map.end())
	{
		throw fatal_error("Could not find cast");
	}
	
	return it_cb->second(this, to);
}

llvm::Value* Orange::Type::cast(void *irBuilder, Valued *val,
								const Orange::Type *target) const
{
	TypeTuple key(typeid(*this).hash_code(), typeid(*target).hash_code());
	
	auto orig_target = target;
	auto src = (Type *)getComparisonTy();
	target = (Type *)target->getComparisonTy();
	
	if (this != src || target != orig_target)
	{
		return src->cast(irBuilder, val, target);
	}
	
	auto it = m_cast_map.find(key);
	if (it == m_cast_map.end() && src != target)
	{
		throw fatal_error("could not find cast to use");
	}
	else if (src == target)
	{
		return val->getValue();
	}
	
	return it->second(irBuilder, val, src, target);
}

llvm::Type* Orange::Type::getLLVMType() const
{
	return m_type;
}

const Orange::Type* Orange::Type::getComparisonTy() const
{
	return this;
}

Comparison Orange::Type::compare(const Orange::Type *source,
								 const Orange::Type *target)
{
	assertExists(source, "Source type must exist");
	assertExists(target, "Target type must exist");
	
	source = source->getComparisonTy();
	target = target->getComparisonTy();
	
	if (source == target)
	{
		return Comparison::EQUAL;
	}
	
	if (source->isIntTy() && target->isPointerTy())
	{
		return Comparison::HIGHER_PRECEDENCE;
	}
	else if (source->isPointerTy() && target->isIntTy())
	{
		return Comparison::LOWER_PRECEDENCE;
	}
	
	// Only compare the precedence of two POD types.
	bool bothPOD = source->isPODTy() && target->isPODTy();
	if (bothPOD == false)
	{
		if (source->isPointerTy() && target->isPointerTy() &&
			source->matches(target))
		{
			return Comparison::EQUAL;
		}
		
		return Comparison::INCOMPATIBLE;
	}
	
	if (source->PODTy() < target->PODTy())
	{
		return Comparison::HIGHER_PRECEDENCE;
	}
	else if (source->PODTy() == target->PODTy())
	{
		return Comparison::EQUAL;
	}
	else
	{
		return Comparison::LOWER_PRECEDENCE;
	}
}

bool Orange::Type::exprValidForArrSize(Expression* expr)
{
	if (expr->isConstant() == false)
	{
		return false;
	}
	
	if (expr->getType()->isIntTy() == false)
	{
		return false;
	}
	
	if (dynamic_cast<Value *>(expr) == nullptr)
	{
		return false;
	}
	
	return true;
}

unsigned int Orange::Type::exprAsArrSize(Expression* expr)
{
	if (dynamic_cast<Value *>(expr) == nullptr)
	{
		return false;
	}
	
	Value* v = dynamic_cast<Value *>(expr);
	unsigned int size = 0;
	
	if (expr->getType()->isSigned())
	{
		size = v->getInt();
	}
	else
	{
		size = v->getUInt();
	}
	
	return size;
}

bool Orange::Type::isVariadiclySized() const
{
	return false;
}

std::vector<Expression *> Orange::Type::getVariadicSizes() const
{
	return std::vector<Expression *>();
}

const Orange::Type* Orange::Type::copyType() const
{
	return this;
}

Orange::Type::Type(bool isConst)
{
	m_context = & llvm::getGlobalContext();
	m_const = isConst;
	m_type = llvm::Type::getVoidTy(*m_context);
}

Orange::Type::~Type()
{
	// Do nothing.
}

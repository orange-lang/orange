/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/VarDecl.h>
#include <grove/Expression.h>
#include <grove/Module.h>

#include <grove/types/Type.h>
#include <grove/types/UIntType.h>
#include <grove/types/NodeType.h>
#include <grove/types/ReferenceType.h>

#include <grove/exceptions/already_defined_error.h>
#include <grove/exceptions/invalid_type_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/IRBuilder.h>

llvm::Value* VarDecl::getValue() const
{
	assertExists(m_value, "m_value never initialized.");
	return IRBuilder()->CreateLoad(m_value);
}

llvm::Value* VarDecl::getPointer() const
{
	return m_value;
}

bool VarDecl::hasPointer() const
{
	return true;
}

Expression* VarDecl::getExpression() const
{
	return m_expr;
}

ASTNode* VarDecl::copy() const
{
	ASTNode* clone = nullptr;
	
	if (m_expr)
	{
		clone = new VarDecl(m_type->copyType(), m_name,
							m_expr->copy()->as<Expression *>());
	}
	else
	{
		clone = new VarDecl(m_type->copyType(), m_name, nullptr);
	}
	
	defineCopy(clone);
	return clone;
}

bool VarDecl::isAccessible() const
{
	// We can have members accessed if we're a reference type,
	// and our reference type is also accessible.
	if (getType()->getRootTy()->is<ReferenceType *>() == false)
	{
		return false;
	}
	
	auto ref = getType()->getRootTy()->as<ReferenceType *>()->getReference();
	return ref->is<Accessible *>() && ref->as<Accessible *>()->isAccessible();
}

Expression* VarDecl::access(OString name, const ASTNode *hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	const ASTNode* hint_to_use = hint;
	if (hint_to_use == nullptr)
	{
		hint_to_use = this;
	}
	
	auto ref = getType()->getRootTy()->as<ReferenceType *>()->getReference();
	auto accessible_ref = ref->as<Accessible *>();
	return accessible_ref->access(name, hint_to_use);
}

bool VarDecl::allocateVariable()
{
	// We want to allocate our variable explicitly in the following cases:
	// 	1. We don't have an expression.
	//  2. The expression isn't transferrable (e.g., it memory can't be
	//     transferred)
	//  3. Our types don't match and we need to do a cast.
	return getExpression() == nullptr ||
		getExpression()->transferrable() == false ||
		getType()->matches(getExpression()->getType()) == false;
}

void VarDecl::resolve()
{
	SearchSettings settings;
	settings.searchWholeTree = false;
	
	auto existing = findNamed(getName(), getType(), settings);
	if (existing != nullptr)
	{
		CodeBase* base = existing->as<CodeBase *>();
		
		if (existing->is<VarDecl *>())
		{
			base = &existing->as<VarDecl *>()->m_name;
		}
		
		throw already_defined_error(&m_name, base, getName());
	}

	if (getType()->isVarTy() && getExpression() == nullptr)
	{
		throw code_error(m_expr, []() -> std::string
			{
				return "A variable of type var must have an initial value";
			});
	}

	if (getExpression())
	{
		assertExists(getExpression()->getType(), "Expression has no type.");

		if (getType()->isVarTy())
		{
			setType(getExpression()->getType());
		}
	}
	else if (getType()->getRootTy()->is<NodeType *>())
	{
		if (getType()->getRootTy()->as<NodeType *>()->canInitializeVar())
		{
			m_expr = getType()->getRootTy()->as<NodeType *>()->initializeVar();
			addChild(m_expr, true);
			getModule()->findDependencies(m_expr);
			getModule()->resolve(m_expr);
		}
		else
		{
			auto ty = getType();
			throw code_error(this, [ty] () { return "no default value exists "
				"for type " + ty->getString(); });
		}
	}
	
	if (getType()->isVariadiclySized())
	{
		for (auto size : getType()->getVariadicSizes())
		{
			if (size->getType()->isIntTy() == false)
			{
				throw invalid_type_error(size, "cannot create variadic array "
										 "with size of type", size->getType());
			}
		}
	}
}

void VarDecl::build()
{
	if (getType()->isVariadiclySized())
	{
		for (auto s : getType()->getVariadicSizes())
		{
			s->build();
			auto s_val = s->castTo(UIntType::get(getModule(), 64));
			
			if (m_size == nullptr)
			{
				m_size = s_val;
			}
			else
			{
				m_size = IRBuilder()->CreateMul(m_size, s_val);
			}
		}
	}
	
	if (allocateVariable())
	{
		setValue(IRBuilder()->CreateAlloca(getType()->getLLVMType(), m_size,
									   getName().str()));	
	}
	
	if (getExpression())
	{
		getExpression()->build();
		
		if (allocateVariable())
		{
    		auto val = getExpression()->getValue();
    		assertExists(val, "Built expression has no value.");

    		val = getExpression()->castTo(getType());

    		assertEqual<VAL, PTR>(val, getPointer(), "value does not match variable");

    		IRBuilder()->CreateStore(val, getPointer());		
		}
		else
		{
			setValue(getExpression()->getPointer());
			m_value->setName(getName().str());
		}
	}
}

VarDecl::VarDecl(const Type* type, OString name, Expression* expression)
{
	assertExists(type, "Type must exist");

	if (type->isVoidTy())
	{
		throw invalid_type_error(&name, "cannot declare variable of type",
								 type);
	}
	
	if (type->isVariadiclySized())
	{
		for (auto size : type->getVariadicSizes())
		{
			addChild(size, true);
		}
	}
	
	if (type->getRootTy()->is<NodeType *>())
	{
		addChild(type->getRootTy()->as<NodeType *>());
	}

	if (name == "")
	{
		throw fatal_error("name was empty");
	}

	m_name = name;
	m_expr = expression;

	setType(type);
	addChild(m_expr, false);
}

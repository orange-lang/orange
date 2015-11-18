/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/VarDecl.h>
#include <grove/Expression.h>
#include <grove/types/Type.h>

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

void VarDecl::resolve()
{
	if (getType()->isVarTy() && getExpression() == nullptr)
	{
		throw std::runtime_error("A variable of type var must have \
								 an expression");
	}
	
	if (getExpression())
	{
		assertExists(getExpression()->getType(), "Expression has no type.");
	
    	if (getType()->isVarTy())
    	{
    		setType(getExpression()->getType());
    	}	
	}
}

void VarDecl::build()
{
	setValue(IRBuilder()->CreateAlloca(getType()->getLLVMType()));
	
	if (getExpression())
	{
		getExpression()->build();
		auto val = getExpression()->getValue();
		assertExists(val, "Built expression has no value.");
		
		val = getExpression()->castTo(getType());
		
		assertEqual<VAL, PTR>(val, getPointer(), "value does not match variable");
		
		IRBuilder()->CreateStore(val, getPointer());
	}
}

VarDecl::VarDecl(Type* type, std::string name, Expression* expression)
{
	assertExists(type, "Type must exist");
	
	if (type->isVoidTy())
	{
		throw std::runtime_error("type of variable cannot be void");
	}
	
	if (name == "")
	{
		throw std::invalid_argument("name cannot be empty");
	}
	
	m_name = name;
	m_expr = expression;
	
	setType(type);
	addChild(m_expr, false);
}
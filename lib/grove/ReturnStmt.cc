/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ReturnStmt.h>
#include <grove/Function.h>
#include <grove/Expression.h>
#include <grove/types/VoidType.h>
#include <util/assertions.h>
#include <util/llvmassertions.h>
#include <llvm/IR/IRBuilder.h>

Expression* ReturnStmt::getExpression()
{
	return m_expr;
}

bool ReturnStmt::hasExpression()
{
	return m_expr != nullptr;
}

bool ReturnStmt::isTerminator() const
{
	return true;
}

void ReturnStmt::resolve()
{
	Statement::resolve();
	
	if (hasExpression())
	{
		setType(getExpression()->getType());
	}
	else
	{
		setType(VoidType::get());
	}
}

void ReturnStmt::build()
{
	auto func = findParent<Function *>();
	assertExists(func, "Couldn't find parent function of ReturnStmt");

	getExpression()->build();
	
	auto value = getExpression()->getValue();
	
	if (getType() != func->getReturnType())
	{
		switch (Type::compare(getType(), func->getReturnType()))
		{
			case LOWER_PRECEDENCE:
			case HIGHER_PRECEDENCE:
				value = getExpression()->castTo(func->getReturnType());
				break;
			case INCOMPATIBLE:
        		throw std::invalid_argument("ReturnStmt ty != func ty");
			default:
				break;
		}
	}
	
	if (hasExpression())
	{
		auto ptr = func->getRetValue();
		
    	assertEqual<VAL,PTR>(value, ptr, "Can't store incompatible type.");
		
		IRBuilder()->CreateStore(value, ptr);
	}
	
	IRBuilder()->CreateBr(func->getExit());
}

ReturnStmt::ReturnStmt(Expression* expression)
{
	addChild(expression);
	
	m_expr = expression->as<Expression *>();
}
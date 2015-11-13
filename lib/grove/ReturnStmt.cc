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
	
	if (getType() != func->getReturnType())
	{
		throw std::invalid_argument("ReturnStmt ty != func ty");
	}
	
	getExpression()->build();
	
	if (hasExpression())
	{
		auto ptr = func->getRetValue();
		auto val = getExpression()->getValue();
		IRBuilder()->CreateStore(val, ptr);
	}
	
	IRBuilder()->CreateBr(func->getExit());
}

ReturnStmt::ReturnStmt(Expression* expression)
{
	addChild(expression);
	
	m_expr = expression->as<Expression *>();
}
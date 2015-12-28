/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/IncrementExpr.h>

#include <grove/types/Type.h>

#include <grove/exceptions/invalid_type_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

Expression* IncrementExpr::getExpression() const
{
	return m_expr;
}

ASTNode* IncrementExpr::copy() const
{
	return new IncrementExpr(*this);
}

std::vector<ObjectBase**> IncrementExpr::getMemberNodes()
{
	auto list = defMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_expr
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> IncrementExpr::getMemberLists()
{
	return defMemberLists();
}

int IncrementExpr::getDelta() const
{
	return m_delta;
}

bool IncrementExpr::isPreIncrement() const
{
	return m_preincrement == true;
}

bool IncrementExpr::isPostIncrement() const
{
	return m_preincrement == false;
}

void IncrementExpr::resolve()
{
	auto ty = getExpression()->getType();
	assertExists(ty, "Expression has no type.");
	
	if (getExpression()->hasPointer() == false)
	{
		throw code_error(getExpression(), []() -> std::string
			{
				return "expression is not an lvalue and cannot be assigned";
			});
	}
	
	if (ty->isIntTy() == false && ty->isFloatingPointTy() == false)
	{
		throw invalid_type_error(getExpression(), "cannot increment expression "
								 "of type", ty);
	}
	
	setType(ty);
}

void IncrementExpr::build()
{
	getExpression()->build();
	
	auto ptr = getExpression()->getPointer();
	auto val = getExpression()->getValue();
	auto ty = getExpression()->getType();
	
	assertExists(ptr, "Expression has no pointer");
	assertExists(val, "Expression generated no value");
	
	llvm::Value* newVal = nullptr;
	if (ty->isIntTy())
	{
		auto delta = llvm::ConstantInt::get(ty->getLLVMType(), getDelta());
    	newVal = IRBuilder()->CreateAdd(val, delta);
	}
	else if (ty->isFloatingPointTy())
	{
		auto delta = llvm::ConstantFP::get(ty->getLLVMType(), (double)getDelta());
    	newVal = IRBuilder()->CreateFAdd(val, delta);
	}
	
	IRBuilder()->CreateStore(newVal, ptr);
	
	if (isPreIncrement())
	{
		setValue(newVal);
	}
	else
	{
		setValue(val);
	}
}

IncrementExpr::IncrementExpr(Expression* expr, int delta, bool preincrement)
{
	assertExists(expr, "Expr cannot be null");
	
	m_preincrement = preincrement;
	m_expr = expr;
	m_delta = delta;
	
	addChild(expr);
}

IncrementExpr::IncrementExpr(const IncrementExpr& other)
{
	m_preincrement = other.m_preincrement;
	m_expr = (Expression *)other.m_expr->copy();
	m_delta = other.m_delta;
	
	addChild(m_expr, true);
	other.defineCopy(this);
}
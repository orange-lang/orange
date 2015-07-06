/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/DerefExpr.h>
#include <orange/generator.h>

std::string DerefExpr::string() {
	return "*" + m_expr->string();
}

Value* DerefExpr::Codegen() {
	Value* ret = m_expr->Codegen();
	
	if (ret == nullptr) {
		throw CompilerMessage(*m_expr, "expression did not generate a value!");
	}
	
	if (ret->getType()->isPointerTy() == false) {
		throw CompilerMessage(*m_expr, "expression is not a pointer.");
	} 

	m_value = GE::builder()->CreateLoad(ret);
	return m_value;
}

ASTNode* DerefExpr::clone() {
	return new DerefExpr((Expression*)m_expr->clone());
}

OrangeTy* DerefExpr::getType() {
	OrangeTy* exprType = m_expr->getType();

	if (exprType->isPointerTy()) {
		return m_expr->getType()->getPointerElementType();
	} else if (exprType->isArrayTy()) {
		return m_expr->getType()->getArrayElementType();
	} else {
		throw CompilerMessage(*m_expr, "expression is not a pointer");
	}

	// should never reach this line.
	return nullptr; 
}

bool DerefExpr::returnsPtr() {

	return m_expr->getType()->isPointerTy();
}

bool DerefExpr::isSigned() {
	return getType()->isSigned();
}

DerefExpr::DerefExpr(Expression* expr) {
	if (expr == nullptr) {
		throw std::runtime_error("DerefExpr ctor: expr should not be nullptr");
	}

	m_expr = expr;

	addChild("m_expr", m_expr);
}

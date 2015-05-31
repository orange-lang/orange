/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/NegativeExpr.h>
#include <orange/generator.h>

NegativeExpr::NegativeExpr(Expression *expr) : m_expr(expr) {
	if (expr == nullptr) {
		throw std::runtime_error("expr in NegativeExpr must not be null!");
	}

	m_expr->setParent(this);
}

Value* NegativeExpr::Codegen() {
	Value* negateVal = m_expr->Codegen();

	if (negateVal == nullptr) {
		throw std::runtime_error("expr did not generate a value!");
	}

	if (m_expr->returnsPtr()) {
		negateVal = GE::builder()->CreateLoad(negateVal);
	}

	if (getType()->isFloatingPointTy()) {
		return GE::builder()->CreateFNeg(negateVal);
	} else {
		return GE::builder()->CreateNeg(negateVal);
	}
}

std::string NegativeExpr::string() {
	return "-" + m_expr->string();
}

OrangeTy* NegativeExpr::getType() {
	return m_expr->getType();
}

void NegativeExpr::resolve() {
	if (m_resolved) return;
	m_resolved = true; 

	m_expr->resolve();
}

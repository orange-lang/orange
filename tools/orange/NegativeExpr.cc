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

	addChild("m_expr", m_expr);
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
		m_value = GE::builder()->CreateFNeg(negateVal);
	} else {
		m_value = GE::builder()->CreateNeg(negateVal);
	}

	return m_value;
}

void NegativeExpr::resolve() {
	ASTNode::resolve();
	m_type = m_expr->getType();
}

std::string NegativeExpr::string() {
	return "-" + m_expr->string();
}

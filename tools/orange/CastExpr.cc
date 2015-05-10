/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CastExpr.h>
#include <orange/generator.h>

std::string CastExpr::string() {
	return "(" + m_type->string() + ")" + m_expr->string();
}

Value* CastExpr::Codegen() { 
	Value* val = m_expr->Codegen();
	
	if (val == nullptr) {
		throw std::runtime_error("CastExpr::Codegen(): m_expr did not generate a value!");
	}

	if (m_expr->returnsPtr()) {
		val = GE::builder()->CreateLoad(val);
	}

	CastingEngine::CastValueToType(&val, m_type, isSigned(), true);
	return val;
}

ASTNode* CastExpr::clone() {
	return new CastExpr(m_type, (Expression *)m_expr->clone());
}

AnyType* CastExpr::getType() { 
	return m_type; 
}

void CastExpr::resolve() {
	if (m_resolved) return; 
	m_resolved = true; 

	m_expr->resolve();
}

bool CastExpr::isSigned() { 
	return m_type->isSigned();
}

CastExpr::CastExpr(AnyType* type, Expression* expr) {
	if (type == nullptr) {
		throw std::runtime_error("CastExpr ctor: type must not be nullptr!");
	}

	if (expr == nullptr) {
		throw std::runtime_error("CastExpr ctor: expr must not be nullptr!");
	}

	m_type = type; 
	m_expr = expr; 
}

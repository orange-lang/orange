/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/AddressOfExpr.h>
#include <orange/generator.h>

Value* AddressOfExpr::Codegen() {
	Value *v = m_expr->Codegen();
	return v;
}

ASTNode* AddressOfExpr::clone() {
	return new AddressOfExpr((Expression *)m_expr->clone());
}

AnyType* AddressOfExpr::getType() {
	return m_expr->getType()->getPointerTo();
}

void AddressOfExpr::resolve() { 
	if (m_resolved) return; 
	m_resolved = true;

	m_expr->resolve();

	if (m_expr->returnsPtr() == false) {
		throw CompilerMessage(*m_expr, "can not get the address of this expression"); 
	}
}

AddressOfExpr::AddressOfExpr(Expression* expr) {
	if (expr == nullptr) {
		throw std::runtime_error("AddressOfExpr ctor: expr can not be nullptr");
	}

	m_expr = expr;
}
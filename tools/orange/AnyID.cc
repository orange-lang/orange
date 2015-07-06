/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/

#include <orange/AnyID.h>
#include <orange/SymTable.h>
#include <orange/generator.h>

void AnyID::ensureValid() {
	if (m_any_expr == nullptr) {
		throw std::runtime_error("AnyID::ensureValid(): m_any_expr must not be nullptr!");
	}
}

Value* AnyID::Codegen() {
	ensureValid();
	m_value = m_any_expr->Codegen();
	return m_value;
}

Value* AnyID::getValue() {
	ensureValid();
	return m_any_expr->getValue();
}

ASTNode* AnyID::clone() {
	return new AnyID(m_name);
}

std::string AnyID::string() {
	if (m_any_expr == nullptr) return m_name;
	return m_any_expr->string();
}

bool AnyID::returnsPtr() {
	ensureValid();
	return m_any_expr->returnsPtr();
}

bool AnyID::isBlock() {
	ensureValid();
	return m_any_expr->isBlock();
}

OrangeTy* AnyID::getType() {
	ensureValid();	
	return m_any_expr->getType();
}

void AnyID::resolve() {
	// In the resolve step, we want to actually determine 
	// what object we're using. If it exists in the symbol 
	// table, we use that one. Otherwise, we create our own 
	// VarExpr.

	// If something exists in the symtab, just use that that.
	// We don't want to use existing VarExprs since the code expects
	// every instance of an id that is a variable to have a different 
	// VarExpr instance.
	SymTable* tab = GE::runner()->topBlock()->symtab();
	ASTNode* node = tab->find(m_name);

	if (node != nullptr && node->getClass() != "VarExpr") {
		m_any_expr = (Expression *)node; 
	} else {
		// Otherwise, we have to create something it should default to a VarExpr.
		m_any_expr = new VarExpr(m_name);
  	m_any_expr->resolve();
	}

	// We essentially transform into our any_expr here, so set its parent to our parent.
	addChild("m_any_expr", m_any_expr);

	// Resolve it. If the variable already exists, this probably won't do anything.
}

bool AnyID::isSigned() {
	ensureValid();
	return m_any_expr->isSigned();
}

bool AnyID::isConstant() {
	// This is the only case where we don't need ensureValid;
	// we can assume that isConstant returns false here.
	if (m_any_expr == nullptr) return false;
	
	return m_any_expr->isConstant();
}

Expression* AnyID::expression() {
	ensureValid();
	return m_any_expr;
}

void AnyID::newVarExpr() {
	m_any_expr = new VarExpr(m_name);
	m_any_expr->resolve();
}

AnyID::AnyID(std::string name) {
	m_name = name;
}

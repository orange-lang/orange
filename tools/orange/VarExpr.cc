/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/VarExpr.h>
#include <orange/generator.h>

Value* VarExpr::Codegen() {
	// "Generating" a variable doesn't actually do anything; 
	// its creation is handled by other classes like BinOpExpr.
	// Instead, all this does is return its value.
	return getValue();
}

Value* VarExpr::getValue() {
	// IF we have a value, just return it.
	if (m_value) return m_value;

	// If a variable exists in the symtab by this name, 
	SymTable* tab = GE::runner()->topBlock()->symtab();

	ASTNode* node = tab->find(m_name);
	if (node == nullptr) return m_value; 

	if (node->getClass() != getClass()) {
		throw std::runtime_error(node->string() + " is not a variable!");
	}

	if (node == this) return nullptr;
	return node->getValue();
}

std::string VarExpr::string() {
	return m_name; 
}

Type* VarExpr::getType() {
	// If we've been assigned a value, we'll return that, otherwise 
	// we'll return the default type from ASTNode.
	if (getValue() && getValue()->getType()) 
		return getValue()->getType()->getPointerElementType(); 
	
	if (m_type) {
		return m_type; 
	} else if (GE::runner()->topBlock()->symtab()->find(m_name)) {
		ASTNode* node = GE::runner()->topBlock()->symtab()->find(m_name);

		if (node->getClass() != getClass()) {
			throw std::runtime_error(node->string() + " is not a variable!");
		}
		VarExpr* nodeExpr = (VarExpr*)node;

		if (nodeExpr->m_type) {
			return nodeExpr->m_type;
		}
	}

	return ASTNode::getType(); 
}

void VarExpr::resolve() {
	if (m_resolved) return; 
	m_resolved = true; 

	// Nothing to do for now.
}

void VarExpr::create(bool throwError) {
	// Tries to add this variable to the symbol table.
	// If it already exists in the symbol table, and it's not this, throw an error.
	SymTable* tab = GE::runner()->topBlock()->symtab();

	if (tab->create(m_name, this) == false && throwError) {
		// We couldn't create it because it already exists. 
		// If the ASTNode in the table isn't this var, throw an error.
		if (tab->find(m_name) && tab->find(m_name) != this) {
			throw std::runtime_error("A variable by this name already exists!");
		} 
	}
}

void VarExpr::setSigned(bool signed_var) {
	m_signed = signed_var; 
}

void VarExpr::setValue(Value* value) {
	m_value = GE::builder()->CreateAlloca(value->getType(), nullptr, m_name);
	GE::builder()->CreateStore(value, m_value);
}

VarExpr::VarExpr(std::string name) : m_name(name) { 

}
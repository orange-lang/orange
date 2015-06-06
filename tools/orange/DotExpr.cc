/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/DotExpr.h>
#include <orange/AnyID.h>
#include <orange/generator.h>
#include <orange/EnumStmt.h>

std::string DotExpr::string() {
	return m_LHS->string() + "." + m_RHS;
}

Value* DotExpr::Codegen() {
	if (m_obj->getClass() == "EnumStmt") {
		EnumStmt* enumStmt = (EnumStmt*)m_obj;
		auto value = enumStmt->getEnumValue(m_RHS);
		
		if (value == nullptr) {
			throw std::runtime_error("enumStmt->getEnumValue() returned nullptr!");
		}
		
		return value->Codegen();
	}

	throw std::runtime_error("DotExpr::Codegen(): object is not an enum!");
	return nullptr; 
}

ASTNode* DotExpr::clone() {
	return new DotExpr((AnyID*)m_LHS->clone(), m_RHS);
}

OrangeTy* DotExpr::getType() {
	if (m_obj->getClass() == "EnumStmt") {
		EnumStmt* enumStmt = (EnumStmt*)m_obj;
		return enumStmt->getType();
	}

	throw std::runtime_error("DotExpr::getType(): object is not an enum!");
	return nullptr;
}

void DotExpr::resolve() {
	if (m_resolved) return; 
	m_resolved = true; 

	// resolve LHS and make sure it's an enum
	m_LHS->resolve();
	
	if (m_LHS->expression()->getClass() != "EnumStmt") {
		throw CompilerMessage(*this, ". only supports enums!");
	} 

	EnumStmt* enumStmt = (EnumStmt *)m_LHS->expression();

	// Make sure RHS exists in the enum
	if (enumStmt->getEnumValue(m_RHS) == nullptr) {
		throw CompilerMessage(*this, enumStmt->name() + "." + m_RHS + " doesn't exist!");
	}

	m_obj = enumStmt; 
}

bool DotExpr::isSigned() {
	if (m_obj->getClass() == "EnumStmt") {
		EnumStmt* enumStmt = (EnumStmt*)m_obj;
		return enumStmt->isSigned();
	}

	throw std::runtime_error("DotExpr::getType(): object is not an enum!");
	return nullptr;
}

DotExpr::DotExpr(AnyID* LHS, std::string RHS) {
	m_LHS = LHS; 
	m_RHS = RHS;	

	addChild("m_LHS", m_LHS);
}

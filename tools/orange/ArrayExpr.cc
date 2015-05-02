/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ArrayExpr.h>

std::string ArrayExpr::string() {
	std::stringstream ss; 

	ss << "[ "; 

	for (int i = 0; i < m_elements.size(); i++) {
		ss << m_elements[i]->string();

		if (i + 1 < m_elements.size()) {
			ss << ", ";
		}
	}

	ss << " ]";

	return ss.str();
}

Value* ArrayExpr::Codegen() {
	throw std::runtime_error("NYI: ArrayExpr::Codegen()");
}

ASTNode* ArrayExpr::clone() {
	ArgList cloned_elements; 

	for (auto element : m_elements) {
		cloned_elements.push_back((Expression *)element->clone());
	}

	return new ArrayExpr(cloned_elements);
}

AnyType* ArrayExpr::getType() {
	// If we don't have any elements, we're an int*. 
	if (m_elements.size() == 0) {
		return AnyType::getIntNTy(64)->getPointerTo();
	}

	// We need to get the highest precedence type from all the elements.
	AnyType* highestType = m_elements[0]->getType();

	for (int i = 1; i < m_elements.size(); i++) {
		highestType = CastingEngine::GetFittingType(highestType, m_elements[i]->getType());
	}

	AnyType* ret = highestType->getArray(m_elements.size());
	return ret; 
}

void ArrayExpr::resolve() {
	if (m_resolved) return;
	m_resolved = true ;

	for (auto element : m_elements) {
		element->resolve();
	}
}

ArrayExpr::ArrayExpr(ArgList elements) {
	m_elements = elements;
}

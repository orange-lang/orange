/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ArrayAccess.h>
#include <orange/generator.h>
#include <orange/Values.h>
#include <orange/OrangeTypes.h>

Value* ArrayAccess::Codegen() {
	Value *var = m_variable->Codegen();
	Value *idx = m_idx->Codegen();
	
	if (var == nullptr || idx == nullptr) {
		throw CompilerMessage(*m_variable, "variable never returned a value!");
	}
	
	if (m_variable->getType()->isArrayTy() == false && m_variable->returnsPtr()) {
		var = GE::builder()->CreateLoad(var);
	}

	if (m_idx->returnsPtr()) {
		idx = GE::builder()->CreateLoad(idx);
	}

	if (m_idx->getType()->isIntegerTy() == false) {
		throw CompilerMessage(*m_idx, "index must be an integer type!");
	}

	std::vector<Value *> indicies; 

	// We must push back a subindex of 0 for arrays.
	if (m_variable->getType()->isConstantArray()) {
		IntVal subIdx(0, 64);
		indicies.push_back(subIdx.Codegen());
	}

	indicies.push_back(idx);

	m_value = GE::builder()->CreateInBoundsGEP(var, indicies);	
	return m_value;
}

ASTNode* ArrayAccess::clone() {
	auto clone = new ArrayAccess((Expression *)m_variable->clone(), (Expression *)m_idx->clone());
	clone->copyProperties(this);
	return clone;
}

std::string ArrayAccess::string() {
	std::stringstream ss; 
	ss << m_variable->string() << "["; 
	ss << m_idx->string() << "]";
	return ss.str();
}

void ArrayAccess::resolve() {
	ASTNode::resolve();

	if (m_resolved) return; 
	m_resolved = true;

	// m_variable must be an array or pointer! 
	if (m_variable->getType()->isArrayTy() == false && m_variable->getType()->isPointerTy() == false) {
		throw CompilerMessage(*m_variable, "variable must be an array!");
	}

	m_type = m_variable->getType();

	if (m_type->isConstantArray() || m_type->isVariadicArray()) {
		m_type = m_type->getArrayElementType();
	} else {
		m_type = m_type->getPointerElementType();
	}
}

Expression* ArrayAccess::variable() const {
	return m_variable; 
}

Expression* ArrayAccess::idx() const {
	return m_idx; 
}

ArrayAccess::ArrayAccess(Expression* variable, Expression* idx) { 
	if (variable == nullptr) {
		throw std::runtime_error("ArrayAccess ctor: variable can not be nullptr!");
	}

	if (idx == nullptr) {
		throw std::runtime_error("ArrayAccess ctor: idx can not be nullptr!");
	}

	m_variable = variable; 
	m_idx = idx; 

	addChild("m_variable", m_variable); 
	addChild("m_idx", m_idx);	
}

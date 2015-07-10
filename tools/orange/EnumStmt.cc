/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <orange/EnumStmt.h>
#include <orange/generator.h>

Value* EnumStmt::Codegen() {
	// Reactivate us in the symbol table.
	GE::runner()->topBlock()->symtab()->activate(m_name, this);

	return nullptr;
}

ASTNode* EnumStmt::clone() {
	EnumStmt* clone = new EnumStmt(m_name);
	clone->m_enums = m_enums;
	clone->copyProperties(this);
	return clone;
}

std::string EnumStmt::string() {
	std::stringstream ss;
	ss << "enum " << m_name << std::endl;

	for (auto pair : m_enums) {
		ss << "\t" << pair.name << " = " << pair.value->string() << std::endl;
	}

	ss << "end";

	return ss.str();
}

void EnumStmt::resolve() {
	if (m_enums.size() == 0) {
		m_type = VoidTy::get();
	} else {
		// We need to determine the highest precedence type and then
		// change the other enums to use that type.
		m_type = m_enums[0].value->getType();

		for (unsigned int i = 1; i < m_enums.size(); i++) {
			m_type = CastingEngine::GetFittingType(m_type, m_enums[i].value->getType());
		}
	}

	for (auto& pair : m_enums) {
		ValFactory factory;
		factory.size = m_type->typeSuffix();
		factory.value = pair.value->valueStr();

		delete pair.value; // Delete our old value.
		pair.value = factory.produce();
	}

	// Now that everything is the same type, let's add the EnumStmt to the symbol table.
	SymTable* tab = GE::runner()->topBlock()->symtab();

	if (tab->create(m_name, this) == false) {
		throw CompilerMessage(*this, "Something named " + m_name + " already exists!");
	}



}

void EnumStmt::addEnum(std::string name) {
	// Make sure the name doesn't already exist.
	if (getEnumValue(name) != nullptr) {
		throw CompilerMessage(*this, m_name + "." + name + " already exists!");
	}

	EnumPair pair;
	pair.name = name;

	if (m_last_val) {
		pair.value = m_last_val->increment();
	} else {
		pair.value = new IntVal(0, 8);
	}

	m_enums.push_back(pair);

	m_last_val = pair.value;
}

void EnumStmt::addEnum(std::string name, BaseVal* value) {
	if (value == nullptr) {
		throw std::runtime_error("EnumStmt::addEnum(): value can not be nullptr!");
	}

	if (value->getType()->isFloatingPointTy()) {
		throw CompilerMessage(*this, "floating-point values are not valid for enums!");
	}

	// Make sure the name doesn't already exist.
	if (getEnumValue(name) != nullptr) {
		throw CompilerMessage(*this, m_name + "." + name + " already exists!");
	}

	value->setParent(this);

	EnumPair pair;
	pair.name = name;
	pair.value = value;

	m_enums.push_back(pair);

	m_last_val = pair.value;
}

bool EnumStmt::isSigned() {
	if (m_enums.size() > 0) {
		return m_enums[0].value->isSigned();
	}

	return false;
}

BaseVal* EnumStmt::getEnumValue(std::string name) {
	for (auto pair : m_enums) {
		if (pair.name == name) return pair.value;
	}

	return nullptr;
}

EnumStmt::EnumStmt(std::string name) : m_name(name) {
	m_last_val = nullptr;
}

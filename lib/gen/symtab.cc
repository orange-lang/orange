#include "gen/AST.h"

//// Symobj
Value *Symobj::getValue() const { return m_value; }
Type *Symobj::getType() const { return m_type; }

void Symobj::setValue(Value *v) {
	this->m_value = v;

	if (v != nullptr) {
		m_type = v->getType();
	}
}

void Symobj::setType(Type *t) {
	if (m_value != nullptr)
		return;
	
	m_type = t;
}

//// Symtab
Symobj* SymTable::find(std::string name) {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		auto obj = ptr->objs.find(name);
		if (obj != ptr->objs.end()) {
			return obj->second;
		}
		
		ptr = ptr->parent;
	}
	
	return nullptr;
}

void SymTable::create(std::string name) {
	if (objs.find(name) == objs.end()) {
		objs[name] = new Symobj();
	}
}
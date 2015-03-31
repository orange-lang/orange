#include "gen/Symtab.h"

static int lastID = 0;

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
	if (m_value != nullptr || isLocked == true)
		return;
	
	m_type = t;
}

//// Symtab
Value *SymTable::getRetVal() {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		if (ptr->TheFunction)
			return ptr->retVal;
		ptr = ptr->parent; 
	} 

	return nullptr; 	
}

std::string SymTable::getFunctionName() {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		if (ptr->FunctionName)
			return *(ptr->FunctionName);
		ptr = ptr->parent; 
	} 

	return ""; 
}

Function *SymTable::getFunction() {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		if (ptr->TheFunction)
			return ptr->TheFunction;
		ptr = ptr->parent; 
	} 

	return nullptr; 
}

BasicBlock* SymTable::getFunctionEnd() {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		if (ptr->FunctionEnd)
			return ptr->FunctionEnd; 
		ptr = ptr->parent;
	}
	
	return nullptr;
}

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

void SymTable::dump() {
	SymTable* ptr = this;
	while (ptr != nullptr) {
		printf("Symtab (%d) %p:\n", ptr->ID, ptr);
		for (auto obj : objs) {
			printf("\t%s (value: %d, type: %d)\n", obj.first.c_str(), 
				obj.second->m_value != nullptr, obj.second->m_type != nullptr);
		}	

		ptr = ptr->parent;
	}

	printf("end.\n");
}

SymTable::SymTable() {
	ID = lastID++;
}
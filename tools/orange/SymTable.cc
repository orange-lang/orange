/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/SymTable.h>

static int lastID = 0;

SymTable* SymTable::parent() const {
	return m_parent;
}

SymTable* SymTable::container() const {
	return m_container; 
}

bool SymTable::create(std::string name, ASTNode* node) {
	// If it's already created, return false.
	if (m_objs.find(name) != m_objs.end()) return false; 

	// We require null to not be false 
	if (node == nullptr) return false; 

	// We also require the name to not be blank
	if (name == "") return false; 

	m_objs[name] = new SymObj(node, true); 
	return true; 
}

ASTNode* SymTable::get(std::string name) {
	auto it = m_objs.find(name); 

	if (it != m_objs.end()) {
		return it->second->node; 
	} else {
		return nullptr;
	}
}

ASTNode* SymTable::find(std::string name, bool includeInactive) {
	auto it = m_objs.find(name); 

	// return null if it doesn't exist 
	// alternatively, if we're _not_ including inactive && we found something inactive, keep looking.
	if (it == m_objs.end() || (includeInactive == false && it->second->active == false)) {
		return m_parent ? m_parent->find(name) : nullptr;
	}  


	return it->second->node; 
}

ASTNode* SymTable::findFromAny(std::string name, bool includeInactive) {
	auto it = m_objs.find(name); 

	// return null if it doesn't exist 
	if (it == m_objs.end() || (includeInactive == false && it->second->active == false)) {
		if (m_parent) {
			auto obj = m_parent->findFromAny(name); 
			if (obj) return obj; 
		}

		if (m_container) {
			auto obj = m_container->findFromAny(name);
			if (obj) return obj; 
		}

		return nullptr;
	}  

	return it->second->node; 
}

bool SymTable::activate(std::string name, ASTNode* node) {
	auto it = m_objs.find(name); 

	if (it == m_objs.end()) {
		return false; 
	}

	// Make sure the node matches.
	if (it->second->node == node) {
		it->second->active = true; 
		return true;
	}

	return false;
}

void SymTable::reset() {
	for (auto obj : m_objs) {
		obj.second->active = false;
	}
}

ASTNode* SymTable::findStructure(std::string className) {
	SymTable* ptr = this; 

	while (ptr != nullptr) {
		// If the ptr has a structure and the class matches our param, we found it
		if (ptr->m_structure && ptr->m_structure->getClass() == className) {
			return ptr->m_structure; 
		}

		// Continue to traverse up the tree
		ptr = ptr->m_parent; 
	}

	// We didn't find it; return nullptr.
	return nullptr; 
}

void SymTable::setStructure(ASTNode* structure) {
	m_structure = structure; 
}

SymTable* SymTable::clone() {
	SymTable* clonedSymtab = new SymTable(m_parent, m_container);
	clonedSymtab->m_structure = m_structure; 
	clonedSymtab->m_objs = m_objs;
	return clonedSymtab;
}

int SymTable::ID() const { 
	return m_ID; 
}

bool SymTable::root() const {
	return m_root;
}


SymTable::SymTable(bool isRoot) {
	m_ID = lastID++;
	m_root = isRoot; 
	m_parent = nullptr;
}

SymTable::SymTable(SymTable* parent) {
	m_ID = lastID++;
	m_parent = m_container = parent;
}

SymTable::SymTable(SymTable* parent, SymTable* container) {
	m_ID = lastID++;
	m_parent = parent; 
	m_container = container; 
}


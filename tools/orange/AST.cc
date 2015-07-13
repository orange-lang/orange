/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/AST.h>
#include <orange/generator.h>
#include <orange/Block.h>
#include <sstream>
#include <helper/string.h>
#include <orange/CastingEngine.h>

unsigned long lastID = 0;

void ASTNode::addChild(ASTNode* child) {
	if (child == nullptr) return; 
	child->setParent(this);
	m_children.push_back(child);
}

void ASTNode::addChild(std::string tag, ASTNode* child) {
	if (child == nullptr) return;
	child->setParent(this);
	m_children.push_back(child);
}

unsigned long ASTNode::ID() const {
	return m_ID; 
}

std::string ASTNode::tag() const {
	return m_tag; 
}

void ASTNode::setTag(std::string tag) {
	m_tag = tag;
}

std::vector<ASTNode*> ASTNode::children() const {
	return m_children;
}

std::vector<ASTNode*> ASTNode::siblings() const {
	std::vector<ASTNode*> copy; 
	if (m_parent == nullptr) return copy; 

	copy = m_parent->m_children; 
	return copy;
}

bool ASTNode::contains(ASTNode* node) {
	if (this == node) return true; 

	for (auto child : m_children) {
		if (child == node) return true; 
		if (child->contains(node)) return true; 
	}

	return false;
}

void ASTNode::copyProperties(ASTNode* from) {
	setLocation(from->location());
}

ASTNode* ASTNode::dependency() const { 
	return m_dependency; 
}

bool ASTNode::resolved() const { 
	return m_resolved; 
}

Value* ASTNode::Codegen() { 
	return nullptr; 
}	

Value* ASTNode::getValue() { 
	return m_value; 
}

void ASTNode::setValue(Value* value) { 
	m_value = value;
}

ASTNode* ASTNode::clone() { 
	auto clone = new ASTNode(); 
	clone->copyProperties(this);
	return clone; 
}

std::string ASTNode::string() {
	return "";
}

bool ASTNode::returnsPtr() { 
	return false; 
}

bool ASTNode::isBlock() { 
	return false; 
}

OrangeTy* ASTNode::getType() const {
	return m_type; 
}

Type* ASTNode::getLLVMType() const { 
	return getType()->getLLVMType(); 
}

FunctionStmt* ASTNode::getContainingFunction() {
	return (FunctionStmt*)GE::runner()->symtab()->findStructure("FunctionStmt");
}

Block* ASTNode::parentBlock() const {
	auto parentPtr = m_parent; 

	while (parentPtr != nullptr && dynamic_cast<Block *>(parentPtr) == nullptr) {
		parentPtr = parentPtr->m_parent; 
	}

	return (Block *)parentPtr; 
}

ASTNode* ASTNode::parent() const { 
	return m_parent; 
}

void ASTNode::setParent(ASTNode* parent) { 
	m_parent = parent; 
} 

ASTNode* ASTNode::root() const {
	auto ptr = m_parent; 

	while (ptr->m_parent != nullptr) {
		ptr = ptr->m_parent;
	}

	return ptr; 
}	

std::string ASTNode::dump() {
	std::stringstream ss; 
	ss << "[" << getClass() << "] " << m_ID << " " << this << std::endl;

	if (m_dependency) {
		ss << "\t@ [" << m_dependency->getClass() << "] " << m_dependency->m_ID << " " << m_dependency << std::endl;
	}

	for (auto child : m_children) {
		std::vector<std::string> lines = split(child->dump(), '\n');
		for (std::string line : lines) {
			ss << "\t" << line << std::endl;
		}
	}

	return ss.str();
}


void ASTNode::initialize() {
	for (auto child : m_children) {
		child->initialize();
	}
}

/**
 * Determines what node this node depends on being resolved.
 */ 
void ASTNode::mapDependencies() {
	for (auto child : m_children) {
		child->mapDependencies();
	}
}

/**
 * Resolves this object, intended for use during the analysis pass. This function's body 
 * will only ever excecute once, to avoid unnecessary duplication of code.
 */
void ASTNode::resolve() { 
	if (m_dependency) m_dependency->resolve();

	for (auto child : m_children) {
		child->resolve();
	}
}

void ASTNode::newID() {
	m_ID = lastID++;

	for (auto child : m_children) {
		child->newID();
	}
}

bool ASTNode::cast(Value** v, OrangeTy* to, bool force) {
	return CastingEngine::CastValue(v, m_type, to, force);
}

ASTNode::ASTNode() {
	m_ID = lastID++;
}

ASTNode::~ASTNode() {
	
}
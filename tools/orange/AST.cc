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

ASTNode* ASTNode::root() const {
	auto ptr = m_parent; 

	while (ptr->m_parent != nullptr) {
		ptr = ptr->m_parent;
	}

	return ptr; 
}	

std::string ASTNode::dump() {
	std::stringstream ss; 
	ss << "[" << getClass() << "] " << this << std::endl;

	for (auto child : m_children) {
		std::vector<std::string> lines = split(child->dump(), '\n');
		for (std::string line : lines) {
			ss << "\t" << line << std::endl;
		}
	}

	return ss.str();
}

bool ASTNode::contains(ASTNode* node) {
	if (this == node) return true; 

	for (auto child : m_children) {
		if (child == node) return true; 
		if (child->contains(node)) return true; 
	}

	return false;
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

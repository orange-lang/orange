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

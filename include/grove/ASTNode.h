/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

class Module;

/**
 * ASTNode is the root node for any element in the AST.
 */
class ASTNode {
private:
	Module* m_module = nullptr;
	ASTNode* m_parent = nullptr;
public:
	/// Gets the module this node resides in.
	Module* getModule() const;
	
	/// Gets the parent of this node.
	ASTNode* getParent() const;
	
	/// Creates a copy of this node.
	virtual ASTNode* copy() const;
	
	/// Returns whether or not this node is a type.
	template <typename T> bool is()
	{
		return dynamic_cast<T>(this) != nullptr;
	}
	
	/// Casts this node to a certain type.
	template <typename T> T as()
	{
		return dynamic_cast<T>(this);
	}
	
	/// Constructs a new root node with a module.
	ASTNode(Module* module);
	
	/// Constructs a child node with a parent. 
	ASTNode(ASTNode* parent);
};
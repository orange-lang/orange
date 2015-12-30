/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include "CodeBase.h"
#include "OString.h"
#include "SearchSettings.h"

namespace llvm {
	class ConstantFolder;

	template <bool preserveNames>
	class IRBuilderDefaultInserter;

	template <bool preserveNames, typename T, typename Inserter>
	class IRBuilder;
}

typedef llvm::IRBuilder<true, llvm::ConstantFolder,
	llvm::IRBuilderDefaultInserter<true> > LLVMBuilder;

class Module;
class Named;
class Type;

/**
 * ASTNode is the root node for any element in the AST.
 */
class ASTNode : virtual public CodeBase {
	friend Module;
private:
	Module* m_module = nullptr;
	ASTNode* m_parent = nullptr;

	std::vector<ASTNode *> m_children;
	std::vector<ASTNode *> m_dependencies;
protected:
	/// Adds all children as dependencies.
	void addAllChildrenAsDependencies();
	
	void defineCopy(const ASTNode* copy) const;
public:
	/// Gets the module this node resides in.
	Module* getModule() const;
	
	/// Overrides the module for this node.
	/// Use with extreme caution.
	void setModule(Module* module);
	
	/// Gets the parent of this node.
	ASTNode* getParent() const;

	/// Gets all children of this node.
	std::vector<ASTNode *> getChildren() const;

	/// Gets all dependencies of this node.
	std::vector<ASTNode *> getDependencies() const;

	/// Gets the default base member nodes from an ASTNode.
	std::vector<ObjectBase**> defMemberNodes();
	
	/// Gets the default member lists from an ASTNode.
	std::vector<std::vector<ObjectBase*>*> defMemberLists();
	
	/// Gets pointers to member nodes from this ASTNode, including defaults.
	virtual std::vector<ObjectBase**> getMemberNodes() = 0;
	
	/// Gets pointers to member lists from this ASTNode, including defaults.
	virtual std::vector<std::vector<ObjectBase*>*> getMemberLists() = 0;
	
	/// Gets whether or not this node depends on a specified node.
	bool dependsOn(ASTNode* node) const;

	/// Gets the IR builder in the module.
	LLVMBuilder* IRBuilder() const;

	/// Returns whether or not a node is a child of this node.
	bool isChild(const ASTNode* child) const;
	
	/// Adds a node as a dependency to this node.
	void addDependency(ASTNode* dependency);
	
	/// Adds a child to this node.
	void addChild(ASTNode* child, int idx, bool mustExist = false);
	
	/// Adds a child to this node.
	void addChild(ASTNode* child, bool mustExist = false);
	
	/// Add a child relative to a reference child plus a delta.
	void addChild(ASTNode* child, const ASTNode* ref, int delta);
	
	/// Removes a child from this node.
	void removeChild(ASTNode* child);

	/// Returns true if this node is a root node (i.e., has no parent).
	bool isRootNode() const;

	/// Creates a copy of this node.
	virtual ASTNode* copy() const = 0;
	
	/// Initializes this node after creation.
	virtual void initialize();

	/// Populates the depdencies list of this node.
	virtual void findDependencies();

	/// Resolve node. Sets type if applicable.
	virtual void resolve();

	/// Generate code. Sets value if applicable.
	virtual void build();

	/// Finds a parent of a type T.
	template <typename T> T findParent() const
	{
		ASTNode* ptr = getParent();

		while (ptr != nullptr)
		{
			if (ptr->is<T>())
			{
				return ptr->as<T>();
			}

			ptr = ptr->getParent();
		}

		return nullptr;
	}
	
	/// Finds the first child, depth-first, of a type T.
	template <typename T> T findChild() const
	{
		for (auto child : getChildren())
		{
			if (child->is<T>())
			{
				return child->as<T>();
			}

			auto val = child->findChild<T>();
			if (val != nullptr)
			{
				return val;
			}
		}

		return nullptr;
	}

	/// Finds all children, depth-first, of a type T.
	template <typename T> std::vector<T> findChildren() const
	{
		std::vector<T> children;

		for (auto child : getChildren())
		{
			if (child->is<T>())
			{
				children.push_back(child->as<T>());
			}

			auto vals = child->findChildren<T>();
			children.insert(children.end(), vals.begin(), vals.end());
		}

		return children;
	}
	
	/// Replaces instances of this node in a parent, across all members
	/// and vectors, with another node.
	void replace(ASTNode *with);

	/// Determines whether or not there is a named node up the AST accessible
	/// from this node.
	bool hasNamed(OString name, SearchSettings settings) const;
	
	/// Returns a named node from the AST, searched from this node, using
	/// all the parent blocks.
	Named* findNamed(OString name, const Type* type,
					 SearchSettings settings = SearchSettings())
	const;

	/// Gets all Named nodes with a given name from all AST parents.
	std::vector<Named*> findAllNamed(OString name) const;

	/// Constructs a new root node with a module.
	ASTNode(Module* module);

	/// Constructs a child node with a parent.
	ASTNode(ASTNode* parent);

	/// Constructs an orphaned node.
	/// It is up to the parent to add it as a child.
	ASTNode();

	virtual ~ASTNode();
};

//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <vector>
#include <map>

#include <libast/ast.h>
#include <libast/type.h>

namespace orange { namespace analysis {
	/// The type of some node is dependent on a specific context. There always exists a global context,
	/// but a context is created for each function and class. The default context for a function and class
	/// is specified by the literal typed parameters and members for that node. Non-default contexts are created
	/// for instances of functions/classes if the default context is generic.
	class NodeTypeContext {
	private:
		orange::ast::Node* mNode;

		bool mDefault = true;

		NodeTypeContext* mParent = nullptr;
		
		/// The types that uniquely define this context
		std::vector<orange::ast::Type*> mParameters;

		/// Children contexts that rely on this node's context
		/// The children defined here are for different nodes.
		std::vector<NodeTypeContext*> mChildren;
		
		/// The types defined for all the nodes in this context.
		std::map<int, orange::ast::Type*> mTypes;
	public:
		/// Gets the node assigned to this context.
		orange::ast::Node* GetNode() const;
		
		/// Gets all children contexts.
		std::vector<NodeTypeContext*> GetChildrenContexts() const;

		/// Gets all contexts tied a specific node. Searches contexts for any children where this
		/// node also has a context.
		std::vector<NodeTypeContext*> GetChildrenContexts(orange::ast::Node* node, bool recursive) const;
		
		/// Gets the default context for a node from the set of children.
		NodeTypeContext* GetDefaultChildContext(orange::ast::Node* node, bool recursive) const;

		/// Gets the types for this context.
		std::vector<orange::ast::Type*> GetTypes() const;
		
		/// Gets whether this context is generic (i.e., any of the types to initialize it are of var type)
		bool IsGeneric() const;
		
		/// Gets whether this context is the default for a node.
		bool IsDefault() const;
		
		/// Gets the parent of this context, if one exists.
		NodeTypeContext* GetParent() const;
		
		orange::ast::Type* GetNodeType(orange::ast::Node* node) const;

		void SetNodeType(orange::ast::Node* node, orange::ast::Type* type);
		
		void AddChildContext(NodeTypeContext* ctx);

		NodeTypeContext(orange::ast::Node* node, bool isDefault);
		NodeTypeContext(orange::ast::Node* node, NodeTypeContext* parent, bool isDefault, std::vector<orange::ast::Type*> params);
	};
}}
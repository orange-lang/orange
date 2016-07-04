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

#include "error.h"

namespace orange { namespace analysis {
	/// The type of some node is dependent on a specific context. There always exists a global context,
	/// but a context is created for each function and class. The default context for a function and class
	/// is specified by the literal typed parameters and members for that node. Non-default contexts are created
	/// for instances of functions/classes if the default context is generic.
	class NodeTypeContext {
	private:
		/// Node ID this context is for. -1 if global.
		int mID;

		/// The types that uniquely define this context
		std::vector<orange::ast::Type*> mParameters;

		/// Children contexts that rely on this node's context
		/// The children defined here are for different nodes.
		std::vector<NodeTypeContext*> mChildren;

		/// The types defined for all the nodes in this context.
		std::map<int, orange::ast::Type*> mTypes;
	public:
		/// Gets the node ID this context is for.
		int NodeID() const;

		/// Gets whether this context is global.
		bool IsGlobalContext() const;

		/// Gets all children contexts.
		std::vector<NodeTypeContext*> GetChildrenContexts() const;

		/// Gets all contexts tied a specific node. Searches contexts for any children where this
		/// node also has a context.
		std::vector<NodeTypeContext*> GetChildrenContexts(orange::ast::Node* node) const;

		/// Gets the types for this context.
		std::vector<orange::ast::Type*> GetTypes() const;

		/// Gets whether this context is generic (i.e., any of the types to initialize it are of var type)
		bool IsGeneric() const;

		orange::ast::Type* GetNodeType(orange::ast::Node* node) const;

		void SetNodeType(orange::ast::Node* node, orange::ast::Type* type) const;
	};

	/// The type table holds a reference to the global context and provides methods to get the type for any node.
	/// It provides methods for searching for the type of a node, automating the work for searching for the
	/// node throughout the type context tree.
	class TypeTable {
	private:
		NodeTypeContext* mGlobalContext;
	public:
		/// Gets the global context.
		NodeTypeContext* GetGlobalContext() const;

		/// Gets all contexts tied a specific node. Searches contexts for any children where this
		/// node also has a context.
		std::vector<NodeTypeContext*> GetContexts(orange::ast::Node* node) const;

		/// Find the default context for a node.
		NodeTypeContext* GetDefaultContext() const;

		/// Gets the type of a node. A context may be passed in. If no context is specified, the default
		/// context is used.
		orange::ast::Type* GetNodeType(orange::ast::Node* node, NodeTypeContext* context = nullptr);
	};

	class TypeResolution {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
		AnalysisMessageLog mLog;
	public:
		TypeTable* GenerateTypeTable();

		const AnalysisMessageLog GetLog() const;

		TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs);
	};

	/// Validates that an AST is well-formed and isn't missing any required components
	bool ValidateAST(orange::ast::LongBlockExpr* AST);
}}
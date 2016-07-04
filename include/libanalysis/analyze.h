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
	/// Some structures support generic types and can be instantiated with different types. When
	/// that happens, there are several instances of the same structure with different types that initialize
	/// it (like parameters). These types are used as context to determine the type of all children nodes.
	///
	/// For generic blocks, the default context is whatever what was literally typed in a file.
	class NodeTypeContext {
	private:
		/// Node ID this context is for
		int mID;

		/// The types of this context.
		std::vector<orange::ast::Type*> mTypes;
	public:
		/// Gets the node ID this context is for.
		int NodeID() const;

		/// Gets the types for this context.
		std::vector<orange::ast::Type*> GetTypes() const;

		/// Gets whether this context is generic (i.e., any of the types to initialize it are of var type)
		bool IsGeneric() const;
	};

	class TypeTable {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
		std::vector<NodeTypeContext*> mContexts;
	public:
		/// Gets all contexts
		std::vector<NodeTypeContext*> GetContexts() const;

		/// Gets all contexts tied a specific node.
		std::vector<NodeTypeContext*> GetContexts(orange::ast::Node* node) const;

		/// Gets the type of a node. A context may be passed in. If no context is specified, the default
		/// context is used.
		orange::ast::Type* GetNodeType(orange::ast::Node* node, NodeTypeContext* context = nullptr);
	};

	class TypeResolution {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
	public:
		TypeTable* GenerateTypeTable();

		TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs);
	};
}}
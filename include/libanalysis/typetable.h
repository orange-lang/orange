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

#include <libast/search.h>

#include "error.h"

namespace orange { namespace analysis {
	class NodeTypeContext;
	
	class TypeTable {
	private:
		std::vector<NodeTypeContext*> mGlobalContexts;
		orange::ast::ASTSearcher& mSearcher;
		orange::ast::Walker& mWalker;
	public:
		ast::ASTSearcher& GetSearcher() const;
		
		orange::ast::Walker& GetWalker() const;
		
		/// Gets the global contexts.
		std::vector<NodeTypeContext*> GetGlobalContexts() const;
		
		/// Gets the default context for a node, if one exists.
		NodeTypeContext* GetDefaultContext(orange::ast::Node* node) const;
		
		void AddGlobalContext(NodeTypeContext* ctx);
		
		TypeTable(orange::ast::ASTSearcher& searcher, orange::ast::Walker& walker);
	};
}}
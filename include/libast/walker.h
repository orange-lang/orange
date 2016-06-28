/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ast.h"
#include "visitor.h"

namespace orange { namespace ast {
	class Walker {
	public:
		/// Dispatches to the proper walk method. Does not visit any nodes.
		void WalkNode(Visitor* visitor, Node* node);
		void WalkStmt(Visitor* visitor, Statement* node);
		void WalkExpr(Visitor* visitor, Expression* node);
	};


	/// Walker that will visit concrete elements
	class NonTraversalWalker : public Walker {
	public:
	};

	enum TraversalOrder {
		PREORDER,
		POSTORDER
	};

	// Walker that traverses the hierarchy depth-first.
	class DepthFirstWalker : public Walker {
	private:
		TraversalOrder mOrder;
	public:
		DepthFirstWalker(TraversalOrder order);
	};
}}

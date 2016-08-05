//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/typetable.h>
#include <libanalysis/context.h>

#include "resolve.h"

using namespace orange::ast;
using namespace orange::analysis;

std::vector<NodeTypeContext*> TypeTable::GetGlobalContexts() const {
	return mGlobalContexts;
}

ASTSearcher& TypeTable::GetSearcher() const {
	return mSearcher;
}

orange::ast::Walker& TypeTable::GetWalker() const {
	return mWalker;
}

NodeTypeContext* TypeTable::GetDefaultContext(orange::ast::Node* node) const {
	for (auto ctx : mGlobalContexts) {
		if (ctx->GetNodeType(node) && ctx->IsDefault()) return ctx;
	}
	
	return nullptr;
}

void TypeTable::AddGlobalContext(NodeTypeContext* ctx) {
	mGlobalContexts.push_back(ctx);
}

TypeTable::TypeTable(ASTSearcher& searcher, Walker& walker) : mSearcher(searcher), mWalker(walker) { }


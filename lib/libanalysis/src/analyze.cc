//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/analyze.h>
#include <libast/typecheck.h>
#include <libast/walker.h>

#include "resolve.h"

using namespace orange::analysis;

orange::ast::Node* NodeTypeContext::GetNode() const { return mNode; }

std::vector<NodeTypeContext*> NodeTypeContext::GetChildrenContexts() const { return mChildren; }

std::vector<orange::ast::Type*> NodeTypeContext::GetTypes() const { return mParameters; }

std::vector<NodeTypeContext*> NodeTypeContext::GetChildrenContexts(orange::ast::Node* node) const {
	std::vector<NodeTypeContext*> contexts;

	for (auto ctx : mChildren) {
		if (ctx->mNode->id == mNode->id) contexts.push_back(ctx);
		auto nested_contexts = ctx->GetChildrenContexts(node);
		contexts.insert(contexts.end(), nested_contexts.begin(), nested_contexts.end());
	}

	return contexts;
}

bool NodeTypeContext::IsGeneric() const {
	for (auto type : mParameters) {
		if (IsGenericType(type)) return true;
	}

	return false;
}

orange::ast::Type* NodeTypeContext::GetNodeType(orange::ast::Node* node) const {
	auto it = mTypes.find(node->id);
	return (it != mTypes.end()) ? it->second : nullptr;
}

void NodeTypeContext::SetNodeType(orange::ast::Node* node, orange::ast::Type* type) {
	mTypes[node->id] = type;
}


NodeTypeContext::NodeTypeContext(orange::ast::Node* node) : mNode(node) { }

NodeTypeContext::NodeTypeContext(orange::ast::Node* node, NodeTypeContext* parent,
                                 std::vector<orange::ast::Type*> params) :
mNode(node), mParameters(params), mParent(parent) { }

NodeTypeContext* NodeTypeContext::GetParent() const { return mParent; }

std::vector<NodeTypeContext*> TypeTable::GetGlobalContexts() const { return mGlobalContexts; }

NodeTypeContext* TypeTable::GetDefaultContext(orange::ast::Node* node) const {
	for (auto ctx : mGlobalContexts) {
		if (ctx->GetNode()->id == node->id && ctx->GetTypes().size() == 0) return ctx;
	}
	
	return nullptr;
}

void TypeTable::AddGlobalContext(NodeTypeContext* ctx) { mGlobalContexts.push_back(ctx); }

TypeTable::TypeTable() { }

TypeTable* TypeResolution::GenerateTypeTable() {
	auto tt = new TypeTable();

	DefaultASTSearcher searcher(mASTs);
	
	// Create a global context for each AST.
	for (auto ast : mASTs) {
		auto ctx = new NodeTypeContext(ast);
		tt->AddGlobalContext(ctx);
	}
	
	// Resolve each context.
	for (auto ctx : tt->GetGlobalContexts()) {
		ResolveVisitor resolver(tt, ctx, mLog, searcher);
		DepthFirstWalker walker(TraversalOrder::POSTORDER);
		
		walker.WalkLongBlockExpr(&resolver, asA<LongBlockExpr>(ctx->GetNode()));
	}
	
	return tt;
}

const AnalysisMessageLog TypeResolution::GetLog() const { return mLog; }

TypeResolution::TypeResolution(orange::ast::LongBlockExpr* ast) {
	mASTs.push_back(ast);
}

TypeResolution::TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs) : mASTs(ASTs) { }

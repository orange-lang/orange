//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/context.h>

#include "resolve.h"

using namespace orange::analysis;

NodeTypeContext* NodeTypeContext::GetParent() const {
	return mParent;
}

bool NodeTypeContext::IsDefault() const {
	return mDefault;
}

orange::ast::Node* NodeTypeContext::GetNode() const {
	return mNode;
}

std::vector<NodeTypeContext*> NodeTypeContext::GetChildrenContexts() const {
	return mChildren;
}

std::vector<orange::ast::Type*> NodeTypeContext::GetTypes() const {
	return mParameters;
}

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

void NodeTypeContext::AddChildContext(NodeTypeContext* ctx) {
	mChildren.push_back(ctx);
}

NodeTypeContext::NodeTypeContext(orange::ast::Node* node, bool def) : mNode(node), mDefault(def) { }

NodeTypeContext::NodeTypeContext(orange::ast::Node* node, NodeTypeContext* parent, bool def,
                                 std::vector<orange::ast::Type*> params) :
	mNode(node), mParameters(params), mParent(parent), mDefault(def) { }

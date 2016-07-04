//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/analyze.h>
#include <libast/typecheck.h>

using namespace orange::analysis;

int NodeTypeContext::NodeID() const { return mID; }

bool NodeTypeContext::IsGlobalContext() const { return mID == -1; }

bool NodeTypeContext::IsDefault() const { return mDefault; }

std::vector<NodeTypeContext*> NodeTypeContext::GetChildrenContexts() const { return mChildren; }

std::vector<orange::ast::Type*> NodeTypeContext::GetTypes() const { return mParameters; }

std::vector<NodeTypeContext*> NodeTypeContext::GetChildrenContexts(orange::ast::Node* node) const {
	std::vector<NodeTypeContext*> contexts;

	for (auto ctx : mChildren) {
		if (ctx->mID == node->id) contexts.push_back(ctx);
		auto nested_contexts = ctx->GetChildrenContexts(node);
		contexts.insert(contexts.end(), nested_contexts.begin(), nested_contexts.end());
	}

	return contexts;
}

bool IsTypeGeneric(orange::ast::Type* ty) {
	using namespace orange::ast;

	if (isA<BuiltinType>(ty)) {
		return asA<BuiltinType>(ty)->kind == BuiltinTypeKind::VAR;
	} else if (isA<AccessType>(ty)) {
		auto _ty = asA<AccessType>(ty);
		return IsTypeGeneric(_ty->LHS) || IsTypeGeneric(_ty->RHS);
	} else if (isA<IdentifierType>(ty)) {
		// TODO: this may be true, depending on the circumstances
		return false;
	} else if (isA<ArrayType>(ty)) {
		return IsTypeGeneric(asA<ArrayType>(ty)->base);
	} else if (isA<PointerType>(ty)) {
		return IsTypeGeneric(asA<PointerType>(ty)->base);
	} else if (isA<ReferenceType>(ty)) {
		return IsTypeGeneric(asA<ReferenceType>(ty)->base);
	} else if (isA<TupleType>(ty)) {
		auto _ty = asA<TupleType>(ty);
		for (auto innerTy : _ty->types) {
			if (IsTypeGeneric(innerTy)) return true;
		}

		return false;
	} else if (isA<FunctionType>(ty)) {
		auto _ty = asA<FunctionType>(ty);

		for (auto innerTy : _ty->params) {
			if (IsTypeGeneric(innerTy)) return true;
		}

		return IsTypeGeneric(_ty->returnType);
	} else throw std::runtime_error("Compiler bug: Unexpected type");
}


bool NodeTypeContext::IsGeneric() const {
	for (auto type : mParameters) {
		if (IsTypeGeneric(type)) return true;
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

NodeTypeContext* TypeTable::GetGlobalContext() const { return mGlobalContext; }


NodeTypeContext* TypeTable::GetDefaultContext(orange::ast::Node* node) const {
	// TODO: Find the default context
	// If this node has a context, get the default context for this node.

	// If not, find the nearest parent of a node where a context exists.
	// Then, with the contexts for that parent, get the default one.
	return nullptr;
}

orange::ast::Type* TypeTable::GetNodeType(orange::ast::Node* node, NodeTypeContext* context) {
	if (context == nullptr) context = GetDefaultContext(node);
	return context->GetNodeType(node);
}

TypeTable* TypeResolution::GenerateTypeTable() {
	return nullptr;
}

const AnalysisMessageLog TypeResolution::GetLog() const { return mLog; }

TypeResolution::TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs) : mASTs(ASTs) { }

//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/search.h>
#include <libast/visitor.h>
#include <libast/walker.h>

using namespace orange::ast;

class NamedNodeFinder : public Visitor {
private:
	ReferenceIDExpr* mName = nullptr;
	ASTSearcher* mSearcher = nullptr;
	Node* mNode = nullptr;
public:
	Node* GetNode() const { return mNode; }

	/// Returns whether or not a node is "declarative" (e.g., declares a structure, function, enum, class, etc)
	bool IsDeclarativeNode(Node* node) {
		return isA<ExternFuncStmt>(node) || isA<FunctionExpr>(node) || isA<EnumStmt>(node) || isA<ClassStmt>(node) ||
			isA<VarDeclExpr>(node);
	}

	virtual void VisitNamedIDExpr(NamedIDExpr* node) {
		if (node->name != mName->name) return;
		// This matches, let's continuously search for the parent of this node until we find a declarative block.

		Node* it = node;
		while (it != nullptr) {
			if (IsDeclarativeNode(it)) break;
			it = mSearcher->GetParent(it);
		}

		mNode = it == node ? nullptr : it;
	}

	NamedNodeFinder(ReferenceIDExpr* name, ASTSearcher* searcher) : mName(name), mSearcher(searcher) { }
};

class ParentFinderVisitor : public Visitor {
private:
	Node* mParent = nullptr;
	Node* mChild = nullptr;
public:
	Node* GetParent() const { return mParent; }
	Node* GetChild() const { return mChild; }

	virtual void VisitLoopStmt(LoopStmt* node) override {
		if (node->initializer == mChild) mParent = node;
		if (node->condition == mChild) mParent = node;
		if (node->afterthought == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitForeachStmt(ForeachStmt* node) override {
		if (node->body == mChild) mParent = node;
		if (node->declaration == mChild) mParent = node;
		if (node->value == mChild) mParent = node;
	}

	virtual void VisitYieldStmt(YieldStmt* node) override {
		if (node->value == mChild) mParent = node;
	}

	virtual void VisitReturnStmt(ReturnStmt* node) override {
		if (node->value == mChild) mParent = node;
	}

	virtual void VisitAggregateStmt(AggregateStmt* node) override {
		if (node->name == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitExternFuncStmt(ExternFuncStmt* node) override {
		if (node->name == mChild) mParent = node;
		for (auto param : node->params) if (param == mChild) mParent = node;
	}

	virtual void VisitEnumValue(EnumValue* node) override {
		if (node->name == mChild) mParent = node;
		for (auto param : node->params) if (param == mChild) mParent = node;
	}

	virtual void VisitEnumStmt(EnumStmt* node) override {
		if (node->name == mChild) mParent = node;
		for (auto value : node->values) if (value == mChild) mParent = node;
	}

	virtual void VisitClassStmt(ClassStmt* node) override {
		if (node->name == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
		for (auto super : node->supers) if (super == mChild) mParent = node;
	}

	virtual void VisitInterfaceStmt(InterfaceStmt* node) override {
		if (node->name == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitExtendStmt(ExtendStmt* node) override {
		if (node->body == mChild) mParent = node;
		if (node->name == mChild) mParent = node;
		for (auto super : node->supers) if (super == mChild) mParent = node;
	}

	virtual void VisitNamespaceStmt(NamespaceStmt* node) override {
		if (node->name == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitImportStmt(ImportStmt* node) override {
		if (node->name == mChild) mParent = node;
	}

	virtual void VisitGetterStmt(GetterStmt* node) override {
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitSetterStmt(SetterStmt* node) override {
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitPropertyStmt(PropertyStmt* node) override {
		if (node->name == mChild) mParent = node;
		if (node->body == mChild) mParent = node;
	}

	virtual void VisitThrowStmt(ThrowStmt* node) override {
		if (node->exception == mChild) mParent = node;
	}

	virtual void VisitDeleteStmt(DeleteStmt* node) override {
		if (node->deallocation == mChild) mParent = node;
	}

	virtual void VisitExprStmt(ExprStmt* node) override {
		if (node->expression == mChild) mParent = node;
	}

	virtual void VisitVarDeclExpr(VarDeclExpr* node) override {
		for (auto binding : node->bindings) if (binding == mChild) mParent = node;
		if (node->value == mChild) mParent = node;
	}

	virtual void VisitDtorIDExpr(DtorIDExpr* node) override {
		if (node->base == mChild) mParent = node;
	}

	virtual void VisitAccessIDExpr(AccessIDExpr* node) override {
		if (node->LHS == mChild) mParent = node;
		if (node->RHS == mChild) mParent = node;
	}

	virtual void VisitLongBlockExpr(LongBlockExpr* node) override {
		for (auto stmt : node->statements) if (stmt == mChild) mParent = node;
	}

	virtual void VisitShortBlockExpr(ShortBlockExpr* node) override {
		if (node->statement == mChild) mParent = node;
	}

	virtual void VisitBinOpExpr(BinOpExpr* node) override {
		if (node->LHS == mChild) mParent = node;
		if (node->RHS == mChild) mParent = node;
	}

	virtual void VisitUnaryExpr(UnaryExpr* node) override {
		if (node->LHS == mChild) mParent = node;
	}

	virtual void VisitTupleExpr(TupleExpr* node) override {
		for (auto val : node->values) if (val == mChild) mParent = node;
	}

	virtual void VisitArrayExpr(ArrayExpr* node) override {
		for (auto val : node->values) if (val == mChild) mParent = node;
	}

	virtual void VisitArrayRangeExpr(ArrayRangeExpr* node) override {
		if (node->LHS == mChild) mParent = node;
		if (node->RHS == mChild) mParent = node;
	}

	virtual void VisitArrayAccessExpr(ArrayAccessExpr* node) override {
		if (node->expression == mChild) mParent = node;
		if (node->index == mChild) mParent = node;
	}

	virtual void VisitMemberAccessExpr(MemberAccessExpr* node) override {
		if (node->LHS == mChild) mParent = node;
		if (node->RHS == mChild) mParent = node;
	}

	virtual void VisitNamedExpr(NamedExpr* node) override {
		if (node->value == mChild) mParent = node;
		if (node->name == mChild) mParent = node;
	}

	virtual void VisitConditionalBlock(ConditionalBlock* node) override {
		if (node->block == mChild) mParent = node;
		if (node->condition == mChild) mParent = node;
	}

	virtual void VisitIfExpr(IfExpr* node) override {
		for (auto block : node->blocks) if (block == mChild) mParent = node;
	}

	virtual void VisitTernaryExpr(TernaryExpr* node) override {
		if (node->condition == mChild) mParent = node;
		if (node->trueValue == mChild) mParent = node;
		if (node->falseValue == mChild) mParent = node;
	}

	virtual void VisitSwitchPattern(SwitchPattern* node) override {
		if (node->block == mChild) mParent = node;
		for (auto pattern : node->patterns) if (pattern == mChild) mParent = node;
	}

	virtual void VisitSwitchExpr(SwitchExpr* node) override {
		if (node->condition == mChild) mParent = node;
		for (auto pattern : node->patterns) if (pattern == mChild) mParent = node;
	}

	virtual void VisitClassConstraint(ClassConstraint* node) override {
		if (node->identifier == mChild) mParent = node;
	}

	virtual void VisitDefaultCtorConstraint(DefaultCtorConstraint* node) override {
		if (node->identifier == mChild) mParent = node;
	}

	virtual void VisitBaseConstraint(BaseConstraint* node) override {
		if (node->identifier == mChild) mParent = node;
		if (node->base == mChild) mParent = node;
	}

	virtual void VisitDataConstraint(DataConstraint* node) override {
		if (node->identifier == mChild) mParent = node;
	}

	virtual void VisitTypeConstraint(TypeConstraint* node) override {
		if (node->identifier == mChild) mParent = node;
	}

	virtual void VisitGenerics(Generics* node) override {
		for (auto constraint : node->constraints) if (constraint == mChild) mParent = node;
		for (auto ty : node->genericTypes) if (ty == mChild) mParent = node;
	}

	virtual void VisitFunctionExpr(FunctionExpr* node) override {
		if (node->block == mChild) mParent = node;
		if (node->generics == mChild) mParent = node;
		if (node->name == mChild) mParent = node;
		for (auto param : node->params) if (param == mChild) mParent = node;
	}

	virtual void VisitCatchBlock(CatchBlock* node) override {
		if (node->block == mChild) mParent = node;
		if (node->exception == mChild) mParent = node;
	}

	virtual void VisitTryExpr(TryExpr* node) override {
		if (node->block == mChild) mParent = node;
		if (node->finally == mChild) mParent = node;
		for (auto catchb : node->catches) if (catchb == mChild) mParent = node;
	}

	virtual void VisitCastExpr(CastExpr* node) override {
		if (node->expr == mChild) mParent = node;
	}

	virtual void VisitFunctionCallExpr(FunctionCallExpr* node) override {
		if (node->function == mChild) mParent = node;
		for (auto arg : node->args) if (arg == mChild) mParent = node;
	}

	virtual void VisitNewExpr(NewExpr* node) override {
		if (node->allocation == mChild) mParent = node;
	}

	ParentFinderVisitor(Node* child) : mChild(child) { }
};


bool ASTSearcher::ValidateParent(Node* parent, Node* child) {
	ParentFinderVisitor visitor(child);
	DepthFirstWalker walker(TraversalOrder::PREORDER);

	for (auto ast : mASTs) {
		walker.WalkLongBlockExpr(&visitor, ast);
		if (visitor.GetParent() != nullptr) break;
	}

	return visitor.GetParent() == parent;
}

Node* ASTSearcher::GetParentFromCache(Node* child) {
	auto it = mParentCache.find(child->id);
	if (it == mParentCache.end()) return nullptr;

	auto parent = it->second;
	if (ValidateParent(parent, child)) return parent;

	return ValidateParent(parent, child) ? parent : nullptr;
}

void ASTSearcher::AddParentToCache(Node* parent, Node* child) {
	mParentCache[child->id] = parent;
}

Node* ASTSearcher::GetParent(Node* child) {
	auto parent = GetParentFromCache(child);
	if (parent != nullptr) return parent;

	ParentFinderVisitor visitor(child);
	DepthFirstWalker walker(TraversalOrder::PREORDER);

	for (auto ast : mASTs) {
		walker.WalkLongBlockExpr(&visitor, ast);
		if (visitor.GetParent() != nullptr) break;
	}

	AddParentToCache(visitor.GetParent(), child);
	return visitor.GetParent();
}

Node* ASTSearcher::FindNode(Identifier* id, Node* from, bool allowForwardRef) {
	if (isA<ReferenceIDExpr>(id) == false)
		throw std::runtime_error("Don't know how to handle anything other than simple IDs yet");

	// Step one: search the ASTs for a node with an identifier.
	NamedNodeFinder nodeFinder(asA<ReferenceIDExpr>(id), this);

	Node* originalDecl = nullptr;

	for (auto ast : mASTs) {
		mWalker->WalkLongBlockExpr(&nodeFinder, ast);
		originalDecl = nodeFinder.GetNode();
		if (originalDecl != nullptr) break;
	}

	if (originalDecl == nullptr) return nullptr;
	if (allowForwardRef == false && from != nullptr && originalDecl->id > from->id) return nullptr;

	return originalDecl;
}

ASTSearcher::ASTSearcher(std::vector<LongBlockExpr*> asts, Walker* walker) : mASTs(asts), mWalker(walker) { }

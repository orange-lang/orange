//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/analyze.h>

#include <libast/visitor.h>
#include <libast/walker.h>

using namespace orange::ast;

class ValidatorVisitor : public Visitor {
private:
	Walker& mWalker;
	bool mValid = true;
public:
	bool GetValid() const { return mValid; }

	bool BaseValid(Node* node) {
		for (auto flag : node->flags) {
			if (flag == nullptr) return false;
		}

		return true;
	}

	virtual void VisitLoopStmt(LoopStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		if (node->initializer) mWalker.WalkExpr(this, node->initializer);
		if (node->condition) mWalker.WalkExpr(this, node->condition);
		if (node->afterthought) mWalker.WalkExpr(this, node->afterthought);

		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitForeachStmt(ForeachStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->declaration == nullptr) { mValid = false; return; }
		if (node->value == nullptr) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		mWalker.WalkVarDeclExpr(this, node->declaration);
		mWalker.WalkExpr(this, node->value);
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitYieldStmt(YieldStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->value == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->value);
	}

	virtual void VisitReturnStmt(ReturnStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		mWalker.WalkExpr(this, node->value);
	}

	virtual void VisitAggregateStmt(AggregateStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }
		if (node->name) mWalker.WalkIdentifier(this, node->name);
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitExternFuncStmt(ExternFuncStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->retType == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		for (auto param : node->params) {
			if (param == nullptr) { mValid = false; return; }
			mWalker.WalkVarDeclExpr(this, param);
		}
	}

	virtual void VisitEnumValue(EnumValue* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		for (auto param : node->params) {
			if (param == nullptr) { mValid = false; return; }
			mWalker.WalkVarDeclExpr(this, param);
		}
	}

	virtual void VisitEnumStmt(EnumStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		for (auto value : node->values) {
			if (value == nullptr) { mValid = false; return; }
			mWalker.WalkEnumValue(this, value);
		}
	}

	virtual void VisitClassStmt(ClassStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		for (auto super : node->supers) {
			if (super == nullptr) { mValid = false; return; }
			mWalker.WalkIdentifier(this, super);
		}

		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitInterfaceStmt(InterfaceStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitExtendStmt(ExtendStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		for (auto super : node->supers) {
			if (super == nullptr) { mValid = false; return; }
			mWalker.WalkIdentifier(this, super);
		}

		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitNamespaceStmt(NamespaceStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);

		if (node->body != nullptr) mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitImportStmt(ImportStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		mWalker.WalkIdentifier(this, node->name);
	}

	virtual void VisitGetterStmt(GetterStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitSetterStmt(SetterStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitPropertyStmt(PropertyStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->body == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->name);
		mWalker.WalkBlockExpr(this, node->body);
	}

	virtual void VisitThrowStmt(ThrowStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->exception == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->exception);
	}

	virtual void VisitDeleteStmt(DeleteStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->deallocation == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->deallocation);
	}

	virtual void VisitExprStmt(ExprStmt* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->expression == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->expression);
	}

	virtual void VisitVarDeclExpr(VarDeclExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto binding : node->bindings) {
			if (binding == nullptr) { mValid = false; return; }
			mWalker.WalkIdentifier(this, binding);
		}

		for (auto ty : node->types) {
			if (ty == nullptr) { mValid = false; return; }
		}

		if (node->value) mWalker.WalkExpr(this, node->value);
	}

	virtual void VisitAccessIDExpr(AccessIDExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->LHS == nullptr) { mValid = false; return; }
		if (node->RHS == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->LHS);
		mWalker.WalkIdentifier(this, node->RHS);
	}

	virtual void VisitLongBlockExpr(LongBlockExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto stmt : node->statements) {
			if (stmt == nullptr) { mValid = false; return; }
			mWalker.WalkNode(this, stmt);
		}
	}

	virtual void VisitShortBlockExpr(ShortBlockExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->statement == nullptr) { mValid = false; return; }
		mWalker.WalkNode(this, node->statement);
	}

	virtual void VisitBinOpExpr(BinOpExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->LHS == nullptr) { mValid = false; return; }
		if (node->RHS == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->LHS);
		mWalker.WalkExpr(this, node->RHS);
	}

	virtual void VisitUnaryExpr(UnaryExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->LHS == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->LHS);
	}

	virtual void VisitTupleExpr(TupleExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto value : node->values) {
			if (value == nullptr) { mValid = false; return; }
			mWalker.WalkExpr(this, value);
		}
	}

	virtual void VisitArrayExpr(ArrayExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto value : node->values) {
			if (value == nullptr) { mValid = false; return; }
			mWalker.WalkExpr(this, value);
		}
	}

	virtual void VisitArrayRangeExpr(ArrayRangeExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->LHS == nullptr) { mValid = false; return; }
		if (node->RHS == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->LHS);
		mWalker.WalkExpr(this, node->RHS);
	}

	virtual void VisitArrayAccessExpr(ArrayAccessExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->expression == nullptr) { mValid = false; return; }
		if (node->index == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->expression);
		mWalker.WalkExpr(this, node->index);
	}

	virtual void VisitMemberAccessExpr(MemberAccessExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->LHS == nullptr) { mValid = false; return; }
		if (node->RHS == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->LHS);
		mWalker.WalkExpr(this, node->RHS);
	}

	virtual void VisitNamedExpr(NamedExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name == nullptr) { mValid = false; return; }
		if (node->value == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->name);
		mWalker.WalkExpr(this, node->value);
	}

	virtual void VisitConditionalBlock(ConditionalBlock* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->block == nullptr) { mValid = false; return; }

		if (node->condition) mWalker.WalkExpr(this, node->condition);
		mWalker.WalkBlockExpr(this, node->block);
	}

	virtual void VisitIfExpr(IfExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto block : node->blocks) {
			if (block == nullptr) { mValid = false; return; }
			mWalker.WalkConditionalBlock(this, block);
		}
	}

	virtual void VisitTernaryExpr(TernaryExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->condition == nullptr) { mValid = false; return; }
		if (node->trueValue == nullptr) { mValid = false; return; }
		if (node->falseValue == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->condition);
		mWalker.WalkExpr(this, node->trueValue);
		mWalker.WalkExpr(this, node->falseValue);
	}

	virtual void VisitSwitchPattern(SwitchPattern* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto pattern : node->patterns) {
			if (pattern == nullptr) { mValid = false; return; }
			mWalker.WalkExpr(this, pattern);
		}

		if (node->block == nullptr) { mValid = false; return; }
		mWalker.WalkBlockExpr(this, node->block);
	}

	virtual void VisitSwitchExpr(SwitchExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->condition == nullptr) { mValid = false; return; }

		for (auto pattern : node->patterns) {
			if (pattern == nullptr) { mValid = false; return; }
			mWalker.WalkSwitchPattern(this, pattern);
		}
	}

	virtual void VisitClassConstraint(ClassConstraint* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->identifier == nullptr) { mValid = false; return; }
		mWalker.WalkIdentifier(this, node->identifier);
	}

	virtual void VisitDefaultCtorConstraint(DefaultCtorConstraint* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->identifier == nullptr) { mValid = false; return; }
		mWalker.WalkIdentifier(this, node->identifier);
	}

	virtual void VisitBaseConstraint(BaseConstraint* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->identifier == nullptr) { mValid = false; return; }
		if (node->base == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->identifier);
		mWalker.WalkIdentifier(this, node->base);
	}

	virtual void VisitDataConstraint(DataConstraint* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->identifier == nullptr) { mValid = false; return; }
		if (node->dataType == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->identifier);
	}

	virtual void VisitTypeConstraint(TypeConstraint* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->identifier == nullptr) { mValid = false; return; }
		if (node->type == nullptr) { mValid = false; return; }

		mWalker.WalkIdentifier(this, node->identifier);
	}

	virtual void VisitGenerics(Generics* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		for (auto declaredTy : node->genericTypes) {
			if (declaredTy == nullptr) { mValid = false; return; }
			mWalker.WalkIdentifier(this, declaredTy);
		}

		for (auto constraint : node->constraints) {
			if (constraint == nullptr) { mValid = false; return; }
			mWalker.WalkConstraint(this, constraint);
		}
	}

	virtual void VisitFunctionExpr(FunctionExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->name != nullptr) mWalker.WalkIdentifier(this, node->name);
		if (node->generics != nullptr) mWalker.WalkGenerics(this, node->generics);

		for (auto param : node->params) {
			if (param == nullptr) { mValid = false; return; }
			mWalker.WalkVarDeclExpr(this, param);
		}

		if (node->block == nullptr) { mValid = false; return; }
		mWalker.WalkBlockExpr(this, node->block);
	}

	virtual void VisitCatchBlock(CatchBlock* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->exception == nullptr) { mValid = false; return; }
		if (node->block == nullptr) { mValid = false; return; }

		mWalker.WalkVarDeclExpr(this, node->exception);
		mWalker.WalkBlockExpr(this, node->block);
	}

	virtual void VisitTryExpr(TryExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->block == nullptr) { mValid = false; return; }
		mWalker.WalkBlockExpr(this, node->block);

		for (auto catchBlock : node->catches) {
			if (catchBlock == nullptr) { mValid = false; return; }
			mWalker.WalkCatchBlock(this, catchBlock);
		}

		if (node->finally) mWalker.WalkBlockExpr(this, node->finally);
	}

	virtual void VisitCastExpr(CastExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->targetType == nullptr) { mValid = false; return; }
		if (node->expr == nullptr) { mValid = false; return; }

		mWalker.WalkExpr(this, node->expr);
	}

	virtual void VisitFunctionCallExpr(FunctionCallExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->function == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->function);

		for (auto arg : node->args) {
			if (arg == nullptr) { mValid = false; return; }
			mWalker.WalkExpr(this, arg);
		}
	}

	virtual void VisitNewExpr(NewExpr* node) override {
		if (BaseValid(node) == false) { mValid = false; return; }
		if (node->allocation == nullptr) { mValid = false; return; }
		mWalker.WalkExpr(this, node->allocation);
	}

	virtual void VisitIntValue(IntValue* node) override {
		if (node->type == nullptr) { mValid = false; return; }
	}

	virtual void VisitUIntValue(UIntValue* node) override {
		if (node->type == nullptr) { mValid = false; return; }
	}

	ValidatorVisitor(Walker& walker) : mWalker(walker) { }
};

bool orange::analysis::ValidateAST(LongBlockExpr* AST) {
	NonTraversalWalker walker;
	ValidatorVisitor visitor(walker);
	walker.WalkLongBlockExpr(&visitor, AST);

	return visitor.GetValid();
}
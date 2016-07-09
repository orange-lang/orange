//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <map>

#include <libast/visitor.h>
#include <libast/walker.h>
#include <libast/search.h>
#include <libtranslate/translate.h>
#include <libanalysis/analyze.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>

namespace orange { namespace translate {
	using namespace orange::ast;

	typedef llvm::IRBuilder<true, llvm::ConstantFolder, llvm::IRBuilderDefaultInserter<true>> LLVMIRBuilder;

	/// Visitor that builds statements into an LLVM IR program. Requires a custom walker.
	class TranslateVisitor : public Visitor {
	private:
		orange::analysis::NodeTypeContext* mCurrentContext = nullptr;

		std::shared_ptr<llvm::Module> mModule;
		llvm::BasicBlock* mCurrentBlock = nullptr;

		Walker& mWalker;

		std::shared_ptr<LLVMIRBuilder> mBuilder;

		ASTSearcher& mSearcher;

		struct ValueInfo {
			llvm::Value* val;

			// Whether or not this value is an identifier that will
			// be loaded on GetValue.
			bool reference;

			ValueInfo() { }
			ValueInfo(llvm::Value* v, bool ref = false) : val(v), reference(ref) { }
		};

		/// A map of node IDs to values
		std::map<int, ValueInfo> mValues;

		void SetValue(Node* node, ValueInfo vi);
	public:
		llvm::Value* GetValue(Node* node, bool disableLoading = false);

		virtual void VisitLoopStmt(LoopStmt* node) override;
		virtual void VisitForeachStmt(ForeachStmt* node) override;
		virtual void VisitBreakStmt(BreakStmt* node) override;
		virtual void VisitContinueStmt(ContinueStmt* node) override;
		virtual void VisitYieldStmt(YieldStmt* node) override;
		virtual void VisitReturnStmt(ReturnStmt* node) override;
		virtual void VisitAggregateStmt(AggregateStmt* node) override;
		virtual void VisitExternFuncStmt(ExternFuncStmt* node) override;
		virtual void VisitEnumValue(EnumValue* node) override;
		virtual void VisitEnumStmt(EnumStmt* node) override;
		virtual void VisitClassStmt(ClassStmt* node) override;
		virtual void VisitInterfaceStmt(InterfaceStmt* node) override;
		virtual void VisitExtendStmt(ExtendStmt* node) override;
		virtual void VisitGetterStmt(GetterStmt* node) override;
		virtual void VisitSetterStmt(SetterStmt* node) override;
		virtual void VisitPropertyStmt(PropertyStmt* node) override;
		virtual void VisitThrowStmt(ThrowStmt* node) override;
		virtual void VisitDeleteStmt(DeleteStmt* node) override;
		virtual void VisitExprStmt(ExprStmt* node) override;
		virtual void VisitVarDeclExpr(VarDeclExpr* node) override;
		virtual void VisitIntValue(IntValue* node) override;
		virtual void VisitUIntValue(UIntValue* node) override;
		virtual void VisitFloatValue(FloatValue* node) override;
		virtual void VisitDoubleValue(DoubleValue* node) override;
		virtual void VisitStringValue(StringValue* node) override;
		virtual void VisitCharValue(CharValue* node) override;
		virtual void VisitThisID(ThisID* node) override;
		virtual void VisitReferenceIDExpr(ReferenceIDExpr* node) override;
		virtual void VisitNamedIDExpr(NamedIDExpr* node) override;
		virtual void VisitTempIDExpr(TempIDExpr* node) override;
		virtual void VisitDtorIDExpr(DtorIDExpr* node) override;
		virtual void VisitAccessIDExpr(AccessIDExpr* node) override;
		virtual void VisitLongBlockExpr(LongBlockExpr* node) override;
		virtual void VisitShortBlockExpr(ShortBlockExpr* node) override;
		virtual void VisitBinOpExpr(BinOpExpr* node) override;
		virtual void VisitUnaryExpr(UnaryExpr* node) override;
		virtual void VisitTupleExpr(TupleExpr* node) override;
		virtual void VisitArrayExpr(ArrayExpr* node) override;
		virtual void VisitArrayRangeExpr(ArrayRangeExpr* node) override;
		virtual void VisitArrayAccessExpr(ArrayAccessExpr* node) override;
		virtual void VisitMemberAccessExpr(MemberAccessExpr* node) override;
		virtual void VisitNamedExpr(NamedExpr* node) override;
		virtual void VisitConditionalBlock(ConditionalBlock* node) override;
		virtual void VisitIfExpr(IfExpr* node) override;
		virtual void VisitTernaryExpr(TernaryExpr* node) override;
		virtual void VisitSwitchPattern(SwitchPattern* node) override;
		virtual void VisitSwitchExpr(SwitchExpr* node) override;
		virtual void VisitClassConstraint(ClassConstraint* node) override;
		virtual void VisitDefaultCtorConstraint(DefaultCtorConstraint* node) override;
		virtual void VisitBaseConstraint(BaseConstraint* node) override;
		virtual void VisitDataConstraint(DataConstraint* node) override;
		virtual void VisitTypeConstraint(TypeConstraint* node) override;
		virtual void VisitGenerics(Generics* node) override;
		virtual void VisitFunctionExpr(FunctionExpr* node) override;
		virtual void VisitCatchBlock(CatchBlock* node) override;
		virtual void VisitTryExpr(TryExpr* node) override;
		virtual void VisitCastExpr(CastExpr* node) override;
		virtual void VisitFunctionCallExpr(FunctionCallExpr* node) override;
		virtual void VisitNewExpr(NewExpr* node) override;

		void SetCurrentBlock(llvm::BasicBlock* currentBlock);
		void SetCurrentContext(orange::analysis::NodeTypeContext* ctx);

		TranslateVisitor(Walker& walker, std::shared_ptr<llvm::Module> mod, ASTSearcher& searcher);
	};
}}
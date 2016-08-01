//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <stack>

#include <libast/visitor.h>
#include <libast/search.h>

#include <libanalysis/error.h>
#include <libanalysis/analyze.h>

namespace orange { namespace analysis {
	using namespace orange::ast;

	/// Visitor that determines the types for specific nodes. Best used with
	/// a depth-first, post-order walker, as the type of a node depends on the
	/// types of its components
	class ResolveVisitor : public Visitor {
	private:
		NodeTypeContext* mContext;
		ASTSearcher& mSearcher;
		AnalysisMessageLog& mLog;
	public:
		virtual void VisitYieldStmt(YieldStmt* node) override;
		virtual void VisitReturnStmt(ReturnStmt* node) override;
		virtual void VisitExternFuncStmt(ExternFuncStmt* node) override;
		virtual void VisitClassStmt(ClassStmt* node) override;
		virtual void VisitGetterStmt(GetterStmt* node) override;
		virtual void VisitPropertyStmt(PropertyStmt* node) override;
		virtual void VisitVarDeclExpr(VarDeclExpr* node) override;
		virtual void VisitBoolValue(BoolValue* node) override;
		virtual void VisitIntValue(IntValue* node) override;
		virtual void VisitUIntValue(UIntValue* node) override;
		virtual void VisitFloatValue(FloatValue* node) override;
		virtual void VisitDoubleValue(DoubleValue* node) override;
		virtual void VisitStringValue(StringValue* node) override;
		virtual void VisitCharValue(CharValue* node) override;
		virtual void VisitThisID(ThisID* node) override;
		virtual void VisitReferenceIDExpr(ReferenceIDExpr* node) override;
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
		virtual void VisitConditionalBlock(ConditionalBlock* node) override;
		virtual void VisitIfExpr(IfExpr* node) override;
		virtual void VisitTernaryExpr(TernaryExpr* node) override;
		virtual void VisitSwitchPattern(SwitchPattern* node) override;
		virtual void VisitSwitchExpr(SwitchExpr* node) override;
		virtual void VisitFunctionExpr(FunctionExpr* node) override;
		virtual void VisitCatchBlock(CatchBlock* node) override;
		virtual void VisitTryExpr(TryExpr* node) override;
		virtual void VisitCastExpr(CastExpr* node) override;
		virtual void VisitFunctionCallExpr(FunctionCallExpr* node) override;
		virtual void VisitNewExpr(NewExpr* node) override;
		virtual void VisitEnumMatch(EnumMatch* node) override;

		ResolveVisitor(NodeTypeContext* context, AnalysisMessageLog& log, ASTSearcher& searcher);
	};
}}
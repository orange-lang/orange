/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ast.h"

namespace orange { namespace ast {
	class Visitor {
	public:
		void VisitCommentStmt(CommentStmt* node) { }
		void VisitLoopStmt(LoopStmt* node) { }
		void VisitForeachStmt(ForeachStmt* node) { }
		void VisitBreakStmt(BreakStmt* node) { }
		void VisitContinueStmt(ContinueStmt* node) { }
		void VisitYieldStmt(YieldStmt* node) { }
		void VisitReturnStmt(ReturnStmt* node) { }
		void VisitAggregateStmt(AggregateStmt* node) { }
		void VisitExternFuncStmt(ExternFuncStmt* node) { }
		void VisitEnumValue(EnumValue* node) { }
		void VisitEnumStmt(EnumStmt* node) { }
		void VisitClassStmt(ClassStmt* node) { }
		void VisitInterfaceStmt(InterfaceStmt* node) { }
		void VisitExtendStmt(ExtendStmt* node) { }
		void VisitNamespaceStmt(NamespaceStmt* node) { }
		void VisitImportStmt(ImportStmt* node) { }
		void VisitGetterStmt(GetterStmt* node) { }
		void VisitSetterStmt(SetterStmt* node) { }
		void VisitPropertyStmt(PropertyStmt* node) { }
		void VisitThrowStmt(ThrowStmt* node) { }
		void VisitDeleteStmt(DeleteStmt* node) { }
		void VisitVarDeclExpr(VarDeclExpr* node) { }
		void VisitIntValue(IntValue* node) { }
		void VisitUIntValue(UIntValue* node) { }
		void VisitFloatValue(FloatValue* node) { }
		void VisitDoubleValue(DoubleValue* node) { }
		void VisitStringValue(StringValue* node) { }
		void VisitCharValue(CharValue* node) { }
		void VisitNamedIDExpr(NamedIDExpr* node) { }
		void VisitTempIDExpr(TempIDExpr* node) { }
		void VisitLongBlockExpr(LongBlockExpr* node) { }
		void VisitShortBlockExpr(ShortBlockExpr* node) { }
		void VisitBinOpExpr(BinOpExpr* node) { }
		void VisitUnaryExpr(UnaryExpr* node) { }
		void VisitTupleExpr(TupleExpr* node) { }
		void VisitArrayExpr(ArrayExpr* node) { }
		void VisitArrayRangeExpr(ArrayRangeExpr* node) { }
		void VisitArrayAccessExpr(ArrayAccessExpr* node) { }
		void VisitMemberAccessExpr(MemberAccessExpr* node) { }
		void VisitNamedExpr(NamedExpr* node) { }
		void VisitConditionalBlock(ConditionalBlock* node) { }
		void VisitIfExpr(IfExpr* node) { }
		void VisitTernaryExpr(TernaryExpr* node) { }
		void VisitSwitchPattern(SwitchPattern* node) { }
		void VisitSwitchExpr(SwitchExpr* node) { }
		void VisitClassConstraint(ClassConstraint* node) { }
		void VisitDefaultCtorConstraint(DefaultCtorConstraint* node) { }
		void VisitBaseConstraint(BaseConstraint* node) { }
		void VisitDataConstraint(DataConstraint* node) { }
		void VisitTypeConstraint(TypeConstraint* node) { }
		void VisitGenerics(Generics* node) { }
		void VisitFunctionExpr(FunctionExpr* node) { }
		void VisitCatchBlock(CatchBlock* node) { }
		void VisitTryExpr(TryExpr* node) { }
		void VisitCastExpr(CastExpr* node) { }
		void VisitFunctionCallExpr(FunctionCallExpr* node) { }
		void VisitNewExpr(NewExpr* node) { }
	};
}}

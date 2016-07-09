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
		virtual void VisitCommentStmt(CommentStmt* node) { }
		virtual void VisitLoopStmt(LoopStmt* node) { }
		virtual void VisitForeachStmt(ForeachStmt* node) { }
		virtual void VisitBreakStmt(BreakStmt* node) { }
		virtual void VisitContinueStmt(ContinueStmt* node) { }
		virtual void VisitYieldStmt(YieldStmt* node) { }
		virtual void VisitReturnStmt(ReturnStmt* node) { }
		virtual void VisitAggregateStmt(AggregateStmt* node) { }
		virtual void VisitExternFuncStmt(ExternFuncStmt* node) { }
		virtual void VisitEnumValue(EnumValue* node) { }
		virtual void VisitEnumStmt(EnumStmt* node) { }
		virtual void VisitClassStmt(ClassStmt* node) { }
		virtual void VisitInterfaceStmt(InterfaceStmt* node) { }
		virtual void VisitExtendStmt(ExtendStmt* node) { }
		virtual void VisitNamespaceStmt(NamespaceStmt* node) { }
		virtual void VisitImportStmt(ImportStmt* node) { }
		virtual void VisitGetterStmt(GetterStmt* node) { }
		virtual void VisitSetterStmt(SetterStmt* node) { }
		virtual void VisitPropertyStmt(PropertyStmt* node) { }
		virtual void VisitThrowStmt(ThrowStmt* node) { }
		virtual void VisitDeleteStmt(DeleteStmt* node) { }
		virtual void VisitExprStmt(ExprStmt* node) { }
		virtual void VisitVarDeclExpr(VarDeclExpr* node) { }
		virtual void VisitBoolValue(BoolValue* node) { }
		virtual void VisitIntValue(IntValue* node) { }
		virtual void VisitUIntValue(UIntValue* node) { }
		virtual void VisitFloatValue(FloatValue* node) { }
		virtual void VisitDoubleValue(DoubleValue* node) { }
		virtual void VisitStringValue(StringValue* node) { }
		virtual void VisitCharValue(CharValue* node) { }
		virtual void VisitThisID(ThisID* node) { }
		virtual void VisitReferenceIDExpr(ReferenceIDExpr* node) { }
		virtual void VisitNamedIDExpr(NamedIDExpr* node) { }
		virtual void VisitTempIDExpr(TempIDExpr* node) { }
		virtual void VisitDtorIDExpr(DtorIDExpr* node) { }
		virtual void VisitAccessIDExpr(AccessIDExpr* node) { }
		virtual void VisitLongBlockExpr(LongBlockExpr* node) { }
		virtual void VisitShortBlockExpr(ShortBlockExpr* node) { }
		virtual void VisitBinOpExpr(BinOpExpr* node) { }
		virtual void VisitUnaryExpr(UnaryExpr* node) { }
		virtual void VisitTupleExpr(TupleExpr* node) { }
		virtual void VisitArrayExpr(ArrayExpr* node) { }
		virtual void VisitArrayRangeExpr(ArrayRangeExpr* node) { }
		virtual void VisitArrayAccessExpr(ArrayAccessExpr* node) { }
		virtual void VisitMemberAccessExpr(MemberAccessExpr* node) { }
		virtual void VisitNamedExpr(NamedExpr* node) { }
		virtual void VisitConditionalBlock(ConditionalBlock* node) { }
		virtual void VisitIfExpr(IfExpr* node) { }
		virtual void VisitTernaryExpr(TernaryExpr* node) { }
		virtual void VisitSwitchPattern(SwitchPattern* node) { }
		virtual void VisitSwitchExpr(SwitchExpr* node) { }
		virtual void VisitClassConstraint(ClassConstraint* node) { }
		virtual void VisitDefaultCtorConstraint(DefaultCtorConstraint* node) { }
		virtual void VisitBaseConstraint(BaseConstraint* node) { }
		virtual void VisitDataConstraint(DataConstraint* node) { }
		virtual void VisitTypeConstraint(TypeConstraint* node) { }
		virtual void VisitGenerics(Generics* node) { }
		virtual void VisitFunctionExpr(FunctionExpr* node) { }
		virtual void VisitCatchBlock(CatchBlock* node) { }
		virtual void VisitTryExpr(TryExpr* node) { }
		virtual void VisitCastExpr(CastExpr* node) { }
		virtual void VisitFunctionCallExpr(FunctionCallExpr* node) { }
		virtual void VisitNewExpr(NewExpr* node) { }
	};
}}

//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/compare.h>

#include "resolve.h"
#include "compatibility.h"

using namespace orange::analysis;

void ResolveVisitor::VisitYieldStmt(YieldStmt* node) {
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
}

void ResolveVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
}

void ResolveVisitor::VisitClassStmt(ClassStmt* node) {
}

void ResolveVisitor::VisitGetterStmt(GetterStmt* node) {
}

void ResolveVisitor::VisitPropertyStmt(PropertyStmt* node) {
}

void ResolveVisitor::VisitThrowStmt(ThrowStmt* node) {
}

void ResolveVisitor::VisitDeleteStmt(DeleteStmt* node) {
}

void ResolveVisitor::VisitVarDeclExpr(VarDeclExpr* node) {
}

void ResolveVisitor::VisitIntValue(IntValue* node) {
	mContext->SetNodeType(node, node->type);
}

void ResolveVisitor::VisitUIntValue(UIntValue* node) {
	mContext->SetNodeType(node, node->type);
}

void ResolveVisitor::VisitFloatValue(FloatValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::FLOAT));
}

void ResolveVisitor::VisitDoubleValue(DoubleValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::DOUBLE));
}

void ResolveVisitor::VisitStringValue(StringValue* node) {
	mContext->SetNodeType(node, new PointerType(new BuiltinType(BuiltinTypeKind::CHAR)));
}

void ResolveVisitor::VisitCharValue(CharValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::CHAR));
}

void ResolveVisitor::VisitThisID(ThisID* node) {
}

void ResolveVisitor::VisitNamedIDExpr(NamedIDExpr* node) {
}

void ResolveVisitor::VisitTempIDExpr(TempIDExpr* node) {
}

void ResolveVisitor::VisitDtorIDExpr(DtorIDExpr* node) {
}

void ResolveVisitor::VisitAccessIDExpr(AccessIDExpr* node) {
}

void ResolveVisitor::VisitLongBlockExpr(LongBlockExpr* node) {
}

void ResolveVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
}

void ResolveVisitor::VisitBinOpExpr(BinOpExpr* node) {
	auto tyLHS = mContext->GetNodeType(node->LHS);
	auto tyRHS = mContext->GetNodeType(node->RHS);

	if (CompareType(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, tyLHS);
	} else if (AreTypesCompatible(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, GetImplicitType(tyLHS, tyRHS));
	}
}

void ResolveVisitor::VisitUnaryExpr(UnaryExpr* node) {
}

void ResolveVisitor::VisitTupleExpr(TupleExpr* node) {
}

void ResolveVisitor::VisitArrayExpr(ArrayExpr* node) {
}

void ResolveVisitor::VisitArrayRangeExpr(ArrayRangeExpr* node) {
}

void ResolveVisitor::VisitArrayAccessExpr(ArrayAccessExpr* node) {
}

void ResolveVisitor::VisitMemberAccessExpr(MemberAccessExpr* node) {
}

void ResolveVisitor::VisitNamedExpr(NamedExpr* node) {
}

void ResolveVisitor::VisitConditionalBlock(ConditionalBlock* node) {
}

void ResolveVisitor::VisitIfExpr(IfExpr* node) {
}

void ResolveVisitor::VisitTernaryExpr(TernaryExpr* node) {
}

void ResolveVisitor::VisitSwitchPattern(SwitchPattern* node) {
}

void ResolveVisitor::VisitSwitchExpr(SwitchExpr* node) {
}

void ResolveVisitor::VisitFunctionExpr(FunctionExpr* node) {
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
}

void ResolveVisitor::VisitFunctionCallExpr(FunctionCallExpr* node) {
}

void ResolveVisitor::VisitNewExpr(NewExpr* node) {
}

ResolveVisitor::ResolveVisitor(NodeTypeContext* context) : mContext(context) { }


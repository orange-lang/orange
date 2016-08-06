//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/ast.h>
#include <libast/walker.h>
#include <libast/visitor.h>

using namespace orange::ast;

//
// NonTraversalWalker
//

void NonTraversalWalker::WalkCommentStmt(Visitor* visitor, CommentStmt* node) {
	visitor->VisitCommentStmt(node);
}

void NonTraversalWalker::WalkLoopStmt(Visitor* visitor, LoopStmt* node) {
	visitor->VisitLoopStmt(node);
}

void NonTraversalWalker::WalkBreakStmt(Visitor* visitor, BreakStmt* node) {
	visitor->VisitBreakStmt(node);
}

void NonTraversalWalker::WalkContinueStmt(Visitor* visitor, ContinueStmt* node) {
	visitor->VisitContinueStmt(node);
}

void NonTraversalWalker::WalkReturnStmt(Visitor* visitor, ReturnStmt* node) {
	visitor->VisitReturnStmt(node);
}

void NonTraversalWalker::WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) {
	visitor->VisitExternFuncStmt(node);
}

void NonTraversalWalker::WalkEnumStmt(Visitor* visitor, EnumStmt* node) {
	visitor->VisitEnumStmt(node);
}

void NonTraversalWalker::WalkClassStmt(Visitor* visitor, ClassStmt* node) {
	visitor->VisitClassStmt(node);
}

void NonTraversalWalker::WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) {
	visitor->VisitInterfaceStmt(node);
}

void NonTraversalWalker::WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) {
	visitor->VisitNamespaceStmt(node);
}

void NonTraversalWalker::WalkImportStmt(Visitor* visitor, ImportStmt* node) {
	visitor->VisitImportStmt(node);
}

void NonTraversalWalker::WalkThrowStmt(Visitor* visitor, ThrowStmt* node) {
	visitor->VisitThrowStmt(node);
}

void NonTraversalWalker::WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) {
	visitor->VisitDeleteStmt(node);
}

void NonTraversalWalker::WalkExprStmt(Visitor* visitor, ExprStmt* node) {
	visitor->VisitExprStmt(node);
}

void NonTraversalWalker::WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) {
	visitor->VisitVarDeclExpr(node);
}

void NonTraversalWalker::WalkBoolValue(Visitor* visitor, BoolValue* node) {
	visitor->VisitBoolValue(node);
}

void NonTraversalWalker::WalkIntValue(Visitor* visitor, IntValue* node) {
	visitor->VisitIntValue(node);
}

void NonTraversalWalker::WalkUIntValue(Visitor* visitor, UIntValue* node) {
	visitor->VisitUIntValue(node);
}

void NonTraversalWalker::WalkFloatValue(Visitor* visitor, FloatValue* node) {
	visitor->VisitFloatValue(node);
}

void NonTraversalWalker::WalkDoubleValue(Visitor* visitor, DoubleValue* node) {
	visitor->VisitDoubleValue(node);
}

void NonTraversalWalker::WalkStringValue(Visitor* visitor, StringValue* node) {
	visitor->VisitStringValue(node);
}

void NonTraversalWalker::WalkCharValue(Visitor* visitor, CharValue* node) {
	visitor->VisitCharValue(node);
}

void NonTraversalWalker::WalkThisID(Visitor* visitor, ThisID* node) {
	visitor->VisitThisID(node);
}

void NonTraversalWalker::WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) {
	visitor->VisitReferenceIDExpr(node);
}

void NonTraversalWalker::WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) {
	visitor->VisitNamedIDExpr(node);
}

void NonTraversalWalker::WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) {
	visitor->VisitDtorIDExpr(node);
}

void NonTraversalWalker::WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) {
	visitor->VisitAccessIDExpr(node);
}

void NonTraversalWalker::WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) {
	visitor->VisitLongBlockExpr(node);
}

void NonTraversalWalker::WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) {
	visitor->VisitShortBlockExpr(node);
}

void NonTraversalWalker::WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) {
	visitor->VisitBinOpExpr(node);
}

void NonTraversalWalker::WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) {
	visitor->VisitUnaryExpr(node);
}

void NonTraversalWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* node) {
	visitor->VisitArrayExpr(node);
}

void NonTraversalWalker::WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) {
	visitor->VisitArrayAccessExpr(node);
}

void NonTraversalWalker::WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) {
	visitor->VisitMemberAccessExpr(node);
}

void NonTraversalWalker::WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) {
	visitor->VisitConditionalBlock(node);
}

void NonTraversalWalker::WalkIfExpr(Visitor* visitor, IfExpr* node) {
	visitor->VisitIfExpr(node);
}

void NonTraversalWalker::WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) {
	visitor->VisitTernaryExpr(node);
}

void NonTraversalWalker::WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) {
	visitor->VisitFunctionExpr(node);
}

void NonTraversalWalker::WalkTryExpr(Visitor* visitor, TryExpr* node) {
	visitor->VisitTryExpr(node);
}

void NonTraversalWalker::WalkCastExpr(Visitor* visitor, CastExpr* node) {
	visitor->VisitCastExpr(node);
}

void NonTraversalWalker::WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) {
	visitor->VisitFunctionCallExpr(node);
}

void NonTraversalWalker::WalkCatchBlock(Visitor* visitor, CatchBlock* node) {
	visitor->VisitCatchBlock(node);
}

void NonTraversalWalker::WalkNewExpr(Visitor* visitor, NewExpr* node) {
	visitor->VisitNewExpr(node);
}


//
// DepthFirstWalker
//

void DepthFirstWalker::WalkCommentStmt(Visitor* visitor, CommentStmt* node) {
	visitor->VisitCommentStmt(node);
}

void DepthFirstWalker::WalkLoopStmt(Visitor* visitor, LoopStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitLoopStmt(node);

	if (node->initializer) WalkExpr(visitor, node->initializer);
	if (node->condition) WalkExpr(visitor, node->condition);
	if (node->afterthought) WalkExpr(visitor, node->afterthought);
	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitLoopStmt(node);
}

void DepthFirstWalker::WalkBreakStmt(Visitor* visitor, BreakStmt* node) {
	visitor->VisitBreakStmt(node);
}

void DepthFirstWalker::WalkContinueStmt(Visitor* visitor, ContinueStmt* node) {
	visitor->VisitContinueStmt(node);
}

void DepthFirstWalker::WalkReturnStmt(Visitor* visitor, ReturnStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitReturnStmt(node);

	if (node->value != nullptr) WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitReturnStmt(node);
}

void DepthFirstWalker::WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitExternFuncStmt(node);

	for (auto param : node->params) WalkVarDeclExpr(visitor, param);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitExternFuncStmt(node);
}

void DepthFirstWalker::WalkEnumStmt(Visitor* visitor, EnumStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitEnumStmt(node);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitEnumStmt(node);
}

void DepthFirstWalker::WalkClassStmt(Visitor* visitor, ClassStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitClassStmt(node);

	WalkIdentifier(visitor, node->name);
	for (auto id : node->supers) WalkIdentifier(visitor, id);
	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitClassStmt(node);
}

void DepthFirstWalker::WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitInterfaceStmt(node);

	WalkIdentifier(visitor, node->name);
	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitInterfaceStmt(node);
}

void DepthFirstWalker::WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitNamespaceStmt(node);

	WalkIdentifier(visitor, node->name);
	if (node->body) WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitNamespaceStmt(node);
}

void DepthFirstWalker::WalkImportStmt(Visitor* visitor, ImportStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitImportStmt(node);

	WalkIdentifier(visitor, node->name);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitImportStmt(node);
}

void DepthFirstWalker::WalkThrowStmt(Visitor* visitor, ThrowStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitThrowStmt(node);

	WalkExpr(visitor, node->exception);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitThrowStmt(node);
}

void DepthFirstWalker::WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitDeleteStmt(node);

	WalkExpr(visitor, node->deallocation);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitDeleteStmt(node);
}

void DepthFirstWalker::WalkExprStmt(Visitor* visitor, ExprStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitExprStmt(node);

	WalkExpr(visitor, node->expression);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitExprStmt(node);
}

void DepthFirstWalker::WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitVarDeclExpr(node);

	if (node->value) WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitVarDeclExpr(node);
}

void DepthFirstWalker::WalkBoolValue(Visitor* visitor, BoolValue* node) {
	visitor->VisitBoolValue(node);
}

void DepthFirstWalker::WalkIntValue(Visitor* visitor, IntValue* node) {
	visitor->VisitIntValue(node);
}

void DepthFirstWalker::WalkUIntValue(Visitor* visitor, UIntValue* node) {
	visitor->VisitUIntValue(node);
}

void DepthFirstWalker::WalkFloatValue(Visitor* visitor, FloatValue* node) {
	visitor->VisitFloatValue(node);
}

void DepthFirstWalker::WalkDoubleValue(Visitor* visitor, DoubleValue* node) {
	visitor->VisitDoubleValue(node);
}

void DepthFirstWalker::WalkStringValue(Visitor* visitor, StringValue* node) {
	visitor->VisitStringValue(node);
}

void DepthFirstWalker::WalkCharValue(Visitor* visitor, CharValue* node) {
	visitor->VisitCharValue(node);
}

void DepthFirstWalker::WalkThisID(Visitor* visitor, ThisID* node) {
	visitor->VisitThisID(node);
}

void DepthFirstWalker::WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) {
	visitor->VisitReferenceIDExpr(node);
}

void DepthFirstWalker::WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) {
	visitor->VisitNamedIDExpr(node);
}

void DepthFirstWalker::WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) {
	visitor->VisitDtorIDExpr(node);
}

void DepthFirstWalker::WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitAccessIDExpr(node);

	WalkIdentifier(visitor, node->LHS);
	WalkIdentifier(visitor, node->RHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitAccessIDExpr(node);
}

void DepthFirstWalker::WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitLongBlockExpr(node);

	for (auto stmt : node->statements) WalkNode(visitor, stmt);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitLongBlockExpr(node);
}

void DepthFirstWalker::WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitShortBlockExpr(node);

	WalkNode(visitor, node->statement);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitShortBlockExpr(node);
}

void DepthFirstWalker::WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitBinOpExpr(node);

	WalkExpr(visitor, node->LHS);
	WalkExpr(visitor, node->RHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitBinOpExpr(node);
}

void DepthFirstWalker::WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitUnaryExpr(node);

	WalkExpr(visitor, node->LHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitUnaryExpr(node);
}

void DepthFirstWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayExpr(node);

	for (auto value : node->values) WalkExpr(visitor, value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayExpr(node);
}

void DepthFirstWalker::WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayAccessExpr(node);

	WalkExpr(visitor, node->expression);
	WalkExpr(visitor, node->index);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayAccessExpr(node);
}

void DepthFirstWalker::WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitMemberAccessExpr(node);

	WalkExpr(visitor, node->LHS);
	WalkExpr(visitor, node->RHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitMemberAccessExpr(node);
}

void DepthFirstWalker::WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitConditionalBlock(node);

	if (node->condition) WalkExpr(visitor, node->condition);
	WalkBlockExpr(visitor, node->block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitConditionalBlock(node);
}

void DepthFirstWalker::WalkIfExpr(Visitor* visitor, IfExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitIfExpr(node);

	for (auto block : node->blocks) WalkConditionalBlock(visitor, block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitIfExpr(node);
}

void DepthFirstWalker::WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTernaryExpr(node);

	WalkExpr(visitor, node->condition);
	WalkExpr(visitor, node->trueValue);
	WalkExpr(visitor, node->falseValue);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTernaryExpr(node);
}

void DepthFirstWalker::WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFunctionExpr(node);

	for (auto param : node->params) WalkVarDeclExpr(visitor, param);
	WalkBlockExpr(visitor, node->block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitFunctionExpr(node);
}

void DepthFirstWalker::WalkTryExpr(Visitor* visitor, TryExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTryExpr(node);

	WalkBlockExpr(visitor, node->block);
	WalkBlockExpr(visitor, node->finally);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTryExpr(node);
}

void DepthFirstWalker::WalkCastExpr(Visitor* visitor, CastExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitCastExpr(node);

	WalkExpr(visitor, node->expr);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitCastExpr(node);
}

void DepthFirstWalker::WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFunctionCallExpr(node);

	WalkExpr(visitor, node->function);
	for (auto arg : node->args) WalkExpr(visitor, arg);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitFunctionCallExpr(node);
}

void DepthFirstWalker::WalkCatchBlock(Visitor* visitor, CatchBlock* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitCatchBlock(node);

	WalkVarDeclExpr(visitor, node->exception);
	WalkBlockExpr(visitor, node->block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitCatchBlock(node);
}

void DepthFirstWalker::WalkNewExpr(Visitor* visitor, NewExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitNewExpr(node);

	WalkExpr(visitor, node->allocation);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitNewExpr(node);
}

DepthFirstWalker::DepthFirstWalker(TraversalOrder order) {
	mOrder = order;
}

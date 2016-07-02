//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/ast.h>
#include <libast/walker.h>
#include "typecheck.h"

using namespace orange::ast;

void Walker::WalkNode(Visitor* visitor, Node* node) {
	if      (isA<Statement>(node))  WalkStmt(visitor, asA<Statement>(node));
	else if (isA<Expression>(node)) WalkExpr(visitor, asA<Expression>(node));
	else if (isA<Constraint>(node)) WalkConstraint(visitor, asA<Constraint>(node));
	else if (isA<Generics>(node))   WalkGenerics(visitor, asA<Generics>(node));
	else                            throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkExpr(Visitor* visitor, Expression* node) {
	if      (isA<VarDeclExpr>(node))      WalkVarDeclExpr(visitor, asA<VarDeclExpr>(node));
	else if (isA<EnumValue>(node))        WalkEnumValue(visitor, asA<EnumValue>(node));
	else if (isA<ConditionalBlock>(node)) WalkConditionalBlock(visitor, asA<ConditionalBlock>(node));
	else if (isA<BlockExpr>(node))        WalkBlockExpr(visitor, asA<BlockExpr>(node));
	else if (isA<Value>(node))            WalkValue(visitor, asA<Value>(node));
	else if (isA<BlockExpr>(node))        WalkBlockExpr(visitor, asA<BlockExpr>(node));
	else if (isA<BinOpExpr>(node))        WalkBinOpExpr(visitor, asA<BinOpExpr>(node));
	else if (isA<UnaryExpr>(node))        WalkUnaryExpr(visitor, asA<UnaryExpr>(node));
	else if (isA<TupleExpr>(node))        WalkTupleExpr(visitor, asA<TupleExpr>(node));
	else if (isA<ArrayExpr>(node))        WalkArrayExpr(visitor, asA<ArrayExpr>(node));
	else if (isA<ArrayRangeExpr>(node))   WalkArrayRangeExpr(visitor, asA<ArrayRangeExpr>(node));
	else if (isA<ArrayAccessExpr>(node))  WalkArrayAccessExpr(visitor, asA<ArrayAccessExpr>(node));
	else if (isA<MemberAccessExpr>(node)) WalkMemberAccessExpr(visitor, asA<MemberAccessExpr>(node));
	else if (isA<NamedExpr>(node))        WalkNamedExpr(visitor, asA<NamedExpr>(node));
	else if (isA<IfExpr>(node))           WalkIfExpr(visitor, asA<IfExpr>(node));
	else if (isA<TernaryExpr>(node))      WalkTernaryExpr(visitor, asA<TernaryExpr>(node));
	else if (isA<SwitchExpr>(node))       WalkSwitchExpr(visitor, asA<SwitchExpr>(node));
	else if (isA<FunctionExpr>(node))     WalkFunctionExpr(visitor, asA<FunctionExpr>(node));
	else if (isA<CatchBlock>(node))       WalkCatchBlock(visitor, asA<CatchBlock>(node));
	else if (isA<TryExpr>(node))          WalkTryExpr(visitor, asA<TryExpr>(node));
	else if (isA<CastExpr>(node))         WalkCastExpr(visitor, asA<CastExpr>(node));
	else if (isA<FunctionCallExpr>(node)) WalkFunctionCallExpr(visitor, asA<FunctionCallExpr>(node));
	else                                  throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkStmt(Visitor* visitor, Statement* node) {
	if      (isA<LoopStmt>(node))       WalkLoopStmt(visitor, asA<LoopStmt>(node));
	else if (isA<CommentStmt>(node))    WalkCommentStmt(visitor, asA<CommentStmt>(node));
	else if (isA<SwitchPattern>(node))  WalkSwitchPattern(visitor, asA<SwitchPattern>(node));
	else if (isA<ForeachStmt>(node))    WalkForeachStmt(visitor, asA<ForeachStmt>(node));
	else if (isA<BreakStmt>(node))      WalkBreakStmt(visitor, asA<BreakStmt>(node));
	else if (isA<ContinueStmt>(node))   WalkContinueStmt(visitor, asA<ContinueStmt>(node));
	else if (isA<YieldStmt>(node))      WalkYieldStmt(visitor, asA<YieldStmt>(node));
	else if (isA<ReturnStmt>(node))     WalkReturnStmt(visitor, asA<ReturnStmt>(node));
	else if (isA<AggregateStmt>(node))  WalkAggregateStmt(visitor, asA<AggregateStmt>(node));
	else if (isA<ExternFuncStmt>(node)) WalkExternFuncStmt(visitor, asA<ExternFuncStmt>(node));
	else if (isA<EnumStmt>(node))       WalkEnumStmt(visitor, asA<EnumStmt>(node));
	else if (isA<ClassStmt>(node))      WalkClassStmt(visitor, asA<ClassStmt>(node));
	else if (isA<InterfaceStmt>(node))  WalkInterfaceStmt(visitor, asA<InterfaceStmt>(node));
	else if (isA<ExtendStmt>(node))     WalkExtendStmt(visitor, asA<ExtendStmt>(node));
	else if (isA<NamespaceStmt>(node))  WalkNamespaceStmt(visitor, asA<NamespaceStmt>(node));
	else if (isA<ImportStmt>(node))     WalkImportStmt(visitor, asA<ImportStmt>(node));
	else if (isA<GetterStmt>(node))     WalkGetterStmt(visitor, asA<GetterStmt>(node));
	else if (isA<SetterStmt>(node))     WalkSetterStmt(visitor, asA<SetterStmt>(node));
	else if (isA<PropertyStmt>(node))   WalkPropertyStmt(visitor, asA<PropertyStmt>(node));
	else if (isA<ThrowStmt>(node))      WalkThrowStmt(visitor, asA<ThrowStmt>(node));
	else                                throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkConstraint(Visitor* visitor, Constraint* node) {
	if      (isA<ClassConstraint>(node))       WalkClassConstraint(visitor, asA<ClassConstraint>(node));
	else if (isA<DefaultCtorConstraint>(node)) WalkDefaultCtorConstraint(visitor, asA<DefaultCtorConstraint>(node));
	else if (isA<BaseConstraint>(node))        WalkBaseConstraint(visitor, asA<BaseConstraint>(node));
	else if (isA<DataConstraint>(node))        WalkDataConstraint(visitor, asA<DataConstraint>(node));
	else if (isA<TypeConstraint>(node))        WalkTypeConstraint(visitor, asA<TypeConstraint>(node));
	else                                       throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkValue(Visitor* visitor, Value* node) {
	if      (isA<IntValue>(node))    WalkIntValue(visitor, asA<IntValue>(node));
	else if (isA<UIntValue>(node))   WalkUIntValue(visitor, asA<UIntValue>(node));
	else if (isA<FloatValue>(node))  WalkFloatValue(visitor, asA<FloatValue>(node));
	else if (isA<DoubleValue>(node)) WalkDoubleValue(visitor, asA<DoubleValue>(node));
	else if (isA<StringValue>(node)) WalkStringValue(visitor, asA<StringValue>(node));
	else if (isA<CharValue>(node))   WalkCharValue(visitor, asA<CharValue>(node));
	else                             throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkIdentifier(Visitor* visitor, Identifier* node) {
	if      (isA<NamedIDExpr>(node)) WalkNamedIDExpr(visitor, asA<NamedIDExpr>(node));
	else if (isA<TempIDExpr>(node))  WalkTempIDExpr(visitor, asA<TempIDExpr>(node));
	else                             throw std::runtime_error("Unknown node to walk.");
}

void Walker::WalkBlockExpr(Visitor* visitor, BlockExpr* node) {
	if      (isA<LongBlockExpr>(node))  WalkLongBlockExpr(visitor, asA<LongBlockExpr>(node));
	else if (isA<ShortBlockExpr>(node)) WalkShortBlockExpr(visitor, asA<ShortBlockExpr>(node));
	else                                throw std::runtime_error("Unknown node to walk.");
}

//
// NonTraversalWalker
//

void NonTraversalWalker::WalkCommentStmt(Visitor* visitor, CommentStmt* node) {
	visitor->VisitCommentStmt(node);
}

void NonTraversalWalker::WalkLoopStmt(Visitor* visitor, LoopStmt* node) {
	visitor->VisitLoopStmt(node);
}

void NonTraversalWalker::WalkForeachStmt(Visitor* visitor, ForeachStmt* node) {
	visitor->VisitForeachStmt(node);
}

void NonTraversalWalker::WalkBreakStmt(Visitor* visitor, BreakStmt* node) {
	visitor->VisitBreakStmt(node);
}

void NonTraversalWalker::WalkContinueStmt(Visitor* visitor, ContinueStmt* node) {
	visitor->VisitContinueStmt(node);
}

void NonTraversalWalker::WalkYieldStmt(Visitor* visitor, YieldStmt* node) {
	visitor->VisitYieldStmt(node);
}

void NonTraversalWalker::WalkReturnStmt(Visitor* visitor, ReturnStmt* node) {
	visitor->VisitReturnStmt(node);
}

void NonTraversalWalker::WalkAggregateStmt(Visitor* visitor, AggregateStmt* node) {
	visitor->VisitAggregateStmt(node);
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

void NonTraversalWalker::WalkExtendStmt(Visitor* visitor, ExtendStmt* node) {
	visitor->VisitExtendStmt(node);
}

void NonTraversalWalker::WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) {
	visitor->VisitNamespaceStmt(node);
}

void NonTraversalWalker::WalkImportStmt(Visitor* visitor, ImportStmt* node) {
	visitor->VisitImportStmt(node);
}

void NonTraversalWalker::WalkGetterStmt(Visitor* visitor, GetterStmt* node) {
	visitor->VisitGetterStmt(node);
}

void NonTraversalWalker::WalkSetterStmt(Visitor* visitor, SetterStmt* node) {
	visitor->VisitSetterStmt(node);
}

void NonTraversalWalker::WalkPropertyStmt(Visitor* visitor, PropertyStmt* node) {
	visitor->VisitPropertyStmt(node);
}

void NonTraversalWalker::WalkThrowStmt(Visitor* visitor, ThrowStmt* node) {
	visitor->VisitThrowStmt(node);
}

void NonTraversalWalker::WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) {
	visitor->VisitVarDeclExpr(node);
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

void NonTraversalWalker::WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) {
	visitor->VisitNamedIDExpr(node);
}

void NonTraversalWalker::WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) {
	visitor->VisitTempIDExpr(node);
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

void NonTraversalWalker::WalkTupleExpr(Visitor* visitor, TupleExpr* node) {
	visitor->VisitTupleExpr(node);
}

void NonTraversalWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* node) {
	visitor->VisitArrayExpr(node);
}

void NonTraversalWalker::WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node) {
	visitor->VisitArrayRangeExpr(node);
}

void NonTraversalWalker::WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) {
	visitor->VisitArrayAccessExpr(node);
}

void NonTraversalWalker::WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) {
	visitor->VisitMemberAccessExpr(node);
}

void NonTraversalWalker::WalkNamedExpr(Visitor* visitor, NamedExpr* node) {
	visitor->VisitNamedExpr(node);
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

void NonTraversalWalker::WalkSwitchExpr(Visitor* visitor, SwitchExpr* node) {
	visitor->VisitSwitchExpr(node);
}

void NonTraversalWalker::WalkClassConstraint(Visitor* visitor, ClassConstraint* node) {
	visitor->VisitClassConstraint(node);
}

void NonTraversalWalker::WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node) {
	visitor->VisitDefaultCtorConstraint(node);
}

void NonTraversalWalker::WalkBaseConstraint(Visitor* visitor, BaseConstraint* node) {
	visitor->VisitBaseConstraint(node);
}

void NonTraversalWalker::WalkDataConstraint(Visitor* visitor, DataConstraint* node) {
	visitor->VisitDataConstraint(node);
}

void NonTraversalWalker::WalkTypeConstraint(Visitor* visitor, TypeConstraint* node) {
	visitor->VisitTypeConstraint(node);
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

void NonTraversalWalker::WalkEnumValue(Visitor* visitor, EnumValue* node) {
	visitor->VisitEnumValue(node);
}

void NonTraversalWalker::WalkSwitchPattern(Visitor* visitor, SwitchPattern* node) {
	visitor->VisitSwitchPattern(node);
}

void NonTraversalWalker::WalkGenerics(Visitor* visitor, Generics* node) {
	visitor->VisitGenerics(node);
}

void NonTraversalWalker::WalkCatchBlock(Visitor* visitor, CatchBlock* node) {
	visitor->VisitCatchBlock(node);
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

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitLoopStmt(node);
}

void DepthFirstWalker::WalkForeachStmt(Visitor* visitor, ForeachStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitForeachStmt(node);

	WalkVarDeclExpr(visitor, node->declaration);
	WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitForeachStmt(node);
}

void DepthFirstWalker::WalkBreakStmt(Visitor* visitor, BreakStmt* node) {
	visitor->VisitBreakStmt(node);
}

void DepthFirstWalker::WalkContinueStmt(Visitor* visitor, ContinueStmt* node) {
	visitor->VisitContinueStmt(node);
}

void DepthFirstWalker::WalkYieldStmt(Visitor* visitor, YieldStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitYieldStmt(node);

	WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitYieldStmt(node);
}

void DepthFirstWalker::WalkReturnStmt(Visitor* visitor, ReturnStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitReturnStmt(node);

	WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitReturnStmt(node);
}

void DepthFirstWalker::WalkAggregateStmt(Visitor* visitor, AggregateStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitAggregateStmt(node);

	WalkIdentifier(visitor, node->name);
	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitAggregateStmt(node);
}

void DepthFirstWalker::WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitExternFuncStmt(node);

	WalkIdentifier(visitor, node->name);
	for (auto param : node->params) WalkVarDeclExpr(visitor, param);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitExternFuncStmt(node);
}

void DepthFirstWalker::WalkEnumStmt(Visitor* visitor, EnumStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitEnumStmt(node);

	WalkIdentifier(visitor, node->name);

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

void DepthFirstWalker::WalkExtendStmt(Visitor* visitor, ExtendStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitExtendStmt(node);

	WalkIdentifier(visitor, node->name);
	for (auto id : node->supers) WalkIdentifier(visitor, id);
	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitExtendStmt(node);
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

void DepthFirstWalker::WalkGetterStmt(Visitor* visitor, GetterStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitGetterStmt(node);

	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitGetterStmt(node);
}

void DepthFirstWalker::WalkSetterStmt(Visitor* visitor, SetterStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitSetterStmt(node);

	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitSetterStmt(node);
}

void DepthFirstWalker::WalkPropertyStmt(Visitor* visitor, PropertyStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitPropertyStmt(node);

	WalkBlockExpr(visitor, node->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitPropertyStmt(node);
}

void DepthFirstWalker::WalkThrowStmt(Visitor* visitor, ThrowStmt* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitThrowStmt(node);

	WalkExpr(visitor, node->exception);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitThrowStmt(node);
}

void DepthFirstWalker::WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitVarDeclExpr(node);

	for (auto id : node->bindings) WalkIdentifier(visitor, id);
	if (node->value) WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitVarDeclExpr(node);
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

void DepthFirstWalker::WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) {
	visitor->VisitNamedIDExpr(node);
}

void DepthFirstWalker::WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) {
	visitor->VisitTempIDExpr(node);
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

void DepthFirstWalker::WalkTupleExpr(Visitor* visitor, TupleExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTupleExpr(node);

	for (auto value : node->values) WalkExpr(visitor, value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTupleExpr(node);
}

void DepthFirstWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayExpr(node);

	for (auto value : node->values) WalkExpr(visitor, value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayExpr(node);
}

void DepthFirstWalker::WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayRangeExpr(node);

	WalkExpr(visitor, node->LHS);
	WalkExpr(visitor, node->RHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayRangeExpr(node);
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

void DepthFirstWalker::WalkNamedExpr(Visitor* visitor, NamedExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitNamedExpr(node);

	WalkIdentifier(visitor, node->name);
	WalkExpr(visitor, node->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitNamedExpr(node);
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

void DepthFirstWalker::WalkSwitchExpr(Visitor* visitor, SwitchExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitSwitchExpr(node);

	WalkExpr(visitor, node->condition);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitSwitchExpr(node);
}

void DepthFirstWalker::WalkClassConstraint(Visitor* visitor, ClassConstraint* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitClassConstraint(node);

	WalkIdentifier(visitor, node->identifier);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitClassConstraint(node);
}

void DepthFirstWalker::WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitDefaultCtorConstraint(node);

	WalkIdentifier(visitor, node->identifier);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitDefaultCtorConstraint(node);
}

void DepthFirstWalker::WalkBaseConstraint(Visitor* visitor, BaseConstraint* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitBaseConstraint(node);

	WalkIdentifier(visitor, node->identifier);
	WalkIdentifier(visitor, node->base);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitBaseConstraint(node);
}

void DepthFirstWalker::WalkDataConstraint(Visitor* visitor, DataConstraint* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitDataConstraint(node);

	WalkIdentifier(visitor, node->identifier);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitDataConstraint(node);
}

void DepthFirstWalker::WalkTypeConstraint(Visitor* visitor, TypeConstraint* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTypeConstraint(node);

	WalkIdentifier(visitor, node->identifier);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTypeConstraint(node);
}

void DepthFirstWalker::WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFunctionExpr(node);

	if (node->name) WalkIdentifier(visitor, node->name);
	for (auto param : node->params) WalkVarDeclExpr(visitor, param);

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

void DepthFirstWalker::WalkEnumValue(Visitor* visitor, EnumValue* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitEnumValue(node);

	WalkIdentifier(visitor, node->name);
	for (auto param : node->params) WalkVarDeclExpr(visitor, param);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitEnumValue(node);
}

void DepthFirstWalker::WalkSwitchPattern(Visitor* visitor, SwitchPattern* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitSwitchPattern(node);

	for (auto pattern : node->patterns) WalkExpr(visitor, pattern);
	WalkBlockExpr(visitor, node->block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitSwitchPattern(node);
}

void DepthFirstWalker::WalkCatchBlock(Visitor* visitor, CatchBlock* node) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitCatchBlock(node);

	WalkVarDeclExpr(visitor, node->exception);
	WalkBlockExpr(visitor, node->block);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitCatchBlock(node);
}

DepthFirstWalker::DepthFirstWalker(TraversalOrder order) {
	mOrder = order;
}

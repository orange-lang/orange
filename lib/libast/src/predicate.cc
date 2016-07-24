//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/visitor.h>
#include <libast/typecheck.h>
#include <libast/predicate.h>
#include <libast/ast.h>
#include <libast/walker.h>

using namespace orange::ast;

std::vector<Node*> PredicateWalker::GetMatches() const { return mMatches; }

void PredicateWalker::TestPredicate(Predicate* p, Node* n) {
	if (p->Matches(n)) mMatches.push_back(n);
}

void PredicateWalker::WalkCommentStmt(Predicate* predicate, CommentStmt* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkLoopStmt(Predicate* predicate, LoopStmt* node) {
	TestPredicate(predicate, node);
	
	if (node->initializer) WalkExpr(predicate, node->initializer);
	if (node->condition) WalkExpr(predicate, node->condition);
	if (node->afterthought) WalkExpr(predicate, node->afterthought);
	
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkForeachStmt(Predicate* predicate, ForeachStmt* node) {
	TestPredicate(predicate, node);
	
	WalkVarDeclExpr(predicate, node->declaration);
	WalkExpr(predicate, node->value);
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkBreakStmt(Predicate* predicate, BreakStmt* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkContinueStmt(Predicate* predicate, ContinueStmt* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkYieldStmt(Predicate* predicate, YieldStmt* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->value);
}

void PredicateWalker::WalkReturnStmt(Predicate* predicate, ReturnStmt* node) {
	TestPredicate(predicate, node);
	
	if (node->value) WalkExpr(predicate, node->value);
}

void PredicateWalker::WalkAggregateStmt(Predicate* predicate, AggregateStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkExternFuncStmt(Predicate* predicate, ExternFuncStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	
	for (auto param : node->params) WalkVarDeclExpr(predicate, param);
}

void PredicateWalker::WalkEnumValue(Predicate* predicate, EnumValue* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	
	for (auto param : node->params) WalkVarDeclExpr(predicate, param);
}

void PredicateWalker::WalkEnumStmt(Predicate* predicate, EnumStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	
	for (auto value : node->values) WalkEnumValue(predicate, value);
}

void PredicateWalker::WalkClassStmt(Predicate* predicate, ClassStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	
	for (auto super : node->supers) WalkIdentifier(predicate, super);
	
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkInterfaceStmt(Predicate* predicate, InterfaceStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkExtendStmt(Predicate* predicate, ExtendStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	
	for (auto super : node->supers) WalkIdentifier(predicate, super);
	
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkNamespaceStmt(Predicate* predicate, NamespaceStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	if (node->body) WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkImportStmt(Predicate* predicate, ImportStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
}

void PredicateWalker::WalkGetterStmt(Predicate* predicate, GetterStmt* node) {
	TestPredicate(predicate, node);
	
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkSetterStmt(Predicate* predicate, SetterStmt* node) {
	TestPredicate(predicate, node);
	
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkPropertyStmt(Predicate* predicate, PropertyStmt* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	WalkBlockExpr(predicate, node->body);
}

void PredicateWalker::WalkThrowStmt(Predicate* predicate, ThrowStmt* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->exception);
}

void PredicateWalker::WalkDeleteStmt(Predicate* predicate, DeleteStmt* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->deallocation);
}

void PredicateWalker::WalkExprStmt(Predicate* predicate, ExprStmt* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->expression);
}

void PredicateWalker::WalkVarDeclExpr(Predicate* predicate, VarDeclExpr* node) {
	TestPredicate(predicate, node);
	
	for (auto binding : node->bindings) WalkIdentifier(predicate, binding);
	
	if (node->value) WalkExpr(predicate, node->value);
}

void PredicateWalker::WalkBoolValue(Predicate* predicate, BoolValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkIntValue(Predicate* predicate, IntValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkUIntValue(Predicate* predicate, UIntValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkFloatValue(Predicate* predicate, FloatValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkDoubleValue(Predicate* predicate, DoubleValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkStringValue(Predicate* predicate, StringValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkCharValue(Predicate* predicate, CharValue* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkThisID(Predicate* predicate, ThisID* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkReferenceIDExpr(Predicate* predicate, ReferenceIDExpr* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkNamedIDExpr(Predicate* predicate, NamedIDExpr* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkTempIDExpr(Predicate* predicate, TempIDExpr* node) {
	TestPredicate(predicate, node);
}

void PredicateWalker::WalkDtorIDExpr(Predicate* predicate, DtorIDExpr* node) {
	TestPredicate(predicate, node);
	
	WalkNamedIDExpr(predicate, node->base);
}

void PredicateWalker::WalkAccessIDExpr(Predicate* predicate, AccessIDExpr* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->LHS);
	WalkIdentifier(predicate, node->RHS);
}

void PredicateWalker::WalkLongBlockExpr(Predicate* predicate, LongBlockExpr* node) {
	TestPredicate(predicate, node);
	
	for (auto statement : node->statements) WalkNode(predicate, statement);
}

void PredicateWalker::WalkShortBlockExpr(Predicate* predicate, ShortBlockExpr* node) {
	TestPredicate(predicate, node);
	
	WalkNode(predicate, node->statement);
}

void PredicateWalker::WalkBinOpExpr(Predicate* predicate, BinOpExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->LHS);
	WalkExpr(predicate, node->RHS);
}

void PredicateWalker::WalkUnaryExpr(Predicate* predicate, UnaryExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->LHS);
}

void PredicateWalker::WalkTupleExpr(Predicate* predicate, TupleExpr* node) {
	TestPredicate(predicate, node);
	
	for (auto value : node->values) WalkExpr(predicate, value);
}

void PredicateWalker::WalkArrayExpr(Predicate* predicate, ArrayExpr* node) {
	TestPredicate(predicate, node);
	
	for (auto value : node->values) WalkExpr(predicate, value);
}

void PredicateWalker::WalkArrayRangeExpr(Predicate* predicate, ArrayRangeExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->LHS);
	WalkExpr(predicate, node->RHS);
}

void PredicateWalker::WalkArrayAccessExpr(Predicate* predicate, ArrayAccessExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->expression);
	WalkExpr(predicate, node->index);
}

void PredicateWalker::WalkMemberAccessExpr(Predicate* predicate, MemberAccessExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->LHS);
	WalkIdentifier(predicate, node->RHS);
}

void PredicateWalker::WalkNamedExpr(Predicate* predicate, NamedExpr* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->name);
	WalkExpr(predicate, node->value);
}

void PredicateWalker::WalkConditionalBlock(Predicate* predicate, ConditionalBlock* node) {
	TestPredicate(predicate, node);
	
	if (node->condition) WalkExpr(predicate, node->condition);
	WalkBlockExpr(predicate, node->block);
}

void PredicateWalker::WalkIfExpr(Predicate* predicate, IfExpr* node) {
	TestPredicate(predicate, node);
	
	for (auto block : node->blocks) WalkConditionalBlock(predicate, block);
}

void PredicateWalker::WalkTernaryExpr(Predicate* predicate, TernaryExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->condition);
	WalkExpr(predicate, node->trueValue);
	WalkExpr(predicate, node->falseValue);
}

void PredicateWalker::WalkSwitchPattern(Predicate* predicate, SwitchPattern* node) {
	TestPredicate(predicate, node);
	
	for (auto pattern : node->patterns) WalkExpr(predicate, pattern);
	WalkBlockExpr(predicate, node->block);
}

void PredicateWalker::WalkSwitchExpr(Predicate* predicate, SwitchExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->condition);
	for (auto pattern : node->patterns) WalkSwitchPattern(predicate, pattern);
}

void PredicateWalker::WalkClassConstraint(Predicate* predicate, ClassConstraint* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->identifier);
}

void PredicateWalker::WalkDefaultCtorConstraint(Predicate* predicate, DefaultCtorConstraint* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->identifier);
}

void PredicateWalker::WalkBaseConstraint(Predicate* predicate, BaseConstraint* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->identifier);
	WalkIdentifier(predicate, node->base);
}

void PredicateWalker::WalkDataConstraint(Predicate* predicate, DataConstraint* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->identifier);
}

void PredicateWalker::WalkTypeConstraint(Predicate* predicate, TypeConstraint* node) {
	TestPredicate(predicate, node);
	
	WalkIdentifier(predicate, node->identifier);
}

void PredicateWalker::WalkGenerics(Predicate* predicate, Generics* node) {
	TestPredicate(predicate, node);
	
	for (auto identifier : node->genericTypes) WalkIdentifier(predicate, identifier);
	for (auto constraint : node->constraints) WalkConstraint(predicate, constraint);
}

void PredicateWalker::WalkFunctionExpr(Predicate* predicate, FunctionExpr* node) {
	TestPredicate(predicate, node);
	
	if (node->name) WalkIdentifier(predicate, node->name);
	if (node->generics) WalkGenerics(predicate, node->generics);
	
	for (auto param : node->params) WalkVarDeclExpr(predicate, param);
	
	WalkBlockExpr(predicate, node->block);
}

void PredicateWalker::WalkCatchBlock(Predicate* predicate, CatchBlock* node) {
	TestPredicate(predicate, node);
	
	WalkVarDeclExpr(predicate, node->exception);
	WalkBlockExpr(predicate, node->block);
}

void PredicateWalker::WalkTryExpr(Predicate* predicate, TryExpr* node) {
	TestPredicate(predicate, node);
	
	WalkBlockExpr(predicate, node->block);
	
	for (auto catchBlock : node->catches) WalkCatchBlock(predicate, catchBlock);
	
	WalkBlockExpr(predicate, node->finally);
}

void PredicateWalker::WalkCastExpr(Predicate* predicate, CastExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->expr);
}

void PredicateWalker::WalkFunctionCallExpr(Predicate* predicate, FunctionCallExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->function);
	
	for (auto arg : node->args) WalkExpr(predicate, arg);
}

void PredicateWalker::WalkNewExpr(Predicate* predicate, NewExpr* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->allocation);
}

void PredicateWalker::WalkEnumMatch(Predicate* predicate, EnumMatch* node) {
	TestPredicate(predicate, node);
	
	WalkExpr(predicate, node->value);
	
	for (auto param : node->params) WalkExpr(predicate, param);
}

PredicateWalker::PredicateWalker() { }

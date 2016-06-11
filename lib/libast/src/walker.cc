//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/walker.h>

using namespace orange::ast;

template <typename T>
static T* asA(Node* node) { return dynamic_cast<T*>(node); }

template <typename T>
static bool isA(Node* node) { return asA<T>(node) != nullptr; }

void Walker::WalkNode(Visitor* visitor, Node* node) {
	if (isA<Statement>(node)) {
		WalkStmt(visitor, asA<Statement>(node));
	} else if (isA<Expression>(node)) {
		WalkExpr(visitor, asA<Expression>(node));
	} else {
		throw std::runtime_error("Unknown node to walk.");
	}
}

void Walker::WalkExpr(Visitor* visitor, Expression* node) {
	if (isA<TupleComponent>(node)) {
		WalkTupleComponent(visitor, asA<TupleComponent>(node));
	} else if (isA<TupleExpr>(node)) {
		WalkTupleExpr(visitor, asA<TupleExpr>(node));
	} else if (isA<BinaryExpr>(node)) {
		WalkBinaryExpr(visitor, asA<BinaryExpr>(node));
	} else if (isA<UnaryExpr>(node)) {
		WalkUnaryExpr(visitor, asA<UnaryExpr>(node));
	} else if (isA<ArrayExpr>(node)) {
		WalkArrayExpr(visitor, asA<ArrayExpr>(node));
	} else if (isA<ArrayAccessExpr>(node)) {
		WalkArrayAccessExpr(visitor, asA<ArrayAccessExpr>(node));
	} else if (isA<ArrayRangeExpr>(node)) {
		WalkArrayRangeExpr(visitor, asA<ArrayRangeExpr>(node));
	} else if (isA<BlockExpr>(node)) {
		WalkBlockExpr(visitor, asA<BlockExpr>(node));
	} else if (isA<ConditionalBlock>(node)) {
		WalkConditionalBlock(visitor, asA<ConditionalBlock>(node));
	} else if (isA<IfExpr>(node)) {
		WalkIfExpr(visitor, asA<IfExpr>(node));
	} else if (isA<LoopExpr>(node)) {
		WalkLoopExpr(visitor, asA<LoopExpr>(node));
	} else if (isA<StringExpr>(node)) {
		WalkStringExpr(visitor, asA<StringExpr>(node));
	} else if (isA<VarRefExpr>(node)) {
		WalkVarRefExpr(visitor, asA<VarRefExpr>(node));
	} else if (isA<IntExpr>(node)) {
		WalkIntExpr(visitor, asA<IntExpr>(node));
	} else if (isA<FunctionExpr>(node)) {
		WalkFunctionExpr(visitor, asA<FunctionExpr>(node));
	} else if (isA<FuncCallExpr>(node)) {
		WalkFuncCallExpr(visitor, asA<FuncCallExpr>(node));
	} else if (isA<FloatExpr>(node)) {
		WalkFloatExpr(visitor, asA<FloatExpr>(node));
	} else if (isA<DoubleExpr>(node)) {
		WalkDoubleExpr(visitor, asA<DoubleExpr>(node));
	} else {
		throw std::runtime_error("Unknown expression to walk.");
	}
}

void Walker::WalkStmt(Visitor* visitor, Statement* node) {
	if (isA<PackageStmt>(node)) {
		WalkPackageStmt(visitor, asA<PackageStmt>(node));
	} else if (isA<UsingStmt>(node)) {
		WalkUsingStmt(visitor, asA<UsingStmt>(node));
	} else if (isA<EnumMember>(node)) {
		WalkEnumMember(visitor, asA<EnumMember>(node));
	} else if (isA<ClassStmt>(node)) {
		WalkClassStmt(visitor, asA<ClassStmt>(node));
	} else if (isA<EnumStmt>(node)) {
		WalkEnumStmt(visitor, asA<EnumStmt>(node));
	} else if (isA<VarDeclStmt>(node)) {
		WalkVarDeclStmt(visitor, asA<VarDeclStmt>(node));
	} else if (isA<PropertyStmt>(node)) {
		WalkPropertyStmt(visitor, asA<PropertyStmt>(node));
	} else if (isA<GetterStmt>(node)) {
		WalkGetterStmt(visitor, asA<GetterStmt>(node));
	} else if (isA<SetterStmt>(node)) {
		WalkSetterStmt(visitor, asA<SetterStmt>(node));
	} else if (isA<ExternFuncDeclStmt>(node)) {
		WalkExternFuncDeclStmt(visitor, asA<ExternFuncDeclStmt>(node));
	} else if (isA<FuncDeclStmt>(node)) {
		WalkFuncDeclStmt(visitor, asA<FuncDeclStmt>(node));
	} else if (isA<InterfaceStmt>(node)) {
		WalkInterfaceStmt(visitor, asA<InterfaceStmt>(node));
	} else if (isA<ParamStmt>(node)) {
		WalkParamStmt(visitor, asA<ParamStmt>(node));
	} else if (isA<ExtendsStmt>(node)) {
		WalkExtendsStmt(visitor, asA<ExtendsStmt>(node));
	} else {
		throw std::runtime_error("Unknown statement to walk.");
	}
}


void NonTraversalWalker::WalkPackageStmt(Visitor* visitor, PackageStmt* stmt) {
	visitor->VisitPackageStmt(stmt);
}

void NonTraversalWalker::WalkUsingStmt(Visitor* visitor, UsingStmt* stmt) {
	visitor->VisitUsingStmt(stmt);
}

void NonTraversalWalker::WalkEnumMember(Visitor* visitor, EnumMember* stmt) {
	visitor->VisitEnumMember(stmt);
}

void NonTraversalWalker::WalkClassStmt(Visitor* visitor, ClassStmt* stmt) {
	visitor->VisitClassStmt(stmt);
}

void NonTraversalWalker::WalkEnumStmt(Visitor* visitor, EnumStmt* stmt) {
	visitor->VisitEnumStmt(stmt);
}

void NonTraversalWalker::WalkVarDeclStmt(Visitor* visitor, VarDeclStmt* stmt) {
	visitor->VisitVarDeclStmt(stmt);
}

void NonTraversalWalker::WalkPropertyStmt(Visitor* visitor, PropertyStmt* stmt) {
	visitor->VisitPropertyStmt(stmt);
}

void NonTraversalWalker::WalkGetterStmt(Visitor* visitor, GetterStmt* stmt) {
	visitor->VisitGetterStmt(stmt);
}

void NonTraversalWalker::WalkSetterStmt(Visitor* visitor, SetterStmt* stmt) {
	visitor->VisitSetterStmt(stmt);
}

void NonTraversalWalker::WalkFuncDeclStmt(Visitor* visitor, FuncDeclStmt* stmt) {
	visitor->VisitFuncDeclStmt(stmt);
}

void NonTraversalWalker::WalkExternFuncDeclStmt(Visitor* visitor, ExternFuncDeclStmt* stmt) {
	visitor->VisitExternFuncDeclStmt(stmt);
}

void NonTraversalWalker::WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* stmt) {
	visitor->VisitInterfaceStmt(stmt);
}

void NonTraversalWalker::WalkParamStmt(Visitor* visitor, ParamStmt* stmt) {
	visitor->VisitParamStmt(stmt);
}

void NonTraversalWalker::WalkExtendsStmt(Visitor* visitor, ExtendsStmt* stmt) {
	visitor->VisitExtendsStmt(stmt);
}

void NonTraversalWalker::WalkTupleComponent(Visitor* visitor, TupleComponent* expr) {
	visitor->VisitTupleComponent(expr);
}

void NonTraversalWalker::WalkTupleExpr(Visitor* visitor, TupleExpr* expr) {
	visitor->VisitTupleExpr(expr);
}

void NonTraversalWalker::WalkBinaryExpr(Visitor* visitor, BinaryExpr* expr) {
	visitor->VisitBinaryExpr(expr);
}

void NonTraversalWalker::WalkUnaryExpr(Visitor* visitor, UnaryExpr* expr) {
	visitor->VisitUnaryExpr(expr);
}

void NonTraversalWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* expr) {
	visitor->VisitArrayExpr(expr);
}

void NonTraversalWalker::WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* expr) {
	visitor->VisitArrayAccessExpr(expr);
}

void NonTraversalWalker::WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* expr) {
	visitor->VisitArrayRangeExpr(expr);
}

void NonTraversalWalker::WalkBlockExpr(Visitor* visitor, BlockExpr* expr) {
	visitor->VisitBlockExpr(expr);
}

void NonTraversalWalker::WalkConditionalBlock(Visitor* visitor, ConditionalBlock* expr) {
	visitor->VisitConditionalBlock(expr);
}

void NonTraversalWalker::WalkIfExpr(Visitor* visitor, IfExpr* expr) {
	visitor->VisitIfExpr(expr);
}

void NonTraversalWalker::WalkLoopExpr(Visitor* visitor, LoopExpr* expr) {
	visitor->VisitLoopExpr(expr);
}

void NonTraversalWalker::WalkStringExpr(Visitor* visitor, StringExpr* expr) {
	visitor->VisitStringExpr(expr);
}

void NonTraversalWalker::WalkVarRefExpr(Visitor* visitor, VarRefExpr* expr) {
	visitor->VisitVarRefExpr(expr);
}

void NonTraversalWalker::WalkIntExpr(Visitor* visitor, IntExpr* expr) {
	visitor->VisitIntExpr(expr);
}

void NonTraversalWalker::WalkFunctionExpr(Visitor* visitor, FunctionExpr* expr) {
	visitor->VisitFunctionExpr(expr);
}

void NonTraversalWalker::WalkFuncCallExpr(Visitor* visitor, FuncCallExpr* expr) {
	visitor->VisitFuncCallExpr(expr);
}

void NonTraversalWalker::WalkFloatExpr(Visitor* visitor, FloatExpr* expr) {
	visitor->VisitFloatExpr(expr);
}

void NonTraversalWalker::WalkDoubleExpr(Visitor* visitor, DoubleExpr* expr) {
	visitor->VisitDoubleExpr(expr);
}


void DepthFirstWalker::WalkPackageStmt(Visitor* visitor, PackageStmt* stmt) {
	visitor->VisitPackageStmt(stmt);
}

void DepthFirstWalker::WalkUsingStmt(Visitor* visitor, UsingStmt* stmt) {
	visitor->VisitUsingStmt(stmt);
}

void DepthFirstWalker::WalkEnumMember(Visitor* visitor, EnumMember* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitEnumMember(stmt);

	for (auto param : stmt->params) WalkParamStmt(visitor, param);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitEnumMember(stmt);
}

void DepthFirstWalker::WalkClassStmt(Visitor* visitor, ClassStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitClassStmt(stmt);

	WalkBlockExpr(visitor, stmt->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitClassStmt(stmt);
}

void DepthFirstWalker::WalkEnumStmt(Visitor* visitor, EnumStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitEnumStmt(stmt);

	for (auto member : stmt->members) WalkEnumMember(visitor, member);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitEnumStmt(stmt);
}

void DepthFirstWalker::WalkVarDeclStmt(Visitor* visitor, VarDeclStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitVarDeclStmt(stmt);

	WalkExpr(visitor, stmt->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitVarDeclStmt(stmt);
}

void DepthFirstWalker::WalkPropertyStmt(Visitor* visitor, PropertyStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitPropertyStmt(stmt);

	WalkGetterStmt(visitor, stmt->getter);
	WalkSetterStmt(visitor, stmt->setter);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitPropertyStmt(stmt);
}

void DepthFirstWalker::WalkGetterStmt(Visitor* visitor, GetterStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitGetterStmt(stmt);

	WalkBlockExpr(visitor, stmt->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitGetterStmt(stmt);
}

void DepthFirstWalker::WalkSetterStmt(Visitor* visitor, SetterStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitSetterStmt(stmt);

	WalkBlockExpr(visitor, stmt->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitSetterStmt(stmt);
}

void DepthFirstWalker::WalkFuncDeclStmt(Visitor* visitor, FuncDeclStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFuncDeclStmt(stmt);

	for (auto param : stmt->params) WalkParamStmt(visitor, param);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitFuncDeclStmt(stmt);
}

void DepthFirstWalker::WalkExternFuncDeclStmt(Visitor* visitor, ExternFuncDeclStmt* stmt) {
	WalkFuncDeclStmt(visitor, stmt);
}

void DepthFirstWalker::WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitInterfaceStmt(stmt);

	for (auto func : stmt->functions) WalkFuncDeclStmt(visitor, func);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitInterfaceStmt(stmt);
}

void DepthFirstWalker::WalkParamStmt(Visitor* visitor, ParamStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitParamStmt(stmt);

	WalkExpr(visitor, stmt->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitParamStmt(stmt);
}

void DepthFirstWalker::WalkExtendsStmt(Visitor* visitor, ExtendsStmt* stmt) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitExtendsStmt(stmt);

	WalkBlockExpr(visitor, stmt->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitExtendsStmt(stmt);
}

void DepthFirstWalker::WalkTupleComponent(Visitor* visitor, TupleComponent* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTupleComponent(expr);

	WalkExpr(visitor, expr->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTupleComponent(expr);
}

void DepthFirstWalker::WalkTupleExpr(Visitor* visitor, TupleExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitTupleExpr(expr);

	for (auto comp : expr->components) WalkTupleComponent(visitor, comp);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitTupleExpr(expr);
}

void DepthFirstWalker::WalkBinaryExpr(Visitor* visitor, BinaryExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitBinaryExpr(expr);

	WalkExpr(visitor, expr->LHS);
	WalkExpr(visitor, expr->RHS);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitBinaryExpr(expr);
}

void DepthFirstWalker::WalkUnaryExpr(Visitor* visitor, UnaryExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitUnaryExpr(expr);

	WalkExpr(visitor, expr->value);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitUnaryExpr(expr);
}

void DepthFirstWalker::WalkArrayExpr(Visitor* visitor, ArrayExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayExpr(expr);

	for (auto element : expr->values) WalkExpr(visitor, element);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayExpr(expr);
}

void DepthFirstWalker::WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayAccessExpr(expr);

	WalkExpr(visitor, expr->LHS);
	WalkExpr(visitor, expr->index);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayAccessExpr(expr);
}

void DepthFirstWalker::WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitArrayRangeExpr(expr);

	WalkExpr(visitor, expr->start);
	WalkExpr(visitor, expr->end);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitArrayRangeExpr(expr);
}

void DepthFirstWalker::WalkBlockExpr(Visitor* visitor, BlockExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitBlockExpr(expr);

	for (auto stmt : expr->statements) WalkNode(visitor, stmt);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitBlockExpr(expr);
}

void DepthFirstWalker::WalkConditionalBlock(Visitor* visitor, ConditionalBlock* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitConditionalBlock(expr);

	WalkExpr(visitor, expr->condition);
	WalkBlockExpr(visitor, expr->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitConditionalBlock(expr);
}

void DepthFirstWalker::WalkIfExpr(Visitor* visitor, IfExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitIfExpr(expr);

	for (auto cond : expr->blocks) WalkConditionalBlock(visitor, cond);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitIfExpr(expr);
}

void DepthFirstWalker::WalkLoopExpr(Visitor* visitor, LoopExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitLoopExpr(expr);

	WalkExpr(visitor, expr->initializer);
	WalkExpr(visitor, expr->condition);
	WalkExpr(visitor, expr->afterthought);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitLoopExpr(expr);
}

void DepthFirstWalker::WalkStringExpr(Visitor* visitor, StringExpr* expr) {
	visitor->VisitStringExpr(expr);
}

void DepthFirstWalker::WalkVarRefExpr(Visitor* visitor, VarRefExpr* expr) {
	visitor->VisitVarRefExpr(expr);
}

void DepthFirstWalker::WalkIntExpr(Visitor* visitor, IntExpr* expr) {
	visitor->VisitIntExpr(expr);
}

void DepthFirstWalker::WalkFunctionExpr(Visitor* visitor, FunctionExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFunctionExpr(expr);

	for (auto param : expr->params) WalkParamStmt(visitor, param);
	WalkBlockExpr(visitor, expr->body);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitFunctionExpr(expr);
}

void DepthFirstWalker::WalkFuncCallExpr(Visitor* visitor, FuncCallExpr* expr) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitFuncCallExpr(expr);

	WalkExpr(visitor, expr->function);
	for (auto arg : expr->args) WalkExpr(visitor, arg);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitFuncCallExpr(expr);
}

void DepthFirstWalker::WalkFloatExpr(Visitor* visitor, FloatExpr* expr) {
	visitor->VisitFloatExpr(expr);
}

void DepthFirstWalker::WalkDoubleExpr(Visitor* visitor, DoubleExpr* expr) {
	visitor->VisitDoubleExpr(expr);
}

DepthFirstWalker::DepthFirstWalker(TraversalOrder order) : mOrder(order) { }

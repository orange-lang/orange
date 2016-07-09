//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/compare.h>
#include <libast/typecheck.h>

#include <limits>
#include <cmath>

template <typename T>
bool CompareOptNode(T a, T b) {
	if (a == nullptr && b == nullptr) return true;
	if (a == nullptr && b != nullptr) return false;
	if (a != nullptr && b == nullptr) return false;
	return orange::ast::CompareNode(a, b);
}

template <typename T>
bool CompareOptType(T a, T b) {
	if (a == nullptr && b == nullptr) return true;
	if (a == nullptr && b != nullptr) return false;
	if (a != nullptr && b == nullptr) return false;
	return orange::ast::CompareType(a, b);
}

template <typename T>
bool CompareOptList(T a, T b) {
	if (a.size() != b.size()) return false;

	for (unsigned long i = 0; i < a.size(); i++) {
		if (!CompareOptNode(a[i], b[i])) return false;
	}

	return true;
}

template <typename T>
bool CompareOptTypeList(T a, T b) {
	if (a.size() != b.size()) return false;

	for (unsigned long i = 0; i < a.size(); i++) {
		if (!CompareOptType(a[i], b[i])) return false;
	}

	return true;
}

bool orange::ast::CompareNode(Node* a, Node* b) {
	if (isA<Statement>(a) && isA<Statement>(b))
		return CompareNode(asA<Statement>(a), asA<Statement>(b));

	if (isA<Expression>(a) && isA<Expression>(b))
		return CompareNode(asA<Expression>(a), asA<Expression>(b));

	if (isA<Constraint>(a) && isA<Constraint>(b))
		return CompareNode(asA<Constraint>(a), asA<Constraint>(b));

	if (isA<Generics>(a) && isA<Generics>(b))
		return CompareNode(asA<Generics>(a), asA<Generics>(b));

	return false;
}

bool orange::ast::CompareNode(Statement* a, Statement* b) {
	if (isA<CommentStmt>(a) && isA<CommentStmt>(b))
		return CompareNode(asA<CommentStmt>(a), asA<CommentStmt>(b));

	if (isA<LoopStmt>(a) && isA<LoopStmt>(b))
		return CompareNode(asA<LoopStmt>(a), asA<LoopStmt>(b));

	if (isA<ForeachStmt>(a) && isA<ForeachStmt>(b))
		return CompareNode(asA<ForeachStmt>(a), asA<ForeachStmt>(b));

	if (isA<BreakStmt>(a) && isA<BreakStmt>(b))
		return CompareNode(asA<BreakStmt>(a), asA<BreakStmt>(b));

	if (isA<ContinueStmt>(a) && isA<ContinueStmt>(b))
		return CompareNode(asA<ContinueStmt>(a), asA<ContinueStmt>(b));

	if (isA<YieldStmt>(a) && isA<YieldStmt>(b))
		return CompareNode(asA<YieldStmt>(a), asA<YieldStmt>(b));

	if (isA<ReturnStmt>(a) && isA<ReturnStmt>(b))
		return CompareNode(asA<ReturnStmt>(a), asA<ReturnStmt>(b));

	if (isA<AggregateStmt>(a) && isA<AggregateStmt>(b))
		return CompareNode(asA<AggregateStmt>(a), asA<AggregateStmt>(b));

	if (isA<ExternFuncStmt>(a) && isA<ExternFuncStmt>(b))
		return CompareNode(asA<ExternFuncStmt>(a), asA<ExternFuncStmt>(b));

	if (isA<EnumStmt>(a) && isA<EnumStmt>(b))
		return CompareNode(asA<EnumStmt>(a), asA<EnumStmt>(b));

	if (isA<ClassStmt>(a) && isA<ClassStmt>(b))
		return CompareNode(asA<ClassStmt>(a), asA<ClassStmt>(b));

	if (isA<InterfaceStmt>(a) && isA<InterfaceStmt>(b))
		return CompareNode(asA<InterfaceStmt>(a), asA<InterfaceStmt>(b));

	if (isA<ExtendStmt>(a) && isA<ExtendStmt>(b))
		return CompareNode(asA<ExtendStmt>(a), asA<ExtendStmt>(b));

	if (isA<NamespaceStmt>(a) && isA<NamespaceStmt>(b))
		return CompareNode(asA<NamespaceStmt>(a), asA<NamespaceStmt>(b));

	if (isA<ImportStmt>(a) && isA<ImportStmt>(b))
		return CompareNode(asA<ImportStmt>(a), asA<ImportStmt>(b));

	if (isA<GetterStmt>(a) && isA<GetterStmt>(b))
		return CompareNode(asA<GetterStmt>(a), asA<GetterStmt>(b));

	if (isA<SetterStmt>(a) && isA<SetterStmt>(b))
		return CompareNode(asA<SetterStmt>(a), asA<SetterStmt>(b));

	if (isA<PropertyStmt>(a) && isA<PropertyStmt>(b))
		return CompareNode(asA<PropertyStmt>(a), asA<PropertyStmt>(b));

	if (isA<ThrowStmt>(a) && isA<ThrowStmt>(b))
		return CompareNode(asA<ThrowStmt>(a), asA<ThrowStmt>(b));

	if (isA<DeleteStmt>(a) && isA<DeleteStmt>(b))
		return CompareNode(asA<DeleteStmt>(a), asA<DeleteStmt>(b));

	if (isA<ExprStmt>(a) && isA<ExprStmt>(b))
		return CompareNode(asA<ExprStmt>(a), asA<ExprStmt>(b));

	if (isA<SwitchPattern>(a) && isA<SwitchPattern>(b))
		return CompareNode(asA<SwitchPattern>(a), asA<SwitchPattern>(b));

	return false;
}

bool orange::ast::CompareNode(CommentStmt* a, CommentStmt* b) {
	return a->value == b->value;
}

bool orange::ast::CompareNode(LoopStmt* a, LoopStmt* b) {
	return CompareOptNode(a->initializer, b->initializer) &&
	       CompareOptNode(a->condition, b->condition) &&
	       CompareOptNode(a->afterthought, b->afterthought) &&
	       a->check == b->check &&
	       CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(ForeachStmt* a, ForeachStmt* b) {
	return CompareOptNode(a->declaration, b->declaration) &&
           CompareOptNode(a->value, b->value) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(BreakStmt* a, BreakStmt* b) {
	return true;
}

bool orange::ast::CompareNode(ContinueStmt* a, ContinueStmt* b) {
	return true;
}

bool orange::ast::CompareNode(YieldStmt* a, YieldStmt* b) {
	return CompareOptNode(a->value, b->value);
}

bool orange::ast::CompareNode(ReturnStmt* a, ReturnStmt* b) {
	return CompareOptNode(a->value, b->value);
}

bool orange::ast::CompareNode(AggregateStmt* a, AggregateStmt* b) {
	return CompareOptNode(a->name, b->name) &&
	       CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(ExternFuncStmt* a, ExternFuncStmt* b) {
	return CompareOptNode(a->name, b->name) &&
	       CompareOptList(a->params, b->params) &&
           CompareOptType(a->retType, b->retType);
}

bool orange::ast::CompareNode(EnumStmt* a, EnumStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptList(a->values, b->values);
}

bool orange::ast::CompareNode(ClassStmt* a, ClassStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptList(a->supers, b->supers) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(InterfaceStmt* a, InterfaceStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(ExtendStmt* a, ExtendStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptList(a->supers, b->supers) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(NamespaceStmt* a, NamespaceStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(ImportStmt* a, ImportStmt* b) {
	return CompareOptNode(a->name, b->name);
}

bool orange::ast::CompareNode(GetterStmt* a, GetterStmt* b) {
	return CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(SetterStmt* a, SetterStmt* b) {
	return CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(PropertyStmt* a, PropertyStmt* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptType(a->type, b->type) &&
           CompareOptNode(a->body, b->body);
}

bool orange::ast::CompareNode(ThrowStmt* a, ThrowStmt* b) {
	return CompareOptNode(a->exception, b->exception);
}

bool orange::ast::CompareNode(DeleteStmt* a, DeleteStmt* b) {
	return CompareOptNode(a->deallocation, b->deallocation);
}

bool orange::ast::CompareNode(ExprStmt* a, ExprStmt* b) {
	return CompareOptNode(a->expression, b->expression);
}

bool orange::ast::CompareNode(Expression* a, Expression* b) {
	if (isA<EnumValue>(a) && isA<EnumValue>(b))
		return CompareNode(asA<EnumValue>(a), asA<EnumValue>(b));

	if (isA<VarDeclExpr>(a) && isA<VarDeclExpr>(b))
		return CompareNode(asA<VarDeclExpr>(a), asA<VarDeclExpr>(b));

	if (isA<Value>(a) && isA<Value>(b))
		return CompareNode(asA<Value>(a), asA<Value>(b));

	if (isA<Identifier>(a) && isA<Identifier>(b))
		return CompareNode(asA<Identifier>(a), asA<Identifier>(b));

	if (isA<BlockExpr>(a) && isA<BlockExpr>(b))
		return CompareNode(asA<BlockExpr>(a), asA<BlockExpr>(b));

	if (isA<BinOpExpr>(a) && isA<BinOpExpr>(b))
		return CompareNode(asA<BinOpExpr>(a), asA<BinOpExpr>(b));

	if (isA<UnaryExpr>(a) && isA<UnaryExpr>(b))
		return CompareNode(asA<UnaryExpr>(a), asA<UnaryExpr>(b));

	if (isA<TupleExpr>(a) && isA<TupleExpr>(b))
		return CompareNode(asA<TupleExpr>(a), asA<TupleExpr>(b));

	if (isA<ArrayExpr>(a) && isA<ArrayExpr>(b))
		return CompareNode(asA<ArrayExpr>(a), asA<ArrayExpr>(b));

	if (isA<ArrayRangeExpr>(a) && isA<ArrayRangeExpr>(b))
		return CompareNode(asA<ArrayRangeExpr>(a), asA<ArrayRangeExpr>(b));

	if (isA<ArrayAccessExpr>(a) && isA<ArrayAccessExpr>(b))
		return CompareNode(asA<ArrayAccessExpr>(a), asA<ArrayAccessExpr>(b));

	if (isA<MemberAccessExpr>(a) && isA<MemberAccessExpr>(b))
		return CompareNode(asA<MemberAccessExpr>(a), asA<MemberAccessExpr>(b));

	if (isA<NamedExpr>(a) && isA<NamedExpr>(b))
		return CompareNode(asA<NamedExpr>(a), asA<NamedExpr>(b));

	if (isA<ConditionalBlock>(a) && isA<ConditionalBlock>(b))
		return CompareNode(asA<ConditionalBlock>(a), asA<ConditionalBlock>(b));

	if (isA<IfExpr>(a) && isA<IfExpr>(b))
		return CompareNode(asA<IfExpr>(a), asA<IfExpr>(b));

	if (isA<TernaryExpr>(a) && isA<TernaryExpr>(b))
		return CompareNode(asA<TernaryExpr>(a), asA<TernaryExpr>(b));

	if (isA<SwitchPattern>(a) && isA<SwitchPattern>(b))
		return CompareNode(asA<SwitchPattern>(a), asA<SwitchPattern>(b));

	if (isA<SwitchExpr>(a) && isA<SwitchExpr>(b))
		return CompareNode(asA<SwitchExpr>(a), asA<SwitchExpr>(b));

	if (isA<Constraint>(a) && isA<Constraint>(b))
		return CompareNode(asA<Constraint>(a), asA<Constraint>(b));

	if (isA<Generics>(a) && isA<Generics>(b))
		return CompareNode(asA<Generics>(a), asA<Generics>(b));

	if (isA<FunctionExpr>(a) && isA<FunctionExpr>(b))
		return CompareNode(asA<FunctionExpr>(a), asA<FunctionExpr>(b));

	if (isA<CatchBlock>(a) && isA<CatchBlock>(b))
		return CompareNode(asA<CatchBlock>(a), asA<CatchBlock>(b));

	if (isA<TryExpr>(a) && isA<TryExpr>(b))
		return CompareNode(asA<TryExpr>(a), asA<TryExpr>(b));

	if (isA<CastExpr>(a) && isA<CastExpr>(b))
		return CompareNode(asA<CastExpr>(a), asA<CastExpr>(b));

	if (isA<FunctionCallExpr>(a) && isA<FunctionCallExpr>(b))
		return CompareNode(asA<FunctionCallExpr>(a), asA<FunctionCallExpr>(b));

	if (isA<NewExpr>(a) && isA<NewExpr>(b))
		return CompareNode(asA<NewExpr>(a), asA<NewExpr>(b));

	return false;
}

bool orange::ast::CompareNode(EnumValue* a, EnumValue* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptList(a->params, b->params);
}

bool orange::ast::CompareNode(VarDeclExpr* a, VarDeclExpr* b) {
	return CompareOptList(a->bindings, b->bindings) &&
           CompareOptTypeList(a->types, b->types) &&
           CompareOptNode(a->value, b->value);
}

bool orange::ast::CompareNode(Value* a, Value* b) {
	if (isA<IntValue>(a) && isA<IntValue>(b))
		return CompareNode(asA<IntValue>(a), asA<IntValue>(b));

	if (isA<UIntValue>(a) && isA<UIntValue>(b))
		return CompareNode(asA<UIntValue>(a), asA<UIntValue>(b));

	if (isA<FloatValue>(a) && isA<FloatValue>(b))
		return CompareNode(asA<FloatValue>(a), asA<FloatValue>(b));

	if (isA<DoubleValue>(a) && isA<DoubleValue>(b))
		return CompareNode(asA<DoubleValue>(a), asA<DoubleValue>(b));

	if (isA<StringValue>(a) && isA<StringValue>(b))
		return CompareNode(asA<StringValue>(a), asA<StringValue>(b));

	if (isA<CharValue>(a) && isA<CharValue>(b))
		return CompareNode(asA<CharValue>(a), asA<CharValue>(b));

	return false;
}

bool orange::ast::CompareNode(IntValue* a, IntValue* b) {
	return a->value == b->value && CompareOptType(a->type, b->type);
}

bool orange::ast::CompareNode(UIntValue* a, UIntValue* b) {
	return a->value == b->value && CompareOptType(a->type, b->type);
}

bool orange::ast::CompareNode(FloatValue* a, FloatValue* b) {
	return std::fabs(a->value - b->value) < std::numeric_limits<float>::epsilon();
}

bool orange::ast::CompareNode(DoubleValue* a, DoubleValue* b) {
	return std::fabs(a->value - b->value) < std::numeric_limits<double>::epsilon();
}

bool orange::ast::CompareNode(StringValue* a, StringValue* b) {
	return a->value == b->value;
}

bool orange::ast::CompareNode(CharValue* a, CharValue* b) {
	return a->value == b->value;
}

bool orange::ast::CompareNode(Identifier* a, Identifier* b) {
	if (isA<ThisID>(a) && isA<ThisID>(b))
		return CompareNode(asA<ThisID>(a), asA<ThisID>(b));

	if (isA<ReferenceIDExpr>(a) && isA<ReferenceIDExpr>(b))
		return CompareNode(asA<ReferenceIDExpr>(a), asA<ReferenceIDExpr>(b));

	if (isA<NamedIDExpr>(a) && isA<NamedIDExpr>(b))
		return CompareNode(asA<NamedIDExpr>(a), asA<NamedIDExpr>(b));

	if (isA<DtorIDExpr>(a) && isA<DtorIDExpr>(b))
		return CompareNode(asA<DtorIDExpr>(a), asA<DtorIDExpr>(b));

	if (isA<TempIDExpr>(a) && isA<TempIDExpr>(b))
		return CompareNode(asA<TempIDExpr>(a), asA<TempIDExpr>(b));

	if (isA<AccessIDExpr>(a) && isA<AccessIDExpr>(b))
		return CompareNode(asA<AccessIDExpr>(a), asA<AccessIDExpr>(b));

	return false;
}

bool orange::ast::CompareNode(ThisID* a, ThisID* b) {
	return true;
}


bool orange::ast::CompareNode(ReferenceIDExpr* a, ReferenceIDExpr* b) {
	return a->name == b->name;
}

bool orange::ast::CompareNode(NamedIDExpr* a, NamedIDExpr* b) {
	return a->name == b->name;
}

bool orange::ast::CompareNode(DtorIDExpr* a, DtorIDExpr* b) {
	return CompareOptNode(a->base, b->base);
}

bool orange::ast::CompareNode(TempIDExpr* a, TempIDExpr* b) {
	return true;
}

bool orange::ast::CompareNode(AccessIDExpr* a, AccessIDExpr* b) {
	return CompareOptNode(a->LHS, b->LHS) &&
           CompareOptNode(a->RHS, b->RHS);
}

bool orange::ast::CompareNode(BlockExpr* a, BlockExpr* b) {
	if (isA<LongBlockExpr>(a) && isA<LongBlockExpr>(b))
		return CompareNode(asA<LongBlockExpr>(a), asA<LongBlockExpr>(b));

	if (isA<ShortBlockExpr>(a) && isA<ShortBlockExpr>(b))
		return CompareNode(asA<ShortBlockExpr>(a), asA<ShortBlockExpr>(b));

	return false;
}

bool orange::ast::CompareNode(LongBlockExpr* a, LongBlockExpr* b) {
	return CompareOptList(a->statements, b->statements);
}

bool orange::ast::CompareNode(ShortBlockExpr* a, ShortBlockExpr* b) {
	return CompareOptNode(a->statement, b->statement);
}

bool orange::ast::CompareNode(BinOpExpr* a, BinOpExpr* b) {
	return CompareOptNode(a->LHS, b->LHS) &&
           a->op == b->op &&
           CompareOptNode(a->RHS, b->RHS);
}

bool orange::ast::CompareNode(UnaryExpr* a, UnaryExpr* b) {
	return a->op == b->op &&
           a->order == b->order &&
           CompareOptNode(a->LHS, b->LHS);
}

bool orange::ast::CompareNode(TupleExpr* a, TupleExpr* b) {
	return CompareOptList(a->values, b->values);
}

bool orange::ast::CompareNode(ArrayExpr* a, ArrayExpr* b) {
	return CompareOptList(a->values, b->values);
}

bool orange::ast::CompareNode(ArrayRangeExpr* a, ArrayRangeExpr* b) {
	return CompareOptNode(a->LHS, b->LHS) &&
           a->type == b->type &&
           CompareOptNode(a->RHS, b->RHS);
}

bool orange::ast::CompareNode(ArrayAccessExpr* a, ArrayAccessExpr* b) {
	return CompareOptNode(a->expression, b->expression) &&
           CompareOptNode(a->index, b->index);
}

bool orange::ast::CompareNode(MemberAccessExpr* a, MemberAccessExpr* b) {
	return CompareOptNode(a->LHS, b->LHS) &&
           CompareOptNode(a->RHS, b->RHS);
}

bool orange::ast::CompareNode(NamedExpr* a, NamedExpr* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptNode(a->value, b->value);
}

bool orange::ast::CompareNode(ConditionalBlock* a, ConditionalBlock* b) {
	return CompareOptNode(a->condition, b->condition) &&
           CompareOptNode(a->block, b->block);
}

bool orange::ast::CompareNode(IfExpr* a, IfExpr* b) {
	return CompareOptList(a->blocks, b->blocks);
}

bool orange::ast::CompareNode(TernaryExpr* a, TernaryExpr* b) {
	return CompareOptNode(a->condition, b->condition) &&
           CompareOptNode(a->trueValue, b->trueValue) &&
           CompareOptNode(a->falseValue, b->falseValue);
}

bool orange::ast::CompareNode(SwitchPattern* a, SwitchPattern* b) {
	return CompareOptList(a->patterns, b->patterns) &&
           CompareOptNode(a->block, b->block);
}

bool orange::ast::CompareNode(SwitchExpr* a, SwitchExpr* b) {
	return CompareOptNode(a->condition, b->condition) &&
           CompareOptList(a->patterns, b->patterns);
}

bool orange::ast::CompareNode(Constraint* a, Constraint* b) {
	if (isA<ClassConstraint>(a) && isA<ClassConstraint>(b))
		return CompareNode(asA<ClassConstraint>(a), asA<ClassConstraint>(b));

	if (isA<DefaultCtorConstraint>(a) && isA<DefaultCtorConstraint>(b))
		return CompareNode(asA<DefaultCtorConstraint>(a), asA<DefaultCtorConstraint>(b));

	if (isA<BaseConstraint>(a) && isA<BaseConstraint>(b))
		return CompareNode(asA<BaseConstraint>(a), asA<BaseConstraint>(b));

	if (isA<DataConstraint>(a) && isA<DataConstraint>(b))
		return CompareNode(asA<DataConstraint>(a), asA<DataConstraint>(b));

	if (isA<TypeConstraint>(a) && isA<TypeConstraint>(b))
		return CompareNode(asA<TypeConstraint>(a), asA<TypeConstraint>(b));

	return false;
}

bool orange::ast::CompareNode(ClassConstraint* a, ClassConstraint* b) {
	return CompareOptNode(a->identifier, b->identifier);
}

bool orange::ast::CompareNode(DefaultCtorConstraint* a, DefaultCtorConstraint* b) {
	return CompareOptNode(a->identifier, b->identifier);
}

bool orange::ast::CompareNode(BaseConstraint* a, BaseConstraint* b) {
	return CompareOptNode(a->identifier, b->identifier) &&
           CompareOptNode(a->base, b->base);
}

bool orange::ast::CompareNode(DataConstraint* a, DataConstraint* b) {
	return CompareOptNode(a->identifier, b->identifier) &&
           CompareOptType(a->dataType, b->dataType);
}

bool orange::ast::CompareNode(TypeConstraint* a, TypeConstraint* b) {
	return CompareOptNode(a->identifier, b->identifier) &&
           CompareOptType(a->type, b->type);
}

bool orange::ast::CompareNode(Generics* a, Generics* b) {
	return CompareOptList(a->genericTypes, b->genericTypes) &&
           CompareOptList(a->constraints, b->constraints);
}

bool orange::ast::CompareNode(FunctionExpr* a, FunctionExpr* b) {
	return CompareOptNode(a->name, b->name) &&
           CompareOptNode(a->generics, b->generics) &&
           CompareOptList(a->params, b->params) &&
           CompareOptType(a->retType, b->retType) &&
           CompareOptNode(a->block, b->block);
}

bool orange::ast::CompareNode(CatchBlock* a, CatchBlock* b) {
	return CompareOptNode(a->exception, b->exception) &&
           CompareOptNode(a->block, b->block);
}

bool orange::ast::CompareNode(TryExpr* a, TryExpr* b) {
	return CompareOptNode(a->block, b->block) &&
           CompareOptList(a->catches, b->catches) &&
           CompareOptNode(a->finally, b->finally);
}

bool orange::ast::CompareNode(CastExpr* a, CastExpr* b) {
	return CompareOptType(a->targetType, b->targetType) &&
           CompareOptNode(a->expr, b->expr);
}

bool orange::ast::CompareNode(FunctionCallExpr* a, FunctionCallExpr* b) {
	return CompareOptNode(a->function, b->function) &&
           CompareOptList(a->args, b->args);
}

bool orange::ast::CompareNode(NewExpr* a, NewExpr* b) {
	return CompareOptNode(a->allocation, b->allocation);
}

bool orange::ast::CompareFlag(Flag* a, Flag* b) {
	if (isA<PartialFlag>(a) && isA<PartialFlag>(b))
		return CompareFlag(asA<PartialFlag>(a), asA<PartialFlag>(b));

	if (isA<ConstFlag>(a) && isA<ConstFlag>(b))
		return CompareFlag(asA<ConstFlag>(a), asA<ConstFlag>(b));

	if (isA<VirtualFlag>(a) && isA<VirtualFlag>(b))
		return CompareFlag(asA<VirtualFlag>(a), asA<VirtualFlag>(b));

	if (isA<PrivacyFlag>(a) && isA<PrivacyFlag>(b))
		return CompareFlag(asA<PrivacyFlag>(a), asA<PrivacyFlag>(b));

	return false;
}

bool orange::ast::CompareFlag(PartialFlag* a, PartialFlag* b) {
	return true;
}

bool orange::ast::CompareFlag(ConstFlag* a, ConstFlag* b) {
	return true;
}

bool orange::ast::CompareFlag(VirtualFlag* a, VirtualFlag* b) {
	return true;
}

bool orange::ast::CompareFlag(PrivacyFlag* a, PrivacyFlag* b) {
	return a->level == b->level;
}


bool orange::ast::CompareType(Type* a, Type* b) {
	if (isA<FunctionType>(a) && isA<FunctionType>(b)) return CompareType(asA<FunctionType>(a), asA<FunctionType>(b));
	if (isA<AccessType>(a) && isA<AccessType>(b)) return CompareType(asA<AccessType>(a), asA<AccessType>(b));
	if (isA<IdentifierType>(a) && isA<IdentifierType>(b)) return CompareType(asA<IdentifierType>(a), asA<IdentifierType>(b));
	if (isA<BuiltinType>(a) && isA<BuiltinType>(b)) return CompareType(asA<BuiltinType>(a), asA<BuiltinType>(b));
	if (isA<ArrayType>(a) && isA<ArrayType>(b)) return CompareType(asA<ArrayType>(a), asA<ArrayType>(b));
	if (isA<PointerType>(a) && isA<PointerType>(b)) return CompareType(asA<PointerType>(a), asA<PointerType>(b));
	if (isA<ReferenceType>(a) && isA<ReferenceType>(b)) return CompareType(asA<ReferenceType>(a), asA<ReferenceType>(b));
	if (isA<TupleType>(a) && isA<TupleType>(b)) return CompareType(asA<TupleType>(a), asA<TupleType>(b));

	return false;
}

bool orange::ast::CompareType(FunctionType* a, FunctionType* b) {
	return CompareOptTypeList(a->params, b->params) &&
           CompareOptType(a->returnType, b->returnType);
}

bool orange::ast::CompareType(AccessType* a, AccessType* b) {
	return CompareOptType(a->LHS, b->LHS) &&
           CompareOptType(a->RHS, b->RHS);
}

bool orange::ast::CompareType(IdentifierType* a, IdentifierType* b) {
	return CompareOptNode(a->id, b->id);
}

bool orange::ast::CompareType(BuiltinType* a, BuiltinType* b) {
	return a->kind == b->kind;
}

bool orange::ast::CompareType(ArrayType* a, ArrayType* b) {
	return CompareOptType(a->base, b->base) &&
           CompareOptNode(a->size, b->size);
}

bool orange::ast::CompareType(PointerType* a, PointerType* b) {
	return CompareOptType(a->base, b->base);
}

bool orange::ast::CompareType(ReferenceType* a, ReferenceType* b) {
	return CompareOptType(a->base, b->base);
}

bool orange::ast::CompareType(TupleType* a, TupleType* b) {
	return CompareOptTypeList(a->types, b->types);
}


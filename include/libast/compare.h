//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include "ast.h"
#include "flag.h"
#include "type.h"

namespace orange { namespace ast {
	bool CompareNode(Node* a, Node* b);
	bool CompareNode(Statement* a, Statement* b);
	bool CompareNode(CommentStmt* a, CommentStmt* b);
	bool CompareNode(LoopStmt* a, LoopStmt* b);
	bool CompareNode(BreakStmt* a, BreakStmt* b);
	bool CompareNode(ContinueStmt* a, ContinueStmt* b);
	bool CompareNode(ReturnStmt* a, ReturnStmt* b);
	bool CompareNode(ExternFuncStmt* a, ExternFuncStmt* b);
	bool CompareNode(EnumStmt* a, EnumStmt* b);
	bool CompareNode(ClassStmt* a, ClassStmt* b);
	bool CompareNode(InterfaceStmt* a, InterfaceStmt* b);
	bool CompareNode(NamespaceStmt* a, NamespaceStmt* b);
	bool CompareNode(ImportStmt* a, ImportStmt* b);
	bool CompareNode(ThrowStmt* a, ThrowStmt* b);
	bool CompareNode(DeleteStmt* a, DeleteStmt* b);
	bool CompareNode(ExprStmt* a, ExprStmt* b);
	bool CompareNode(Expression* a, Expression* b);
	bool CompareNode(EnumValue* a, EnumValue* b);
	bool CompareNode(VarDeclExpr* a, VarDeclExpr* b);
	bool CompareNode(Value* a, Value* b);
	bool CompareNode(BoolValue* a, BoolValue* b);
	bool CompareNode(IntValue* a, IntValue* b);
	bool CompareNode(UIntValue* a, UIntValue* b);
	bool CompareNode(FloatValue* a, FloatValue* b);
	bool CompareNode(DoubleValue* a, DoubleValue* b);
	bool CompareNode(StringValue* a, StringValue* b);
	bool CompareNode(CharValue* a, CharValue* b);
	bool CompareNode(Identifier* a, Identifier* b);
	bool CompareNode(ThisID* a, ThisID* b);
	bool CompareNode(ReferenceIDExpr* a, ReferenceIDExpr* b);
	bool CompareNode(NamedIDExpr* a, NamedIDExpr* b);
	bool CompareNode(DtorIDExpr* a, DtorIDExpr* b);
	bool CompareNode(AccessIDExpr* a, AccessIDExpr* b);
	bool CompareNode(BlockExpr* a, BlockExpr* b);
	bool CompareNode(LongBlockExpr* a, LongBlockExpr* b);
	bool CompareNode(ShortBlockExpr* a, ShortBlockExpr* b);
	bool CompareNode(BinOpExpr* a, BinOpExpr* b);
	bool CompareNode(UnaryExpr* a, UnaryExpr* b);
	bool CompareNode(ArrayExpr* a, ArrayExpr* b);
	bool CompareNode(ArrayAccessExpr* a, ArrayAccessExpr* b);
	bool CompareNode(MemberAccessExpr* a, MemberAccessExpr* b);
	bool CompareNode(ConditionalBlock* a, ConditionalBlock* b);
	bool CompareNode(IfExpr* a, IfExpr* b);
	bool CompareNode(TernaryExpr* a, TernaryExpr* b);
	bool CompareNode(FunctionExpr* a, FunctionExpr* b);
	bool CompareNode(CatchBlock* a, CatchBlock* b);
	bool CompareNode(TryExpr* a, TryExpr* b);
	bool CompareNode(CastExpr* a, CastExpr* b);
	bool CompareNode(FunctionCallExpr* a, FunctionCallExpr* b);
	bool CompareNode(NewExpr* a, NewExpr* b);

	bool CompareFlag(Flag* a, Flag* b);
	bool CompareFlag(PartialFlag* a, PartialFlag* b);
	bool CompareFlag(ConstFlag* a, ConstFlag* b);
	bool CompareFlag(VirtualFlag* a, VirtualFlag* b);
	bool CompareFlag(PrivacyFlag* a, PrivacyFlag* b);

	bool CompareType(Type* a, Type* b);
	bool CompareType(AccessType* a, AccessType* b);
	bool CompareType(IdentifierType* a, IdentifierType* b);
	bool CompareType(BuiltinType* a, BuiltinType* b);
	bool CompareType(ArrayType* a, ArrayType* b);
	bool CompareType(PointerType* a, PointerType* b);
	bool CompareType(FunctionType* a, FunctionType* b);
}}

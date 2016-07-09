/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ast.h"
#include "visitor.h"

namespace orange { namespace ast {
	class Walker {
	public:
		/// Dispatches to the proper walk method. Does not visit any nodes.
		void WalkNode(Visitor* visitor, Node* node);
		void WalkStmt(Visitor* visitor, Statement* node);
		void WalkExpr(Visitor* visitor, Expression* node);
		void WalkConstraint(Visitor* visitor, Constraint* node);
		void WalkValue(Visitor* visitor, Value* node);
		void WalkIdentifier(Visitor* visitor, Identifier* node);
		void WalkBlockExpr(Visitor* visitor, BlockExpr* node);

		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node) = 0;
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node) = 0;
		virtual void WalkForeachStmt(Visitor* visitor, ForeachStmt* node) = 0;
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node) = 0;
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node) = 0;
		virtual void WalkYieldStmt(Visitor* visitor, YieldStmt* node) = 0;
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node) = 0;
		virtual void WalkAggregateStmt(Visitor* visitor, AggregateStmt* node) = 0;
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) = 0;
		virtual void WalkEnumValue(Visitor* visitor, EnumValue* node) = 0;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* node) = 0;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node) = 0;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) = 0;
		virtual void WalkExtendStmt(Visitor* visitor, ExtendStmt* node) = 0;
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) = 0;
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node) = 0;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* node) = 0;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* node) = 0;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* node) = 0;
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node) = 0;
		virtual void WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) = 0;
		virtual void WalkExprStmt(Visitor* visitor, ExprStmt* node) = 0;
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) = 0;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) = 0;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) = 0;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) = 0;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) = 0;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) = 0;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) = 0;
		virtual void WalkThisID(Visitor* visitor, ThisID* node) = 0;
		virtual void WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) = 0;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) = 0;
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) = 0;
		virtual void WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) = 0;
		virtual void WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) = 0;
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) = 0;
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) = 0;
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) = 0;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) = 0;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* node) = 0;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node) = 0;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node) = 0;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) = 0;
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) = 0;
		virtual void WalkNamedExpr(Visitor* visitor, NamedExpr* node) = 0;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) = 0;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node) = 0;
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) = 0;
		virtual void WalkSwitchPattern(Visitor* visitor, SwitchPattern* node) = 0;
		virtual void WalkSwitchExpr(Visitor* visitor, SwitchExpr* node) = 0;
		virtual void WalkClassConstraint(Visitor* visitor, ClassConstraint* node) = 0;
		virtual void WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node) = 0;
		virtual void WalkBaseConstraint(Visitor* visitor, BaseConstraint* node) = 0;
		virtual void WalkDataConstraint(Visitor* visitor, DataConstraint* node) = 0;
		virtual void WalkTypeConstraint(Visitor* visitor, TypeConstraint* node) = 0;
		virtual void WalkGenerics(Visitor* visitor, Generics* node) = 0;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) = 0;
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node) = 0;
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node) = 0;
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node) = 0;
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) = 0;
		virtual void WalkNewExpr(Visitor* visitor, NewExpr* node) = 0;
	};


	/// Walker that will visit concrete elements
	class NonTraversalWalker : public Walker {
	public:
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node) override;
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node) override;
		virtual void WalkForeachStmt(Visitor* visitor, ForeachStmt* node) override;
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node) override;
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node) override;
		virtual void WalkYieldStmt(Visitor* visitor, YieldStmt* node) override;
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node) override;
		virtual void WalkAggregateStmt(Visitor* visitor, AggregateStmt* node) override;
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) override;
		virtual void WalkEnumValue(Visitor* visitor, EnumValue* node) override;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* node) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) override;
		virtual void WalkExtendStmt(Visitor* visitor, ExtendStmt* node) override;
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) override;
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node) override;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* node) override;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* node) override;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* node) override;
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node) override;
		virtual void WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) override;
		virtual void WalkExprStmt(Visitor* visitor, ExprStmt* node) override;
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) override;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) override;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) override;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) override;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) override;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) override;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) override;
		virtual void WalkThisID(Visitor* visitor, ThisID* node) override;
		virtual void WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) override;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) override;
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) override;
		virtual void WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) override;
		virtual void WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) override;
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) override;
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) override;
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) override;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* node) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node) override;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) override;
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) override;
		virtual void WalkNamedExpr(Visitor* visitor, NamedExpr* node) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node) override;
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) override;
		virtual void WalkSwitchPattern(Visitor* visitor, SwitchPattern* node) override;
		virtual void WalkSwitchExpr(Visitor* visitor, SwitchExpr* node) override;
		virtual void WalkClassConstraint(Visitor* visitor, ClassConstraint* node) override;
		virtual void WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node) override;
		virtual void WalkBaseConstraint(Visitor* visitor, BaseConstraint* node) override;
		virtual void WalkDataConstraint(Visitor* visitor, DataConstraint* node) override;
		virtual void WalkTypeConstraint(Visitor* visitor, TypeConstraint* node) override;
		virtual void WalkGenerics(Visitor* visitor, Generics* node) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) override;
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node) override;
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node) override;
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node) override;
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) override;
		virtual void WalkNewExpr(Visitor* visitor, NewExpr* node) override;
	};

	enum TraversalOrder {
		PREORDER,
		POSTORDER
	};

	// Walker that traverses the hierarchy depth-first.
	class DepthFirstWalker : public Walker {
	private:
		TraversalOrder mOrder;
	public:
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node) override;
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node) override;
		virtual void WalkForeachStmt(Visitor* visitor, ForeachStmt* node) override;
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node) override;
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node) override;
		virtual void WalkYieldStmt(Visitor* visitor, YieldStmt* node) override;
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node) override;
		virtual void WalkAggregateStmt(Visitor* visitor, AggregateStmt* node) override;
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) override;
		virtual void WalkEnumValue(Visitor* visitor, EnumValue* node) override;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* node) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) override;
		virtual void WalkExtendStmt(Visitor* visitor, ExtendStmt* node) override;
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) override;
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node) override;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* node) override;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* node) override;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* node) override;
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node) override;
		virtual void WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) override;
		virtual void WalkExprStmt(Visitor* visitor, ExprStmt* node) override;
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) override;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) override;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) override;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) override;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) override;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) override;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) override;
		virtual void WalkThisID(Visitor* visitor, ThisID* node) override;
		virtual void WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) override;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) override;
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) override;
		virtual void WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) override;
		virtual void WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) override;
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) override;
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) override;
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) override;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* node) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node) override;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) override;
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) override;
		virtual void WalkNamedExpr(Visitor* visitor, NamedExpr* node) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node) override;
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) override;
		virtual void WalkSwitchPattern(Visitor* visitor, SwitchPattern* node) override;
		virtual void WalkSwitchExpr(Visitor* visitor, SwitchExpr* node) override;
		virtual void WalkClassConstraint(Visitor* visitor, ClassConstraint* node) override;
		virtual void WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node) override;
		virtual void WalkBaseConstraint(Visitor* visitor, BaseConstraint* node) override;
		virtual void WalkDataConstraint(Visitor* visitor, DataConstraint* node) override;
		virtual void WalkTypeConstraint(Visitor* visitor, TypeConstraint* node) override;
		virtual void WalkGenerics(Visitor* visitor, Generics* node) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) override;
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node) override;
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node) override;
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node) override;
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) override;
		virtual void WalkNewExpr(Visitor* visitor, NewExpr* node) override;

		DepthFirstWalker(TraversalOrder order);
	};
}}

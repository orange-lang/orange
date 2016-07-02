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
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) = 0;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) = 0;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) = 0;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) = 0;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) = 0;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) = 0;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) = 0;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) = 0;
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node) = 0;
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
	};


	/// Walker that will visit concrete elements
	class NonTraversalWalker : public Walker {
	public:
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node);
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node);
		virtual void WalkForeachStmt(Visitor* visitor, ForeachStmt* node);
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node);
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node);
		virtual void WalkYieldStmt(Visitor* visitor, YieldStmt* node);
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node);
		virtual void WalkAggregateStmt(Visitor* visitor, AggregateStmt* node);
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node);
		virtual void WalkEnumValue(Visitor* visitor, EnumValue* node);
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* node);
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node);
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node);
		virtual void WalkExtendStmt(Visitor* visitor, ExtendStmt* node);
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node);
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node);
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* node);
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* node);
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* node);
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node);
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node);
		virtual void WalkIntValue(Visitor* visitor, IntValue* node);
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node);
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node);
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node);
		virtual void WalkStringValue(Visitor* visitor, StringValue* node);
		virtual void WalkCharValue(Visitor* visitor, CharValue* node);
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node);
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node);
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node);
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node);
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node);
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node);
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* node);
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node);
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node);
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node);
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node);
		virtual void WalkNamedExpr(Visitor* visitor, NamedExpr* node);
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node);
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node);
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node);
		virtual void WalkSwitchPattern(Visitor* visitor, SwitchPattern* node);
		virtual void WalkSwitchExpr(Visitor* visitor, SwitchExpr* node);
		virtual void WalkClassConstraint(Visitor* visitor, ClassConstraint* node);
		virtual void WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node);
		virtual void WalkBaseConstraint(Visitor* visitor, BaseConstraint* node);
		virtual void WalkDataConstraint(Visitor* visitor, DataConstraint* node);
		virtual void WalkTypeConstraint(Visitor* visitor, TypeConstraint* node);
		virtual void WalkGenerics(Visitor* visitor, Generics* node);
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node);
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node);
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node);
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node);
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node);
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
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node);
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node);
		virtual void WalkForeachStmt(Visitor* visitor, ForeachStmt* node);
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node);
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node);
		virtual void WalkYieldStmt(Visitor* visitor, YieldStmt* node);
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node);
		virtual void WalkAggregateStmt(Visitor* visitor, AggregateStmt* node);
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node);
		virtual void WalkEnumValue(Visitor* visitor, EnumValue* node);
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* node);
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node);
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node);
		virtual void WalkExtendStmt(Visitor* visitor, ExtendStmt* node);
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node);
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node);
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* node);
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* node);
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* node);
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node);
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node);
		virtual void WalkIntValue(Visitor* visitor, IntValue* node);
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node);
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node);
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node);
		virtual void WalkStringValue(Visitor* visitor, StringValue* node);
		virtual void WalkCharValue(Visitor* visitor, CharValue* node);
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node);
		virtual void WalkTempIDExpr(Visitor* visitor, TempIDExpr* node);
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node);
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node);
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node);
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node);
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* node);
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node);
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* node);
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node);
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node);
		virtual void WalkNamedExpr(Visitor* visitor, NamedExpr* node);
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node);
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node);
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node);
		virtual void WalkSwitchPattern(Visitor* visitor, SwitchPattern* node);
		virtual void WalkSwitchExpr(Visitor* visitor, SwitchExpr* node);
		virtual void WalkClassConstraint(Visitor* visitor, ClassConstraint* node);
		virtual void WalkDefaultCtorConstraint(Visitor* visitor, DefaultCtorConstraint* node);
		virtual void WalkBaseConstraint(Visitor* visitor, BaseConstraint* node);
		virtual void WalkDataConstraint(Visitor* visitor, DataConstraint* node);
		virtual void WalkTypeConstraint(Visitor* visitor, TypeConstraint* node);
		virtual void WalkGenerics(Visitor* visitor, Generics* node) = 0;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node);
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node);
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node);
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node);
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node);

		DepthFirstWalker(TraversalOrder order);
	};
}}

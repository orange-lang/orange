/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <stdexcept>

#include "ast.h"
#include "typecheck.h"

namespace orange { namespace ast {
	class Visitor;
	
	template <class T>
	class WalkerBase {
	public:
		/// Dispatches to the proper walk method. Does not visit any nodes.
		virtual void WalkNode(T* helper, Node* node) {
			if      (isA<Statement>(node))  WalkStmt(helper, asA<Statement>(node));
			else if (isA<Expression>(node)) WalkExpr(helper, asA<Expression>(node));
			else                            throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkExpr(T* helper, Expression* node) {
			if      (isA<VarDeclExpr>(node))      WalkVarDeclExpr(helper, asA<VarDeclExpr>(node));
			else if (isA<ConditionalBlock>(node)) WalkConditionalBlock(helper, asA<ConditionalBlock>(node));
			else if (isA<BlockExpr>(node))        WalkBlockExpr(helper, asA<BlockExpr>(node));
			else if (isA<Value>(node))            WalkValue(helper, asA<Value>(node));
			else if (isA<BlockExpr>(node))        WalkBlockExpr(helper, asA<BlockExpr>(node));
			else if (isA<BinOpExpr>(node))        WalkBinOpExpr(helper, asA<BinOpExpr>(node));
			else if (isA<UnaryExpr>(node))        WalkUnaryExpr(helper, asA<UnaryExpr>(node));
			else if (isA<ArrayExpr>(node))        WalkArrayExpr(helper, asA<ArrayExpr>(node));
			else if (isA<ArrayAccessExpr>(node))  WalkArrayAccessExpr(helper, asA<ArrayAccessExpr>(node));
			else if (isA<MemberAccessExpr>(node)) WalkMemberAccessExpr(helper, asA<MemberAccessExpr>(node));
			else if (isA<IfExpr>(node))           WalkIfExpr(helper, asA<IfExpr>(node));
			else if (isA<TernaryExpr>(node))      WalkTernaryExpr(helper, asA<TernaryExpr>(node));
			else if (isA<FunctionExpr>(node))     WalkFunctionExpr(helper, asA<FunctionExpr>(node));
			else if (isA<CatchBlock>(node))       WalkCatchBlock(helper, asA<CatchBlock>(node));
			else if (isA<TryExpr>(node))          WalkTryExpr(helper, asA<TryExpr>(node));
			else if (isA<CastExpr>(node))         WalkCastExpr(helper, asA<CastExpr>(node));
			else if (isA<FunctionCallExpr>(node)) WalkFunctionCallExpr(helper, asA<FunctionCallExpr>(node));
			else if (isA<NewExpr>(node))          WalkNewExpr(helper, asA<NewExpr>(node));
			else if (isA<Identifier>(node))       WalkIdentifier(helper, asA<Identifier>(node));
			else                                  throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkStmt(T* helper, Statement* node) {
			if      (isA<LoopStmt>(node))       WalkLoopStmt(helper, asA<LoopStmt>(node));
			else if (isA<CommentStmt>(node))    WalkCommentStmt(helper, asA<CommentStmt>(node));
			else if (isA<BreakStmt>(node))      WalkBreakStmt(helper, asA<BreakStmt>(node));
			else if (isA<ContinueStmt>(node))   WalkContinueStmt(helper, asA<ContinueStmt>(node));
			else if (isA<ReturnStmt>(node))     WalkReturnStmt(helper, asA<ReturnStmt>(node));
			else if (isA<ExternFuncStmt>(node)) WalkExternFuncStmt(helper, asA<ExternFuncStmt>(node));
			else if (isA<ClassStmt>(node))      WalkClassStmt(helper, asA<ClassStmt>(node));
			else if (isA<InterfaceStmt>(node))  WalkInterfaceStmt(helper, asA<InterfaceStmt>(node));
			else if (isA<NamespaceStmt>(node))  WalkNamespaceStmt(helper, asA<NamespaceStmt>(node));
			else if (isA<ImportStmt>(node))     WalkImportStmt(helper, asA<ImportStmt>(node));
			else if (isA<ThrowStmt>(node))      WalkThrowStmt(helper, asA<ThrowStmt>(node));
			else if (isA<DeleteStmt>(node))     WalkDeleteStmt(helper, asA<DeleteStmt>(node));
			else if (isA<ExprStmt>(node))       WalkExprStmt(helper, asA<ExprStmt>(node));
			else                                throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkValue(T* helper, Value* node) {
			if      (isA<IntValue>(node))    WalkIntValue(helper, asA<IntValue>(node));
			else if (isA<UIntValue>(node))   WalkUIntValue(helper, asA<UIntValue>(node));
			else if (isA<FloatValue>(node))  WalkFloatValue(helper, asA<FloatValue>(node));
			else if (isA<DoubleValue>(node)) WalkDoubleValue(helper, asA<DoubleValue>(node));
			else if (isA<StringValue>(node)) WalkStringValue(helper, asA<StringValue>(node));
			else if (isA<CharValue>(node))   WalkCharValue(helper, asA<CharValue>(node));
			else if (isA<BoolValue>(node))   WalkBoolValue(helper, asA<BoolValue>(node));
			else                             throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkIdentifier(T* helper, Identifier* node) {
			if      (isA<NamedIDExpr>(node))      WalkNamedIDExpr(helper, asA<NamedIDExpr>(node));
			else if (isA<ReferenceIDExpr>(node))  WalkReferenceIDExpr(helper, asA<ReferenceIDExpr>(node));
			else if (isA<DtorIDExpr>(node))       WalkDtorIDExpr(helper, asA<DtorIDExpr>(node));
			else if (isA<AccessIDExpr>(node))     WalkAccessIDExpr(helper, asA<AccessIDExpr>(node));
			else if (isA<ThisID>(node))           WalkThisID(helper, asA<ThisID>(node));
			else                                  throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkBlockExpr(T* helper, BlockExpr* node) {
			if      (isA<LongBlockExpr>(node))  WalkLongBlockExpr(helper, asA<LongBlockExpr>(node));
			else if (isA<ShortBlockExpr>(node)) WalkShortBlockExpr(helper, asA<ShortBlockExpr>(node));
			else                                throw std::runtime_error("Unknown node to walk.");
		}
		
		virtual void WalkCommentStmt(T* helper, CommentStmt* node) = 0;
		virtual void WalkLoopStmt(T* helper, LoopStmt* node) = 0;
		virtual void WalkBreakStmt(T* helper, BreakStmt* node) = 0;
		virtual void WalkContinueStmt(T* helper, ContinueStmt* node) = 0;
		virtual void WalkReturnStmt(T* helper, ReturnStmt* node) = 0;
		virtual void WalkExternFuncStmt(T* helper, ExternFuncStmt* node) = 0;
		virtual void WalkClassStmt(T* helper, ClassStmt* node) = 0;
		virtual void WalkInterfaceStmt(T* helper, InterfaceStmt* node) = 0;
		virtual void WalkNamespaceStmt(T* helper, NamespaceStmt* node) = 0;
		virtual void WalkImportStmt(T* helper, ImportStmt* node) = 0;
		virtual void WalkThrowStmt(T* helper, ThrowStmt* node) = 0;
		virtual void WalkDeleteStmt(T* helper, DeleteStmt* node) = 0;
		virtual void WalkExprStmt(T* helper, ExprStmt* node) = 0;
		virtual void WalkVarDeclExpr(T* helper, VarDeclExpr* node) = 0;
		virtual void WalkBoolValue(T* helper, BoolValue* node) = 0;
		virtual void WalkIntValue(T* helper, IntValue* node) = 0;
		virtual void WalkUIntValue(T* helper, UIntValue* node) = 0;
		virtual void WalkFloatValue(T* helper, FloatValue* node) = 0;
		virtual void WalkDoubleValue(T* helper, DoubleValue* node) = 0;
		virtual void WalkStringValue(T* helper, StringValue* node) = 0;
		virtual void WalkCharValue(T* helper, CharValue* node) = 0;
		virtual void WalkThisID(T* helper, ThisID* node) = 0;
		virtual void WalkReferenceIDExpr(T* helper, ReferenceIDExpr* node) = 0;
		virtual void WalkNamedIDExpr(T* helper, NamedIDExpr* node) = 0;
		virtual void WalkDtorIDExpr(T* helper, DtorIDExpr* node) = 0;
		virtual void WalkAccessIDExpr(T* helper, AccessIDExpr* node) = 0;
		virtual void WalkLongBlockExpr(T* helper, LongBlockExpr* node) = 0;
		virtual void WalkShortBlockExpr(T* helper, ShortBlockExpr* node) = 0;
		virtual void WalkBinOpExpr(T* helper, BinOpExpr* node) = 0;
		virtual void WalkUnaryExpr(T* helper, UnaryExpr* node) = 0;
		virtual void WalkArrayExpr(T* helper, ArrayExpr* node) = 0;
		virtual void WalkArrayAccessExpr(T* helper, ArrayAccessExpr* node) = 0;
		virtual void WalkMemberAccessExpr(T* helper, MemberAccessExpr* node) = 0;
		virtual void WalkConditionalBlock(T* helper, ConditionalBlock* node) = 0;
		virtual void WalkIfExpr(T* helper, IfExpr* node) = 0;
		virtual void WalkTernaryExpr(T* helper, TernaryExpr* node) = 0;
		virtual void WalkFunctionExpr(T* helper, FunctionExpr* node) = 0;
		virtual void WalkCatchBlock(T* helper, CatchBlock* node) = 0;
		virtual void WalkTryExpr(T* helper, TryExpr* node) = 0;
		virtual void WalkCastExpr(T* helper, CastExpr* node) = 0;
		virtual void WalkFunctionCallExpr(T* helper, FunctionCallExpr* node) = 0;
		virtual void WalkNewExpr(T* helper, NewExpr* node) = 0;
		
		virtual ~WalkerBase() { }
	};
	
	class Walker : public WalkerBase<Visitor> { };

	/// Walker that will visit concrete elements
	class NonTraversalWalker : public Walker {
	public:
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node) override;
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node) override;
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node) override;
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node) override;
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node) override;
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) override;
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) override;
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node) override;
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node) override;
		virtual void WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) override;
		virtual void WalkExprStmt(Visitor* visitor, ExprStmt* node) override;
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) override;
		virtual void WalkBoolValue(Visitor* visitor, BoolValue* node) override;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) override;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) override;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) override;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) override;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) override;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) override;
		virtual void WalkThisID(Visitor* visitor, ThisID* node) override;
		virtual void WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) override;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) override;
		virtual void WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) override;
		virtual void WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) override;
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) override;
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) override;
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) override;
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node) override;
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) override;
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node) override;
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node) override;
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node) override;
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) override;
		virtual void WalkNewExpr(Visitor* visitor, NewExpr* node) override;
	};

	enum TraversalOrder { PREORDER, POSTORDER };

	/// Walker that traverses the hierarchy depth-first.
	class DepthFirstWalker : public Walker {
	private:
		TraversalOrder mOrder;
	public:
		virtual void WalkCommentStmt(Visitor* visitor, CommentStmt* node) override;
		virtual void WalkLoopStmt(Visitor* visitor, LoopStmt* node) override;
		virtual void WalkBreakStmt(Visitor* visitor, BreakStmt* node) override;
		virtual void WalkContinueStmt(Visitor* visitor, ContinueStmt* node) override;
		virtual void WalkReturnStmt(Visitor* visitor, ReturnStmt* node) override;
		virtual void WalkExternFuncStmt(Visitor* visitor, ExternFuncStmt* node) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* node) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* node) override;
		virtual void WalkNamespaceStmt(Visitor* visitor, NamespaceStmt* node) override;
		virtual void WalkImportStmt(Visitor* visitor, ImportStmt* node) override;
		virtual void WalkThrowStmt(Visitor* visitor, ThrowStmt* node) override;
		virtual void WalkDeleteStmt(Visitor* visitor, DeleteStmt* node) override;
		virtual void WalkExprStmt(Visitor* visitor, ExprStmt* node) override;
		virtual void WalkVarDeclExpr(Visitor* visitor, VarDeclExpr* node) override;
		virtual void WalkBoolValue(Visitor* visitor, BoolValue* node) override;
		virtual void WalkIntValue(Visitor* visitor, IntValue* node) override;
		virtual void WalkUIntValue(Visitor* visitor, UIntValue* node) override;
		virtual void WalkFloatValue(Visitor* visitor, FloatValue* node) override;
		virtual void WalkDoubleValue(Visitor* visitor, DoubleValue* node) override;
		virtual void WalkStringValue(Visitor* visitor, StringValue* node) override;
		virtual void WalkCharValue(Visitor* visitor, CharValue* node) override;
		virtual void WalkThisID(Visitor* visitor, ThisID* node) override;
		virtual void WalkReferenceIDExpr(Visitor* visitor, ReferenceIDExpr* node) override;
		virtual void WalkNamedIDExpr(Visitor* visitor, NamedIDExpr* node) override;
		virtual void WalkDtorIDExpr(Visitor* visitor, DtorIDExpr* node) override;
		virtual void WalkAccessIDExpr(Visitor* visitor, AccessIDExpr* node) override;
		virtual void WalkLongBlockExpr(Visitor* visitor, LongBlockExpr* node) override;
		virtual void WalkShortBlockExpr(Visitor* visitor, ShortBlockExpr* node) override;
		virtual void WalkBinOpExpr(Visitor* visitor, BinOpExpr* node) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* node) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* node) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* node) override;
		virtual void WalkMemberAccessExpr(Visitor* visitor, MemberAccessExpr* node) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* node) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* node) override;
		virtual void WalkTernaryExpr(Visitor* visitor, TernaryExpr* node) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* node) override;
		virtual void WalkCatchBlock(Visitor* visitor, CatchBlock* node) override;
		virtual void WalkTryExpr(Visitor* visitor, TryExpr* node) override;
		virtual void WalkCastExpr(Visitor* visitor, CastExpr* node) override;
		virtual void WalkFunctionCallExpr(Visitor* visitor, FunctionCallExpr* node) override;
		virtual void WalkNewExpr(Visitor* visitor, NewExpr* node) override;

		DepthFirstWalker(TraversalOrder order);
	};
}}

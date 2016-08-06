/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <functional>
#include "ast.h"
#include "typecheck.h"
#include "walker.h"

namespace orange { namespace ast {
	class Predicate {
	public:
		/// Determines whether or not this node specifically matches this predicate.
		virtual bool Matches(Node* n) = 0;
		virtual ~Predicate() { }
	};
	
	template <class T>
	class PredicateT : public Predicate {
	protected:
		std::function<bool(T*)> Matches_impl;
	public:
		virtual bool Matches(Node* n) override {
			if (isA<T>(n) == false) return false;
			return Matches_impl(asA<T>(n));
		}
		
		PredicateT(std::function<bool(T*)> func) : Matches_impl(func) { }
	};
	
	template class PredicateT<CommentStmt>;
	template class PredicateT<LoopStmt>;
	template class PredicateT<BreakStmt>;
	template class PredicateT<ContinueStmt>;
	template class PredicateT<ReturnStmt>;
	template class PredicateT<ExternFuncStmt>;
	template class PredicateT<ClassStmt>;
	template class PredicateT<InterfaceStmt>;
	template class PredicateT<NamespaceStmt>;
	template class PredicateT<ImportStmt>;
	template class PredicateT<ThrowStmt>;
	template class PredicateT<DeleteStmt>;
	template class PredicateT<ExprStmt>;
	template class PredicateT<VarDeclExpr>;
	template class PredicateT<BoolValue>;
	template class PredicateT<IntValue>;
	template class PredicateT<UIntValue>;
	template class PredicateT<FloatValue>;
	template class PredicateT<DoubleValue>;
	template class PredicateT<StringValue>;
	template class PredicateT<CharValue>;
	template class PredicateT<ThisID>;
	template class PredicateT<ReferenceIDExpr>;
	template class PredicateT<NamedIDExpr>;
	template class PredicateT<DtorIDExpr>;
	template class PredicateT<AccessIDExpr>;
	template class PredicateT<LongBlockExpr>;
	template class PredicateT<ShortBlockExpr>;
	template class PredicateT<BinOpExpr>;
	template class PredicateT<UnaryExpr>;
	template class PredicateT<ArrayExpr>;
	template class PredicateT<ArrayAccessExpr>;
	template class PredicateT<MemberAccessExpr>;
	template class PredicateT<ConditionalBlock>;
	template class PredicateT<IfExpr>;
	template class PredicateT<TernaryExpr>;
	template class PredicateT<FunctionExpr>;
	template class PredicateT<CatchBlock>;
	template class PredicateT<TryExpr>;
	template class PredicateT<CastExpr>;
	template class PredicateT<FunctionCallExpr>;
	template class PredicateT<NewExpr>;
	
	/// Creates a predicate class that accepts a specific conrete AST node.
	template <class T>
	Predicate* CreatePredicate(std::function<bool(T*)> function) {
		return new PredicateT<T>(function);
	}
	
	/// Walker that finds a node in the AST that matches some predicate.
	class PredicateWalker : public WalkerBase<Predicate> {
	private:
		std::vector<Node*> mMatches;
	protected:
		/// Tests if a predicate is true for a node. If it is, adds it to the list of
		/// matches.
		void TestPredicate(Predicate* p, Node* n);
	public:
		void Reset();
		std::vector<Node*> GetMatches() const;
		
		virtual void WalkCommentStmt(Predicate* predicate, CommentStmt* node);
		virtual void WalkLoopStmt(Predicate* predicate, LoopStmt* node);
		virtual void WalkBreakStmt(Predicate* predicate, BreakStmt* node);
		virtual void WalkContinueStmt(Predicate* predicate, ContinueStmt* node);
		virtual void WalkReturnStmt(Predicate* predicate, ReturnStmt* node);
		virtual void WalkExternFuncStmt(Predicate* predicate, ExternFuncStmt* node);
		virtual void WalkClassStmt(Predicate* predicate, ClassStmt* node);
		virtual void WalkInterfaceStmt(Predicate* predicate, InterfaceStmt* node);
		virtual void WalkNamespaceStmt(Predicate* predicate, NamespaceStmt* node);
		virtual void WalkImportStmt(Predicate* predicate, ImportStmt* node);
		virtual void WalkThrowStmt(Predicate* predicate, ThrowStmt* node);
		virtual void WalkDeleteStmt(Predicate* predicate, DeleteStmt* node);
		virtual void WalkExprStmt(Predicate* predicate, ExprStmt* node);
		virtual void WalkVarDeclExpr(Predicate* predicate, VarDeclExpr* node);
		virtual void WalkBoolValue(Predicate* predicate, BoolValue* node);
		virtual void WalkIntValue(Predicate* predicate, IntValue* node);
		virtual void WalkUIntValue(Predicate* predicate, UIntValue* node);
		virtual void WalkFloatValue(Predicate* predicate, FloatValue* node);
		virtual void WalkDoubleValue(Predicate* predicate, DoubleValue* node);
		virtual void WalkStringValue(Predicate* predicate, StringValue* node);
		virtual void WalkCharValue(Predicate* predicate, CharValue* node);
		virtual void WalkThisID(Predicate* predicate, ThisID* node);
		virtual void WalkReferenceIDExpr(Predicate* predicate, ReferenceIDExpr* node);
		virtual void WalkNamedIDExpr(Predicate* predicate, NamedIDExpr* node);
		virtual void WalkDtorIDExpr(Predicate* predicate, DtorIDExpr* node);
		virtual void WalkAccessIDExpr(Predicate* predicate, AccessIDExpr* node);
		virtual void WalkLongBlockExpr(Predicate* predicate, LongBlockExpr* node);
		virtual void WalkShortBlockExpr(Predicate* predicate, ShortBlockExpr* node);
		virtual void WalkBinOpExpr(Predicate* predicate, BinOpExpr* node);
		virtual void WalkUnaryExpr(Predicate* predicate, UnaryExpr* node);
		virtual void WalkArrayExpr(Predicate* predicate, ArrayExpr* node);
		virtual void WalkArrayAccessExpr(Predicate* predicate, ArrayAccessExpr* node);
		virtual void WalkMemberAccessExpr(Predicate* predicate, MemberAccessExpr* node);
		virtual void WalkConditionalBlock(Predicate* predicate, ConditionalBlock* node);
		virtual void WalkIfExpr(Predicate* predicate, IfExpr* node);
		virtual void WalkTernaryExpr(Predicate* predicate, TernaryExpr* node);
		virtual void WalkFunctionExpr(Predicate* predicate, FunctionExpr* node);
		virtual void WalkCatchBlock(Predicate* predicate, CatchBlock* node);
		virtual void WalkTryExpr(Predicate* predicate, TryExpr* node);
		virtual void WalkCastExpr(Predicate* predicate, CastExpr* node);
		virtual void WalkFunctionCallExpr(Predicate* predicate, FunctionCallExpr* node);
		virtual void WalkNewExpr(Predicate* predicate, NewExpr* node);
		
		PredicateWalker();
	};
	
}}

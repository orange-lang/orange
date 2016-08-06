//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <stack>

#include <libast/visitor.h>
#include <libast/search.h>

#include <libanalysis/error.h>
#include <libanalysis/analyze.h>
#include <libanalysis/typetable.h>
#include <libanalysis/context.h>

namespace orange { namespace analysis {
	using namespace orange::ast;

	/// Visitor that determines the types for specific nodes. Best used with
	/// a depth-first, post-order walker, as the type of a node depends on the
	/// types of its components
	class ResolveVisitor : public Visitor {
	private:
		TypeTable* mTypeTable;
		NodeTypeContext* mContext;
		AnalysisMessageLog& mLog;
		
		/// Gets the context parameters for a specific node in this context.
		std::vector<Type*> GetContextParameters(Node* node);
		
		/// Gets the context parameters that would instantiate some context.
		std::vector<Type*> GetContextInstParams(Node* node, Node* target);
		
		/// Logs an error and sets the type of node to var.
		void LogError(Node* node, AnalysisError err);
		
		template <typename T>
		std::vector<Type*> GetTypes(std::vector<T*> params) {
			std::vector<Type*> ret;
			for (auto param : params) {
				ret.push_back(mContext->GetNodeType(param));
			}
			return ret;
		}
		
		bool ExpectCompatible(std::vector<Type*> params, Type* expected);
		Type* GetHighestType(std::vector<Type*> params);
	public:
		NodeTypeContext* GetContext() const;
		AnalysisMessageLog& GetLog() const;
		
		virtual void VisitReturnStmt(ReturnStmt* node) override;
		virtual void VisitExternFuncStmt(ExternFuncStmt* node) override;
		virtual void VisitClassStmt(ClassStmt* node) override;
		virtual void VisitVarDeclExpr(VarDeclExpr* node) override;
		virtual void VisitBoolValue(BoolValue* node) override;
		virtual void VisitIntValue(IntValue* node) override;
		virtual void VisitUIntValue(UIntValue* node) override;
		virtual void VisitFloatValue(FloatValue* node) override;
		virtual void VisitDoubleValue(DoubleValue* node) override;
		virtual void VisitStringValue(StringValue* node) override;
		virtual void VisitCharValue(CharValue* node) override;
		virtual void VisitThisID(ThisID* node) override;
		virtual void VisitReferenceIDExpr(ReferenceIDExpr* node) override;
		virtual void VisitDtorIDExpr(DtorIDExpr* node) override;
		virtual void VisitAccessIDExpr(AccessIDExpr* node) override;
		virtual void VisitLongBlockExpr(LongBlockExpr* node) override;
		virtual void VisitShortBlockExpr(ShortBlockExpr* node) override;
		virtual void VisitBinOpExpr(BinOpExpr* node) override;
		virtual void VisitUnaryExpr(UnaryExpr* node) override;
		virtual void VisitArrayExpr(ArrayExpr* node) override;
		virtual void VisitArrayAccessExpr(ArrayAccessExpr* node) override;
		virtual void VisitMemberAccessExpr(MemberAccessExpr* node) override;
		virtual void VisitConditionalBlock(ConditionalBlock* node) override;
		virtual void VisitIfExpr(IfExpr* node) override;
		virtual void VisitTernaryExpr(TernaryExpr* node) override;
		virtual void VisitFunctionExpr(FunctionExpr* node) override;
		virtual void VisitCatchBlock(CatchBlock* node) override;
		virtual void VisitTryExpr(TryExpr* node) override;
		virtual void VisitCastExpr(CastExpr* node) override;
		virtual void VisitFunctionCallExpr(FunctionCallExpr* node) override;
		virtual void VisitNewExpr(NewExpr* node) override;

		ResolveVisitor(TypeTable* tt, NodeTypeContext* context, AnalysisMessageLog& log);
	};
}}
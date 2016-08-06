//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include "ast.h"
#include "visitor.h"
#include "walker.h"

namespace orange { namespace ast {
	class ASTPrinter : public Visitor {
	private:
		Walker& mWalker;

		std::stringstream mOutput;
		int mIndentation = 0;

		void handleIdententation();
		void printID(Node* node);
	public:
		void PrintType(Type* ty);

		virtual void VisitCommentStmt(CommentStmt* node) override;
		virtual void VisitLoopStmt(LoopStmt* node) override;
		virtual void VisitBreakStmt(BreakStmt* node) override;
		virtual void VisitContinueStmt(ContinueStmt* node) override;
		virtual void VisitReturnStmt(ReturnStmt* node) override;
		virtual void VisitExternFuncStmt(ExternFuncStmt* node) override;
		virtual void VisitEnumValue(EnumValue* node) override;
		virtual void VisitEnumStmt(EnumStmt* node) override;
		virtual void VisitClassStmt(ClassStmt* node) override;
		virtual void VisitInterfaceStmt(InterfaceStmt* node) override;
		virtual void VisitNamespaceStmt(NamespaceStmt* node) override;
		virtual void VisitImportStmt(ImportStmt* node) override;
		virtual void VisitThrowStmt(ThrowStmt* node) override;
		virtual void VisitDeleteStmt(DeleteStmt* node) override;
		virtual void VisitExprStmt(ExprStmt* node) override;
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
		virtual void VisitNamedIDExpr(NamedIDExpr* node) override;
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

		std::string getOutput() const;

		ASTPrinter(Walker& walker);
	};

	/// Pretty prints an AST.
	std::string PrettyPrint(LongBlockExpr* ast);
}}
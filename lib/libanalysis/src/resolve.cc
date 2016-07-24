//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/compare.h>
#include <libast/typecheck.h>
#include <libast/binop.h>

#include "resolve.h"
#include "compatibility.h"

using namespace orange::analysis;

void ResolveVisitor::VisitYieldStmt(YieldStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
	auto ty = (node->value == nullptr) ? new BuiltinType(BuiltinTypeKind::VOID) : mContext->GetNodeType(node->value);
	mContext->SetNodeType(node, ty);
}

void ResolveVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitClassStmt(ClassStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitGetterStmt(GetterStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitPropertyStmt(PropertyStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitThrowStmt(ThrowStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitDeleteStmt(DeleteStmt* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitVarDeclExpr(VarDeclExpr* node) {
	if (node->bindings.size() > 1) {
		throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
	}

	if (node->types.size() > 0 && node->types.size() != node->bindings.size()) {
		mLog.LogMessage(MessageSeverity::ERROR, MISMATCHED_TYPES_FOR_BINDINGS, node, mContext);
		for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
		return;
	}

	if (node->value == nullptr && node->types.size() == 0) {
		mLog.LogMessage(ERROR, MISSING_DEFAULT_VALUE, node, mContext);
		for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
		return;
	}

	auto binding = node->bindings[0];

	if (isA<NamedIDExpr>(binding) == false) {
		throw AnalysisMessage(FATAL, INVALID_NAME, node->id, mContext);
	}

	Type* nodeType = nullptr;

	if (node->value != nullptr) {
		nodeType = mContext->GetNodeType(node->value);
		if (IsVoidType(nodeType)) {
			mLog.LogMessage(ERROR, INVALID_VALUE, node, mContext);
			for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
			return;
		}
	}

	if (node->types.size() > 0) {
		nodeType = node->types[0];
		if (IsVoidType(nodeType)) {
			mLog.LogMessage(ERROR, INVALID_TYPE, node, mContext);
			for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
			return;
		}
	}

	if (isA<ReferenceType>(nodeType)) {
		throw AnalysisMessage(FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
	}

	mContext->SetNodeType(binding, nodeType);

	// Finally, set the type for the variable declaration, which will be a tuple of all the bindings
	mContext->SetNodeType(node, new TupleType(std::vector<Type*>({
		mContext->GetNodeType(binding)
	})));
}


void ResolveVisitor::VisitBoolValue(BoolValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::BOOL));
}

void ResolveVisitor::VisitIntValue(IntValue* node) {
	mContext->SetNodeType(node, node->type);
}

void ResolveVisitor::VisitUIntValue(UIntValue* node) {
	mContext->SetNodeType(node, node->type);
}

void ResolveVisitor::VisitFloatValue(FloatValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::FLOAT));
}

void ResolveVisitor::VisitDoubleValue(DoubleValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::DOUBLE));
}

void ResolveVisitor::VisitStringValue(StringValue* node) {
	mContext->SetNodeType(node, new PointerType(new BuiltinType(BuiltinTypeKind::CHAR)));
}

void ResolveVisitor::VisitCharValue(CharValue* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::CHAR));
}

void ResolveVisitor::VisitThisID(ThisID* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitReferenceIDExpr(ReferenceIDExpr* node) {
	auto original = mSearcher.FindNode(node, node, true);

	if (original == nullptr) {
		mLog.LogMessage(ERROR, REFERENCE_NOT_FOUND, node, mContext);
		mContext->SetNodeType(node, new BuiltinType(VAR));
		return;
	}

	if (isA<VarDeclExpr>(original) == false) {
		throw AnalysisMessage(FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
	}

	if (isA<VarDeclExpr>(original)) {
		auto varDecl = asA<VarDeclExpr>(original);
		for (auto binding : varDecl->bindings) {
			if (isA<NamedIDExpr>(binding) == false) continue;
			if (asA<NamedIDExpr>(binding)->name == node->name) {
				mContext->SetNodeType(node, mContext->GetNodeType(binding));
				break;
			}
		}
	}
}

void ResolveVisitor::VisitTempIDExpr(TempIDExpr* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::VAR));
}

void ResolveVisitor::VisitDtorIDExpr(DtorIDExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitAccessIDExpr(AccessIDExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitLongBlockExpr(LongBlockExpr* node) {
	// The type of a long block is inherited from all yield statements of direct children.
	auto yieldStatements = mSearcher.FindChildren<YieldStmt>(node, true);
	
	if (yieldStatements.size() == 0) {
		mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::VOID));
	} else {
		throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
	}
}

void ResolveVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitBinOpExpr(BinOpExpr* node) {
	auto tyLHS = mContext->GetNodeType(node->LHS);
	auto tyRHS = mContext->GetNodeType(node->RHS);

	if (CompareType(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, tyLHS);
	} else if (AreTypesCompatible(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, GetImplicitType(tyLHS, tyRHS));
	} else {
		mLog.LogMessage(ERROR, INCOMPATIBLE_TYPES, node, mContext);
		mContext->SetNodeType(node, new BuiltinType(VAR));
		return;
	}

	if (IsAssignBinOp(node->op)) {
		mContext->SetNodeType(node, tyLHS);

		if (mContext->IsLValue(node->LHS) == false)
			throw std::runtime_error("Can only assign to lvalues");
	}

	if (IsCompareBinOp(node->op)) {
		// The type of compare nodes is always a boolean. Code generation will 
		// have to find the implicit type between the two nodes to be able to 
		// generate it successfully.
		//
		// By this point, we've already determined that the types are compatible,
		// so we don't need to do any extra error checking.
		mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::BOOL));
	}
}

void ResolveVisitor::VisitUnaryExpr(UnaryExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitTupleExpr(TupleExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitArrayExpr(ArrayExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitArrayRangeExpr(ArrayRangeExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitArrayAccessExpr(ArrayAccessExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitMemberAccessExpr(MemberAccessExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitNamedExpr(NamedExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitConditionalBlock(ConditionalBlock* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitIfExpr(IfExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitTernaryExpr(TernaryExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitSwitchPattern(SwitchPattern* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitSwitchExpr(SwitchExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitFunctionExpr(FunctionExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitFunctionCallExpr(FunctionCallExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitNewExpr(NewExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitEnumMatch(EnumMatch* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

ResolveVisitor::ResolveVisitor(NodeTypeContext* context, AnalysisMessageLog& log, ASTSearcher& searcher) :
	mContext(context), mLog(log), mSearcher(searcher) { }


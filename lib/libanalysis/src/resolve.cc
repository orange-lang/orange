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
	throw std::runtime_error("Don't know how to determine type of YieldStmt");
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
	auto ty = (node->value == nullptr) ? new BuiltinType(BuiltinTypeKind::VOID) : mContext->GetNodeType(node->value);
	mContext->SetNodeType(node, ty);
}

void ResolveVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
	throw std::runtime_error("Don't know how to determine type of ExternFuncStmt");
}

void ResolveVisitor::VisitClassStmt(ClassStmt* node) {
	throw std::runtime_error("Don't know how to determine type of ClassStmt");
}

void ResolveVisitor::VisitGetterStmt(GetterStmt* node) {
	throw std::runtime_error("Don't know how to determine type of GetterStmt");
}

void ResolveVisitor::VisitPropertyStmt(PropertyStmt* node) {
	throw std::runtime_error("Don't know how to determine type of PropertyStmt");
}

void ResolveVisitor::VisitThrowStmt(ThrowStmt* node) {
	throw std::runtime_error("Don't know how to determine type of ThrowStmt");
}

void ResolveVisitor::VisitDeleteStmt(DeleteStmt* node) {
	throw std::runtime_error("Don't know how to determine type of DeleteStmt");
}

void ResolveVisitor::VisitVarDeclExpr(VarDeclExpr* node) {
	if (node->bindings.size() > 1) {
		throw std::runtime_error("Can't handle multiple bindings yet.");
	}

	if (node->types.size() > 0 && node->types.size() != node->bindings.size()) {
		throw std::runtime_error("The number of defined types do not match the number of declared variables");
	}

	if (node->value == nullptr && node->types.size() == 0) {
		throw std::runtime_error("Implicitly typed variables need an initial value");
	}

	auto binding = node->bindings[0];

	if (isA<NamedIDExpr>(binding) == false) {
		throw std::runtime_error("Invalid name for variable");
	}

	Type* nodeType = nullptr;

	if (node->value != nullptr) {
		nodeType = mContext->GetNodeType(node->value);
		if (IsVoidType(nodeType)) throw std::runtime_error("Cannot assign void typed expresion to variable");
	}

	if (node->types.size() > 0) {
		nodeType = node->types[0];
		if (IsVoidType(nodeType)) throw std::runtime_error("");
	}

	if (isA<ReferenceType>(nodeType)) {
		throw std::runtime_error("Not sure how to handle reference types yet.");
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
	throw std::runtime_error("Don't know how to determine type of ThisID");
}

void ResolveVisitor::VisitReferenceIDExpr(ReferenceIDExpr* node) {
	auto original = mSearcher.FindNode(node, node, true);

	if (original == nullptr) {
		throw std::runtime_error("Unknown reference to identifier");
	}

	if (isA<VarDeclExpr>(original) == false) {
		throw std::runtime_error("Don't know how to handle non-variable identifier");
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

void ResolveVisitor::VisitNamedIDExpr(NamedIDExpr* node) {
	throw std::runtime_error("Don't know how to determine type of NamedIDExpr");
}

void ResolveVisitor::VisitTempIDExpr(TempIDExpr* node) {
	mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::VAR));
}

void ResolveVisitor::VisitDtorIDExpr(DtorIDExpr* node) {
	throw std::runtime_error("Don't know how to determine type of DtorIDExpr");
}

void ResolveVisitor::VisitAccessIDExpr(AccessIDExpr* node) {
	throw std::runtime_error("Don't know how to determine type of AccessIDExpr");
}

void ResolveVisitor::VisitLongBlockExpr(LongBlockExpr* node) {
	throw std::runtime_error("Don't know how to determine type of LongBlockExpr");
}

void ResolveVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
	throw std::runtime_error("Don't know how to determine type of ShortBlockExpr");
}

void ResolveVisitor::VisitBinOpExpr(BinOpExpr* node) {
	auto tyLHS = mContext->GetNodeType(node->LHS);
	auto tyRHS = mContext->GetNodeType(node->RHS);

	if (CompareType(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, tyLHS);
	} else if (AreTypesCompatible(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, GetImplicitType(tyLHS, tyRHS));
	} else {
		throw std::runtime_error("Incompatible types.");
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
	throw std::runtime_error("Don't know how to determine type of UnaryExpr");
}

void ResolveVisitor::VisitTupleExpr(TupleExpr* node) {
	throw std::runtime_error("Don't know how to determine type of TupleExpr");
}

void ResolveVisitor::VisitArrayExpr(ArrayExpr* node) {
	throw std::runtime_error("Don't know how to determine type of ArrayExpr");
}

void ResolveVisitor::VisitArrayRangeExpr(ArrayRangeExpr* node) {
	throw std::runtime_error("Don't know how to determine type of ArrayRangeExpr");
}

void ResolveVisitor::VisitArrayAccessExpr(ArrayAccessExpr* node) {
	throw std::runtime_error("Don't know how to determine type of ArrayAccessExpr");
}

void ResolveVisitor::VisitMemberAccessExpr(MemberAccessExpr* node) {
	throw std::runtime_error("Don't know how to determine type of MemberAccessExpr");
}

void ResolveVisitor::VisitNamedExpr(NamedExpr* node) {
	throw std::runtime_error("Don't know how to determine type of NamedExpr");
}

void ResolveVisitor::VisitConditionalBlock(ConditionalBlock* node) {
	throw std::runtime_error("Don't know how to determine type of ConditionalBlock");
}

void ResolveVisitor::VisitIfExpr(IfExpr* node) {
	throw std::runtime_error("Don't know how to determine type of IfExpr");
}

void ResolveVisitor::VisitTernaryExpr(TernaryExpr* node) {
	throw std::runtime_error("Don't know how to determine type of TernaryExpr");
}

void ResolveVisitor::VisitSwitchPattern(SwitchPattern* node) {
	throw std::runtime_error("Don't know how to determine type of SwitchPattern");
}

void ResolveVisitor::VisitSwitchExpr(SwitchExpr* node) {
	throw std::runtime_error("Don't know how to determine type of SwitchExpr");
}

void ResolveVisitor::VisitFunctionExpr(FunctionExpr* node) {
	throw std::runtime_error("Don't know how to determine type of FunctionExpr");
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
	throw std::runtime_error("Don't know how to determine type of CatchBlock");
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
	throw std::runtime_error("Don't know how to determine type of TryExpr");
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
	throw std::runtime_error("Don't know how to determine type of CastExpr");
}

void ResolveVisitor::VisitFunctionCallExpr(FunctionCallExpr* node) {
	throw std::runtime_error("Don't know how to determine type of FunctionCallExpr");
}

void ResolveVisitor::VisitNewExpr(NewExpr* node) {
	throw std::runtime_error("Don't know how to determine type of NewExpr");
}

void ResolveVisitor::VisitEnumMatch(EnumMatch* node) {
	throw std::runtime_error("Don't know how to determine type of EnumMatch");
}

ResolveVisitor::ResolveVisitor(NodeTypeContext* context, AnalysisMessageLog& log, ASTSearcher& searcher) :
	mContext(context), mLog(log), mSearcher(searcher) { }


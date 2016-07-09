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
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
	auto ty = (node->value == nullptr) ? new BuiltinType(BuiltinTypeKind::VOID) : mContext->GetNodeType(node->value);
	mContext->SetNodeType(node, ty);
}

void ResolveVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
}

void ResolveVisitor::VisitClassStmt(ClassStmt* node) {
}

void ResolveVisitor::VisitGetterStmt(GetterStmt* node) {
}

void ResolveVisitor::VisitPropertyStmt(PropertyStmt* node) {
}

void ResolveVisitor::VisitThrowStmt(ThrowStmt* node) {
}

void ResolveVisitor::VisitDeleteStmt(DeleteStmt* node) {
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
}

void ResolveVisitor::VisitTempIDExpr(TempIDExpr* node) {
}

void ResolveVisitor::VisitDtorIDExpr(DtorIDExpr* node) {
}

void ResolveVisitor::VisitAccessIDExpr(AccessIDExpr* node) {
}

void ResolveVisitor::VisitLongBlockExpr(LongBlockExpr* node) {
}

void ResolveVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
}

void ResolveVisitor::VisitBinOpExpr(BinOpExpr* node) {
	auto tyLHS = mContext->GetNodeType(node->LHS);
	auto tyRHS = mContext->GetNodeType(node->RHS);

	if (CompareType(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, tyLHS);
	} else if (AreTypesCompatible(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, GetImplicitType(tyLHS, tyRHS));
	}

	if (IsAssignBinOp(node->op)) {
		mContext->SetNodeType(node, tyLHS);

		if (mContext->IsLValue(node->LHS) == false)
			throw std::runtime_error("Can only assign to lvalues");
	}
}

void ResolveVisitor::VisitUnaryExpr(UnaryExpr* node) {
}

void ResolveVisitor::VisitTupleExpr(TupleExpr* node) {
}

void ResolveVisitor::VisitArrayExpr(ArrayExpr* node) {
}

void ResolveVisitor::VisitArrayRangeExpr(ArrayRangeExpr* node) {
}

void ResolveVisitor::VisitArrayAccessExpr(ArrayAccessExpr* node) {
}

void ResolveVisitor::VisitMemberAccessExpr(MemberAccessExpr* node) {
}

void ResolveVisitor::VisitNamedExpr(NamedExpr* node) {
}

void ResolveVisitor::VisitConditionalBlock(ConditionalBlock* node) {
}

void ResolveVisitor::VisitIfExpr(IfExpr* node) {
}

void ResolveVisitor::VisitTernaryExpr(TernaryExpr* node) {
}

void ResolveVisitor::VisitSwitchPattern(SwitchPattern* node) {
}

void ResolveVisitor::VisitSwitchExpr(SwitchExpr* node) {
}

void ResolveVisitor::VisitFunctionExpr(FunctionExpr* node) {
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
}

void ResolveVisitor::VisitFunctionCallExpr(FunctionCallExpr* node) {
}

void ResolveVisitor::VisitNewExpr(NewExpr* node) {
}

ResolveVisitor::ResolveVisitor(NodeTypeContext* context, ASTSearcher& searcher) :
	mContext(context), mSearcher(searcher) { }


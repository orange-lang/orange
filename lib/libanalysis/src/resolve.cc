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

std::vector<Type*> ResolveVisitor::GetContextParameters(Node* node) {
	std::vector<Type*> types;
	
	if (isA<FunctionExpr>(node)) {
		auto params = asA<FunctionExpr>(node)->params;
		for (auto param : params) types.push_back(mContext->GetNodeType(param));
	} else {
		throw std::runtime_error("fatal: invalid node for context parameters");
	}
	
	return types;
}

std::vector<Type*> ResolveVisitor::GetContextInstParams(Node* node, Node* target) {
	std::vector<Type*> types;
	
	if (isA<FunctionCallExpr>(node)) {
		auto original = GetContextParameters(target);
		
		auto args = asA<FunctionCallExpr>(node)->args;
		
		if (original.size() != args.size()) {
			throw std::runtime_error("fatal: mismatch argument count");
		}
		
		for (auto i = 0ul; i < original.size(); i++) {
			if (IsGenericType(original[i])) {
				types.push_back(mContext->GetNodeType(node));
			} else {
				types.push_back(original[i]);
			}
		}
	} else {
		throw std::runtime_error("fatal: invalid node for ctx instantiation parameters");
	}
	
	return types;
}

void ResolveVisitor::LogError(Node* node, AnalysisError err) {
	mLog.LogMessage(ERROR, err, node, mContext);
	mContext->SetNodeType(node, new BuiltinType(VAR));
}

void ResolveVisitor::VisitYieldStmt(YieldStmt* node) {
	mContext->SetNodeType(node, mContext->GetNodeType(node->value));
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
	auto ty = (node->value == nullptr) ? new BuiltinType(BuiltinTypeKind::VOID) : mContext->GetNodeType(node->value);
	
	if (IsVoidType(ty) && node->value != nullptr) {
		mLog.LogMessage(MessageSeverity::ERROR, AnalysisError::INVALID_TYPE, node, mContext);
		mContext->SetNodeType(node, new BuiltinType(VAR));
		return;
	}
	
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
	mContext->SetNodeType(node, mContext->GetNodeType(binding));
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
	auto original = mTypeTable->GetSearcher()->FindNode(node, node, true);

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
	auto yieldStatements = mTypeTable->GetSearcher()->FindChildren<YieldStmt>(node, true);
	
	if (yieldStatements.size() == 0) {
		mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::VOID));
		return;
	}
	
	auto maxType = mContext->GetNodeType(yieldStatements[0]);
	for (unsigned long i = 1; i < yieldStatements.size(); i++) {
		auto stmtType = mContext->GetNodeType(yieldStatements[i]);
		
		if (CompareType(maxType, stmtType)) {
			continue;
		} else if (AreTypesCompatible(stmtType, maxType)) {
			maxType = GetImplicitType(stmtType, maxType);
		} else {
			mLog.LogMessage(ERROR, INCOMPATIBLE_TYPES, node, mContext);
			mContext->SetNodeType(node, new BuiltinType(VAR));
			return;
		}
	}
	
	mContext->SetNodeType(node, maxType);
}

void ResolveVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
	auto type = mContext->GetNodeType(node->statement);
	if (type == nullptr) type = new BuiltinType(VOID);
	
	mContext->SetNodeType(node, type);
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
		
		auto lval = IsLValue(node->LHS, mContext->GetNodeType(node->LHS));
		if (!lval) throw std::runtime_error("Can only assign to lvalues");
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
	// By default, inherit the type from the expression
	mContext->SetNodeType(node, mContext->GetNodeType(node->LHS));
	
	// If INCREMENT, DECREMENT or REFERENCE, LHS must be an lvalue
	if ((node->op == INCREMENT || node->op == DECREMENT || node->op == REFERENCE)) {
		auto lval = IsLValue(node->LHS, mContext->GetNodeType(node->LHS));
		
		if (!lval) {
			mLog.LogMessage(ERROR, AnalysisError::INVALID_VALUE, node, mContext);
			mContext->SetNodeType(node, new BuiltinType(VAR));
			return;
		}
		
		if (node->op == REFERENCE) {
			mContext->SetNodeType(node, new PointerType(mContext->GetNodeType(node->LHS)));
		}
	}
	
	// If NOT, LHS must be a boolean
	if (node->op == NOT && !IsBooleanType(mContext->GetNodeType(node->LHS))) {
		mLog.LogMessage(ERROR, AnalysisError::INVALID_VALUE, node, mContext);
		mContext->SetNodeType(node, new BuiltinType(VAR));
		return;
	}
	
	// If TIMES, LHS must be a pointer
	if (node->op == UnaryOp::TIMES) {
		if (!isA<PointerType>(mContext->GetNodeType(node->LHS))) {
			mLog.LogMessage(ERROR, AnalysisError::INVALID_VALUE, node, mContext);
			mContext->SetNodeType(node, new BuiltinType(VAR));
			return;
		}
		
		mContext->SetNodeType(node, asA<PointerType>(mContext->GetNodeType(node->LHS))->base);
	}
}

void ResolveVisitor::VisitTupleExpr(TupleExpr* node) {
	std::vector<Type*> types;
	
	for (auto value : node->values) {
		types.push_back(mContext->GetNodeType(value));
	}
	
	mContext->SetNodeType(node, new TupleType(types));
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
	if (mContext->GetNode()->id != node->id) {
		auto existingCtx = mContext->GetDefaultChildContext(node, false);
		
		if (existingCtx == nullptr) {
			// Create a context and resolve this function in that context.
			auto ctxParams = GetContextParameters(node);
			
			auto newCtx = new NodeTypeContext(node, mContext, true, ctxParams);
			mContext->AddChildContext(newCtx);
			
			// Resolve this node in that context.
			ResolveVisitor subVisitor(mTypeTable, newCtx, mLog);
			mTypeTable->GetWalker()->WalkFunctionExpr(&subVisitor, node);
		}
		
		return;
	}
	
	// Determine return type.
	Type* retType      = node->retType;
	Type* highestType  = nullptr;
	
	auto allRetStatements = mTypeTable->GetSearcher()->FindChildren<ReturnStmt>(node, false);
	
	// Filter out return statements who have a different parent function than our node.
	std::vector<ReturnStmt*> retStatements;
	std::copy_if(allRetStatements.begin(), allRetStatements.end(), std::back_inserter(retStatements),
	[this, node] (ReturnStmt* stmt) {
		auto parent = this->mTypeTable->GetSearcher()->FindParent<FunctionExpr>(stmt);
		return parent != nullptr && parent->id == node->id;
	});
	
	if (retStatements.size() == 0) {
		if (retType != nullptr && IsVoidType(retType) == false) {
			LogError(node, MISSING_RETURN);
		} else {
			mContext->SetNodeType(node, new BuiltinType(VOID));
		}
		
		return;
	}
	
	highestType = mContext->GetNodeType(retStatements.front());
	
	// Iterate through all the retStatements. Determine highest type and ensure compatibility with retType,
	// if it exists.
	for (auto retStatement : retStatements) {
		auto ty = mContext->GetNodeType(retStatement);
		
		if (AreTypesCompatible(highestType, ty) == false) {
			LogError(node, INVALID_TYPE);
			return;
		}
		
		if (retType && !AreTypesCompatible(ty, retType)) {
			LogError(node, INVALID_TYPE);
			return;
		}
		
		highestType = GetImplicitType(highestType, ty);
	}
	
	retType = (retType != nullptr) ? retType : highestType;
	
	std::vector<Type*> paramTys;
	for (auto param : node->params) paramTys.push_back(mContext->GetNodeType(param));
	
	mContext->SetNodeType(node, new FunctionType(paramTys, retType));
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
	mContext->SetNodeType(node, node->targetType);
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

NodeTypeContext* ResolveVisitor::GetContext() const { return mContext; }

AnalysisMessageLog& ResolveVisitor::GetLog() const { return mLog; }

ResolveVisitor::ResolveVisitor(TypeTable* tt, NodeTypeContext* context, AnalysisMessageLog& log)
	:
	mTypeTable(tt), mContext(context), mLog(log) { }



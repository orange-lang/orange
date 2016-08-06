//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <algorithm>

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

bool ResolveVisitor::ExpectCompatible(std::vector<Type*> params, Type* expected) {
	for (auto param : params) {
		if (!AreTypesCompatible(param, expected)) return false;
	}
	
	return true;
}

Type* ResolveVisitor::GetHighestType(std::vector<Type*> params){
	if (params.size() == 0) return nullptr;
	
	auto highestType = params.front();
	for (auto ty : params) highestType = GetImplicitType(ty, highestType);
	
	return highestType;
}

void ResolveVisitor::VisitYieldStmt(YieldStmt* node) {
	if (IsVoidType(mContext->GetNodeType(node->value))) {
		LogError(node, INVALID_TYPE);
		return;
	}
	
	mContext->SetNodeType(node, mContext->GetNodeType(node->value));
}

void ResolveVisitor::VisitReturnStmt(ReturnStmt* node) {
	auto ty = (node->value == nullptr) ? new BuiltinType(BuiltinTypeKind::VOID) : mContext->GetNodeType(node->value);
	
	if (IsVoidType(ty) && node->value != nullptr) {
		LogError(node, INVALID_TYPE);
		return;
	}
	
	mContext->SetNodeType(node, ty);
}

void ResolveVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
	std::vector<Type*> paramTys;
	for (auto param : node->params) paramTys.push_back(mContext->GetNodeType(param));
	
	mContext->SetNodeType(node, new FunctionType(paramTys, node->retType));
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
	if (node->types.size() > 0 && node->types.size() != node->bindings.size()) {
		LogError(node, MISMATCHED_TYPES_FOR_BINDINGS);
		for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
		return;
	}

	if (node->value == nullptr && node->types.size() == 0) {
		LogError(node, MISSING_DEFAULT_VALUE);
		for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
		return;
	}
	
	if (node->value != nullptr && node->bindings.size() > 1) {
		auto valueTy = mContext->GetNodeType(node->value);
		if (!isA<TupleType>(valueTy) || asA<TupleType>(valueTy)->types.size() != node->bindings.size()) {
			LogError(node, MISSING_DEFAULT_VALUE);
			for (auto binding : node->bindings) mContext->SetNodeType(binding, new BuiltinType(VAR));
			return;
		}
	}
	
	for (unsigned long i = 0; i < node->bindings.size(); i++) {
		auto binding = node->bindings[i];
		
		if (isA<NamedIDExpr>(binding) == false) {
			throw AnalysisMessage(FATAL, INVALID_NAME, node->id, mContext);
		}
		
		Type* bindingType = nullptr;
		
		if (node->value != nullptr) {
			bindingType = mContext->GetNodeType(node->value);
			
			if (node->bindings.size() > 1) {
				bindingType = asA<TupleType>(bindingType)->types[i];
			}
			
			if (IsVoidType(bindingType)) LogError(binding, INVALID_VALUE);
		}
		
		if (node->types.size() > 0) {
			bindingType = node->types[i];
			if (IsVoidType(bindingType)) LogError(binding, INVALID_VALUE);
		}
		
		if (isA<ReferenceType>(bindingType)) {
			LogError(binding, ERROR_UNIMPLEMENTED);
		}

		mContext->SetNodeType(binding, bindingType);
	}
	
	Type* varDeclType = mContext->GetNodeType(node->bindings.front());
	
	if (node->bindings.size() > 1) {
		varDeclType = new TupleType(GetTypes(node->bindings));
	}
	
	mContext->SetNodeType(node, varDeclType);
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
	
	auto maxType = GetHighestType(GetTypes(yieldStatements));
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
	
	if (AreTypesCompatible(tyLHS, tyRHS)) {
		mContext->SetNodeType(node, GetImplicitType(tyLHS, tyRHS));
	} else {
		LogError(node, INCOMPATIBLE_TYPES);
		return;
	}

	if (IsAssignBinOp(node->op)) {
		mContext->SetNodeType(node, tyLHS);
		
		auto lval = IsLValue(node->LHS, mContext->GetNodeType(node->LHS));
		if (!lval) {
			LogError(node, INVALID_VALUE);
			return;
		}
	}

	if (IsCompareBinOp(node->op)) {
		mContext->SetNodeType(node, new BuiltinType(BuiltinTypeKind::BOOL));
	}
	
	if (IsLogicalBinOp(node->op) && (!IsBooleanType(tyLHS) || !IsBooleanType(tyRHS))) {
		LogError(node, INVALID_TYPE);
	}
}

void ResolveVisitor::VisitUnaryExpr(UnaryExpr* node) {
	// By default, inherit the type from the expression
	mContext->SetNodeType(node, mContext->GetNodeType(node->LHS));
	
	// If INCREMENT, DECREMENT or REFERENCE, LHS must be an lvalue
	if ((node->op == INCREMENT || node->op == DECREMENT || node->op == REFERENCE)) {
		auto lval = IsLValue(node->LHS, mContext->GetNodeType(node->LHS));
		
		if (!lval) {
			LogError(node, INVALID_VALUE);
			return;
		}
		
		if (node->op == REFERENCE) {
			mContext->SetNodeType(node, new PointerType(mContext->GetNodeType(node->LHS)));
		}
	}
	
	// If NOT, LHS must be a boolean
	if (node->op == NOT && !IsBooleanType(mContext->GetNodeType(node->LHS))) {
		LogError(node, INVALID_VALUE);
		return;
	}
	
	// If TIMES, LHS must be a pointer
	if (node->op == UnaryOp::TIMES) {
		if (!isA<PointerType>(mContext->GetNodeType(node->LHS))) {
			LogError(node, INVALID_VALUE);
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
	if (node->condition && !IsBooleanType(mContext->GetNodeType(node->condition))) {
		LogError(node, INVALID_TYPE);
		return;
	}

	mContext->SetNodeType(node, mContext->GetNodeType(node->block));
}

void ResolveVisitor::VisitIfExpr(IfExpr* node) {
	Type* highestType = mContext->GetNodeType(node->blocks.front());
	
	if (node->blocks.front()->condition == nullptr) {
		LogError(node, INVALID_PRECEDING_ELSE);
		return;
	}
	
	bool sawElse = false;
	
	for (auto ifExpr : node->blocks) {
		if (sawElse) LogError(node, ELIF_AFTER_ELSE);
		
		auto ifType = mContext->GetNodeType(ifExpr->block);
		
		if ((highestType == nullptr || ifType == nullptr) && (highestType != nullptr || ifType != nullptr)) {
			LogError(node, MISSING_YIELD);
			return;
		}
		
		if (!AreTypesCompatible(highestType, ifType)) {
			LogError(node, INVALID_TYPE);
		}
		
		highestType = GetImplicitType(highestType, ifType);
		
		sawElse = sawElse || (ifExpr->condition == nullptr);
	}
	
	if (highestType == nullptr) highestType = new VoidType();
	
	if (mContext->GetNodeType(node) == nullptr)
		mContext->SetNodeType(node, highestType);
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
	
	auto retStatements = mTypeTable->GetSearcher()->FindFunctionStatements<ReturnStmt>(node);
	
	if (retStatements.size() == 0) {
		if (retType != nullptr && IsVoidType(retType) == false) {
			LogError(node, MISSING_RETURN);
		} else {
			mContext->SetNodeType(node, new FunctionType(std::vector<Type*>(), new VoidType));
		}
		
		return;
	}
	
	bool typeError = false;
	
	if (retType != nullptr) {
		typeError = !ExpectCompatible(GetTypes(retStatements), retType);
	} else {
		retType = GetHighestType(GetTypes(retStatements));
	}
	
	typeError = typeError || (retType == nullptr);
	
	if (typeError) {
		LogError(node, INVALID_TYPE);
		return;
	}
	
	auto paramTys = GetTypes(node->params);
	mContext->SetNodeType(node, new FunctionType(paramTys, retType));
}

void ResolveVisitor::VisitCatchBlock(CatchBlock* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitTryExpr(TryExpr* node) {
	throw AnalysisMessage(MessageSeverity::FATAL, ERROR_UNIMPLEMENTED, node->id, mContext);
}

void ResolveVisitor::VisitCastExpr(CastExpr* node) {
	if (IsVoidType(mContext->GetNodeType(node->expr)) || IsVoidType(node->targetType)) {
		LogError(node, INVALID_TYPE);
		return;
	}
	
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



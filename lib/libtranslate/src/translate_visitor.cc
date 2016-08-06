//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <llvm/IR/IRBuilder.h>
#include <libast/typecheck.h>
#include <libast/binop.h>

#include "translate_visitor.h"
#include "type_converter.h"
#include "llvm_helpers.h"

using namespace orange::translate;
using namespace orange::analysis;
using namespace llvm;

llvm::Value* TranslateVisitor::GetValue(Node* node, bool disableLoading) {
	auto it = mValues.find(node->id);
	if (it == mValues.end()) return nullptr;
	auto v = it->second.val;

	if (!disableLoading && it->second.reference) {
		v = mBuilder->CreateLoad(v);
	}

	return v;
}

void TranslateVisitor::SetValue(Node* node, ValueInfo vi) {
	mValues[node->id] = vi;
}

void TranslateVisitor::VisitLoopStmt(LoopStmt* node) {
	throw std::runtime_error("Don't know how to handle LoopStmt");
}

void TranslateVisitor::VisitBreakStmt(BreakStmt* node) {
	throw std::runtime_error("Don't know how to handle BreakStmt");
}

void TranslateVisitor::VisitContinueStmt(ContinueStmt* node) {
	throw std::runtime_error("Don't know how to handle ContinueStmt");
}

void TranslateVisitor::VisitReturnStmt(ReturnStmt* node) {
	if (mCurrentBlock == nullptr) return;

	llvm::Value* retValue = nullptr;

	if (node->value != nullptr) {
		mWalker.WalkExpr(this, node->value);
		retValue = GetValue(node->value);
	}

	auto val = mBuilder->CreateRet(retValue);
	SetValue(node, val);
}

void TranslateVisitor::VisitExternFuncStmt(ExternFuncStmt* node) {
	throw std::runtime_error("Don't know how to handle ExternFuncStmt");
}

void TranslateVisitor::VisitClassStmt(ClassStmt* node) {
	throw std::runtime_error("Don't know how to handle ClassStmt");
}

void TranslateVisitor::VisitInterfaceStmt(InterfaceStmt* node) {
	throw std::runtime_error("Don't know how to handle InterfaceStmt");
}

void TranslateVisitor::VisitThrowStmt(ThrowStmt* node) {
	throw std::runtime_error("Don't know how to handle ThrowStmt");
}

void TranslateVisitor::VisitDeleteStmt(DeleteStmt* node) {
	throw std::runtime_error("Don't know how to handle DeleteStmt");
}

void TranslateVisitor::VisitExprStmt(ExprStmt* node) {
	throw std::runtime_error("Don't know how to handle ExprStmt");
}

void TranslateVisitor::VisitVarDeclExpr(VarDeclExpr* node) {
	auto ty = mCurrentContext->GetNodeType(node);
	auto llvmTy = GetLLVMType(ty);

	auto var = mBuilder->CreateAlloca(llvmTy, nullptr, node->name);

	if (node->value != nullptr) {
		mWalker.WalkExpr(this, node->value);
		auto val = GetValue(node->value);

		if (val->getType() != llvmTy) {
			throw std::runtime_error("Don't know how to do implicit cast to variable type");
		}

		mBuilder->CreateStore(val, var);
	}

	SetValue(node, ValueInfo(var, true));
}


void TranslateVisitor::VisitBoolValue(BoolValue* node) {
	auto orangeTy = mCurrentContext->GetNodeType(node);
	auto llvmTy = GetLLVMType(orangeTy);
	auto llvmVal = llvm::APInt(1, (int)node->value, IsSignedType(orangeTy));
	auto val = llvm::Constant::getIntegerValue(llvmTy, llvmVal);
	SetValue(node, val);
}

void TranslateVisitor::VisitIntValue(IntValue* node) {
	auto orangeTy = mCurrentContext->GetNodeType(node);
	auto llvmTy = GetLLVMType(orangeTy);
	auto llvmVal = llvm::APInt(GetIntegerBitWidth(orangeTy), node->value, IsSignedType(orangeTy));
	auto val = llvm::Constant::getIntegerValue(llvmTy, llvmVal);
	SetValue(node, val);
}

void TranslateVisitor::VisitUIntValue(UIntValue* node) {
	auto orangeTy = mCurrentContext->GetNodeType(node);
	auto llvmTy = GetLLVMType(orangeTy);
	auto llvmVal = llvm::APInt(GetIntegerBitWidth(orangeTy), node->value, IsSignedType(orangeTy));
	auto val = llvm::Constant::getIntegerValue(llvmTy, llvmVal);
	SetValue(node, val);
}

void TranslateVisitor::VisitFloatValue(FloatValue* node) {
	auto llvmVal = llvm::APFloat(node->value);
	auto val = llvm::ConstantFP::get(llvm::getGlobalContext(), llvmVal);
	SetValue(node, val);
}

void TranslateVisitor::VisitDoubleValue(DoubleValue* node) {
	auto llvmVal = llvm::APFloat(node->value);
	auto val = llvm::ConstantFP::get(llvm::getGlobalContext(), llvmVal);
	SetValue(node, val);
}

void TranslateVisitor::VisitStringValue(StringValue* node) {
	throw std::runtime_error("Don't know how to handle StringValue");
}

void TranslateVisitor::VisitCharValue(CharValue* node) {
	throw std::runtime_error("Don't know how to handle CharValue");
}

void TranslateVisitor::VisitThisID(ThisID* node) {
	throw std::runtime_error("Don't know how to handle ThisID");
}

void TranslateVisitor::VisitReferenceIDExpr(ReferenceIDExpr* node) {
	auto original = mSearcher.FindNode(node, node, true);

	if (original == nullptr) {
		throw std::runtime_error("Unknown reference to identifier");
	}

	if (isA<VarDeclExpr>(original) == false) {
		throw std::runtime_error("Don't know how to handle non-variable identifier");
	}

	if (isA<VarDeclExpr>(original)) {
		auto varDecl = asA<VarDeclExpr>(original);
		auto value = GetValue(varDecl, true);
		SetValue(node, ValueInfo(value, true));
	}
}

void TranslateVisitor::VisitNamedIDExpr(NamedIDExpr* node) {
	throw std::runtime_error("Don't know how to handle NamedIDExpr");
}

void TranslateVisitor::VisitDtorIDExpr(DtorIDExpr* node) {
	throw std::runtime_error("Don't know how to handle DtorIDExpr");
}

void TranslateVisitor::VisitAccessIDExpr(AccessIDExpr* node) {
	throw std::runtime_error("Don't know how to handle AccessIDExpr");
}

void TranslateVisitor::VisitLongBlockExpr(LongBlockExpr* node) {
	for (auto stmt : node->statements) mWalker.WalkNode(this, stmt);
}

void TranslateVisitor::VisitShortBlockExpr(ShortBlockExpr* node) {
	throw std::runtime_error("Don't know how to handle ShortBlockExpr");
}

llvm::Value* TranslateVisitor::HandleArithBinOp(BinOpExpr* node, BinOp op) {
	auto nodeTy      = mCurrentContext->GetNodeType(node);
	auto targetLHSTy = mCurrentContext->GetNodeType(node->LHS);
	auto targetRHSTy = mCurrentContext->GetNodeType(node->RHS);

	auto vLHS = GetValue(node->LHS);
	auto vRHS = GetValue(node->RHS);

	if (vLHS->getType() != GetLLVMType(targetLHSTy)) {
		throw std::runtime_error("Don't know how to do implicit cast");
	}

	if (vRHS->getType() != GetLLVMType(targetRHSTy)) {
		throw std::runtime_error("Don't know how to do implicit cast");
	}

	Instruction::BinaryOps llvmOp = GetLLVMBinOp(op, IsFloatingPointType(nodeTy), IsSignedType(nodeTy));
	if (llvmOp == Instruction::BinaryOps::BinaryOpsEnd)
		throw std::runtime_error("Unknown binary operator to convert to LLVM operation");

	return mBuilder->CreateBinOp(llvmOp, vLHS, vRHS);
}


llvm::Value* TranslateVisitor::HandleAssignBinOp(BinOpExpr* node, BinOp op) {
	auto nodeTy = mCurrentContext->GetNodeType(node);

	auto vPtr = GetValue(node->LHS, true);

	llvm::Value* vRHS = nullptr;

	if (IsArithAssignBinOp(op)) {
		// Do a binary operation between LHS and RHS.
		vRHS = HandleArithBinOp(node, GetArithBinOp(op));
	} else {
		// Just assign RHS
		vRHS = GetValue(node->RHS);
	}

	if (vRHS->getType() != GetLLVMType(nodeTy)) {
		throw std::runtime_error("Don't know how to do implicit cast");
	}

	mBuilder->CreateStore(vRHS, vPtr);

	return vRHS;
}


llvm::Value* TranslateVisitor::HandleCompareBinOp(BinOpExpr* node, BinOp op) {
	auto nodeTy      = mCurrentContext->GetNodeType(node);
	auto targetLHSTy = mCurrentContext->GetNodeType(node->LHS);
	auto targetRHSTy = mCurrentContext->GetNodeType(node->RHS);

	auto vLHS = GetValue(node->LHS);
	auto vRHS = GetValue(node->RHS);

	if (vLHS->getType() != GetLLVMType(targetLHSTy)) {
		throw std::runtime_error("Don't know how to do implicit cast");
	}

	if (vRHS->getType() != GetLLVMType(targetRHSTy)) {
		throw std::runtime_error("Don't know how to do implicit cast");
	}

	bool fp = vLHS->getType()->isFloatingPointTy();

	CmpInst::Predicate llvmOp = GetLLVMCompareOp(op, fp, IsSignedType(targetLHSTy));

	if (fp) {
		return mBuilder->CreateFCmp(llvmOp, vLHS, vRHS);
	} else {
		return mBuilder->CreateICmp(llvmOp, vLHS, vRHS);
	}
}

void TranslateVisitor::VisitBinOpExpr(BinOpExpr* node) {
	mWalker.WalkExpr(this, node->LHS);
	mWalker.WalkExpr(this, node->RHS);

	if (IsArithBinOp(node->op)) {
		SetValue(node, HandleArithBinOp(node, node->op));
	} else if (IsAssignBinOp(node->op)) {
		HandleAssignBinOp(node, node->op);
		SetValue(node, GetValue(node->LHS, true));
	} else if (IsCompareBinOp(node->op)) {
		SetValue(node, HandleCompareBinOp(node, node->op));
	} else {
		throw std::runtime_error("Don't know how to handle binary operator");
	}
}

void TranslateVisitor::VisitUnaryExpr(UnaryExpr* node) {
	throw std::runtime_error("Don't know how to handle UnaryExpr");
}

void TranslateVisitor::VisitArrayExpr(ArrayExpr* node) {
	throw std::runtime_error("Don't know how to handle ArrayExpr");
}

void TranslateVisitor::VisitArrayAccessExpr(ArrayAccessExpr* node) {
	throw std::runtime_error("Don't know how to handle ArrayAccessExpr");
}

void TranslateVisitor::VisitMemberAccessExpr(MemberAccessExpr* node) {
	throw std::runtime_error("Don't know how to handle MemberAccessExpr");
}

void TranslateVisitor::VisitConditionalBlock(ConditionalBlock* node) {
	throw std::runtime_error("Don't know how to handle ConditionalBlock");
}

void TranslateVisitor::VisitIfExpr(IfExpr* node) {
	throw std::runtime_error("Don't know how to handle IfExpr");
}

void TranslateVisitor::VisitTernaryExpr(TernaryExpr* node) {
	throw std::runtime_error("Don't know how to handle TernaryExpr");
}

void TranslateVisitor::VisitFunctionExpr(FunctionExpr* node) {
	throw std::runtime_error("Don't know how to handle FunctionExpr");
}

void TranslateVisitor::VisitCatchBlock(CatchBlock* node) {
	throw std::runtime_error("Don't know how to handle CatchBlock");
}

void TranslateVisitor::VisitTryExpr(TryExpr* node) {
	throw std::runtime_error("Don't know how to handle TryExpr");
}

void TranslateVisitor::VisitCastExpr(CastExpr* node) {
	throw std::runtime_error("Don't know how to handle CastExpr");
}

void TranslateVisitor::VisitFunctionCallExpr(FunctionCallExpr* node) {
	throw std::runtime_error("Don't know how to handle FunctionCallExpr");
}

void TranslateVisitor::VisitNewExpr(NewExpr* node) {
	throw std::runtime_error("Don't know how to handle NewExpr");
}

void TranslateVisitor::SetCurrentBlock(llvm::BasicBlock* currentBlock) {
	mCurrentBlock = currentBlock;
	mBuilder->SetInsertPoint(mCurrentBlock);
}

void TranslateVisitor::SetCurrentContext(orange::analysis::NodeTypeContext* ctx) {
	mCurrentContext = ctx;
}

TranslateVisitor::TranslateVisitor(Walker& walker, std::shared_ptr<llvm::Module> mod, ASTSearcher& searcher) :
	mWalker(walker), mModule(mod), mSearcher(searcher) {
	mBuilder = std::make_shared<LLVMIRBuilder>(llvm::getGlobalContext());
}

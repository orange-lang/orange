//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include "llvm_helpers.h"

using namespace orange::ast;
using namespace llvm;

llvm::Instruction::BinaryOps orange::translate::GetLLVMBinOp(orange::ast::BinOp binop, bool fp, bool isSigned) {
	if (binop == BinOp::ADD) return fp ? Instruction::BinaryOps::FAdd : Instruction::BinaryOps::Add;
	if (binop == BinOp::SUBTRACT) return fp ? Instruction::BinaryOps::FSub : Instruction::BinaryOps::Sub;
	if (binop == BinOp::DIVIDE) {
		if (fp) return Instruction::BinaryOps::FDiv;
		return isSigned ? Instruction::BinaryOps::SDiv : Instruction::BinaryOps::UDiv;
	}
	if (binop == BinOp::MULTIPLY) return fp ? Instruction::BinaryOps::FMul : Instruction::BinaryOps::Mul;
	if (binop == BinOp::REMAINDER) {
		if (fp) return Instruction::BinaryOps::FRem;
		return isSigned ? Instruction::BinaryOps::SRem : Instruction::BinaryOps::URem;
	}
	if (binop == BinOp::BIT_OR) return Instruction::BinaryOps::Or;
	if (binop == BinOp::BIT_AND) return Instruction::BinaryOps::And;
	if (binop == BinOp::BIT_XOR) return Instruction::BinaryOps::Xor;
	if (binop == BinOp::SHIFT_LEFT) return Instruction::BinaryOps::Shl;
	if (binop == BinOp::SHIFT_RIGHT) return Instruction::BinaryOps::LShr;

	return Instruction::BinaryOps::BinaryOpsEnd;
}

bool orange::translate::IsLLVMBinOp(orange::ast::BinOp binop) {
	return binop == BinOp::ADD || binop == BinOp::SUBTRACT || binop == BinOp::DIVIDE ||
	       binop == BinOp::MULTIPLY || binop == BinOp::REMAINDER || binop == BinOp::BIT_OR ||
	       binop == BinOp::BIT_AND || binop == BinOp::BIT_XOR || binop == BinOp::SHIFT_LEFT ||
	       binop == BinOp::SHIFT_RIGHT;
}

bool orange::translate::IsLLVMAssignOp(orange::ast::BinOp binop) {
	return binop == BinOp::ASSIGN || binop == BinOp::PLUS_ASSIGN || binop == BinOp::MINUS_ASSIGN ||
	       binop == BinOp::TIMES_ASSIGN || binop == BinOp::DIVIDE_ASSIGN || binop == BinOp::REMAINDER_ASSIGN ||
	       binop == BinOp::SHIFT_LEFT_ASSIGN || binop == BinOp::SHIFT_RIGHT_ASSIGN || binop == BinOp::BIT_OR_ASSIGN ||
	       binop == BinOp::BIT_AND_ASSIGN || binop == BinOp::BIT_XOR_ASSIGN;
}

bool orange::translate::IsLLVMCompareOp(orange::ast::BinOp binop) {
	return binop == BinOp::EQUALS || binop == BinOp::LESS_THAN || binop == BinOp::GREATER_THAN ||
	       binop == BinOp::LEQ || binop == BinOp::GEQ || binop == BinOp::NEQ;
}

bool orange::translate::IsLLVMLogicalOp(orange::ast::BinOp binop) {
	return binop == BinOp::AND || binop == BinOp::OR;
}

//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/binop.h>

using namespace orange::ast;

bool orange::ast::IsArithBinOp(BinOp binop) {
	return binop == BinOp::ADD || binop == BinOp::SUBTRACT || binop == BinOp::DIVIDE ||
	       binop == BinOp::MULTIPLY || binop == BinOp::REMAINDER || binop == BinOp::BIT_OR ||
	       binop == BinOp::BIT_AND || binop == BinOp::BIT_XOR || binop == BinOp::SHIFT_LEFT ||
	       binop == BinOp::SHIFT_RIGHT;
}

bool orange::ast::IsAssignBinOp(BinOp binop) {
	return binop == BinOp::ASSIGN || binop == BinOp::PLUS_ASSIGN || binop == BinOp::MINUS_ASSIGN ||
	       binop == BinOp::TIMES_ASSIGN || binop == BinOp::DIVIDE_ASSIGN || binop == BinOp::REMAINDER_ASSIGN ||
	       binop == BinOp::SHIFT_LEFT_ASSIGN || binop == BinOp::SHIFT_RIGHT_ASSIGN || binop == BinOp::BIT_OR_ASSIGN ||
	       binop == BinOp::BIT_AND_ASSIGN || binop == BinOp::BIT_XOR_ASSIGN;
}

bool orange::ast::IsCompareBinOp(BinOp binop) {
	return binop == BinOp::EQUALS || binop == BinOp::LESS_THAN || binop == BinOp::GREATER_THAN ||
	       binop == BinOp::LEQ || binop == BinOp::GEQ || binop == BinOp::NEQ;
}

bool orange::ast::IsLogicalBinOp(BinOp binop) {
	return binop == BinOp::AND || binop == BinOp::OR;
}


bool orange::ast::IsArithAssignBinOp(BinOp binop) {
	// Is it anything _but_ the basic assign
	return IsAssignBinOp(binop) && binop != BinOp::ASSIGN;
}

BinOp orange::ast::GetArithBinOp(BinOp binop){
	if (IsArithBinOp(binop)) return binop;

	if (binop == BinOp::PLUS_ASSIGN) return BinOp::ADD;
	if (binop == BinOp::MINUS_ASSIGN) return BinOp::SUBTRACT;
	if (binop == BinOp::TIMES_ASSIGN) return BinOp::MULTIPLY;
	if (binop == BinOp::DIVIDE_ASSIGN) return BinOp::DIVIDE;
	if (binop == BinOp::REMAINDER_ASSIGN) return BinOp::REMAINDER;
	if (binop == BinOp::SHIFT_LEFT_ASSIGN) return BinOp::SHIFT_LEFT;
	if (binop == BinOp::SHIFT_RIGHT_ASSIGN) return BinOp::SHIFT_RIGHT;
	if (binop == BinOp::BIT_OR_ASSIGN) return BinOp::BIT_OR;
	if (binop == BinOp::BIT_AND_ASSIGN) return BinOp::BIT_AND;
	if (binop == BinOp::BIT_XOR_ASSIGN) return BinOp::BIT_XOR;

	throw std::runtime_error("Binary operator does not do any arithmetic");
}


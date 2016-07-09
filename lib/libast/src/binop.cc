//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/binop.h>

bool orange::ast::IsArithBinOp(orange::ast::BinOp binop) {
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
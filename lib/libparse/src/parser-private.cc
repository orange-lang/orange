//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>

#include <libparse/parser.h>
#include <libast/type.h>
#include <libast/flag.h>
#include <libast/typecheck.h>
#include "lex_stream.h"
#include "lex_helpers.h"
#include "parser-private.h"

using namespace orange::ast;
using namespace orange::parser;
using namespace orange::parser::impl;

int impl::GetOperatorPrecedence(TokenType tok) {
	const static std::map<TokenType, int> OperatorPrecedence = {
		{TokenType::TIMES, 12}, {TokenType::DIVIDE, 12}, {TokenType::REMAINDER, 12},
		{TokenType::PLUS, 11}, {TokenType::MINUS, 11},
		{TokenType::SHIFT_LEFT, 10}, {TokenType::SHIFT_RIGHT, 10},
		{TokenType::LESS_THAN, 9}, {TokenType::GREATER_THAN, 9},
		{TokenType::LEQ, 8}, {TokenType::GEQ, 8},
		{TokenType::EQUALS, 7}, {TokenType::NEQ, 7},
		{TokenType::BIT_AND, 6},
		{TokenType::BIT_XOR, 5},
		{TokenType::BIT_OR, 4},
		{TokenType::AND, 3},
		{TokenType::OR, 2},
		{TokenType::QUESTION, 1}, {TokenType::ASSIGN, 1},
		{TokenType::PLUS_ASSIGN, 1}, {TokenType::MINUS_ASSIGN, 1},
		{TokenType::TIMES_ASSIGN, 1}, {TokenType::DIVIDE_ASSIGN, 1},
		{TokenType::REMAINDER_ASSIGN, 1}, {TokenType::SHIFT_LEFT_ASSIGN, 1},
		{TokenType::SHIFT_RIGHT_ASSIGN, 1}, {TokenType::BIT_OR_ASSIGN, 1},
		{TokenType::BIT_AND_ASSIGN, 1}, {TokenType::BIT_XOR_ASSIGN, 1}
	};

	auto it = OperatorPrecedence.find(tok);
	if (it == OperatorPrecedence.end()) return -1;
	return it->second;
}

OperatorAssociativity impl::GetAssociativity(TokenType tok) {
	auto prec = GetOperatorPrecedence(tok);

	if (prec == 13) return OperatorAssociativity::RIGHT;
	else return OperatorAssociativity::LEFT;
}

UnaryOp impl::GetUnaryOp(TokenType ty) {
	switch (ty) {
		case TokenType::INCREMENT: return UnaryOp::INCREMENT;
		case TokenType::DECREMENT: return UnaryOp::DECREMENT;
		case TokenType::MINUS:     return UnaryOp::MINUS;
		case TokenType::NOT:       return UnaryOp::NOT;
		case TokenType::TILDE:     return UnaryOp::TILDE;
		case TokenType::TIMES:     return UnaryOp::TIMES;
		case TokenType::BIT_AND:   return UnaryOp::REFERENCE;
		default:
			throw std::runtime_error("Not a valid unary operator token");
	}
}

BinOp impl::GetBinOp(TokenType ty) {
	switch (ty) {
		case TokenType::PLUS:               return BinOp::ADD;
		case TokenType::MINUS:              return BinOp::SUBTRACT;
		case TokenType::DIVIDE:             return BinOp::DIVIDE;
		case TokenType::TIMES:              return BinOp::MULTIPLY;
		case TokenType::REMAINDER:          return BinOp::REMAINDER;
		case TokenType::BIT_OR:             return BinOp::BIT_OR;
		case TokenType::BIT_AND:            return BinOp::BIT_AND;
		case TokenType::BIT_XOR:            return BinOp::BIT_XOR;
		case TokenType::SHIFT_LEFT:         return BinOp::SHIFT_LEFT;
		case TokenType::SHIFT_RIGHT:        return BinOp::SHIFT_RIGHT;
		case TokenType::ASSIGN:             return BinOp::ASSIGN;
		case TokenType::EQUALS:             return BinOp::EQUALS;
		case TokenType::PLUS_ASSIGN:        return BinOp::PLUS_ASSIGN;
		case TokenType::MINUS_ASSIGN:       return BinOp::MINUS_ASSIGN;
		case TokenType::TIMES_ASSIGN:       return BinOp::TIMES_ASSIGN;
		case TokenType::DIVIDE_ASSIGN:      return BinOp::DIVIDE_ASSIGN;
		case TokenType::REMAINDER_ASSIGN:   return BinOp::REMAINDER_ASSIGN;
		case TokenType::SHIFT_LEFT_ASSIGN:  return BinOp::SHIFT_LEFT_ASSIGN;
		case TokenType::SHIFT_RIGHT_ASSIGN: return BinOp::SHIFT_RIGHT_ASSIGN;
		case TokenType::BIT_OR_ASSIGN:      return BinOp::BIT_OR_ASSIGN;
		case TokenType::BIT_AND_ASSIGN:     return BinOp::BIT_AND_ASSIGN;
		case TokenType::BIT_XOR_ASSIGN:     return BinOp::BIT_XOR_ASSIGN;
		case TokenType::LESS_THAN:          return BinOp::LESS_THAN;
		case TokenType::GREATER_THAN:       return BinOp::GREATER_THAN;
		case TokenType::LEQ:                return BinOp::LEQ;
		case TokenType::GEQ:                return BinOp::GEQ;
		case TokenType::NEQ:                return BinOp::NEQ;
		case TokenType::AND:                return BinOp::AND;
		case TokenType::OR:                 return BinOp::OR;
		default:
			throw std::runtime_error("Not a valid binary operator token");
	}
}



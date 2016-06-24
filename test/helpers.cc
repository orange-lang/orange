//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <iostream>
#include <map>
#include "helpers.h"

namespace orange { namespace parser {
	static std::map<orange::parser::TokenType, std::string> TokenTyNames = {
		{COMMENT, "COMMENT"}, {FLOAT, "FLOAT"}, {STRING, "STRING"},
		{NEWLINE, "NEWLINE"}, {SEMICOLON, "SEMICOLON"}, {INT, "INT"}, {UINT, "UINT"},
		{INT8, "INT8"}, {INT16, "INT16"}, {INT32, "INT32"}, {INT64, "INT64"},
		{UINT8, "UINT8"}, {UINT16, "UINT16"}, {UINT32, "UINT32"}, {UINT64, "UINT64"},
		{DOUBLE, "DOUBLE"}, {VAR, "VAR"}, {VOID, "VOID"}, {IDENTIFIER, "IDENTIFIER"},
		{TEMP, "TEMP"}, {OPERATOR, "OPERATOR"}, {OPEN_PAREN, "OPEN_PAREN"},
		{CLOSE_PAREN, "CLOSE_PAREN"}, {PLUS, "PLUS"}, {MINUS, "MINUS"},
		{DIVIDE, "DIVIDE"}, {TIMES, "TIMES"}, {REMAINDER, "REMAINDER"},
		{BIT_OR, "BIT_OR"}, {BIT_AND, "BIT_AND"}, {BIT_XOR, "BIT_XOR"},
		{QUESTION, "QUESTION"}, {SHIFT_LEFT, "SHIFT_LEFT"},
		{SHIFT_RIGHT, "SHIFT_RIGHT"}, {ASSIGN, "ASSIGN"}, {EQUALS, "EQUALS"},
		{PLUS_ASSIGN, "PLUS_ASSIGN"}, {MINUS_ASSIGN, "MINUS_ASSIGN"},
		{TIMES_ASSIGN, "TIMES_ASSIGN"}, {DIVIDE_ASSIGN, "DIVIDE_ASSIGN"},
		{REMAINDER_ASSIGN, "REMAINDER_ASSIGN"},
		{SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN"},
		{SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN"}, {BIT_OR_ASSIGN, "BIT_OR_ASSIGN"},
		{BIT_AND_ASSIGN, "BIT_AND_ASSIGN"}, {BIT_XOR_ASSIGN, "BIT_XOR_ASSIGN"},
		{LESS_THAN, "LESS_THAN"}, {GREATER_THAN, "GREATER_THAN"}, {LEQ, "LEQ"},
		{GEQ, "GEQ"}, {NEQ, "NEQ"}, {AND, "AND"}, {OR, "OR"},
		{INCREMENT, "INCREMENT"}, {DECREMENT, "DECREMENT"}, {ENUM, "ENUM"},
		{OPEN_CURLY, "OPEN_CURLY"}, {CLOSE_CURLY, "CLOSE_CURLY"}, {COMMA, "COMMA"},
		{DOT, "DOT"}, {CLASS, "CLASS"}, {PARTIAL, "PARTIAL"},
		{OPEN_BRACKET, "OPEN_BRACKET"}, {CLOSE_BRACKET, "CLOSE_BRACKET"},
		{EXLUSIVE_RANGE, "EXLUSIVE_RANGE"}, {INCLUSIVE_RANGE, "INCLUSIVE_RANGE"},
		{COLON, "COLON"}, {IN, "IN"}, {IF, "IF"}, {ELIF, "ELIF"}, {ELSE, "ELSE"},
		{FOR, "FOR"}, {FOREACH, "FOREACH"}, {WHILE, "WHILE"}, {FOREVER, "FOREVER"},
		{DO, "DO"}, {SWITCH, "SWITCH"}, {BREAK, "BREAK"}, {CONTINUE, "CONTINUE"},
		{YIELD, "YIELD"}, {DEF, "DEF"}, {ARROW, "ARROW"}, {EXTERN, "EXTERN"},
		{AGGREGATE, "AGGREGATE"}, {INTERFACE, "INTERFACE"}, {TILDE, "TILDE"},
		{NAMESPACE, "NAMESPACE"}, {IMPORT, "IMPORT"}, {NEW, "NEW"},
		{DELETE, "DELETE"}, {PRIVATE, "PRIVATE"}, {PROTECTED, "PROTECTED"},
		{PUBLIC, "PUBLIC"}, {GET, "GET"}, {SET, "SET"}, {VIRTUAL, "VIRTUAL"},
		{FINAL, "FINAL"}, {WHERE, "WHERE"}, {DATA, "DATA"}, {EXTEND, "EXTEND"},
		{NOT, "NOT"}, {CONST, "CONST"}, {TRY, "TRY"}, {CATCH, "CATCH"},
		{FINALLY, "FINALLY"}, {THROW, "THROW"}, {OF, "OF"},
	};

	std::ostream& operator<<(std::ostream& os, const TokenType& tok) {
		auto it = TokenTyNames.find(tok);
		if (it == TokenTyNames.end()) return os << tok;
		return os << it->second;
	}
}}

using namespace orange::parser;

template <>
bool tokensEq(Token* tok, Token to) { return tok != nullptr && tok->type == to.type && tok->value == to.value; }

template <>
bool tokensEq(Token* tok, TokenType ty) { return tok != nullptr && tok->type == ty; }

template <>
bool tokensEq(Token* tok, std::string val) { return tok != nullptr && tok->value == val; }

template <>
bool tokensEq(Token* tok, const char* val) { return tok != nullptr && tok->value == val; }


template <>
void expectToken(Lexer& l, Token val) {
	auto tok = l.readToken();
	EXPECT_TRUE(tok != nullptr);
	EXPECT_EQ(tok->type, val.type);
	EXPECT_EQ(tok->value, val.value);
}

template <>
void expectToken(Lexer& l, TokenType val) {
	auto tok = l.readToken();
	EXPECT_TRUE(tok != nullptr);
	EXPECT_EQ(tok->type, val);
}

template <>
void expectToken(Lexer& l, std::string val) {
	auto tok = l.readToken();
	EXPECT_TRUE(tok != nullptr);
	EXPECT_EQ(tok->value, val);
}

template <>
void expectToken(Lexer& l, const char* val) {
	auto tok = l.readToken();
	EXPECT_TRUE(tok != nullptr);
	EXPECT_EQ(tok->value, val);
}
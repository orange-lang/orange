//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <string>
#include <istream>

namespace orange { namespace parser {
	enum TokenType {
		VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64,
		VAL_FLOAT, VAL_DOUBLE, VAL_STRING, VAL_CHAR,

		COMMENT, FLOAT, STRING, NEWLINE, SEMICOLON, INT, UINT, INT8, INT16, INT32,
		INT64, UINT8, UINT16, UINT32, UINT64, DOUBLE, CHAR, VAR, VOID, IDENTIFIER, TEMP,
		OPERATOR, OPEN_PAREN, CLOSE_PAREN, PLUS, MINUS, DIVIDE, TIMES, REMAINDER,
		BIT_OR, BIT_AND, BIT_XOR, QUESTION, SHIFT_LEFT, SHIFT_RIGHT, ASSIGN, EQUALS,
		PLUS_ASSIGN, MINUS_ASSIGN, TIMES_ASSIGN, DIVIDE_ASSIGN, REMAINDER_ASSIGN,
		SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, BIT_OR_ASSIGN, BIT_AND_ASSIGN,
		BIT_XOR_ASSIGN, LESS_THAN, GREATER_THAN, LEQ, GEQ, NEQ, AND, OR, INCREMENT,
		DECREMENT, ENUM, OPEN_CURLY, CLOSE_CURLY, COMMA, DOT, CLASS, PARTIAL,
		OPEN_BRACKET, CLOSE_BRACKET, EXLUSIVE_RANGE, INCLUSIVE_RANGE, COLON, IN, IF,
		ELIF, ELSE, FOR, FOREACH, WHILE, FOREVER, DO, SWITCH, BREAK, CONTINUE, YIELD,
		DEF, ARROW, EXTERN, AGGREGATE, INTERFACE, TILDE, NAMESPACE, IMPORT, NEW,
		DELETE, PRIVATE, PROTECTED, PUBLIC, GET, SET, VIRTUAL, FINAL, WHERE, DATA,
		EXTEND, NOT, CONST, TRY, CATCH, FINALLY, THROW, OF, AS
	};

	class Token {
	public:
		TokenType type;
		std::string value;

		Token() { }
		Token(TokenType ty, std::string v) : type(ty), value(v) { }
	};

	class Lexer {
	private:
		std::istream& mStream;
	public:
		/// Reads the next token from the stream.
		/// Returns nullptr on EOF. Throws exception on error.
		Token* readToken();

		/// Returns whether or not we're at the end of the stream.
		bool eof() const;

		Lexer(std::istream& stream);
	};
}}

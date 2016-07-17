//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <string>
#include <map>
#include <istream>

namespace orange { namespace parser {
	enum TokenType {
		TOKEN_EOF, // EOF token

		VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64,
		VAL_FLOAT, VAL_DOUBLE, VAL_STRING, VAL_CHAR, VAL_BOOL,

		COMMENT, FLOAT, STRING, NEWLINE, SEMICOLON, INT, UINT, INT8, INT16, INT32,
		INT64, UINT8, UINT16, UINT32, UINT64, DOUBLE, CHAR, VAR, VOID, IDENTIFIER, TEMP,
		OPERATOR, OPEN_PAREN, CLOSE_PAREN, PLUS, MINUS, DIVIDE, TIMES, REMAINDER,
		BIT_OR, BIT_AND, BIT_XOR, QUESTION, SHIFT_LEFT, SHIFT_RIGHT, ASSIGN, EQUALS,
		PLUS_ASSIGN, MINUS_ASSIGN, TIMES_ASSIGN, DIVIDE_ASSIGN, REMAINDER_ASSIGN,
		SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, BIT_OR_ASSIGN, BIT_AND_ASSIGN,
		BIT_XOR_ASSIGN, LESS_THAN, GREATER_THAN, LEQ, GEQ, NEQ, AND, OR, INCREMENT,
		DECREMENT, ENUM, OPEN_CURLY, CLOSE_CURLY, COMMA, DOT, CLASS, PARTIAL,
		OPEN_BRACKET, CLOSE_BRACKET, EXCLUSIVE_RANGE, INCLUSIVE_RANGE, COLON, IN, IF,
		ELIF, ELSE, FOR, FOREACH, WHILE, FOREVER, DO, SWITCH, BREAK, CONTINUE, YIELD,
		DEF, ARROW, EXTERN, AGGREGATE, INTERFACE, TILDE, NAMESPACE, IMPORT, NEW,
		DELETE, PRIVATE, PROTECTED, PUBLIC, GET, SET, VIRTUAL, FINAL, WHERE, DATA,
		EXTEND, NOT, CONST, TRY, CATCH, FINALLY, THROW, OF, AS, PROPERTY, THIS, BOOL
	};

	static std::map<TokenType, std::string> TokenDescriptionMap = {
		{TOKEN_EOF, "EOF"}, {VAL_INT, "int value"}, {VAL_INT8, "int8 value"}, {VAL_INT16, "int16 value"},
		{VAL_INT32, "int32 value"}, {VAL_INT64, "int64 value"}, {VAL_UINT, "uint value"}, {VAL_UINT8, "uint8 value"},
		{VAL_UINT16, "uint16 value"}, {VAL_UINT32, "uint32 value"}, {VAL_UINT64, "uint64 value"}, {VAL_FLOAT, "float value"},
		{VAL_DOUBLE, "double value"}, {VAL_STRING, "string value"}, {VAL_CHAR, "char value"}, {VAL_BOOL, "bool value"},
		{COMMENT, "comment"}, {FLOAT, "float"}, {STRING, "string"}, {NEWLINE, "newline"},
		{SEMICOLON, ";"}, {INT, "int"}, {UINT, "uint"}, {INT8, "int8"},
		{INT16, "int16"}, {INT32, "int32"}, {INT64, "int64"}, {UINT8, "uint8"},
		{UINT16, "uint16"}, {UINT32, "uint32"}, {UINT64, "uint64"}, {DOUBLE, "double"},
		{CHAR, "char"}, {VAR, "var"}, {VOID, "void"}, {IDENTIFIER, "identifier"},
		{TEMP, "_"}, {OPERATOR, "operator"}, {OPEN_PAREN, "("}, {CLOSE_PAREN, ")"},
		{PLUS, "+"}, {MINUS, "-"}, {DIVIDE, "/"}, {TIMES, "*"},
		{REMAINDER, "%"}, {BIT_OR, "|"}, {BIT_AND, "&"}, {BIT_XOR, "^"},
		{QUESTION, "?"}, {SHIFT_LEFT, "<<"}, {SHIFT_RIGHT, ">>"}, {ASSIGN, "="},
		{EQUALS, "=="}, {PLUS_ASSIGN, "+="}, {MINUS_ASSIGN, "-="}, {TIMES_ASSIGN, "*="},
		{DIVIDE_ASSIGN, "/="}, {REMAINDER_ASSIGN, "%="}, {SHIFT_LEFT_ASSIGN, "<<="}, {SHIFT_RIGHT_ASSIGN, ">>="},
		{BIT_OR_ASSIGN, "|="}, {BIT_AND_ASSIGN, "&="}, {BIT_XOR_ASSIGN, "^="}, {LESS_THAN, "<"},
		{GREATER_THAN, ">"}, {LEQ, "<="}, {GEQ, ">="}, {NEQ, "!="},
		{AND, "&&"}, {OR, "||"}, {INCREMENT, "++"}, {DECREMENT, "--"},
		{ENUM, "enum"}, {OPEN_CURLY, "{"}, {CLOSE_CURLY, "}"}, {COMMA, ","},
		{DOT, "."}, {CLASS, "class"}, {PARTIAL, "partial"}, {OPEN_BRACKET, "["},
		{CLOSE_BRACKET, "]"}, {EXCLUSIVE_RANGE, "..."}, {INCLUSIVE_RANGE, ".."}, {COLON, ":"},
		{IN, "in"}, {IF, "if"}, {ELIF, "elif"}, {ELSE, "else"},
		{FOR, "for"}, {FOREACH, "foreach"}, {WHILE, "while"}, {FOREVER, "forever"},
		{DO, "do"}, {SWITCH, "switch"}, {BREAK, "break"}, {CONTINUE, "continue"},
		{YIELD, "yield"}, {DEF, "def"}, {ARROW, "->"}, {EXTERN, "extern"},
		{AGGREGATE, "aggregate"}, {INTERFACE, "interface"}, {TILDE, "~"}, {NAMESPACE, "namespace"},
		{IMPORT, "import"}, {NEW, "new"}, {DELETE, "delete"}, {PRIVATE, "private"},
		{PROTECTED, "protected"}, {PUBLIC, "public"}, {GET, "get"}, {SET, "set"},
		{VIRTUAL, "virtual"}, {FINAL, "final"}, {WHERE, "where"}, {DATA, "data"},
		{EXTEND, "extend"}, {NOT, "!"}, {CONST, "const"}, {TRY, "try"},
		{CATCH, "catch"}, {FINALLY, "finally"}, {THROW, "throw"}, {OF, "of"},
		{AS, "as"}, {PROPERTY, "property"}, {THIS, "this"}, {BOOL, "bool"}
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

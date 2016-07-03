//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>

#include <gtest/gtest.h>

#include "lex.h"
#include "helpers.h"

TEST(Lexer, AcceptsNoInput) {
	using namespace orange::parser;

	std::stringstream ss("");
	Lexer l(ss);

	EXPECT_TRUE(l.eof());
	expectToken(l, TOKEN_EOF);
}

TEST(Lexer, LexesComments) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "// This is a nice comment!\n";
	ss << "+";

	Lexer l(ss);

	std::vector<TokenType> expects = { COMMENT, PLUS };

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesBlockComment) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "-- /* This is a nice comment! */ ++";

	Lexer l(ss);

	std::vector<TokenType> expects = { DECREMENT, COMMENT, INCREMENT };

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesNestedBlockComment) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "-- /* This /* is */ a nice comment! */ ++";

	Lexer l(ss);

	std::vector<TokenType> expects = { DECREMENT, COMMENT, INCREMENT };

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, CatchesUnterminatedBlockComment) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "/* This /* is a nice comment! */";

	Lexer l(ss);

	EXPECT_THROW(l.readToken(), std::runtime_error);
}

TEST(Lexer, LexesOperators) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "; ( ) + - / * % | & ^ ? << >> = == += -= *= /= %= <<= ";
	ss << ">>= |= &= \n ^= < > <= >= != ! && || ++ -- { } , . [ ] ... .. ";
	ss << ": -> ~";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		SEMICOLON, OPEN_PAREN, CLOSE_PAREN, PLUS, MINUS, DIVIDE, TIMES,
		REMAINDER, BIT_OR, BIT_AND, BIT_XOR, QUESTION, SHIFT_LEFT, SHIFT_RIGHT,
		ASSIGN, EQUALS, PLUS_ASSIGN, MINUS_ASSIGN, TIMES_ASSIGN, DIVIDE_ASSIGN,
		REMAINDER_ASSIGN, SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, BIT_OR_ASSIGN,
		BIT_AND_ASSIGN, NEWLINE, BIT_XOR_ASSIGN, LESS_THAN, GREATER_THAN, LEQ,
		GEQ, NEQ, NOT, AND, OR, INCREMENT, DECREMENT, OPEN_CURLY, CLOSE_CURLY,
		COMMA, DOT, OPEN_BRACKET, CLOSE_BRACKET, EXCLUSIVE_RANGE, INCLUSIVE_RANGE,
		COLON, ARROW, TILDE
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesOperatorsNoSpaces) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << ";()+-/ *%|&^?<<>> = ==+=-=*=/=%=<<=";
	ss << ">>=|=&=\n^=<><=>=!=!&&||++--{},.[]... ..";
	ss << ":->~";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		SEMICOLON, OPEN_PAREN, CLOSE_PAREN, PLUS, MINUS, DIVIDE, TIMES,
		REMAINDER, BIT_OR, BIT_AND, BIT_XOR, QUESTION, SHIFT_LEFT, SHIFT_RIGHT,
		ASSIGN, EQUALS, PLUS_ASSIGN, MINUS_ASSIGN, TIMES_ASSIGN, DIVIDE_ASSIGN,
		REMAINDER_ASSIGN, SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, BIT_OR_ASSIGN,
		BIT_AND_ASSIGN, NEWLINE, BIT_XOR_ASSIGN, LESS_THAN, GREATER_THAN, LEQ,
		GEQ, NEQ, NOT, AND, OR, INCREMENT, DECREMENT, OPEN_CURLY, CLOSE_CURLY,
		COMMA, DOT, OPEN_BRACKET, CLOSE_BRACKET, EXCLUSIVE_RANGE, INCLUSIVE_RANGE,
		COLON, ARROW, TILDE
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, ClumpedOperators) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << ");+++/=/<<==....\n\n!";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		CLOSE_PAREN, SEMICOLON, INCREMENT, PLUS, DIVIDE_ASSIGN, DIVIDE,
		SHIFT_LEFT_ASSIGN, ASSIGN, EXCLUSIVE_RANGE, DOT, NEWLINE, NEWLINE, NOT
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesIdentifiers) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "int uint int8 int16 int32 int64 uint8 uint16 uint32 uint64 float double ";
	ss << "var void _ operator enum class partial in if elif else for foreach while forever do ";
	ss << "switch break continue yield def extern aggregate interface namespace import new ";
	ss << "delete private protected public get set virtual final partial where data extend const ";
	ss << "try catch finally throw of as property this";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		INT, UINT, INT8, INT16, INT32, INT64, UINT8, UINT16, UINT32, UINT64, FLOAT, DOUBLE,
		VAR, VOID, TEMP, OPERATOR, ENUM, CLASS, PARTIAL, IN, IF, ELIF, ELSE, FOR, FOREACH,
		WHILE, FOREVER, DO, SWITCH, BREAK, CONTINUE, YIELD, DEF, EXTERN, AGGREGATE, INTERFACE,
		NAMESPACE, IMPORT, NEW, DELETE, PRIVATE, PROTECTED, PUBLIC, GET, SET, VIRTUAL,
		FINAL, PARTIAL, WHERE, DATA, EXTEND, CONST, TRY, CATCH, FINALLY, THROW, OF, AS, PROPERTY,
	    THIS
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesCustomIdentifiers) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "_foo foo FOO F00 _F00 F_1_2_3_foo";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		IDENTIFIER, IDENTIFIER, IDENTIFIER,
		IDENTIFIER, IDENTIFIER, IDENTIFIER
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	EXPECT_TRUE(l.eof());
}

TEST(Lexer, CatchesBadIdentifiers) {
	using namespace orange::parser;

	std::stringstream ss1("__foo");
	EXPECT_THROW((Lexer(ss1)).readToken(), std::runtime_error);

	std::stringstream ss2("_9");
	EXPECT_THROW((Lexer(ss2)).readToken(), std::runtime_error);
}

TEST(Lexer, LexesEmptyChar) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "+''-";

	Lexer l(ss);

	std::vector<TokenType> expects = { PLUS, VAL_CHAR, MINUS };
	for (auto token : expects) expectToken(l, token);

	expectToken(l, TOKEN_EOF);
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesChar) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "+'D'-";

	Lexer l(ss);

	std::vector<TokenType> expects = { PLUS, VAL_CHAR, MINUS };
	for (auto token : expects) expectToken(l, token);

	expectToken(l, TOKEN_EOF);
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesEscapedChar) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "+'\\n'-";

	Lexer l(ss);

	std::vector<TokenType> expects = { PLUS, VAL_CHAR, MINUS };
	for (auto token : expects) expectToken(l, token);

	expectToken(l, TOKEN_EOF);
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, CatchesInvalidChar) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "'no'";

	Lexer l(ss);

	EXPECT_THROW(l.readToken(), std::runtime_error);
}

TEST(Lexer, LexesSlashAtEnd) {
	using namespace orange::parser;

	std::stringstream ss("/");
	Lexer l(ss);
	expectToken(l, DIVIDE);
}

TEST(Lexer, LexesEmptyString) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "+\"\"-";

	Lexer l(ss);

	std::vector<TokenType> expects = { PLUS, VAL_STRING, MINUS };

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}

	expectToken(l, TOKEN_EOF);
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesStrings) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "\"!!@#%)*@!#3/*STRING123\\\"\\n\\n\"";

	Lexer l(ss);

	auto tok = l.readToken();
	expectToken(tok, Token(VAL_STRING, "!!@#%)*@!#3/*STRING123\\\"\\n\\n"));

	expectToken(l, TOKEN_EOF);
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, LexesNumbers) {
	using namespace orange::parser;

	std::stringstream ss;
	ss << "0 0i 0i8 0i16 0i32 0i64 0u 0u8 0u16 0u32 0u64 0d 0f 0.5213 1234.5123f 0.523f 0.532d ";

	ss << "123456789 123456789i 123456789i8 123456789i16 123456789i32 123456789i64 ";
	ss << "123456789u 123456789u8 123456789u16 123456789u32 123456789u64 ";
	ss << "0b100010111 0b100010111i 0b100010111i8 0b100010111i16 0b100010111i32 0b100010111i64 ";
	ss << "0b100010111u 0b100010111u8 0b100010111u16 0b100010111u32 0b100010111u64 ";
	ss << "0xABCDEF123456789 0xABCDEF123456789i 0xABCDEF123456789i8 0x0ABCDEF123456789i16 0xABCDEF123456789i32 ";
	ss << "0xABCDEF123456789i64 ";
	ss << "0xABCDEF123456789u 0x0ABCDEF123456789u8 0xABCDEF123456789u16 0xABCDEF123456789u32 0xABCDEF123456789u64 ";
	ss << "0o01234567 0o01234567i 0o01234567i8 0o01234567i16 0o01234567i32 0o01234567i64 ";
	ss << "0o01234567u 0o01234567u8 0o01234567u16 0o01234567u32 0o01234567u64";

	Lexer l(ss);

	std::vector<TokenType> expects = {
		VAL_INT, VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64, VAL_DOUBLE, VAL_FLOAT, VAL_DOUBLE,
	    VAL_FLOAT, VAL_FLOAT, VAL_DOUBLE,
		VAL_INT, VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64,
		VAL_INT, VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64,
		VAL_INT, VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64,
		VAL_INT, VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64,
		VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}
	
	EXPECT_TRUE(l.eof());
}

TEST(Lexer, CatchesInvalidConstants) {
	using namespace orange::parser;

	std::vector<std::string> badNumbers = {
		"0b010123", "0o1289"
	};

	for (auto input : badNumbers) {
		std::stringstream ss(input);
		Lexer l(ss);

		EXPECT_THROW(l.readToken(), std::runtime_error);
	}
}

TEST(Lexer, NumberRightValues) {
	using namespace orange::parser;

	std::stringstream ss("0b01i64 0o01i64 0x01i64 0i64 0.1234 0.1234f 0.1234d");

	Lexer l(ss);

	std::vector<std::string> expects = {
		"0b01", "0o01", "0x01", "0", "0.1234", "0.1234", "0.1234"
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}
}
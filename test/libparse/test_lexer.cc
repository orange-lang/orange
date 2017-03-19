/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/


#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "lexeme.h"
#include "tokens.h"
#include "lexer.h"

using namespace orange::parse;

#define TEST_TOKEN(INPUT, EXPECTED_TOKEN) \
{\
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_EQ(lex.next().token, EXPECTED_TOKEN); \
}

#define TEST_VALUE(INPUT, EXPECTED_VALUE) \
{\
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_EQ(lex.next().value, EXPECTED_VALUE); \
}

#define TEST_INVALID(INPUT) \
{\
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_THROW(lex.next(), std::runtime_error); \
}

//
//   NUMBERS TESTS
//

TEST(Lexer, TestTypes) {
    std::map<std::string, Token> testTable = {
        {"0b01", Token::UINT_VAL},
		{"0o01234567", Token::UINT_VAL},
        {"0x0123456789abcdefABCDEF", Token::UINT_VAL},
        {"1234567890", Token::INT_VAL},
        {"1234.567890", Token::DOUBLE_VAL},
        {"1234.567890f", Token::FLOAT_VAL},
        {"1234.0567890", Token::DOUBLE_VAL},
        {"1234.0567890f", Token::FLOAT_VAL},
    };

	for (auto row : testTable) {
		TEST_TOKEN(row.first, row.second);
	}
}

TEST(Lexer, TestSuffixedTypes) {
	std::map<std::string, Token> testTable = {
        {"0b11u", Token::UINT_VAL},
        {"0o32u", Token::UINT_VAL},
        {"0xFAu", Token::UINT_VAL},
        {"12u", Token::UINT_VAL},
        {"0b11u8", Token::UINT8_VAL},
        {"0o32u8", Token::UINT8_VAL},
        {"0xFAu8", Token::UINT8_VAL},
        {"12u8",   Token::UINT8_VAL},
        {"0b11u16", Token::UINT16_VAL},
        {"0o32u16", Token::UINT16_VAL},
        {"0xFAu16", Token::UINT16_VAL},
        {"12u16",   Token::UINT16_VAL},
        {"0b11u32", Token::UINT32_VAL},
        {"0o32u32", Token::UINT32_VAL},
        {"0xFAu32", Token::UINT32_VAL},
        {"12u32",   Token::UINT32_VAL},
        {"0b11u64", Token::UINT64_VAL},
        {"0o32u64", Token::UINT64_VAL},
        {"0xFAu64", Token::UINT64_VAL},
        {"12u64",   Token::UINT64_VAL},
        {"0b11i", Token::UINT_VAL},
        {"0o32i", Token::UINT_VAL},
        {"0xFAi", Token::UINT_VAL},
        {"12i",   Token::UINT_VAL},
        {"0b11i8", Token::UINT8_VAL},
        {"0o32i8", Token::UINT8_VAL},
        {"0xFAi8", Token::UINT8_VAL},
        {"12i8",   Token::UINT8_VAL},
        {"0b11i16", Token::UINT16_VAL},
        {"0o32i16", Token::UINT16_VAL},
        {"0xFAi16", Token::UINT16_VAL},
        {"12i16",   Token::UINT16_VAL},
        {"0b11i32", Token::UINT32_VAL},
        {"0o32i32", Token::UINT32_VAL},
        {"0xFAi32", Token::UINT32_VAL},
        {"12i32",   Token::UINT32_VAL},
        {"0b11i64", Token::UINT64_VAL},
        {"0o32i64", Token::UINT64_VAL},
        {"0xFAi64", Token::UINT64_VAL},
        {"12i64",   Token::UINT64_VAL},
	};

 	for (auto row : testTable) {
		TEST_TOKEN(row.first, row.second);
	}
}

TEST(Lexer, TestSeparators) {
    std::map<std::string, Token> testTable = {
        {"0b0000_1111_1010_2_1__2", Token::UINT_VAL},
        {"0o12_345_76__3", Token::UINT_VAL},
        {"0xAAAA_BBBB_C_D_123", Token::UINT_VAL},
        {"123_456_78_9", Token::INT_VAL},
        {"12_34.5_6_78__90", Token::DOUBLE_VAL},
        {"12_34.5_67__89_0_f", Token::FLOAT_VAL},
	};

	for (auto row : testTable) {
		TEST_TOKEN(row.first, row.second);
	}
}

TEST(Lexer, TestValues) {
    std::map<std::string, std::string> testTable = {
        {"0b1111",   "15"},
        {"0o75",     "61"},
        {"0xF1",     "241"},
        {"9501",     "9501"},
        {"59.210",   "59.210"},
        {"989.210f", "989.210"},
	};

    for (auto row : testTable) {
		TEST_VALUE(row.first, row.second);
	}
}

TEST(Lexer, LeadingZeroesValues) {
    std::map<std::string, std::string> testTable = {
        {"0b01111",  "15"},
        {"0o075",    "61"},
        {"0x0F1",    "241"},
	};

	for (auto row : testTable) {
		TEST_VALUE(row.first, row.second);
	}
}

TEST(Lexer, ValuesWithSuffixes) {
    std::map<std::string, std::string> testTable = {
			{"0b11u", "3"},
			{"0o32u", "26"},
			{"0xFAu", "250"},
			{"12u",   "12"},
			{"0b11u8", "3"},
			{"0o32u8", "26"},
			{"0xFAu8", "250"},
			{"12u8",   "12"},
			{"0b11u16", "3"},
			{"0o32u16", "26"},
			{"0xFAu16", "250"},
			{"12u16",   "12"},
			{"0b11u32", "3"},
			{"0o32u32", "26"},
			{"0xFAu32", "250"},
			{"12u32",   "12"},
			{"0b11u64", "3"},
			{"0o32u64", "26"},
			{"0xFAu64", "250"},
			{"12u64",   "12"},
			{"0b11i", "3"},
			{"0o32i", "26"},
			{"0xFAi", "250"},
			{"12i",   "12"},
			{"0b11i8", "3"},
			{"0o32i8", "26"},
			{"0xFAi8", "250"},
			{"12i8",   "12"},
			{"0b11i16", "3"},
			{"0o32i16", "26"},
			{"0xFAi16", "250"},
			{"12i16",   "12"},
			{"0b11i32", "3"},
			{"0o32i32", "26"},
			{"0xFAi32", "250"},
			{"12i32",   "12"},
			{"0b11i64", "3"},
			{"0o32i64", "26"},
			{"0xFAi64", "250"},
			{"12i64",   "12"},
	};

	for (auto row : testTable) {
		TEST_VALUE(row.first, row.second);
	}
}

TEST(Lexer, InvalidNumbers) {
    std::vector<std::string> testTable = {
        "0d51",
        "052",
        "32z",
	};

	for (auto row : testTable) {
		TEST_INVALID(row);
	}
}


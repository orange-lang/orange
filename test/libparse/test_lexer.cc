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

#define TEST_TOKEN(NAME, INPUT, EXPECTED_TOKEN) \
	TEST(Lexer, LexToken##NAME) { \
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_EQ(lex.next().token, EXPECTED_TOKEN); \
	}

#define TEST_VALUE(NAME, INPUT, EXPECTED_VALUE) \
	TEST(Lexer, LexValue##NAME) { \
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_EQ(lex.next().value, EXPECTED_VALUE); \
	}

#define TEST_INVALID(NAME, INPUT) \
	TEST(Lexer, Lex##NAME) { \
			std::stringstream ss(INPUT); \
			Lexer lex(ss); \
			EXPECT_THROW(lex.next(), std::runtime_error); \
	}

///
//   NUMBERS TESTS
///

// Test type
TEST_TOKEN(BinaryNoSuffix, "0b01",                     Token::UINT_VAL);
TEST_TOKEN(OctalNoSuffix,  "0o01234567",               Token::UINT_VAL);
TEST_TOKEN(HexNoSuffix,    "0x0123456789abcdefABCDEF", Token::UINT_VAL);
TEST_TOKEN(DecNoSuffix,    "1234567890",               Token::INT_VAL);
TEST_TOKEN(Double,         "1234.567890",              Token::DOUBLE_VAL);
TEST_TOKEN(Float,          "1234.567890f",             Token::FLOAT_VAL);
TEST_TOKEN(DoubleLeadZero, "1234.0567890",             Token::DOUBLE_VAL);
TEST_TOKEN(FloatLeadZero,  "1234.0567890f",            Token::FLOAT_VAL);

// Test types w/ suffix
TEST_TOKEN(BinarySuffixU, "0b11u", Token::UINT_VAL);
TEST_TOKEN(OctalSuffixU,  "0o32u", Token::UINT_VAL);
TEST_TOKEN(HexSuffixU,    "0xFAu", Token::UINT_VAL);
TEST_TOKEN(DecSuffixU,    "12u",   Token::UINT_VAL);

TEST_TOKEN(BinarySuffixU8, "0b11u8", Token::UINT8_VAL);
TEST_TOKEN(OctalSuffixU8,  "0o32u8", Token::UINT8_VAL);
TEST_TOKEN(HexSuffixU8,    "0xFAu8", Token::UINT8_VAL);
TEST_TOKEN(DecSuffixU8,    "12u8",   Token::UINT8_VAL);

TEST_TOKEN(BinarySuffixU16, "0b11u16", Token::UINT16_VAL);
TEST_TOKEN(OctalSuffixU16,  "0o32u16", Token::UINT16_VAL);
TEST_TOKEN(HexSuffixU16,    "0xFAu16", Token::UINT16_VAL);
TEST_TOKEN(DecSuffixU16,    "12u16",   Token::UINT16_VAL);

TEST_TOKEN(BinarySuffixU32, "0b11u32", Token::UINT32_VAL);
TEST_TOKEN(OctalSuffixU32,  "0o32u32", Token::UINT32_VAL);
TEST_TOKEN(HexSuffixU32,    "0xFAu32", Token::UINT32_VAL);
TEST_TOKEN(DecSuffixU32,    "12u32",   Token::UINT32_VAL);

TEST_TOKEN(BinarySuffixU64, "0b11u64", Token::UINT64_VAL);
TEST_TOKEN(OctalSuffixU64,  "0o32u64", Token::UINT64_VAL);
TEST_TOKEN(HexSuffixU64,    "0xFAu64", Token::UINT64_VAL);
TEST_TOKEN(DecSuffixU64,    "12u64",   Token::UINT64_VAL);

TEST_TOKEN(BinarySuffixI, "0b11i", Token::UINT_VAL);
TEST_TOKEN(OctalSuffixI,  "0o32i", Token::UINT_VAL);
TEST_TOKEN(HexSuffixI,    "0xFAi", Token::UINT_VAL);
TEST_TOKEN(DecSuffixI,    "12i",   Token::UINT_VAL);

TEST_TOKEN(BinarySuffixI8, "0b11i8", Token::UINT8_VAL);
TEST_TOKEN(OctalSuffixI8,  "0o32i8", Token::UINT8_VAL);
TEST_TOKEN(HexSuffixI8,    "0xFAi8", Token::UINT8_VAL);
TEST_TOKEN(DecSuffixI8,    "12i8",   Token::UINT8_VAL);

TEST_TOKEN(BinarySuffixI16, "0b11i16", Token::UINT16_VAL);
TEST_TOKEN(OctalSuffixI16,  "0o32i16", Token::UINT16_VAL);
TEST_TOKEN(HexSuffixI16,    "0xFAi16", Token::UINT16_VAL);
TEST_TOKEN(DecSuffixI16,    "12i16",   Token::UINT16_VAL);

TEST_TOKEN(BinarySuffixI32, "0b11i32", Token::UINT32_VAL);
TEST_TOKEN(OctalSuffixI32,  "0o32i32", Token::UINT32_VAL);
TEST_TOKEN(HexSuffixI32,    "0xFAi32", Token::UINT32_VAL);
TEST_TOKEN(DecSuffixI32,    "12i32",   Token::UINT32_VAL);

TEST_TOKEN(BinarySuffixI64, "0b11i64", Token::UINT64_VAL);
TEST_TOKEN(OctalSuffixI64,  "0o32i64", Token::UINT64_VAL);
TEST_TOKEN(HexSuffixI64,    "0xFAi64", Token::UINT64_VAL);
TEST_TOKEN(DecSuffixI64,    "12i64",   Token::UINT64_VAL);

// Test type with separators
TEST_TOKEN(BinarySep, "0b0000_1111_1010_2_1__2",  Token::UINT_VAL);
TEST_TOKEN(OctalSep,  "0o12_345_76__3",           Token::UINT_VAL);
TEST_TOKEN(HexSep,    "0xAAAA_BBBB_C_D_123",      Token::UINT_VAL);
TEST_TOKEN(DecSep,    "123_456_78_9",             Token::INT_VAL);
TEST_TOKEN(DoubleSep, "12_34.5_6_78__90",         Token::DOUBLE_VAL);
TEST_TOKEN(FloatSetp, "12_34.5_67__89_0_f",       Token::FLOAT_VAL);

// Test values
TEST_VALUE(BinaryVal, "0b1111",   "15");
TEST_VALUE(OctalVal,  "0o75",     "61");
TEST_VALUE(HexVal,    "0xF1",     "241");
TEST_VALUE(DecVal,    "9501",     "9501");
TEST_VALUE(DoubleVal, "59.210",   "59.210");
TEST_VALUE(FloatVal,  "989.210f", "989.210");

// Test load zeroes
TEST_VALUE(BinaryValLeadZero, "0b01111",  "15");
TEST_VALUE(OctalValLeadZero,  "0o075",    "61");
TEST_VALUE(HexValLeadZero,    "0x0F1",    "241");

// Test values with suffixes
TEST_VALUE(BinarySuffixU, "0b11u", "3");
TEST_VALUE(OctalSuffixU,  "0o32u", "26");
TEST_VALUE(HexSuffixU,    "0xFAu", "250");
TEST_VALUE(DecSuffixU,    "12u",   "12");

TEST_VALUE(BinarySuffixU8, "0b11u8", "3");
TEST_VALUE(OctalSuffixU8,  "0o32u8", "26");
TEST_VALUE(HexSuffixU8,    "0xFAu8", "250");
TEST_VALUE(DecSuffixU8,    "12u8",   "12");

TEST_VALUE(BinarySuffixU16, "0b11u16", "3");
TEST_VALUE(OctalSuffixU16,  "0o32u16", "26");
TEST_VALUE(HexSuffixU16,    "0xFAu16", "250");
TEST_VALUE(DecSuffixU16,    "12u16",   "12");

TEST_VALUE(BinarySuffixU32, "0b11u32", "3");
TEST_VALUE(OctalSuffixU32,  "0o32u32", "26");
TEST_VALUE(HexSuffixU32,    "0xFAu32", "250");
TEST_VALUE(DecSuffixU32,    "12u32",   "12");

TEST_VALUE(BinarySuffixU64, "0b11u64", "3");
TEST_VALUE(OctalSuffixU64,  "0o32u64", "26");
TEST_VALUE(HexSuffixU64,    "0xFAu64", "250");
TEST_VALUE(DecSuffixU64,    "12u64",   "12");

TEST_VALUE(BinarySuffixI, "0b11i", "3");
TEST_VALUE(OctalSuffixI,  "0o32i", "26");
TEST_VALUE(HexSuffixI,    "0xFAi", "250");
TEST_VALUE(DecSuffixI,    "12i",   "12");

TEST_VALUE(BinarySuffixI8, "0b11i8", "3");
TEST_VALUE(OctalSuffixI8,  "0o32i8", "26");
TEST_VALUE(HexSuffixI8,    "0xFAi8", "250");
TEST_VALUE(DecSuffixI8,    "12i8",   "12");

TEST_VALUE(BinarySuffixI16, "0b11i16", "3");
TEST_VALUE(OctalSuffixI16,  "0o32i16", "26");
TEST_VALUE(HexSuffixI16,    "0xFAi16", "250");
TEST_VALUE(DecSuffixI16,    "12i16",   "12");

TEST_VALUE(BinarySuffixI32, "0b11i32", "3");
TEST_VALUE(OctalSuffixI32,  "0o32i32", "26");
TEST_VALUE(HexSuffixI32,    "0xFAi32", "250");
TEST_VALUE(DecSuffixI32,    "12i32",   "12");

TEST_VALUE(BinarySuffixI64, "0b11i64", "3");
TEST_VALUE(OctalSuffixI64,  "0o32i64", "26");
TEST_VALUE(HexSuffixI64,    "0xFAi64", "250");
TEST_VALUE(DecSuffixI64,    "12i64",   "12");

TEST_INVALID(LeadingZeroLetter, "0d51");
TEST_INVALID(LeadingZeroNumber, "052");
TEST_INVALID(InvalidSuffix, "32z");

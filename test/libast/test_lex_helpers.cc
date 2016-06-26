//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#include <libparse/lex_helpers.h>
#include <libparse/lex.h>

#include "../helpers.h"

using namespace orange::parser;

TEST(LexHelpers, ToInt) {
	std::vector<TokenType> intTypes = { VAL_INT, VAL_INT8, VAL_INT16, VAL_INT32, VAL_INT64 };

	for (auto ty : intTypes) {
		Token tok(ty, "123456789");
		EXPECT_EQ(123456789, ToInt(&tok));
	}
}

TEST(LexHelpers, ToIntBase2) {
	Token tok(VAL_INT, "0b1011");
	EXPECT_EQ(11, ToInt(&tok));

	tok.type = VAL_UINT;
	EXPECT_EQ(11, ToUInt(&tok));
}

TEST(LexHelpers, ToIntBase8) {
	Token tok(VAL_INT, "0o64");
	EXPECT_EQ(52, ToInt(&tok));

	tok.type = VAL_UINT;
	EXPECT_EQ(52, ToUInt(&tok));
}

TEST(LexHelpers, ToIntBase16) {
	Token tok(VAL_INT, "0xABC");
	EXPECT_EQ(2748, ToInt(&tok));

	tok.type = VAL_UINT;
	EXPECT_EQ(2748, ToUInt(&tok));
}

TEST(LexHelpers, ToUInt) {
	std::vector<TokenType> uintTypes = { VAL_UINT, VAL_UINT8, VAL_UINT16, VAL_UINT32, VAL_UINT64 };

	for (auto ty : uintTypes) {
		Token tok(ty, "123456789");
		EXPECT_EQ(123456789, ToUInt(&tok));
	}
}

TEST(LexHelpers, ToFloat) {
	Token tok(VAL_FLOAT, "600.50");
	EXPECT_FLOAT_EQ(600.50, ToFloat(&tok));
}

TEST(LexHelpers, ToDouble) {
	Token tok(VAL_DOUBLE, "600.50");
	EXPECT_FLOAT_EQ(600.50, ToDouble(&tok));
}

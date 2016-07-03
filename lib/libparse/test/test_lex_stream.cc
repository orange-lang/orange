//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <gtest/gtest.h>
#include <sstream>

#include "lex_stream.h"
#include "helpers.h"

using namespace orange::parser;

TEST(LexStream, PopulatesPeek) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	expectToken(stream.peek(), PLUS);
	expectToken(stream.peek(), PLUS);
}

TEST(LexStream, GetIgnoresBuffer) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	expectToken(stream.get(), PLUS);
	expectToken(stream.get(), MINUS);
}

TEST(LexStream, GetUsesBuffer) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	expectToken(stream.peek(), PLUS);
	expectToken(stream.get(), PLUS);
	expectToken(stream.get(), MINUS);
}

TEST(LexStream, PeekMultiple) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	auto next = stream.peek(2);

	ASSERT_EQ(2, next.size());

	expectToken(next[0], PLUS);
	expectToken(next[1], MINUS);

	expectToken(stream.peek(), PLUS);
}

TEST(LexStream, GetAfterPeekMultiple) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.peek(2);

	expectToken(stream.get(), PLUS);
	expectToken(stream.get(), MINUS);
}

TEST(LexStream, GetMultiple) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	auto next = stream.get(2);

	ASSERT_EQ(2, next.size());

	expectToken(next[0], PLUS);
	expectToken(next[1], MINUS);
}

TEST(LexStream, GetMultipleAfterPeek) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.peek();
	auto next = stream.get(2);

	ASSERT_EQ(2, next.size());

	expectToken(next[0], PLUS);
	expectToken(next[1], MINUS);
}

TEST(LexStream, GetMultipleAfterPeekMultiple) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.peek(2);
	auto next = stream.get(3);

	ASSERT_EQ(3, next.size());

	expectToken(next[0], PLUS);
	expectToken(next[1], MINUS);
	expectToken(next[2], TIMES);
}

TEST(LexStream, TestStreamEOF) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.get(4);

	ASSERT_TRUE(stream.eof());
}

TEST(LexStream, TestStreamEOFAfterPeek) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.peek(4);
	ASSERT_FALSE(stream.eof());

	stream.get(4);
	ASSERT_TRUE(stream.eof());
}

TEST(LexStream, TestSeekAtBeginning) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.seek(0);
	expectToken(stream.peek(), PLUS);
}

TEST(LexStream, TestSeekAfterPeek) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.peek();
	stream.seek(0);
	expectToken(stream.peek(), PLUS);
}

TEST(LexStream, TestSeekAfterGet) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.get();
	stream.seek(0);
	expectToken(stream.peek(), PLUS);
}

TEST(LexStream, TestSeekPartial) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	stream.get(2);
	stream.seek(1);

	expectToken(stream.get(), MINUS);
	expectToken(stream.get(), TIMES);
}

TEST(LexStream, TestSeekPartialAfterPartialPeek) {
	std::stringstream ss("+ - * /");

	LexStream stream(ss);

	auto pos = stream.tell();

	stream.peek(3);

	stream.get(2);
	stream.seek(pos);

	expectToken(stream.get(), PLUS);
	expectToken(stream.get(), MINUS);
	expectToken(stream.get(), TIMES);
	expectToken(stream.get(), DIVIDE);
}

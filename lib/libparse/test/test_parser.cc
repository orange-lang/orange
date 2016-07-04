//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <sstream>
#include <gtest/gtest.h>

#include <libast/ast.h>
#include <libparse/parser.h>

#include "parser-private.h"
#include "helpers.h"

using namespace orange::ast;
using namespace orange::parser;

TEST(Parser, ParsesNothing) {
	std::stringstream ss("");

	Parser p(ss);

	EXPECT_NO_THROW({
		auto ast = p.parse();
		delete ast;
	});
}

TEST(Parser, ParsesInteger) {
	std::stringstream ss("0xF00");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new IntValue(0xf00)
    }));

	assertEqAST(&expected, ast);

	delete ast;
}

TEST(Parser, ParsesEmptyBlock) {
	std::stringstream ss("{}");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new LongBlockExpr()
    }));

	assertEqAST(&expected, ast);

	delete ast;
}

TEST(Parser, ParsesOpPrecedence) {
	std::stringstream ss("5 + 3 * 12");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BinOpExpr(
			new IntValue(5),
			BinOp::ADD,
			new BinOpExpr(
				new IntValue(3),
				BinOp::MULTIPLY,
				new IntValue(12)
			)
		)
    }));

	assertEqAST(&expected, ast);

	delete ast;
}

TEST(Parser, ParsesOpPrecedence2) {
	std::stringstream ss("5 * 3 + 12");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BinOpExpr(
			new BinOpExpr(
				new IntValue(5),
				BinOp::MULTIPLY,
				new IntValue(3)
			),
			BinOp::ADD,
			new IntValue(12)
		)
	}));

	assertEqAST(&expected, ast);

	delete ast;
}

TEST(Parser, ParsesIfStmt) {
	std::stringstream ss(R"(
		if (3) {
            5 + 2
        }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new IfExpr(std::vector<ConditionalBlock*>({
			new ConditionalBlock(
				new IntValue(3),
				new LongBlockExpr(std::vector<Node*>({
					new BinOpExpr(
						new IntValue(5),
						BinOp::ADD,
						new IntValue(2)
					)
				}))
			)
		}))
	}));

	assertEqAST(&expected, ast);

	delete ast;
}
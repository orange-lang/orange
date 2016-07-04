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
#include <libast/type.h>
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

TEST(Parser, ParsesNothingButTerms) {
	std::stringstream ss(R"(
		;;;

			;
		;
		;
	)");

	Parser p(ss);

	EXPECT_NO_THROW({
		auto ast = p.parse();
		delete ast;
	});
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

TEST(Parser, ParsesLongBlockNothingButTerms) {
	std::stringstream ss(R"({
		;;;

			;
		;
		;
	})");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new LongBlockExpr()
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesLongBlockSimpleExpression) {
	std::stringstream ss(R"({
		3
	})");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new LongBlockExpr(std::vector<Node*>({
			new IntValue(3)
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesLongBlockSimpleExpressionOneLine) {
	std::stringstream ss("{ 3 }");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new LongBlockExpr(std::vector<Node*>({
			new IntValue(3)
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesBasicVarDecl) {
	std::stringstream ss(R"(
		var a
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new VarDeclExpr(
			std::vector<Identifier*>({
				new NamedIDExpr("a")
			}),
			std::vector<Type*>(),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesMultipleBindingVarDecl) {
	std::stringstream ss(R"(
		var (a, b)
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new VarDeclExpr(
			std::vector<Identifier*>({
				new NamedIDExpr("a"),
				new NamedIDExpr("b")
			}),
			std::vector<Type*>(),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesTypedVarDecl) {
	std::stringstream ss(R"(
		var a: int
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new VarDeclExpr(
			std::vector<Identifier*>({
				new NamedIDExpr("a")
			}),
			std::vector<Type*>({
				new BuiltinType(BuiltinTypeKind::INT)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesMultipleTypedVarDecl) {
	std::stringstream ss(R"(
		var (a, b): int, double
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new VarDeclExpr(
			std::vector<Identifier*>({
				new NamedIDExpr("a"),
				new NamedIDExpr("b")
			}),
			std::vector<Type*>({
				new BuiltinType(BuiltinTypeKind::INT),
				new BuiltinType(BuiltinTypeKind::DOUBLE)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

// TODO: Test types (all the kinds, via var decl)
// TODO: Test short identifier (via var decl)
// TODO: Test long identifier (via namespace)
// TODO: Test flags
// TODO: Test enum
// TODO: Test class (and all of its acceptable statements)
// TODO: Test partial class
// TODO: Test functions
// TODO: Test extern functions
// TODO: Test aggregate
// TODO: Test interface
// TODO: Test namespaces
// TODO: Test imports
// TODO: Test single constant value
// TODO: Test single identifier
// TODO: Test unary (INCREMENT, DECREMENT, DEREF, REF)
// TODO: Test function call, array access, member access
// TODO: Test binary expressions & basic operator precedence
// TODO: Test this
// TODO: Test control
// TODO: Test new
// TODO: Test array
// TODO: Test inclusive, exclusive range
// TODO: Test tuple
// TODO: Test named arguments
// TODO: Test if statements (and elif, else)
// TODO: Test short block (via if statement)
// TODO: Test for loop, foreach, while, forever, do_while
// TODO: Test switch
// TODO: Test break, continue, yield
// TODO: Test generics
// TODO: Test delete
// TODO: Test try/catch/finally




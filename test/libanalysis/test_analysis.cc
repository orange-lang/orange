//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <vector>
#include <gtest/gtest.h>

#include <libast/ast.h>
#include <libast/walker.h>
#include <libast/compare.h>
#include <libast/printer.h>
#include "resolve.h"

using namespace orange::ast;
using namespace orange::analysis;

namespace orange { namespace ast {
	struct TypeWrapper {
		Type* internal;

		TypeWrapper(Type *internal) : internal(internal) { }
	};

	bool operator==(TypeWrapper expected, TypeWrapper actual) {
		return CompareType(expected.internal, actual.internal);
	}

	std::ostream& operator<<(std::ostream& os, const TypeWrapper& ty) {
		std::stringstream stream;

		NonTraversalWalker walker;
		ASTPrinter printer(walker);
		printer.PrintType(ty.internal);

		return os << printer.getOutput();
	}

	void ExpectTy(Type* expected, Type* actual) {
		EXPECT_EQ(TypeWrapper(expected), TypeWrapper(actual));
	}
}}

TEST(Analysis, BuildsTypeTable) {
	LongBlockExpr* ast = CreateNode<LongBlockExpr>();

	auto intNode = CreateNode<IntValue>(0xF00);
	ast->statements.push_back(intNode);

	std::vector<LongBlockExpr *> astList = { ast };
	TypeResolution tr(astList);

	auto tt = tr.GenerateTypeTable();

	ASSERT_NE(tt, nullptr);
	ExpectTy(new IntType, tt->GetGlobalContext()->GetNodeType(intNode));

	delete ast;
}

TEST(Analysis, ConstTypes) {
	std::vector<std::pair<Expression*, orange::ast::Type*>> tests({
		std::make_pair(
			CreateNode<IntValue>(0xF00), new IntType
		),
	    std::make_pair(
			CreateNode<IntValue>(0xF00, new IntType), new IntType
		),
	    std::make_pair(
		    CreateNode<IntValue>(0xF00, new Int8Type), new Int8Type
		),
	    std::make_pair(
		    CreateNode<IntValue>(0xF00, new Int16Type), new Int16Type
		),
	    std::make_pair(
		    CreateNode<IntValue>(0xF00, new Int32Type), new Int32Type
		),
	    std::make_pair(
		    CreateNode<IntValue>(0xF00, new Int64Type), new Int64Type
		),
		std::make_pair(
			CreateNode<UIntValue>(0xF00, new UIntType), new UIntType
		),
		std::make_pair(
			CreateNode<UIntValue>(0xF00, new UInt8Type), new UInt8Type
		),
		std::make_pair(
			CreateNode<UIntValue>(0xF00, new UInt16Type), new UInt16Type
		),
		std::make_pair(
			CreateNode<UIntValue>(0xF00, new UInt32Type), new UInt32Type
		),
		std::make_pair(
			CreateNode<UIntValue>(0xF00, new UInt64Type), new UInt64Type
		),
	    std::make_pair(
		    CreateNode<FloatValue>(0.529), new FloatType
	    ),
	    std::make_pair(
		    CreateNode<DoubleValue>(0.529), new DoubleType
	    ),
		std::make_pair(
		    CreateNode<CharValue>('f'), new CharType
	    ),
	    std::make_pair(
		    CreateNode<StringValue>("foo"), new StringType
	    )
	});

	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto pair : tests) {
		walker.WalkExpr(&resolver, pair.first);
		auto ty = ctx.GetNodeType(pair.first);

		ExpectTy(pair.second, ty);
	}
}

TEST(Analysis, BinOps) {
	std::vector<std::pair<Expression*, orange::ast::Type*>> tests({
		std::make_pair(
			CreateNode<BinOpExpr>(CreateNode<IntValue>(5), BinOp::ADD, CreateNode<IntValue>(10)),
			new IntType
		),
	 	std::make_pair(
			CreateNode<BinOpExpr>(CreateNode<IntValue>(5, new Int8Type), BinOp::ADD, CreateNode<IntValue>(10)),
		    new IntType
		),
	 	std::make_pair(
			CreateNode<BinOpExpr>(CreateNode<IntValue>(5, new FloatType), BinOp::ADD, CreateNode<IntValue>(10)),
		    new FloatType
		)
	});

	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto pair : tests) {
		walker.WalkExpr(&resolver, pair.first);
		auto ty = ctx.GetNodeType(pair.first);

		ExpectTy(pair.second, ty);
	}
}
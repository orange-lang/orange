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
		if (expected == actual) return;
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

void TestType(std::vector<Node*> nodes, Type* target) {
	auto ast = CreateNode<LongBlockExpr>(nodes);

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ ast }));
	auto ctx = NodeTypeContext();
	auto log = AnalysisMessageLog();
	ResolveVisitor resolver(&ctx, log, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);
	walker.WalkNode(&resolver, ast);

	auto ty = ctx.GetNodeType(nodes.back());
	ExpectTy(target, ty);

	delete ast;
	delete target;
}

void TestType(Node* node, Type* target) {
	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	auto log = AnalysisMessageLog();
	ResolveVisitor resolver(&ctx, log, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);
	walker.WalkNode(&resolver, node);

	auto ty = ctx.GetNodeType(node);
	ExpectTy(target, ty);

	delete node;
	delete target;
}

TEST(Analysis, ConstTypes) {
	TestType(CreateNode<IntValue>(0xF00), new IntType);
	TestType(CreateNode<IntValue>(0xF00, new IntType), new IntType);
	TestType(CreateNode<IntValue>(0xF00, new Int8Type), new Int8Type);
	TestType(CreateNode<IntValue>(0xF00, new Int16Type), new Int16Type);
	TestType(CreateNode<IntValue>(0xF00, new Int32Type), new Int32Type);
	TestType(CreateNode<IntValue>(0xF00, new Int64Type), new Int64Type);
	TestType(CreateNode<UIntValue>(0xF00, new UIntType), new UIntType);
	TestType(CreateNode<UIntValue>(0xF00, new UInt8Type), new UInt8Type);
	TestType(CreateNode<UIntValue>(0xF00, new UInt16Type), new UInt16Type);
	TestType(CreateNode<UIntValue>(0xF00, new UInt32Type), new UInt32Type);
	TestType(CreateNode<UIntValue>(0xF00, new UInt64Type), new UInt64Type);
	TestType(CreateNode<FloatValue>(0.529), new FloatType);
	TestType(CreateNode<DoubleValue>(0.529), new DoubleType);
	TestType(CreateNode<CharValue>('f'), new CharType);
	TestType(CreateNode<StringValue>("foo"), new StringType);
	TestType(CreateNode<BoolValue>(true), new BoolType);
	TestType(CreateNode<BoolValue>(false), new BoolType);
}

TEST(Analysis, ReturnAdaptsType) {
	TestType(CreateNode<ReturnStmt>(), new BuiltinType(BuiltinTypeKind::VOID));
	TestType(CreateNode<ReturnStmt>(CreateNode<IntValue>(0xF00)), new IntType);
}

TEST(Analysis, BinOps) {
	TestType(CreateNode<BinOpExpr>(CreateNode<IntValue>(5), BinOp::ADD, CreateNode<IntValue>(10)),
		new IntType);

	TestType(CreateNode<BinOpExpr>(CreateNode<IntValue>(5, new Int8Type), BinOp::ADD, CreateNode<IntValue>(10)),
		new IntType);

	TestType(CreateNode<BinOpExpr>(CreateNode<IntValue>(5, new FloatType), BinOp::ADD, CreateNode<IntValue>(10)),
		new FloatType);
}

// The type of a variable declaration is a tuple of a type for each binding
TEST(Analysis, VarDecl) {
	// typeless with value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ }),
		CreateNode<IntValue>(52)
	), new TupleType(std::vector<Type*>({ new IntType })));

	// type without value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new IntType }),
		nullptr
	), new TupleType(std::vector<Type*>({ new IntType })));

	// type with value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new IntType }),
		CreateNode<DoubleValue>(5.23)
	), new TupleType(std::vector<Type*>({ new IntType })));
}

TEST(Analysis, InvalidVarDecl) {
	// invalid name
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<AccessIDExpr>(
				CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b")
			)}),
			std::vector<Type*> ({ }),
			CreateNode<IntValue>(5)
		), nullptr);
	}, std::runtime_error);

	// typeless without value
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ }),
			nullptr
		), nullptr);
	}, std::runtime_error);

	// void type
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
			nullptr
		), nullptr);
	}, std::runtime_error);

	// void value
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
			CreateNode<TempIDExpr>()
		), nullptr);
	}, std::runtime_error);
}

TEST(Analysis, VarDeclPair) {
	// TODO: remove expect throw when this feature is implemented
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b") }),
			std::vector<Type*> ({ }),
			CreateNode<TupleExpr>(std::vector<Expression*>({
				CreateNode<IntValue>(5),
				CreateNode<DoubleValue>(10.93)
			}))
		), new TupleType(std::vector<Type*>({ new IntType, new DoubleType })));
	}, std::runtime_error);
}

TEST(Analysis, VarReference) {
	TestType({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::ADD,
		    CreateNode<IntValue>(5)
	    )
	}, new IntType);
}

TEST(Analysis, InvalidVarReference) {
	EXPECT_THROW({
		TestType(std::vector<Node*>({
			CreateNode<BinOpExpr>(
				CreateNode<ReferenceIDExpr>("a"),
				BinOp::ADD,
				CreateNode<IntValue>(5)
			)
		}), nullptr);
	}, std::runtime_error);
}

TEST(Analysis, AssignBinOps) {
	TestType({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::PLUS_ASSIGN,
		    CreateNode<IntValue>(5)
	    )
	}, new IntType);

	TestType({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::TIMES_ASSIGN,
		    CreateNode<DoubleValue>(52.932)
	    ),
	}, new IntType);
}

TEST(Analysis, CompareBinOps) {
	TestType({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::GREATER_THAN,
			CreateNode<IntValue>(5)
		),
	}, new BoolType);

	TestType({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::LESS_THAN,
			CreateNode<DoubleValue>(52.932)
		),
	}, new BoolType);
}

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

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto pair : tests) {
		walker.WalkExpr(&resolver, pair.first);
		auto ty = ctx.GetNodeType(pair.first);

		ExpectTy(pair.second, ty);
	}
}

TEST(Analysis, ReturnAdaptsType) {
	auto ast = CreateNode<LongBlockExpr>();
	auto voidReturn = CreateNode<ReturnStmt>();
	auto intReturn = CreateNode<ReturnStmt>(CreateNode<IntValue>(0xF00));

	ast->statements.push_back(voidReturn);
	ast->statements.push_back(intReturn);

	TypeResolution tr(ast);

	auto tab = tr.GenerateTypeTable();
	ASSERT_NE(tab, nullptr);

	ExpectTy(new BuiltinType(BuiltinTypeKind::VOID), tab->GetGlobalContext()->GetNodeType(voidReturn));
	ExpectTy(new IntType, tab->GetGlobalContext()->GetNodeType(intReturn));
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

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto pair : tests) {
		walker.WalkExpr(&resolver, pair.first);
		auto ty = ctx.GetNodeType(pair.first);

		ExpectTy(pair.second, ty);
	}
}

TEST(Analysis, VarDecl) {
	std::vector<std::pair<VarDeclExpr*, orange::ast::Type*>> tests({
		// typeless with value
		std::make_pair(
			CreateNode<VarDeclExpr>(
				std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
				std::vector<Type*> ({ }),
				CreateNode<IntValue>(52)
			),
			new IntType
		),

		// type without value
		std::make_pair(
			CreateNode<VarDeclExpr>(
				std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
				std::vector<Type*> ({ new IntType }),
				nullptr
			),
			new IntType
		),

		// type with value
		std::make_pair(
			CreateNode<VarDeclExpr>(
				std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
				std::vector<Type*> ({ new IntType }),
				CreateNode<DoubleValue>(5.23)
			),
			new IntType
		),
	});

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto pair : tests) {
		walker.WalkExpr(&resolver, pair.first);
		auto ty = ctx.GetNodeType(pair.first->bindings[0]);

		ExpectTy(pair.second, ty);
	}
}

TEST(Analysis, InvalidVarDecl) {
	std::vector<VarDeclExpr*> tests({
		// invalid name
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<AccessIDExpr>(
				CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b")
			)}),
			std::vector<Type*> ({ }),
			CreateNode<IntValue>(5)
		),

		// typeless without value
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ }),
			nullptr
		),

		// void type
	    CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
			nullptr
	    ),

	    // void value
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
			CreateNode<TempIDExpr>()
		),
	});

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	for (auto varDecl : tests) {
		EXPECT_THROW({
			walker.WalkExpr(&resolver, varDecl);
		}, std::runtime_error);

		delete varDecl;
	}
}

TEST(Analysis, VarDeclPair) {
	// TODO: change when this feature is implemented
	auto varDecl = CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b") }),
		std::vector<Type*> ({ }),
		CreateNode<TupleExpr>(std::vector<Expression*>({
			CreateNode<IntValue>(5),
			CreateNode<DoubleValue>(10.93)
		}))
	);

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>());
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	EXPECT_THROW({
		walker.WalkExpr(&resolver, varDecl);
	}, std::runtime_error);

	delete varDecl;
}

TEST(Analysis, VarReference) {
	auto ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::ADD,
		    CreateNode<IntValue>(5)
	    ),
	}));

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ ast }));
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	walker.WalkLongBlockExpr(&resolver, ast);
	ExpectTy(new IntType, ctx.GetNodeType(ast->statements[1]));
}

TEST(Analysis, InvalidVarReference) {
	auto ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::ADD,
			CreateNode<IntValue>(5)
		),
	}));

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ ast }));
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	EXPECT_THROW({
		walker.WalkLongBlockExpr(&resolver, ast);
	}, std::runtime_error);
}

TEST(Analysis, AssignBinOps) {
	auto ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<Type*>(), CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::PLUS_ASSIGN,
		    CreateNode<IntValue>(5)
	    ),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::TIMES_ASSIGN,
		    CreateNode<DoubleValue>(52.932)
	    ),
	}));

	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ ast }));
	auto ctx = NodeTypeContext();
	ResolveVisitor resolver(&ctx, searcher);

	DepthFirstWalker walker(TraversalOrder::POSTORDER);

	walker.WalkLongBlockExpr(&resolver, ast);

	for (unsigned long i = 1; i < ast->statements.size(); i++) {
		ExpectTy(new IntType, ctx.GetNodeType(ast->statements[i]));
	}
}
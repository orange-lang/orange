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
	ExpectTy(new IntType, tt->GetDefaultContext(ast)->GetNodeType(intNode));

	delete ast;
}

class MockExpr: public Expression {
public:
	Type* type;
	
	MockExpr(Type* type) : type(type) { }
};

Expression* CreateMockExpr(Type* ty) { return CreateNode<MockExpr>(ty); }

class MockNonTraversalWalker : public NonTraversalWalker {
public:
	virtual void WalkExpr(Visitor* helper, Expression* node) override {
		if (isA<MockExpr>(node)) {
			return;
		} else {
			NonTraversalWalker::WalkExpr(helper, node);
		}
	}
	
	MockNonTraversalWalker() { }
};

class MockDepthFirstWalker : public DepthFirstWalker {
public:
	virtual void WalkExpr(Visitor* helper, Expression* node) override {
		if (isA<MockExpr>(node)) {
			if (dynamic_cast<ResolveVisitor*>(helper) != nullptr) {
				auto resolver = dynamic_cast<ResolveVisitor*>(helper);
				resolver->GetContext()->SetNodeType(node, asA<MockExpr>(node)->type);
			}
			
			return;
		} else {
			DepthFirstWalker::WalkExpr(helper, node);
		}
	}
	
	MockDepthFirstWalker(TraversalOrder order) : DepthFirstWalker(order) { }
};

class MockPredicateWalker : public PredicateWalker {
public:
	virtual void WalkExpr(Predicate* helper, Expression* node) override {
		if (isA<MockExpr>(node)) {
			return;
		} else {
			PredicateWalker::WalkExpr(helper, node);
		}
	}
	
	MockPredicateWalker() { }
};

bool ShouldHaveContext(Node* node) {
	return isA<FunctionExpr>(node);
}

void TestType(std::vector<Node*> nodes, Type* target, bool expectValid = true) {
	auto ast = CreateNode<LongBlockExpr>(nodes);
	MockDepthFirstWalker searchWalker(TraversalOrder::PREORDER);
	MockPredicateWalker predWalker;
	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ast}), &searchWalker, &predWalker);
	
	MockDepthFirstWalker walker(TraversalOrder::POSTORDER);
	
	auto validateWalker = MockNonTraversalWalker();
	ASSERT_EQ(ValidateAST(ast, &validateWalker), expectValid);
	if (expectValid == false) return;
	
	auto ctx = NodeTypeContext(ast, true);
	auto log = AnalysisMessageLog();
	auto tt = TypeTable(&searcher, &walker);
	
	tt.AddGlobalContext(&ctx);
	ResolveVisitor resolver(&tt, &ctx, log);
	
	walker.WalkNode(&resolver, ast);
	
	NodeTypeContext* checkContext = &ctx;
	
	if (ShouldHaveContext(nodes.back())) {
		checkContext = ctx.GetDefaultChildContext(nodes.back(), false);
	}
	
	ASSERT_NE(checkContext, nullptr);

	auto ty = checkContext->GetNodeType(nodes.back());
	ExpectTy(target, ty);
	
	if (isA<BuiltinType>(ty) && asA<BuiltinType>(ty)->kind == VAR) {
		EXPECT_GT(log.GetMessages().size(), 0);
	}

	delete ast;
	delete target;
}

void TestType(Node* node, Type* target, bool expectValid = true) {
	MockDepthFirstWalker searchWalker(TraversalOrder::PREORDER);
	MockPredicateWalker predWalker;
	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({
		CreateNode<LongBlockExpr>(std::vector<Node*>({ node }))
	}), &searchWalker, &predWalker);
	MockDepthFirstWalker walker(TraversalOrder::POSTORDER);
	
	auto validateWalker = MockNonTraversalWalker();
	
	ASSERT_EQ(ValidateAST(CreateNode<LongBlockExpr>(std::vector<Node*>({ node })), &validateWalker), expectValid);
	if (expectValid == false) return;
	
	auto ctx = NodeTypeContext(node, true);
	auto log = AnalysisMessageLog();
	auto tt = TypeTable(&searcher, &walker);
	tt.AddGlobalContext(&ctx);
	ResolveVisitor resolver(&tt, &ctx, log);

	walker.WalkNode(&resolver, node);
	
	NodeTypeContext* checkContext = &ctx;
	if (ShouldHaveContext(node)) {
		checkContext = ctx.GetDefaultChildContext(node, false);
	}

	auto ty = checkContext->GetNodeType(node);
	ExpectTy(target, ty);

	if (isA<BuiltinType>(ty) && asA<BuiltinType>(ty)->kind == VAR) {
		EXPECT_GT(log.GetMessages().size(), 0);
	}

	delete node;
	delete target;
}

TEST(Analysis, MockExpression) {
	TestType(CreateNode<MockExpr>(new DoubleType), new DoubleType);
	TestType(CreateNode<MockExpr>(new IntType), new IntType);
}

TEST(Analysis, EmptyBlock) {
	TestType(CreateNode<LongBlockExpr>(), new BuiltinType(VOID));
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
	TestType(CreateNode<ReturnStmt>(CreateMockExpr(new IntType)), new IntType);
}

TEST(Analysis, BinOps) {
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new IntType), BinOp::ADD, CreateMockExpr(new IntType)),
		new IntType);

	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new Int8Type), BinOp::ADD, CreateMockExpr(new Int16Type)),
		new Int16Type);

	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new FloatType), BinOp::ADD, CreateMockExpr(new IntType)),
		new FloatType);
}

TEST(Analysis, InvalidBinOps) {
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new FloatType), BinOp::ADD, CreateMockExpr(new BuiltinType(VOID))),
		new BuiltinType(VAR));
}

// The type of a variable declaration is a tuple of a type for each binding
TEST(Analysis, VarDecl) {
	// type without value
	TestType(CreateNode<VarDeclExpr>(
		"a", new IntType, nullptr
	), new IntType);

	// type with value
	TestType(CreateNode<VarDeclExpr>(
		"a", new IntType, CreateMockExpr(new DoubleType)
	), new IntType);
}

TEST(Analysis, InvalidVarDecl) {
	// typeless with value
	TestType(CreateNode<VarDeclExpr>(
		"a", nullptr, CreateMockExpr(new IntType)
	), new IntType, false);

	// typeless without value
	TestType(CreateNode<VarDeclExpr>(
		"a", nullptr, nullptr
	), new VarType, false);

	// void type
	TestType(CreateNode<VarDeclExpr>(
		"a", new VoidType, nullptr
	), new VarType, true);

	// void value
	TestType(CreateNode<VarDeclExpr>(
		"a", new VoidType, CreateMockExpr(new VoidType)
	), new VarType, true);
}

TEST(Analysis, VarReference) {
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::ADD,
		    CreateMockExpr(new IntType)
	    )
	}, new IntType);
}

TEST(Analysis, InvalidVarReference) {
	TestType(std::vector<Node*>({
		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::ADD,
			CreateMockExpr(new IntType)
		)
	}), new BuiltinType(VAR));
}

TEST(Analysis, AssignBinOps) {
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::PLUS_ASSIGN,
		    CreateMockExpr(new IntType)
	    )
	}, new IntType);

	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),
		
	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::TIMES_ASSIGN,
		    CreateMockExpr(new IntType)
	    ),
	}, new IntType);
}

TEST(Analysis, CompareBinOps) {
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::GREATER_THAN,
			CreateNode<IntValue>(5)
		),
	}, new BoolType);

	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::LESS_THAN,
			CreateNode<DoubleValue>(52.932)
		),
	}, new BoolType);
}

TEST(Analysis, LogicalBinOps) {
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new BoolType), BinOp::AND, CreateMockExpr(new BoolType)),
		new BoolType);
	
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new BoolType), BinOp::OR, CreateMockExpr(new BoolType)),
		new BoolType);
}

TEST(Analysis, IllegalLogicalBinOps) {
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new IntType), BinOp::AND, CreateMockExpr(new IntType)), new VarType);
	TestType(CreateNode<BinOpExpr>(CreateMockExpr(new IntType), BinOp::OR, CreateMockExpr(new IntType)), new VarType);
}

TEST(Analysis, UnaryOps) {
	// INCREMENT, DECREMENT, MINUS, NOT, TILDE, TIMES, REFERENCE
	std::vector<std::pair<UnaryOp, UnaryOrder>> tests = {
		{UnaryOp::INCREMENT, UnaryOrder::PREFIX},
		{UnaryOp::DECREMENT, UnaryOrder::PREFIX},
		{UnaryOp::INCREMENT, UnaryOrder::POSTFIX},
		{UnaryOp::DECREMENT, UnaryOrder::POSTFIX},
		{UnaryOp::MINUS, UnaryOrder::POSTFIX},
		{UnaryOp::TILDE, UnaryOrder::POSTFIX},
	};
	
	for (auto pair : tests) {
		TestType({
			CreateNode<VarDeclExpr>("a", new IntType, nullptr),
			CreateNode<UnaryExpr>(pair.first, pair.second, CreateNode<ReferenceIDExpr>("a"))
		}, new IntType);
	}
	
	// test NOT, TIMES, REFERENCE
	TestType(
		CreateNode<UnaryExpr>(UnaryOp::NOT, UnaryOrder::PREFIX, CreateMockExpr(new BoolType)),
		new BoolType
	);
	
	TestType(
	    CreateNode<UnaryExpr>(UnaryOp::TIMES, UnaryOrder::PREFIX, CreateMockExpr(new PointerType(new IntType))),
	    new IntType
	);
	
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),
		CreateNode<UnaryExpr>(UnaryOp::REFERENCE, UnaryOrder::PREFIX, CreateNode<ReferenceIDExpr>("a")),
	}, new PointerType(new IntType));
}

TEST(Analysis, InvalidUnaryOps) {
	// INCREMENT/DECREMENT multiple times
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),
		CreateNode<UnaryExpr>(UnaryOp::INCREMENT, UnaryOrder::PREFIX, CreateNode<UnaryExpr>(
			UnaryOp::INCREMENT, UnaryOrder::PREFIX, CreateNode<ReferenceIDExpr>("a")
		)),
	}, new BuiltinType(VAR));
	
	TestType({
		CreateNode<VarDeclExpr>("a", new IntType, nullptr),
		CreateNode<UnaryExpr>(UnaryOp::DECREMENT, UnaryOrder::PREFIX, CreateNode<UnaryExpr>(
			UnaryOp::DECREMENT, UnaryOrder::PREFIX, CreateNode<ReferenceIDExpr>("a")
		)),
	}, new BuiltinType(VAR));
	
	// NOT on not-boolean
	TestType(CreateNode<UnaryExpr>(UnaryOp::NOT, UnaryOrder::PREFIX, CreateMockExpr(new IntType)),
		new BuiltinType(VAR));
	
	// TIMES on not-pointer
	TestType(
		CreateNode<UnaryExpr>(UnaryOp::TIMES, UnaryOrder::PREFIX, CreateMockExpr(new IntType)),
		new BuiltinType(VAR)
	);
	
	// REFERENCE on not-lvalue
	TestType(CreateNode<UnaryExpr>(UnaryOp::REFERENCE, UnaryOrder::PREFIX, CreateMockExpr(new IntType)),
		new BuiltinType(VAR));
}

TEST(Analysis, InvalidReturn) {
	// Test trying to return a void value.
	TestType(CreateNode<ReturnStmt>(CreateMockExpr(new BuiltinType(VOID))), new BuiltinType(VAR));
}

TEST(Analysis, FunctionDecl) {
	// Func Decl with type and multiple returns
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), new IntType,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new IntType));

	// Func Decl without type and one return
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new DoubleType));

	// Func Decl without type and multiple returns
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
			CreateNode<ReturnStmt>(CreateMockExpr(new IntType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new DoubleType));

	// Test using referencing parameter
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>({
			CreateNode<VarDeclExpr>("foo", new IntType, nullptr)
		}), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateNode<ReferenceIDExpr>("foo")),
		}))),
	}), new FunctionType(std::vector<Type*>({new IntType}), new IntType));
}

TEST(Analysis, InvalidFunctionDecls) {
	// Func Decl with type but missing return
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), new IntType,
			CreateNode<LongBlockExpr>()),
	}), new BuiltinType(VAR));

	// Test incompatible types
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), new PointerType(new IntType),
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new PointerType(new IntType))),
		}))),
	}), new BuiltinType(VAR));

	// Returning value with void function
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>("a", std::vector<VarDeclExpr*>(), new BuiltinType(VOID),
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new IntType)),
		}))),
	}), new BuiltinType(VAR));
}

TEST(Analysis, ExternFunctionDecl) {
	TestType(CreateNode<ExternFuncStmt>("a", std::vector<VarDeclExpr*>({
	    CreateNode<VarDeclExpr>("a", new IntType, nullptr),
	}), new DoubleType), new FunctionType(std::vector<Type*>({new IntType}), new DoubleType));
}

TEST(Analysis, CastExpr) {
	TestType(CreateNode<CastExpr>(new IntType, CreateMockExpr(new DoubleType)), new IntType);
}

TEST(Analysis, InvalidCastExpr) {
	TestType(CreateNode<CastExpr>(new BuiltinType(VOID), CreateMockExpr(new DoubleType)), new BuiltinType(VAR));
	TestType(CreateNode<CastExpr>(new IntType, CreateMockExpr(new BuiltinType(VOID))), new BuiltinType(VAR));
}

TEST(Analysis, ConditionalBlock) {
	TestType(CreateNode<ConditionalBlock>(
		CreateNode<MockExpr>(new BoolType),
		CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
	), new VoidType);
}

TEST(Analysis, InvalidConditionalBlock) {
	TestType(CreateNode<ConditionalBlock>(
		CreateNode<MockExpr>(new IntType),
		CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
	), new VarType);
}

TEST(Analysis, IfExpr) {
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<LongBlockExpr>()
		)
	})), new VoidType);
	
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		)
	})), new VoidType);
	
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new DoubleType))
		),
	})), new VoidType);
	
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new DoubleType))
		),
		CreateNode<ConditionalBlock>(
			nullptr,
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
	})), new VoidType);
}

TEST(Analysis, InvalidIfExprs) {
	// More than one condition-less block
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new DoubleType))
		),
		CreateNode<ConditionalBlock>(
			nullptr, CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
	    CreateNode<ConditionalBlock>(
			nullptr, CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
	})), new VarType);
	
	// Condition block after a condition-less block.
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			nullptr, CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new DoubleType))
		),
	})), new VarType);

	// Condition-less block first
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			nullptr, CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
	})), new VarType);

	// Value in one condition block but not others
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<LongBlockExpr>()
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new DoubleType))
		),
	})), new VoidType);

	// Incompatible value in one condition block
	TestType(CreateNode<IfExpr>(std::vector<ConditionalBlock*>({
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new IntType))
		),
		CreateNode<ConditionalBlock>(
			CreateNode<MockExpr>(new BoolType),
			CreateNode<ShortBlockExpr>(CreateNode<MockExpr>(new VoidType))
		),
	})), new VoidType);
}


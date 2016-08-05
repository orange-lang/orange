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

void TestType(std::vector<Node*> nodes, Type* target) {
	auto ast = CreateNode<LongBlockExpr>(nodes);

	MockDepthFirstWalker searchWalker(TraversalOrder::PREORDER);
	MockPredicateWalker predWalker;
	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>({ast}), &searchWalker, &predWalker);
	
	MockDepthFirstWalker walker(TraversalOrder::POSTORDER);
	
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

	delete ast;
	delete target;
}

void TestType(Node* node, Type* target) {
	MockDepthFirstWalker searchWalker(TraversalOrder::PREORDER);
	MockPredicateWalker predWalker;
	auto searcher = ASTSearcher(std::vector<LongBlockExpr*>(), &searchWalker, &predWalker);
	MockDepthFirstWalker walker(TraversalOrder::POSTORDER);
	
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

	delete node;
	delete target;
}

VarDeclExpr* CreateNamedVariable(std::string name, Expression* value) {
	return CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>(name) }),
		std::vector<Type*> ({ }),
		value
	);
}

VarDeclExpr* CreateTypedVariable(std::string name, Type* ty) {
	return CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>(name) }),
		std::vector<Type*> ({ ty }),
		nullptr
	);
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
	// typeless with value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ }),
		CreateMockExpr(new IntType)
	), new IntType);

	// type without value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new IntType }),
		nullptr
	), new IntType);

	// type with value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new IntType }),
		CreateMockExpr(new DoubleType)
	), new IntType);
}

TEST(Analysis, InvalidVarDecl) {
	// invalid name
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<AccessIDExpr>(
				CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b")
			)}),
			std::vector<Type*> ({ }),
			CreateMockExpr(new IntType)
		), nullptr);
	}, AnalysisMessage);
	
	// typeless without value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ }),
		nullptr
	), nullptr);

	// void type
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
		nullptr
	), nullptr);

	// void value
	TestType(CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<Type*> ({ new BuiltinType(BuiltinTypeKind::VOID) }),
		CreateMockExpr(new BuiltinType(VOID))
	), nullptr);
}

TEST(Analysis, VarDeclPair) {
	// TODO: remove expect throw when this feature is implemented
	EXPECT_THROW({
		TestType(CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a"), CreateNode<NamedIDExpr>("b") }),
			std::vector<Type*> ({ }),
			CreateMockExpr(new TupleType(std::vector<Type*>({new IntType, new DoubleType})))
		), new TupleType(std::vector<Type*>({ new IntType, new DoubleType })));
	}, AnalysisMessage);
}

TEST(Analysis, VarReference) {
	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),

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
		CreateNamedVariable("a", CreateMockExpr(new IntType)),

	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::PLUS_ASSIGN,
		    CreateMockExpr(new IntType)
	    )
	}, new IntType);

	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),
		
	    CreateNode<BinOpExpr>(
		    CreateNode<ReferenceIDExpr>("a"),
		    BinOp::TIMES_ASSIGN,
		    CreateMockExpr(new IntType)
	    ),
	}, new IntType);
}

TEST(Analysis, CompareBinOps) {
	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::GREATER_THAN,
			CreateNode<IntValue>(5)
		),
	}, new BoolType);

	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::LESS_THAN,
			CreateNode<DoubleValue>(52.932)
		),
	}, new BoolType);
}

TEST(Analysis, YieldStmt) {
	TestType(
		CreateNode<YieldStmt>(CreateMockExpr(new DoubleType)),
		new DoubleType
	);
}

TEST(Analysis, YieldInBlock) {
	// Single yield
	TestType(CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<YieldStmt>(CreateMockExpr(new DoubleType))
	})), new DoubleType);
	
	// Multiple yields
	TestType(CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<YieldStmt>(CreateMockExpr(new IntType)),
		CreateNode<YieldStmt>(CreateMockExpr(new DoubleType)),
		CreateNode<YieldStmt>(CreateMockExpr(new FloatType)),
	})), new DoubleType);
}

TEST(Analysis, ShortBlock) {
	// With expr
	TestType(CreateNode<ShortBlockExpr>(
		CreateMockExpr(new IntType)
	), new IntType);
	
	// Without expr
	TestType(CreateNode<ShortBlockExpr>(
		CreateNode<ExprStmt>(CreateMockExpr(new DoubleType))
	), new BuiltinType(VOID));
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
			CreateNamedVariable("a", CreateNode<IntValue>(52)),
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
		CreateNamedVariable("a", CreateMockExpr(new IntType)),
		CreateNode<UnaryExpr>(UnaryOp::REFERENCE, UnaryOrder::PREFIX, CreateNode<ReferenceIDExpr>("a")),
	}, new PointerType(new IntType));
}

TEST(Analysis, InvalidUnaryOps) {
	// INCREMENT/DECREMENT multiple times
	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),
		CreateNode<UnaryExpr>(UnaryOp::INCREMENT, UnaryOrder::PREFIX, CreateNode<UnaryExpr>(
			UnaryOp::INCREMENT, UnaryOrder::PREFIX, CreateNode<ReferenceIDExpr>("a")
		)),
	}, new BuiltinType(VAR));
	
	TestType({
		CreateNamedVariable("a", CreateMockExpr(new IntType)),
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
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), new IntType,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new IntType));

	// Func Decl without type and one return
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new DoubleType));

	// Func Decl without type and multiple returns
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new DoubleType)),
			CreateNode<ReturnStmt>(CreateMockExpr(new IntType)),
		}))),
	}), new FunctionType(std::vector<Type*>(), new DoubleType));

	// Test using referencing parameter
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>({
			CreateTypedVariable("foo", new IntType)
		}), nullptr,
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateNode<ReferenceIDExpr>("foo")),
		}))),
	}), new FunctionType(std::vector<Type*>({new IntType}), new IntType));
}

TEST(Analysis, InvalidFunctionDecls) {
	// Func Decl with type but missing return
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), new IntType,
			CreateNode<LongBlockExpr>()),
	}), new BuiltinType(VAR));

	// Test incompatible types
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), new PointerType(new IntType),
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new PointerType(new IntType))),
		}))),
	}), new BuiltinType(VAR));

	// Returning value with void function
	TestType(std::vector<Node*>({
		CreateNode<FunctionExpr>(CreateNode<NamedIDExpr>("a"), nullptr, std::vector<VarDeclExpr*>(), new BuiltinType(VOID),
		CreateNode<LongBlockExpr>(std::vector<Node*>({
			CreateNode<ReturnStmt>(CreateMockExpr(new IntType)),
		}))),
	}), new BuiltinType(VAR));
}
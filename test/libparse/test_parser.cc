//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <sstream>
#include <map>
#include <gtest/gtest.h>

#include <libast/ast.h>
#include <libast/type.h>
#include <libparse/parser.h>

#include "parser-private.h"
#include "helpers.h"

using namespace orange::ast;
using namespace orange::parser;

void TestAST(std::string str, std::vector<Node*> expectedNodes) {
	auto expected = CreateNode<LongBlockExpr>(expectedNodes);

	std::stringstream ss(str);
	Parser p(ss);

	LongBlockExpr* ast = nullptr;

	ASSERT_NO_THROW({
		ast = p.parse();
	});

	ASSERT_TRUE(ast != nullptr);

	assertEqAST(expected, ast);

	delete ast;
	delete expected;
}

TEST(Parser, ParsesNothing) { 
	TestAST("", {});
}

TEST(Parser, ParsesNothingButTerms) { 
	TestAST(R"(
		;;;

			;
		;
		;
	)", {}); 
}

TEST(Parser, ParsesEmptyBlock) {
       TestAST("{}", { new LongBlockExpr });
}

TEST(Parser, ParsesLongBlockNothingButTerms) { 
	TestAST(R"({
		;;;

			;
		;
		;
	})", { new LongBlockExpr });
}

TEST(Parser, ParsesBooleans) { 
	TestAST(R"({
		false
		true
	})", {
		new LongBlockExpr(std::vector<Node*>({
			new BoolValue(false),
		    new BoolValue(true)
		}))
	});
}

TEST(Parser, ParsesLongBlockSimpleExpression) { 
	TestAST(R"({
		3
	})", {
		new LongBlockExpr(std::vector<Node*>({
			new IntValue(3)
		}))
	});
}

TEST(Parser, ParsesLongBlockSimpleExpressionOneLine) { 
	TestAST("{ 3 }", {
		new LongBlockExpr(std::vector<Node*>({
			new IntValue(3)
		}))
	});
}

TEST(Parser, ParsesBasicVarDecl) { 
	TestAST("var a", {
		new VarDeclExpr("a", nullptr, nullptr)
	});
}

TEST(Parser, ParsesBasicVarDeclWithValue) { 
	TestAST(R"(
		var a = 5
	)", {
		new VarDeclExpr("a", nullptr, new IntValue(5))
	});
}

TEST(Parser, ParsesTypedVarDecl) {
	TestAST(R"(
		var a: int
	)", {
		new VarDeclExpr("a", new IntType, nullptr)
	});
}

TEST(Parser, ParsesBasicTypes) {
	std::map<std::string, BuiltinTypeKind> BasicTypes = {
		{"int", BuiltinTypeKind::INT},
		{"int8", BuiltinTypeKind::INT8},
		{"int16", BuiltinTypeKind::INT16},
		{"int32", BuiltinTypeKind::INT32},
		{"int64", BuiltinTypeKind::INT64},
		{"uint", BuiltinTypeKind::UINT},
		{"uint8", BuiltinTypeKind::UINT8},
		{"uint16", BuiltinTypeKind::UINT16},
		{"uint32", BuiltinTypeKind::UINT32},
		{"uint64", BuiltinTypeKind::UINT64},
		{"float", BuiltinTypeKind::FLOAT},
		{"double", BuiltinTypeKind::DOUBLE},
		{"char", BuiltinTypeKind::CHAR},
		{"var", BuiltinTypeKind::VAR},
		{"void", BuiltinTypeKind::VOID}
	};

	for (auto kvp : BasicTypes) {
		std::stringstream ss;
		ss << "var a: " << kvp.first;

		TestAST(ss.str(), {
			new VarDeclExpr("a", new BuiltinType(kvp.second), nullptr)
		});
	}
}

TEST(Parser, ParsesAccessType) { 
	TestAST(R"(
		var a: Foo.Bar.Baz
	)", {
		new VarDeclExpr(
			"a",
			new AccessType(
				new AccessType(
					new IdentifierType(new ReferenceIDExpr("Foo")),
					new IdentifierType(new ReferenceIDExpr("Bar"))
				),
				new IdentifierType(new ReferenceIDExpr("Baz"))
			),
			nullptr
		)
	});
}

TEST(Parser, ParsesIdentifierType) { 
	TestAST(R"(
		var a: Foo
	)", {
		new VarDeclExpr(
			"a", new IdentifierType(new ReferenceIDExpr("Foo")), nullptr
		)
	});
}

TEST(Parser, ParsesArrayType) { 
	TestAST(R"(
		var a: Foo[5][3]
	)", {
		new VarDeclExpr(
			"a",
			new ArrayType(
				new ArrayType(
					new IdentifierType(new ReferenceIDExpr("Foo")),
					new IntValue(5)
				),
				new IntValue(3)
			),
			nullptr
		)
	});
}

TEST(Parser, ParsesPointerType) { 
	TestAST(R"(
		var a: Foo**
	)", {
		new VarDeclExpr(
			"a",
			new PointerType(
				new PointerType(
					new IdentifierType(new ReferenceIDExpr("Foo"))
				)
			),
			nullptr
		)
	});
}

TEST(Parser, ParsesFunctionType) {
	TestAST(R"(
		var a: (int,double) -> Foo
	)", {
		new VarDeclExpr(
			"a",
			new FunctionType(
				std::vector<Type*>({
					new BuiltinType(BuiltinTypeKind::INT),
					new BuiltinType(BuiltinTypeKind::DOUBLE)
				}),
				new IdentifierType(new ReferenceIDExpr("Foo"))
			),
			nullptr
		)
	});
}

TEST(Parser, ParsesComplexType) { 
	TestAST(R"(
		var a: int*[5]*
	)", {
		new VarDeclExpr(
			"a",
			new PointerType(
				new ArrayType(
					new PointerType(
						new BuiltinType(BuiltinTypeKind::INT)
					),
					new IntValue(5)
				)
			),
			nullptr
		)
	});
}

TEST(Parser, ParsesArrayOfFunctionType) { 
	TestAST(R"(
		var a: ((int,double) -> Foo)[5]
	)", {
		new VarDeclExpr(
			"a",
			new ArrayType(
				new FunctionType(
					std::vector<Type*>({
						new BuiltinType(BuiltinTypeKind::INT),
						new BuiltinType(BuiltinTypeKind::DOUBLE)
					}),
					new IdentifierType(new ReferenceIDExpr("Foo"))
				),
				new IntValue(5)
			),
			nullptr
		)
	});
}

TEST(Parser, TestNamespace) { 
	TestAST(R"(
		namespace Foo
	)", {
		new NamespaceStmt(
			new NamedIDExpr("Foo"),
			nullptr
		)
	});
}

TEST(Parser, TestNamespaceLong) { 
	TestAST(R"(
		namespace Foo.Bar.Baz
	)", {
		new NamespaceStmt(
			new AccessIDExpr(
				new AccessIDExpr(
					new NamedIDExpr("Foo"),
					new NamedIDExpr("Bar")
				),
				new NamedIDExpr("Baz")
			),
			nullptr
		)
	});
}

TEST(Parser, TestNamespaceBlock) { 
	TestAST(R"(
		namespace Foo {

		}
	)", {
		new NamespaceStmt(
			new NamedIDExpr("Foo"),
			new LongBlockExpr()
		)
	});
}

TEST(Parser, TestNamespaceLongBlock) { 
	TestAST(R"(
		namespace Foo.Bar.Baz {

	}
	)", {
		new NamespaceStmt(
			new AccessIDExpr(
				new AccessIDExpr(
					new NamedIDExpr("Foo"),
					new NamedIDExpr("Bar")
				),
				new NamedIDExpr("Baz")
			),
			new LongBlockExpr()
		)
	});
}

TEST(Parser, TestFlags) {
	std::stringstream ss(R"(
		virtual public private protected partial def foo() { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			"foo",
			std::vector<VarDeclExpr*>(),
			nullptr,
			new LongBlockExpr()
		)
	}));

	FunctionExpr* fnExpr = (FunctionExpr*)expected.statements[0];
	fnExpr->flags.push_back(new VirtualFlag());
	fnExpr->flags.push_back(new PrivacyFlag(PrivacyLevel::PUBLIC));
	fnExpr->flags.push_back(new PrivacyFlag(PrivacyLevel::PRIVATE));
	fnExpr->flags.push_back(new PrivacyFlag(PrivacyLevel::PROTECTED));
	fnExpr->flags.push_back(new PartialFlag());

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestEmptyEnum) { 
	TestAST(R"(
		enum Status { }
	)", {
		new EnumStmt(
			new NamedIDExpr("Status"),
			std::vector<EnumValue*>()
		)
	});
}

TEST(Parser, TestEnumBasicValues) { 
	TestAST(R"(
		enum Status {
			PENDING,
			RUNNING,
			COMPLETED
	}
	)", {
		new EnumStmt(
			new NamedIDExpr("Status"),
			std::vector<EnumValue*>({
				new EnumValue(
					new NamedIDExpr("PENDING"), std::vector<VarDeclExpr*>()
				),
				new EnumValue(
					new NamedIDExpr("RUNNING"), std::vector<VarDeclExpr*>()
				),
				new EnumValue(
					new NamedIDExpr("COMPLETED"), std::vector<VarDeclExpr*>()
				)
			})
		)
	});
}

TEST(Parser, TestEnumWithData) { 
	TestAST(R"(
		enum Status {
			PENDING,
			RUNNING(time:int),
			COMPLETED(time,completed:double)
	}
	)", {
		new EnumStmt(
			new NamedIDExpr("Status"),
			std::vector<EnumValue*>({
				new EnumValue(
					new NamedIDExpr("PENDING"), std::vector<VarDeclExpr*>()
				),
				new EnumValue(
					new NamedIDExpr("RUNNING"),
					std::vector<VarDeclExpr*>({
						new VarDeclExpr("time", new IntType, nullptr)
					})
				),
				new EnumValue(
					new NamedIDExpr("COMPLETED"),
					std::vector<VarDeclExpr*>({
						new VarDeclExpr("time", nullptr, nullptr),
						new VarDeclExpr("completed", new DoubleType, nullptr)
					})
				)
			})
		)
	});
}

TEST(Parser, Interface) { 
	TestAST(R"(
		interface Foo {
			def foo() -> void
			def bar(a:int,b:int) -> int
		}
	)", {
		new InterfaceStmt(new NamedIDExpr("Foo"), new LongBlockExpr(std::vector<Node*>({
			new ExternFuncStmt(
				"foo",
				std::vector<VarDeclExpr*>(),
				new BuiltinType(BuiltinTypeKind::VOID)
			),
			new ExternFuncStmt(
				"bar",
				std::vector<VarDeclExpr*>({
					new VarDeclExpr("a", new IntType, nullptr),
					new VarDeclExpr("b", new IntType, nullptr),
				}),
				new IntType
			)
		})))
	});
}

TEST(Parser, ParsesClass) { 
	TestAST(R"(
		class MyClass : Base1, Foo.Bar, Base2 {
			var a
			var a: int

			class NestedClass { }
			def foo() { }
			extern def foo() -> int
			import Foo

			enum NestedEnum { }
		}
	)", {
		new ClassStmt(
			new NamedIDExpr("MyClass"),
			std::vector<Identifier*>({
				new NamedIDExpr("Base1"),
				new AccessIDExpr(
					new NamedIDExpr("Foo"),
					new NamedIDExpr("Bar")
				),
				new NamedIDExpr("Base2")
			}),
			new LongBlockExpr(std::vector<Node*>({
				new VarDeclExpr("a", nullptr, nullptr),
				new VarDeclExpr("a", new IntType, nullptr),
				new ClassStmt(
					new NamedIDExpr("NestedClass"),
					std::vector<Identifier*>(),
					new LongBlockExpr()
				),
				new FunctionExpr("foo", std::vector<VarDeclExpr*>(), nullptr, new LongBlockExpr),
				new ExternFuncStmt(
					"foo",
					std::vector<VarDeclExpr*>(),
					new BuiltinType(BuiltinTypeKind::INT)
				),
				new ImportStmt(new NamedIDExpr("Foo")),
				new EnumStmt(
					new NamedIDExpr("NestedEnum"),
					std::vector<EnumValue*>()
				)
			}))
		)
	});
}

TEST(Parser, ClassMemberPrivacy) { 
	TestAST(R"(
		class MyClass {
			private var a: int
		}
	)", {
		new ClassStmt(
			new NamedIDExpr("MyClass"),
			std::vector<Identifier*>({ }),
			new LongBlockExpr(std::vector<Node*>({
				new VarDeclExpr("a", new IntType, nullptr)
			}))
		)
	});
}

TEST(Parser, BasicFunction) { 
	TestAST(R"(
		def foo() { }
	)", {
		new FunctionExpr("foo", std::vector<VarDeclExpr*>(), nullptr, new LongBlockExpr())
	});
}

TEST(Parser, BasicFunctionParameterImplicit) { 
	TestAST(R"(
		def foo(a) { }
	)", {
		new FunctionExpr(
			"foo",
			std::vector<VarDeclExpr*>({
				new VarDeclExpr("a", nullptr, nullptr)
			}),
			nullptr,
			new LongBlockExpr()
		)
	});
}

TEST(Parser, BasicFunctionParameterExplicit) { 
	TestAST(R"(
		def foo(a:int) { }
	)", {
		new FunctionExpr(
			"foo",
			std::vector<VarDeclExpr*>({
				new VarDeclExpr("a", new IntType, nullptr)
			}),
			nullptr,
			new LongBlockExpr()
		)
	});
}

TEST(Parser, BasicFunctionParameterMixed) { 
	TestAST(R"(
		def foo(a,a:int) { }
	)", {
		new FunctionExpr(
			"foo",
			std::vector<VarDeclExpr*>({
				new VarDeclExpr("a", nullptr, nullptr),
				new VarDeclExpr("a", new IntType, nullptr),
			}),
			nullptr,
			new LongBlockExpr()
		)
	});
}

TEST(Parser, BasicFunctionParameterMixedReturn) { 
	TestAST(R"(
		def foo(a,a:int) -> void { }
	)", {
		new FunctionExpr(
			"foo",
			std::vector<VarDeclExpr*>({
				new VarDeclExpr("a", nullptr, nullptr),
				new VarDeclExpr("a", new IntType, nullptr),
			}),
			new BuiltinType(BuiltinTypeKind::VOID),
			new LongBlockExpr()
		)
	});
}

TEST(Parser, BasicValue) { 
	TestAST(R"(
		0xF00u64
	)", {
		new UIntValue(0xF00, new BuiltinType(BuiltinTypeKind::UINT64))
	});
}

TEST(Parser, BasicVarRef) { 
	TestAST(R"(
		a
	)", {
		new ReferenceIDExpr("a")
	});
}

TEST(Parser, MultExprsOneLine) { 
	TestAST(R"(
		3; 3; 3
	)", {
		new IntValue(3),
		new IntValue(3),
		new IntValue(3)
	});
}

TEST(Parser, UnaryOperations) { 
	TestAST(R"(
		++a; --a; *a; &a
	)", {
		new UnaryExpr(UnaryOp::INCREMENT, UnaryOrder::PREFIX, new ReferenceIDExpr("a")),
		new UnaryExpr(UnaryOp::DECREMENT, UnaryOrder::PREFIX, new ReferenceIDExpr("a")),
		new UnaryExpr(UnaryOp::TIMES, UnaryOrder::PREFIX, new ReferenceIDExpr("a")),
		new UnaryExpr(UnaryOp::REFERENCE, UnaryOrder::PREFIX, new ReferenceIDExpr("a")),
	});
}

TEST(Parser, FunctionCall) { 
	TestAST(R"(
		a(1,2)
	)", {
		new FunctionCallExpr(
			new ReferenceIDExpr("a"),
			std::vector<Expression*>({
				new IntValue(1),
				new IntValue(2)
			})
		)
	});
}

TEST(Parser, ArrayAccess) { 
	TestAST(R"(
		a[5]
	)", {
		new ArrayAccessExpr(
			new ReferenceIDExpr("a"),
			new IntValue(5)
		)
	});
}

TEST(Parser, MemberAccess) { 
	TestAST(R"(
		a.b.c
	)", {
		new MemberAccessExpr(
			new MemberAccessExpr(
				new ReferenceIDExpr("a"),
				new ReferenceIDExpr("b")
			),
			new ReferenceIDExpr("c")
		)
	});
}

TEST(Parser, ComplexUnaryMod) { 
	TestAST(R"(
		a[1].b[2].c
	)", {
		new MemberAccessExpr(
			new ArrayAccessExpr(
				new MemberAccessExpr(
					new ArrayAccessExpr(
						new ReferenceIDExpr("a"),
						new IntValue(1)
					),
					new ReferenceIDExpr("b")
				),
				new IntValue(2)
			),
			new ReferenceIDExpr("c")
		)
	});
}

TEST(Parser, BinOpNewline) { 
	TestAST(R"(
		1
		-3
	)", {
		new IntValue(1),
		new UnaryExpr(UnaryOp::MINUS, UnaryOrder::PREFIX, new IntValue(3))
	});
}

TEST(Parser, TestBinaryExpr) { 
	TestAST(R"(
		1 + (2 - 3) * 4
	)", {
		new BinOpExpr(
			new IntValue(1),
			BinOp::ADD,
			new BinOpExpr(
				new BinOpExpr(new IntValue(2), BinOp::SUBTRACT, new IntValue(3)),
				BinOp::MULTIPLY,
				new IntValue(4)
			)
		)
	});
}

TEST(Parser, TestTernaryExpr) { 
	TestAST(R"(
		a = 1 + 2 ? 3 * 4 : 5 * 6
	)", {
		new BinOpExpr(
			new ReferenceIDExpr("a"),
			BinOp::ASSIGN,
			new TernaryExpr(
				new BinOpExpr(new IntValue(1), BinOp::ADD, new IntValue(2)),
				new BinOpExpr(new IntValue(3), BinOp::MULTIPLY, new IntValue(4)),
				new BinOpExpr(new IntValue(5), BinOp::MULTIPLY, new IntValue(6))
			)
		)
	});
}

TEST(Parser, This) { 
	TestAST(R"(
		this.a = 5
	)", {
		new BinOpExpr(
			new MemberAccessExpr(
				new ThisID(), new ReferenceIDExpr("a")
			),
			BinOp::ASSIGN,
			new IntValue(5)
		)
	});
}

TEST(Parser, New) { 
	TestAST(R"(
		new Foo.Bar
	)", {
		new NewExpr(
			new MemberAccessExpr(
				new ReferenceIDExpr("Foo"),
				new ReferenceIDExpr("Bar")
			)
		)
	});
}

TEST(Parser, EmptyArray) { 
	TestAST(R"(
		[]
	)", {
		new ArrayExpr()
	});
}

TEST(Parser, SingleElementArray) { 
	TestAST(R"(
		[1]
	)", {
		new ArrayExpr(std::vector<Expression*>({
			new IntValue(1)
		}))
	});
}

TEST(Parser, MultipleElementArray) { 
	TestAST(R"(
		[1, 2, 3, 4]
	)", {
		new ArrayExpr(std::vector<Expression*>({
			new IntValue(1), new IntValue(2), new IntValue(3), new IntValue(4)
		}))
	});
}

TEST(Parser, NestedArray) { 
	TestAST(R"(
		[[1,2],[3,4]]
	)", {
		new ArrayExpr(std::vector<Expression*>({
			new ArrayExpr(std::vector<Expression*>({
				new IntValue(1), new IntValue(2)
			})),
			new ArrayExpr(std::vector<Expression*>({
				new IntValue(3), new IntValue(4)
			}))
		}))
	});
}

TEST(Parser, TestIfs) {
	TestAST(R"(
		if (1) { }

		if (2) { }
		elif (3) { }
		elif (4) { }

		if (5) { }
		else { }

		if (6) { }
		elif (7) { }
		else { }
	)", {
		new IfExpr(std::vector<ConditionalBlock*>({
			new ConditionalBlock(new IntValue(1), new LongBlockExpr())
		})),
		new IfExpr(std::vector<ConditionalBlock*>({
			new ConditionalBlock(new IntValue(2), new LongBlockExpr()),
			new ConditionalBlock(new IntValue(3), new LongBlockExpr()),
			new ConditionalBlock(new IntValue(4), new LongBlockExpr())
		})),
		new IfExpr(std::vector<ConditionalBlock*>({
			new ConditionalBlock(new IntValue(5), new LongBlockExpr()),
			new ConditionalBlock(nullptr, new LongBlockExpr())
		})),
		new IfExpr(std::vector<ConditionalBlock*>({
			new ConditionalBlock(new IntValue(6), new LongBlockExpr()),
			new ConditionalBlock(new IntValue(7), new LongBlockExpr()),
			new ConditionalBlock(nullptr, new LongBlockExpr())
		}))
	});
}

TEST(Parser, Loops) { 
	TestAST(R"(
		for (;;) { }
		for (a;b;c) { }
		for (var a;b;c) { }
		while (a) { }
		forever { }
		do { } while (a)
	)", {
		new LoopStmt(
			nullptr, nullptr, nullptr, LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			new ReferenceIDExpr("a"), new ReferenceIDExpr("b"), new ReferenceIDExpr("c"),
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			new VarDeclExpr("a", nullptr, nullptr), new ReferenceIDExpr("b"), new ReferenceIDExpr("c"),
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			nullptr, new ReferenceIDExpr("a"), nullptr,
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			nullptr, nullptr, nullptr,
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			nullptr, new ReferenceIDExpr("a"), nullptr,
			LoopConditionCheck::AFTER, new LongBlockExpr()
		)
	});
}

TEST(Parser, ControlStatements) {
	TestAST(R"(
		break; continue;
	)", {
		new BreakStmt(), new ContinueStmt,
	});
}

TEST(Parser, Delete) { 
	TestAST(R"(
		delete a
	)", {
		new DeleteStmt(new ReferenceIDExpr("a"))
	});
}

TEST(Parser, TryCatches) { 
	TestAST(R"(
		try { }
		catch (var a: int) { }
		catch (var b: int) { }
		finally { }
	)", {
		new TryExpr(
			new LongBlockExpr(),
			std::vector<CatchBlock*>({
				new CatchBlock(
					new VarDeclExpr("a", new IntType, nullptr), new LongBlockExpr()
				),
				new CatchBlock(
					new VarDeclExpr("b", new IntType, nullptr), new LongBlockExpr()
				)
			}),
			new LongBlockExpr()
		)
	});
}

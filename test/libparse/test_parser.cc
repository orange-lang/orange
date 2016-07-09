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

TEST(Parser, ParsesMultipleTypedVarDeclWithValue) {
	std::stringstream ss(R"(
		var (a, b): int, double = 5
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
			new IntValue(5)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
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

		Parser p(ss);

		auto ast = p.parse();
		EXPECT_TRUE(ast != nullptr);

		LongBlockExpr expected(std::vector<Node*>({
			new VarDeclExpr(
				std::vector<Identifier*>({
					new NamedIDExpr("a")
				}),
				std::vector<Type*>({
					new BuiltinType(kvp.second),
				}),
				nullptr
			)
		}));

		assertEqAST(&expected, ast);
		delete ast;
	}
}

TEST(Parser, ParsesAccessType) {
	std::stringstream ss(R"(
		var a: Foo.Bar.Baz
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
				new AccessType(
					new AccessType(
						new IdentifierType(new NamedIDExpr("Foo")),
						new IdentifierType(new NamedIDExpr("Bar"))
					),
					new IdentifierType(new NamedIDExpr("Baz"))
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesIdentifierType) {
	std::stringstream ss(R"(
		var a: Foo
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
				new IdentifierType(new NamedIDExpr("Foo"))
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesArrayType) {
	std::stringstream ss(R"(
		var a: Foo[5][3]
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
				new ArrayType(
					new ArrayType(
						new IdentifierType(new NamedIDExpr("Foo")),
						new IntValue(5)
					),
					new IntValue(3)
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesPointerType) {
	std::stringstream ss(R"(
		var a: Foo**
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
				new PointerType(
					new PointerType(
						new IdentifierType(new NamedIDExpr("Foo"))
					)
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesReferenceType) {
	std::stringstream ss(R"(
		var a: Foo&&
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
				new ReferenceType(
					new ReferenceType(
						new IdentifierType(new NamedIDExpr("Foo"))
					)
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesTypeInParens) {
	std::stringstream ss(R"(
		var a: (int)
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

TEST(Parser, ParsesTupleType) {
	std::stringstream ss(R"(
		var a: (int,)
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
				new TupleType(std::vector<Type*>({
					new BuiltinType(BuiltinTypeKind::INT)
				}))
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParseMultipleTupleType) {
	std::stringstream ss(R"(
		var a: (int,double)
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
				new TupleType(std::vector<Type*>({
					new BuiltinType(BuiltinTypeKind::INT),
					new BuiltinType(BuiltinTypeKind::DOUBLE)
				}))
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParseMultipleTupleTypeTrailingComma) {
	std::stringstream ss(R"(
		var a: (int,double,)
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
				new TupleType(std::vector<Type*>({
					new BuiltinType(BuiltinTypeKind::INT),
					new BuiltinType(BuiltinTypeKind::DOUBLE)
				}))
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesFunctionType) {
	std::stringstream ss(R"(
		var a: (int,double) -> Foo
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
				new FunctionType(
					std::vector<Type*>({
						new BuiltinType(BuiltinTypeKind::INT),
						new BuiltinType(BuiltinTypeKind::DOUBLE)
					}),
					new IdentifierType(new NamedIDExpr("Foo"))
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesComplexType) {
	std::stringstream ss(R"(
		var a: int*[5]&
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
				new ReferenceType(
					new ArrayType(
						new PointerType(
							new BuiltinType(BuiltinTypeKind::INT)
						),
						new IntValue(5)
					)
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}
TEST(Parser, ParsesArrayOfFunctionType) {
	std::stringstream ss(R"(
		var a: ((int,double) -> Foo)[5]
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
				new ArrayType(
					new FunctionType(
						std::vector<Type*>({
							new BuiltinType(BuiltinTypeKind::INT),
							new BuiltinType(BuiltinTypeKind::DOUBLE)
						}),
						new IdentifierType(new NamedIDExpr("Foo"))
					),
					new IntValue(5)
				)
			}),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestNamespace) {
	std::stringstream ss(R"(
		namespace Foo
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new NamespaceStmt(
			new NamedIDExpr("Foo"),
			nullptr
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestNamespaceLong) {
	std::stringstream ss(R"(
		namespace Foo.Bar.Baz
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
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
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestNamespaceBlock) {
	std::stringstream ss(R"(
		namespace Foo {

		}
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new NamespaceStmt(
			new NamedIDExpr("Foo"),
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestNamespaceLongBlock) {
	std::stringstream ss(R"(
		namespace Foo.Bar.Baz {

        }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
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
	}));

	assertEqAST(&expected, ast);
	delete ast;
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
			new NamedIDExpr("foo"),
			nullptr,
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
	std::stringstream ss(R"(
		enum Status { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new EnumStmt(
			new NamedIDExpr("Status"),
			std::vector<EnumValue*>()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestEnumBasicValues) {
	std::stringstream ss(R"(
		enum Status {
			PENDING,
			RUNNING,
			COMPLETED
        }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
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
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestEnumWithData) {
	std::stringstream ss(R"(
		enum Status {
			PENDING,
			RUNNING(time:int),
			COMPLETED(time,completed:double)
        }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new EnumStmt(
			new NamedIDExpr("Status"),
			std::vector<EnumValue*>({
				new EnumValue(
					new NamedIDExpr("PENDING"), std::vector<VarDeclExpr*>()
				),
				new EnumValue(
					new NamedIDExpr("RUNNING"),
					std::vector<VarDeclExpr*>({
						new VarDeclExpr(
							std::vector<Identifier*>({new NamedIDExpr("time")}),
							std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}),
							nullptr
						)
					})
				),
				new EnumValue(
					new NamedIDExpr("COMPLETED"),
					std::vector<VarDeclExpr*>({
						new VarDeclExpr(
							std::vector<Identifier*>({new NamedIDExpr("time")}),
							std::vector<Type*>(),
							nullptr
						),
						new VarDeclExpr(
							std::vector<Identifier*>({new NamedIDExpr("completed")}),
							std::vector<Type*>({new BuiltinType(BuiltinTypeKind::DOUBLE)}),
							nullptr
						)
					})
				)
			})
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ParsesClass) {
	std::stringstream ss(R"(
		class MyClass : Base1, Foo.Bar, Base2 {
			var a
			var a: int

			class NestedClass { }
			def foo() { }
			aggregate { }
			extern def foo() -> int
			import Foo
			extend Foo { }

			property Foo: a
			property Foo -> int {
				get: a
				set: a
			}

			enum NestedEnum { }
		}
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
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
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>(), nullptr
				),
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}),
					nullptr
				),
			    new ClassStmt(
				    new NamedIDExpr("NestedClass"),
				    std::vector<Identifier*>(),
				    new LongBlockExpr()
			    ),
			    new FunctionExpr(
				    new NamedIDExpr("foo"),
				    nullptr,
				    std::vector<VarDeclExpr*>(),
				    nullptr,
				    new LongBlockExpr()
			    ),
			    new AggregateStmt(nullptr, new LongBlockExpr),
			    new ExternFuncStmt(
				    new NamedIDExpr("foo"),
				    std::vector<VarDeclExpr*>(),
				    new BuiltinType(BuiltinTypeKind::INT)
			    ),
			    new ImportStmt(new NamedIDExpr("Foo")),
			    new ExtendStmt(
				    new NamedIDExpr("Foo"),
				    std::vector<Identifier*>(),
				    new LongBlockExpr()
			    ),
				new PropertyStmt(
					new NamedIDExpr("Foo"),
					nullptr,
					new ShortBlockExpr(new NamedIDExpr("a"))
				),
				new PropertyStmt(
					new NamedIDExpr("Foo"),
					new BuiltinType(BuiltinTypeKind::INT),
					new LongBlockExpr(std::vector<Node*>({
						new GetterStmt(new ShortBlockExpr(new NamedIDExpr("a"))),
						new SetterStmt(new ShortBlockExpr(new NamedIDExpr("a")))
					}))
				),
			    new EnumStmt(
				    new NamedIDExpr("NestedEnum"),
				    std::vector<EnumValue*>()
			    )
			}))
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ClassMemberPrivacy) {
	std::stringstream ss(R"(
		class MyClass {
			private var a: int
		}
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ClassStmt(
			new NamedIDExpr("MyClass"),
			std::vector<Identifier*>({ }),
			new LongBlockExpr(std::vector<Node*>({
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}),
					nullptr
				)
			}))
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicFunction) {
	std::stringstream ss(R"(
		def foo() { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			new NamedIDExpr("foo"),
			nullptr,
			std::vector<VarDeclExpr*>(),
			nullptr,
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicFunctionParameterImplicit) {
	std::stringstream ss(R"(
		def foo(a) { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			new NamedIDExpr("foo"),
			nullptr,
			std::vector<VarDeclExpr*>({
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>(), nullptr
				)
			}),
			nullptr,
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicFunctionParameterExplicit) {
	std::stringstream ss(R"(
		def foo(a:int) { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			new NamedIDExpr("foo"),
			nullptr,
			std::vector<VarDeclExpr*>({
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}), nullptr
				)
			}),
			nullptr,
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicFunctionParameterMixed) {
	std::stringstream ss(R"(
		def foo(a,a:int) { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			new NamedIDExpr("foo"),
			nullptr,
			std::vector<VarDeclExpr*>({
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>(), nullptr
				),
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}), nullptr
				)
			}),
			nullptr,
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicFunctionParameterMixedReturn) {
	std::stringstream ss(R"(
		def foo(a,a:int) -> void { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionExpr(
			new NamedIDExpr("foo"),
			nullptr,
			std::vector<VarDeclExpr*>({
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>(), nullptr
				),
				new VarDeclExpr(
					std::vector<Identifier*>({new NamedIDExpr("a")}),
					std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}), nullptr
				)
			}),
			new BuiltinType(BuiltinTypeKind::VOID),
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicValue) {
	std::stringstream ss(R"(
		0xF00u64
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new UIntValue(0xF00, new BuiltinType(BuiltinTypeKind::UINT64))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, BasicVarRef) {
	std::stringstream ss(R"(
		a
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new NamedIDExpr("a")
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, MultExprsOneLine) {
	std::stringstream ss(R"(
		3; 3; 3
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new IntValue(3),
		new IntValue(3),
		new IntValue(3)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, UnaryOperations) {
	std::stringstream ss(R"(
		++a; --a; *a; &a
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new UnaryExpr(UnaryOp::INCREMENT, UnaryOrder::PREFIX, new NamedIDExpr("a")),
		new UnaryExpr(UnaryOp::DECREMENT, UnaryOrder::PREFIX, new NamedIDExpr("a")),
		new UnaryExpr(UnaryOp::TIMES, UnaryOrder::PREFIX, new NamedIDExpr("a")),
		new UnaryExpr(UnaryOp::REFERENCE, UnaryOrder::PREFIX, new NamedIDExpr("a")),
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, FunctionCall) {
	std::stringstream ss(R"(
		a(1,2)
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionCallExpr(
			new NamedIDExpr("a"),
			std::vector<Expression*>({
				new IntValue(1),
				new IntValue(2)
			})
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ArrayAccess) {
	std::stringstream ss(R"(
		a[5]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayAccessExpr(
			new NamedIDExpr("a"),
			new IntValue(5)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, MemberAccess) {
	std::stringstream ss(R"(
		a.b.c
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new MemberAccessExpr(
			new MemberAccessExpr(
				new NamedIDExpr("a"),
				new NamedIDExpr("b")
			),
			new NamedIDExpr("c")
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ComplexUnaryMod) {
	std::stringstream ss(R"(
		a[1].b[2].c
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	// ((a[1].b)[2]).c
	LongBlockExpr expected(std::vector<Node*>({
		new MemberAccessExpr(
			new ArrayAccessExpr(
				new MemberAccessExpr(
					new ArrayAccessExpr(
						new NamedIDExpr("a"),
						new IntValue(1)
					),
					new NamedIDExpr("b")
				),
				new IntValue(2)
			),
			new NamedIDExpr("c")
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestBinaryExpr) {
	std::stringstream ss(R"(
		1 + (2 + 3) * 4
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BinOpExpr(
			new IntValue(1),
			BinOp::ADD,
			new BinOpExpr(
				new BinOpExpr(new IntValue(2), BinOp::ADD, new IntValue(3)),
				BinOp::MULTIPLY,
				new IntValue(4)
			)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestTenaryExpr) {
	std::stringstream ss(R"(
		a = 1 + 2 ? 3 * 4 : 5 * 6
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BinOpExpr(
			new NamedIDExpr("a"),
			BinOp::ASSIGN,
			new TernaryExpr(
				new BinOpExpr(new IntValue(1), BinOp::ADD, new IntValue(2)),
				new BinOpExpr(new IntValue(3), BinOp::MULTIPLY, new IntValue(4)),
				new BinOpExpr(new IntValue(5), BinOp::MULTIPLY, new IntValue(6))
			)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, This) {
	std::stringstream ss(R"(
		this.a = 5
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BinOpExpr(
			new MemberAccessExpr(
				new ThisID(), new NamedIDExpr("a")
			),
			BinOp::ASSIGN,
			new IntValue(5)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, New) {
	std::stringstream ss(R"(
		new Foo.Bar
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new NewExpr(
			new AccessIDExpr(
				new NamedIDExpr("Foo"),
				new NamedIDExpr("Bar")
			)
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, EmptyArray) {
	std::stringstream ss(R"(
		[]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayExpr()
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, SingleElementArray) {
	std::stringstream ss(R"(
		[1]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayExpr(std::vector<Expression*>({
			new IntValue(1)
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, MultipleElementArray) {
	std::stringstream ss(R"(
		[1, 2, 3, 4]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayExpr(std::vector<Expression*>({
			new IntValue(1), new IntValue(2), new IntValue(3), new IntValue(4)
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, NestedArray) {
	std::stringstream ss(R"(
		[[1,2],[3,4]]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayExpr(std::vector<Expression*>({
			new ArrayExpr(std::vector<Expression*>({
				new IntValue(1), new IntValue(2)
			})),
			new ArrayExpr(std::vector<Expression*>({
				new IntValue(3), new IntValue(4)
			}))
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ArrayRange) {
	std::stringstream ss(R"(
		[a .. b]; [a ... b]
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new ArrayRangeExpr(
			new NamedIDExpr("a"), ArrayRangeType::INCLUSIVE, new NamedIDExpr("b")
		),
		new ArrayRangeExpr(
			new NamedIDExpr("a"), ArrayRangeType::EXCLUSIVE, new NamedIDExpr("b")
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestTuples) {
	std::stringstream ss(R"(
		(1,)
		(1,2)
		(a:1,b:2)
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new TupleExpr(std::vector<Expression*>({
			new IntValue(1)
		})),
	 	new TupleExpr(std::vector<Expression*>({
		    new IntValue(1),
		    new IntValue(2)
		})),
		new TupleExpr(std::vector<Expression*>({
			new NamedExpr(new NamedIDExpr("a"), new IntValue(1)),
			new NamedExpr(new NamedIDExpr("b"), new IntValue(2))
		}))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, NamedArguments) {
	std::stringstream ss(R"(
		foo(a:1,b:2)
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new FunctionCallExpr(
			new NamedIDExpr("foo"),
			std::vector<Expression*>({
				new NamedExpr(new NamedIDExpr("a"), new IntValue(1)),
				new NamedExpr(new NamedIDExpr("b"), new IntValue(2))
			})
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TestIfs) {
	std::stringstream ss(R"(
		if (1) { }

		if (2) { }
		elif (3) { }
		elif (4) { }

		if (5) { }
		else { }

		if (6) { }
		elif (7) { }
		else { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
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
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, Loops) {
	std::stringstream ss(R"(
		for (;;) { }
		for (a;b;c) { }
		for (var a;b;c) { }
		foreach (var a in b) { }
		while (a) { }
		forever { }
		do { } while (a)
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new LoopStmt(
			nullptr, nullptr, nullptr, LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
	 	new LoopStmt(
			new NamedIDExpr("a"), new NamedIDExpr("b"), new NamedIDExpr("c"),
		    LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			new VarDeclExpr(
				std::vector<Identifier*>({new NamedIDExpr("a")}),
				std::vector<Type*>(),
				nullptr
			), new NamedIDExpr("b"), new NamedIDExpr("c"),
		    LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
	    new ForeachStmt(
		    new VarDeclExpr(
				std::vector<Identifier*>({new NamedIDExpr("a")}),
				std::vector<Type*>(),
				nullptr
		    ), new NamedIDExpr("b"), new LongBlockExpr()
	    ),
		new LoopStmt(
			nullptr, new NamedIDExpr("a"), nullptr,
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			nullptr, nullptr, nullptr,
			LoopConditionCheck::BEFORE, new LongBlockExpr()
		),
		new LoopStmt(
			nullptr, new NamedIDExpr("a"), nullptr,
			LoopConditionCheck::AFTER, new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, SwitchStatement) {
	std::stringstream ss(R"(
		switch (a) {
			1, 2: { },
			A.B(a, b): { },
			_: { }
		}
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new SwitchExpr(
			new NamedIDExpr("a"),
			std::vector<SwitchPattern*>({
				new SwitchPattern(
					std::vector<Expression*>({
						new IntValue(1), new IntValue(2)
					}),
					new LongBlockExpr()
				),
				new SwitchPattern(
					std::vector<Expression*>({
						new FunctionCallExpr(
							new MemberAccessExpr(
								new NamedIDExpr("A"), new NamedIDExpr("B")
							),
							std::vector<Expression*>({
								new NamedIDExpr("a"), new NamedIDExpr("b")
							})
						)
					}),
					new LongBlockExpr()
				),
				new SwitchPattern(
					std::vector<Expression*>({ new TempIDExpr() }),
					new LongBlockExpr()
				),
			})
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, ControlStatements) {
	std::stringstream ss(R"(
		break; continue; yield 5
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new BreakStmt(), new ContinueStmt,
	    new YieldStmt(new IntValue(5))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, Delete) {
	std::stringstream ss(R"(
		delete a
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new DeleteStmt(new NamedIDExpr("a"))
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

TEST(Parser, TryCatches) {
	std::stringstream ss(R"(
		try { }
		catch (var a: int) { }
		catch (var b: int) { }
		finally { }
	)");

	Parser p(ss);

	auto ast = p.parse();
	EXPECT_TRUE(ast != nullptr);

	LongBlockExpr expected(std::vector<Node*>({
		new TryExpr(
			new LongBlockExpr(),
			std::vector<CatchBlock*>({
				new CatchBlock(
					new VarDeclExpr(
						std::vector<Identifier*>({new NamedIDExpr("a")}),
						std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}), nullptr
					), new LongBlockExpr()
				),
				new CatchBlock(
					new VarDeclExpr(
						std::vector<Identifier*>({new NamedIDExpr("b")}),
						std::vector<Type*>({new BuiltinType(BuiltinTypeKind::INT)}), nullptr
					), new LongBlockExpr()
				)
			}),
			new LongBlockExpr()
		)
	}));

	assertEqAST(&expected, ast);
	delete ast;
}

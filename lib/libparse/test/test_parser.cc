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
			a
			a: int

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

// TODO: Test functions
// TODO: Test extern functions
// TODO: Test aggregate
// TODO: Test interface
// TODO: Test imports
// TODO: Test extensions
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

package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = DescribeTable("Parsing functions", expectNode,
	Entry("no arguments", "extern def foo()", &ast.ExternFuncStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		RetType:    &ast.VoidType{},
	}),
	Entry("explicit return", "extern def foo() -> int", &ast.ExternFuncStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		RetType:    &ast.IntType{Size: 64, Signed: true},
	}),
	Entry("one argument", "extern def foo(a: void)", &ast.ExternFuncStmt{
		Name: "foo",
		Parameters: []*ast.VarDecl{
			&ast.VarDecl{Name: "a", Type: &ast.VoidType{}, Value: nil},
		},
		RetType: &ast.VoidType{},
	}),
	Entry("multiple arguments", "extern def foo(a: void, b: void)",
		&ast.ExternFuncStmt{
			Name: "foo",
			Parameters: []*ast.VarDecl{
				&ast.VarDecl{Name: "a", Type: &ast.VoidType{}, Value: nil},
				&ast.VarDecl{Name: "b", Type: &ast.VoidType{}, Value: nil},
			},
			RetType: &ast.VoidType{},
		}),
	Entry("variable argument", "extern def foo(a: void, ...)",
		&ast.ExternFuncStmt{
			Name: "foo",
			Parameters: []*ast.VarDecl{
				&ast.VarDecl{Name: "a", Type: &ast.VoidType{}, Value: nil},
			},
			RetType:          &ast.VoidType{},
			VariableArgument: true,
		}),
)

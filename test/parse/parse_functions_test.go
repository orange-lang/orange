package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = DescribeTable("Parsing functions", expectNode,
	Entry("body on new line", `def foo() 
	{}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("no arguments, return type, or body", "def foo() {  }", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("body", `def foo() {  
		5
		3
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
			&ast.IntExpr{Value: 3, Size: 64},
		}},
	}),

	Entry("return statement", `def foo() {  
		return 5
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.ReturnStmt{Value: &ast.IntExpr{Value: 5, Size: 64}},
		}},
	}),

	Entry("void return statement", `def foo() {  
		return
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.ReturnStmt{},
		}},
	}),

	Entry("return type", "def foo() -> int {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		RetType:    &ast.IntType{Signed: true, Size: 64},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("one parameter", "def foo(a: void) {}", &ast.FunctionStmt{
		Name: "foo",
		Parameters: []*ast.VarDecl{
			&ast.VarDecl{Name: "a", Type: &ast.VoidType{}},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple parameters", "def foo(a: void, b: void) {}", &ast.FunctionStmt{
		Name: "foo",
		Parameters: []*ast.VarDecl{
			&ast.VarDecl{Name: "a", Type: &ast.VoidType{}},
			&ast.VarDecl{Name: "b", Type: &ast.VoidType{}},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("one generic type", "def<T> foo() {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
		},
	}),

	Entry("multiple generic types", "def<T,V,U> foo() {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.VarDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
			&ast.NamedType{Name: "V"},
			&ast.NamedType{Name: "U"},
		},
	}),
)

var _ = DescribeTable("Parsing external functions", expectNode,
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

package parse

import (
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"

	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = DescribeTable("Parsing functions", expectNode,
	CEntry(`def foo()
	{}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("def foo() {  }", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`def foo() {
		5
		3
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
			&ast.IntExpr{Value: 3, Size: 64},
		}},
	}),

	CEntry(`def foo() {
		return 5
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.ReturnStmt{Value: &ast.IntExpr{Value: 5, Size: 64}},
		}},
	}),

	CEntry(`def foo() {
		return
	}`, &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.ReturnStmt{},
		}},
	}),

	CEntry("def foo() -> int {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		RetType:    &types.Int{Signed: true, Size: 64},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("one parameter", "def foo(a: void) {}", &ast.FunctionStmt{
		Name: "foo",
		Parameters: []*ast.ParamDecl{
			&ast.ParamDecl{Name: "a", Type: &types.Void{}},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple parameters", "def foo(a: void, b: void) {}", &ast.FunctionStmt{
		Name: "foo",
		Parameters: []*ast.ParamDecl{
			&ast.ParamDecl{Name: "a", Type: &types.Void{}},
			&ast.ParamDecl{Name: "b", Type: &types.Void{}},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("one generic type", "def<T> foo() {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
		},
	}),

	Entry("multiple generic types", "def<T,V,U> foo() {}", &ast.FunctionStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
			&types.Named{Name: "V"},
			&types.Named{Name: "U"},
		},
	}),
)

var _ = DescribeTable("Parsing external functions", expectNode,
	Entry("no arguments", "extern def foo()", &ast.ExternFuncStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		RetType:    &types.Void{},
	}),

	Entry("explicit return", "extern def foo() -> int", &ast.ExternFuncStmt{
		Name:       "foo",
		Parameters: []*ast.ParamDecl{},
		RetType:    &types.Int{Size: 64, Signed: true},
	}),

	Entry("one argument", "extern def foo(a: void)", &ast.ExternFuncStmt{
		Name: "foo",
		Parameters: []*ast.ParamDecl{
			&ast.ParamDecl{Name: "a", Type: &types.Void{}},
		},
		RetType: &types.Void{},
	}),

	Entry("multiple arguments", "extern def foo(a: void, b: void)",
		&ast.ExternFuncStmt{
			Name: "foo",
			Parameters: []*ast.ParamDecl{
				&ast.ParamDecl{Name: "a", Type: &types.Void{}},
				&ast.ParamDecl{Name: "b", Type: &types.Void{}},
			},
			RetType: &types.Void{},
		}),

	Entry("variable argument", "extern def foo(a: void, ...)",
		&ast.ExternFuncStmt{
			Name: "foo",
			Parameters: []*ast.ParamDecl{
				&ast.ParamDecl{Name: "a", Type: &types.Void{}},
			},
			RetType:          &types.Void{},
			VariableArgument: true,
		}),
)

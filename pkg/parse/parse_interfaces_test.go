package parse

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

var _ = DescribeTable("Parsing interfaces", expectNode,
	//
	// Empty interfaces
	//

	CEntry("interface foo { }", &ast.InterfaceDecl{
		Name: "foo",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`interface foo {

	}`, &ast.InterfaceDecl{
		Name: "foo",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`interface foo
	{

	}`, &ast.InterfaceDecl{
		Name: "foo",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	CEntry("interface foo: A { }", &ast.InterfaceDecl{
		Name: "foo",
		Supers: []types.Type{
			&types.Named{Name: "A"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("interface foo: A,B,C { }", &ast.InterfaceDecl{
		Name: "foo",
		Supers: []types.Type{
			&types.Named{Name: "A"},
			&types.Named{Name: "B"},
			&types.Named{Name: "C"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Generics
	//

	CEntry(`interface<T> foo { }`, &ast.InterfaceDecl{
		Name: "foo",
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`interface<T,U,V> foo { }`, &ast.InterfaceDecl{
		Name: "foo",
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
			&types.Named{Name: "U"},
			&types.Named{Name: "V"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Methods
	//

	CEntry(`interface foo {
		def foo()
		def foo() -> bool
	}`, &ast.InterfaceDecl{
		Name: "foo",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				RetType:    &types.Void{},
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
			},
			&ast.FunctionStmt{
				Name:       "foo",
				RetType:    &types.Bool{},
				Parameters: []*ast.ParamDecl{},
			},
		}},
	}),
)

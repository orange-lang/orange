package test

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
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
		Supers: []ast.Type{
			&ast.NamedType{Name: "A"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("interface foo: A,B,C { }", &ast.InterfaceDecl{
		Name: "foo",
		Supers: []ast.Type{
			&ast.NamedType{Name: "A"},
			&ast.NamedType{Name: "B"},
			&ast.NamedType{Name: "C"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Generics
	//

	CEntry(`interface<T> foo { }`, &ast.InterfaceDecl{
		Name: "foo",
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`interface<T,U,V> foo { }`, &ast.InterfaceDecl{
		Name: "foo",
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
			&ast.NamedType{Name: "U"},
			&ast.NamedType{Name: "V"},
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
				RetType:    &ast.VoidType{},
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
			},
			&ast.FunctionStmt{
				Name:       "foo",
				RetType:    &ast.BoolType{},
				Parameters: []*ast.ParamDecl{},
			},
		}},
	}),
)

package test

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
)

var _ = DescribeTable("Parsing extensions", expectNode,
	//
	// Empty extensions
	//

	CEntry("extend bool { }", &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend bool {

	}`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend bool
	{ 

	}`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	CEntry("extend bool: A { }", &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Supers: []ast.Type{
			&ast.NamedType{Name: "A"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("extend bool: A,B,C { }", &ast.ExtensionDecl{
		Original: &ast.BoolType{},
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

	CEntry(`extend<T> bool { }`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend<T,U,V> bool { }`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
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

	CEntry(`extend bool {
		def foo() {}
	}`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
				Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			},
		}},
	}),
)

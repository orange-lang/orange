package test

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
)

var _ = DescribeTable("Parsing extensions", expectNode,
	//
	// Empty extensions
	//

	Entry("empty extension same line body", "extend bool { }", &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("empty extension } new line", `extend bool { 

	}`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("empty extension { new line", `extend bool
	{ 

	}`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	Entry("single super", "extend bool: A { }", &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		Supers: []ast.Type{
			&ast.NamedType{Name: "A"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple supers", "extend bool: A,B,C { }", &ast.ExtensionDecl{
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

	Entry("one generic extension", `extend<T> bool { }`, &ast.ExtensionDecl{
		Original: &ast.BoolType{},
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple generic extensions", `extend<T,U,V> bool { }`, &ast.ExtensionDecl{
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

	Entry("methods in extension", `extend bool {
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

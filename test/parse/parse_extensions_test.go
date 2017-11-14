package test

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/ast/types"
)

var _ = DescribeTable("Parsing extensions", expectNode,
	//
	// Empty extensions
	//

	CEntry("extend bool { }", &ast.ExtensionDecl{
		Original: &types.Bool{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend bool {

	}`, &ast.ExtensionDecl{
		Original: &types.Bool{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend bool
	{ 

	}`, &ast.ExtensionDecl{
		Original: &types.Bool{},
		Body:     &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	CEntry("extend bool: A { }", &ast.ExtensionDecl{
		Original: &types.Bool{},
		Supers: []types.Type{
			&types.Named{Name: "A"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("extend bool: A,B,C { }", &ast.ExtensionDecl{
		Original: &types.Bool{},
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

	CEntry(`extend<T> bool { }`, &ast.ExtensionDecl{
		Original: &types.Bool{},
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`extend<T,U,V> bool { }`, &ast.ExtensionDecl{
		Original: &types.Bool{},
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

	CEntry(`extend bool {
		def foo() {}
	}`, &ast.ExtensionDecl{
		Original: &types.Bool{},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
				Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			},
		}},
	}),
)

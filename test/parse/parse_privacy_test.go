package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing privacy", func() {
	DescribeTable("Levels", expectNode,
		CEntry("class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyDefault,
		}),

		CEntry("public class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),

		CEntry("protected class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyProtected,
		}),

		CEntry("private class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPrivate,
		}),
	)

	DescribeTable("Elements", expectNode,
		CEntry("public class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),

		CEntry(`class Test {
			public var a: bool
		}`, &ast.ClassDecl{
			Name: "Test",
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.MemberDecl{
					Name:    "a",
					Type:    &ast.BoolType{},
					Privacy: ast.PrivacyPublic,
				},
			}},
		}),

		CEntry(`class Test {
			public const var a: bool
		}`, &ast.ClassDecl{
			Name: "Test",
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.MemberDecl{
					Name: "a",
					Type: &ast.BoolType{
						TypeBase: ast.TypeBase{ast.FlagConst},
					},
					Privacy: ast.PrivacyPublic,
				},
			}},
		}),

		CEntry(`class Test {
			public property Prop -> bool {
				get { true; }
			}
		}`, &ast.ClassDecl{
			Name: "Test",
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.PropertyDecl{
					Name: "Prop",
					Type: &ast.BoolType{},
					Getter: &ast.GetterStmt{
						Body: &ast.BlockStmt{Nodes: []ast.Node{
							&ast.BoolExpr{Value: true},
						}},
					},
					Privacy: ast.PrivacyPublic,
				},
			}},
		}),

		CEntry(`class Test {
			public def foo() {}
		}`, &ast.ClassDecl{
			Name: "Test",
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.FunctionStmt{
					Name:       "foo",
					Parameters: []*ast.ParamDecl{},
					Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
					Privacy:    ast.PrivacyPublic,
				},
			}},
		}),

		CEntry("public def foo(){}", &ast.FunctionStmt{
			Name:       "foo",
			Parameters: []*ast.ParamDecl{},
			Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy:    ast.PrivacyPublic,
		}),

		CEntry("public enum Status { Pending }", &ast.EnumDecl{
			Name:    "Status",
			Members: []string{"Pending"},
			Privacy: ast.PrivacyPublic,
		}),

		CEntry("public interface foo { }", &ast.InterfaceDecl{
			Name:    "foo",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),
	)
})

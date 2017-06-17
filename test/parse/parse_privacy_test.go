package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing privacy", func() {
	DescribeTable("Levels", expectNode,
		Entry("default", "class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyDefault,
		}),

		Entry("public", "public class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),

		Entry("protected", "protected class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyProtected,
		}),

		Entry("private", "private class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPrivate,
		}),
	)

	DescribeTable("Elements", expectNode,
		Entry("class", "public class Test{}", &ast.ClassDecl{
			Name:    "Test",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),

		Entry("class member", `class Test {
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

		Entry("const member", `class Test {
			public const var a: bool
		}`, &ast.ClassDecl{
			Name: "Test",
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.MemberDecl{
					Name:    "a",
					Type:    &ast.ConstType{InnerType: &ast.BoolType{}},
					Privacy: ast.PrivacyPublic,
				},
			}},
		}),

		Entry("class property", `class Test {
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

		Entry("class method", `class Test {
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

		Entry("function", "public def foo(){}", &ast.FunctionStmt{
			Name:       "foo",
			Parameters: []*ast.ParamDecl{},
			Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy:    ast.PrivacyPublic,
		}),

		Entry("enum", "public enum Status { Pending }", &ast.EnumDecl{
			Name:    "Status",
			Members: []string{"Pending"},
			Privacy: ast.PrivacyPublic,
		}),

		Entry("interface", "public interface foo { }", &ast.InterfaceDecl{
			Name:    "foo",
			Body:    &ast.BlockStmt{Nodes: []ast.Node{}},
			Privacy: ast.PrivacyPublic,
		}),
	)
})

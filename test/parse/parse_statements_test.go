package test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"

	"github.com/orange-lang/orange/ast"
)

var _ = Describe("Parsing Statements", func() {
	Describe("should be able to parse multiple statements", func() {
		It("separated by newlines", func() {
			expectNodes(`
				1
				2
				3
			`, []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
				&ast.IntExpr{Value: 2, Size: 64},
				&ast.IntExpr{Value: 3, Size: 64},
			})
		})

		It("separted by semicolons", func() {
			expectNodes("1; 2; 3", []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
				&ast.IntExpr{Value: 2, Size: 64},
				&ast.IntExpr{Value: 3, Size: 64},
			})
		})

		It("separated by newlines and semicolons", func() {
			expectNodes(`
				1;
				2;
				3
			`, []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
				&ast.IntExpr{Value: 2, Size: 64},
				&ast.IntExpr{Value: 3, Size: 64},
			})
		})
	})

	DescribeTable("should be able to handle variable declarations", expectNode,
		Entry("type and value", "var a: int = 5", &ast.VarDecl{
			Name:  "a",
			Type:  &ast.IntType{Size: 64, Signed: true},
			Value: &ast.IntExpr{Value: 5, Size: 64},
		}),

		Entry("type", "var a: int", &ast.VarDecl{
			Name:  "a",
			Type:  &ast.IntType{Size: 64, Signed: true},
			Value: nil,
		}),

		Entry("value", "var a = 5", &ast.VarDecl{
			Name:  "a",
			Type:  nil,
			Value: &ast.IntExpr{Value: 5, Size: 64},
		}),

		Entry("neither type nor value", "var a", &ast.VarDecl{
			Name:  "a",
			Type:  nil,
			Value: nil,
		}),
	)

	DescribeTable("should be able to handle package", expectNode,
		Entry("simple name", "package A", &ast.PackageDecl{
			Name: "A",
		}),

		Entry("nested name", "package A.B", &ast.PackageDecl{
			Name: "A.B",
		}),
	)

	DescribeTable("should be able to handle import", expectNode,
		Entry("simple name", "import A", &ast.ImportDecl{
			Name: "A",
		}),

		Entry("nested name", "import A.B", &ast.ImportDecl{
			Name: "A.B",
		}),
	)

	DescribeTable("should be able to handle conditionals", expectNode,
		Entry("if", `if (5) {
			1
			2
		}`, &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 5, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
				&ast.IntExpr{Value: 2, Size: 64},
			}},
		}),

		Entry("elif", `if (5) {
			1
			2
		} elif (6) {
			3
			4
	  } elif (7) {
		  5
			6	
		}`, &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 5, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
				&ast.IntExpr{Value: 2, Size: 64},
			}},
			Else: &ast.IfStmt{
				Condition: &ast.IntExpr{Value: 6, Size: 64},
				Body: &ast.BlockStmt{Nodes: []ast.Node{
					&ast.IntExpr{Value: 3, Size: 64},
					&ast.IntExpr{Value: 4, Size: 64},
				}},
				Else: &ast.IfStmt{
					Condition: &ast.IntExpr{Value: 7, Size: 64},
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.IntExpr{Value: 5, Size: 64},
						&ast.IntExpr{Value: 6, Size: 64},
					}},
				},
			},
		}),

		Entry("elif and else", `if (5) {
			1
		} elif (6) {
			2
	  } else {
		  3
		}`, &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 5, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
			}},
			Else: &ast.IfStmt{
				Condition: &ast.IntExpr{Value: 6, Size: 64},
				Body: &ast.BlockStmt{Nodes: []ast.Node{
					&ast.IntExpr{Value: 2, Size: 64},
				}},
				Else: &ast.BlockStmt{
					Nodes: []ast.Node{&ast.IntExpr{Value: 3, Size: 64}},
				},
			},
		}),

		Entry("else", `if (5) {
			1
		} else {
		  2
		}`, &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 5, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 1, Size: 64},
			}},
			Else: &ast.BlockStmt{
				Nodes: []ast.Node{&ast.IntExpr{Value: 2, Size: 64}},
			},
		}),
	)
})

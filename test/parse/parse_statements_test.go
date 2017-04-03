package test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"

	"github.com/orange-lang/orange/ast"
)

var _ = Describe("Parsing Statements", func() {
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
})

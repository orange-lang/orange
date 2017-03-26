package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing Operations", func() {
	DescribeTable("should return an expression for", expectNode,
		Entry("single member access", "a.b", &ast.MemberAccessExpr{
			Object: &ast.NamedIDExpr{Name: "a"},
			Name:   "b",
		}),
		Entry("multiple member access", "a.b.c", &ast.MemberAccessExpr{
			Object: &ast.MemberAccessExpr{
				Object: &ast.NamedIDExpr{Name: "a"},
				Name:   "b",
			},
			Name: "c",
		}),
	)
})

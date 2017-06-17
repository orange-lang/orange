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

		Entry("single generic type instantiation", "a.<bool>", &ast.GenericInst{
			Object: &ast.NamedIDExpr{Name: "a"},
			Annotations: []ast.Type{
				&ast.BoolType{},
			},
		}),

		Entry("mutliple generic type instantiation", "a.<bool, bool>", &ast.GenericInst{
			Object: &ast.NamedIDExpr{Name: "a"},
			Annotations: []ast.Type{
				&ast.BoolType{},
				&ast.BoolType{},
			},
		}),

		Entry("multiple member access", "a.b.c", &ast.MemberAccessExpr{
			Object: &ast.MemberAccessExpr{
				Object: &ast.NamedIDExpr{Name: "a"},
				Name:   "b",
			},
			Name: "c",
		}),

		Entry("single array access", "a[1]", &ast.ArrayAccessExpr{
			Object: &ast.NamedIDExpr{Name: "a"},
			Index:  &ast.IntExpr{Value: 1, Size: 64},
		}),

		Entry("multiple array access", "a[1][2]", &ast.ArrayAccessExpr{
			Object: &ast.ArrayAccessExpr{
				Object: &ast.NamedIDExpr{Name: "a"},
				Index:  &ast.IntExpr{Value: 1, Size: 64},
			},
			Index: &ast.IntExpr{Value: 2, Size: 64},
		}),
	)
})

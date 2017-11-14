package test

import (
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/ast/types"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing Operations", func() {
	DescribeTable("should return an expression for", expectNode,
		CEntry("a.b", &ast.MemberAccessExpr{
			Object: &ast.NamedIDExpr{Name: "a"},
			Name:   "b",
		}),

		CEntry("a.<bool>", &ast.GenericInst{
			Object: &ast.NamedIDExpr{Name: "a"},
			Annotations: []types.Type{
				&types.Bool{},
			},
		}),

		CEntry("a.<bool, bool>", &ast.GenericInst{
			Object: &ast.NamedIDExpr{Name: "a"},
			Annotations: []types.Type{
				&types.Bool{},
				&types.Bool{},
			},
		}),

		CEntry("a.b.c", &ast.MemberAccessExpr{
			Object: &ast.MemberAccessExpr{
				Object: &ast.NamedIDExpr{Name: "a"},
				Name:   "b",
			},
			Name: "c",
		}),

		CEntry("a[1]", &ast.ArrayAccessExpr{
			Object: &ast.NamedIDExpr{Name: "a"},
			Index:  &ast.IntExpr{Value: 1, Size: 64},
		}),

		CEntry("a[1][2]", &ast.ArrayAccessExpr{
			Object: &ast.ArrayAccessExpr{
				Object: &ast.NamedIDExpr{Name: "a"},
				Index:  &ast.IntExpr{Value: 1, Size: 64},
			},
			Index: &ast.IntExpr{Value: 2, Size: 64},
		}),
	)
})

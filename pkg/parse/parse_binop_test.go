package parse

import (
	"github.com/orange-lang/orange/pkg/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing Binary Operations", func() {
	It("should support expressions grouped with parens", func() {
		input := `3+(5-2)`
		expectNode(input, &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "+",
			RHS: &ast.BinaryExpr{
				LHS:       &ast.IntExpr{Value: 5, Size: 64},
				Operation: "-",
				RHS:       &ast.IntExpr{Value: 2, Size: 64},
			},
		})
	})

	It("should handle the appropriate operator precedence", func() {
		input := `1-2-3`
		expectNode(input, &ast.BinaryExpr{
			LHS: &ast.BinaryExpr{
				LHS:       &ast.IntExpr{Value: 1, Size: 64},
				Operation: "-",
				RHS:       &ast.IntExpr{Value: 2, Size: 64},
			},
			Operation: "-",
			RHS:       &ast.IntExpr{Value: 3, Size: 64},
		})
	})

	DescribeTable("should return a BinOpExpr for", expectNode,
		CEntry("3+2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "+",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3-2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "-",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3*2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "*",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3/2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "/",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3%2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "%",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3<<2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "<<",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3>>2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: ">>",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3==2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "==",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3!=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "!=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3<2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "<",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3<=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "<=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3>2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: ">",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3>=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: ">=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3+=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "+=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3-=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "-=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3*=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "*=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3/=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "/=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3%=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "%=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3^=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "^=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3&=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "&=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3|=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "|=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3<<=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "<<=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3>>=2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: ">>=",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3|2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "|",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3&2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "&",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3^2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "^",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3||2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "||",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
		CEntry("3&&2", &ast.BinaryExpr{
			LHS:       &ast.IntExpr{Value: 3, Size: 64},
			Operation: "&&",
			RHS:       &ast.IntExpr{Value: 2, Size: 64},
		}),
	)
})

func CEntry(code string, expected interface{}) TableEntry {
	return Entry(code, code, expected)
}

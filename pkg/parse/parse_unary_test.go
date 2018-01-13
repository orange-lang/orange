package parse

import (
	"github.com/orange-lang/orange/pkg/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing Unary Operations", func() {
	DescribeTable("should return a UnaryExpr for", expectNode,
		CEntry("-3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "-",
			Order:     ast.PrefixOrder,
		}),
		CEntry("!3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "!",
			Order:     ast.PrefixOrder,
		}),
		CEntry("~3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "~",
			Order:     ast.PrefixOrder,
		}),
		CEntry("&3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "&",
			Order:     ast.PrefixOrder,
		}),
		CEntry("*3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "*",
			Order:     ast.PrefixOrder,
		}),
		CEntry("++3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "++",
			Order:     ast.PrefixOrder,
		}),
		CEntry("--3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "--",
			Order:     ast.PrefixOrder,
		}),
		CEntry("3++", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "++",
			Order:     ast.PostfixOrder,
		}),
		CEntry("3--", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "--",
			Order:     ast.PostfixOrder,
		}),
	)
})

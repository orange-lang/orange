package test

import (
	"github.com/orange-lang/orange/ast"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Parsing Unary Operations", func() {
	DescribeTable("should return a UnaryExpr for", expectNode,
		Entry("-", "-3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "-",
			Order:     ast.PrefixOrder,
		}),
		Entry("!", "!3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "!",
			Order:     ast.PrefixOrder,
		}),
		Entry("~", "~3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "~",
			Order:     ast.PrefixOrder,
		}),
		Entry("&", "&3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "&",
			Order:     ast.PrefixOrder,
		}),
		Entry("*", "*3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "*",
			Order:     ast.PrefixOrder,
		}),
		Entry("++ prefix", "++3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "++",
			Order:     ast.PrefixOrder,
		}),
		Entry("-- prefix", "--3", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "--",
			Order:     ast.PrefixOrder,
		}),
		Entry("++ postfix", "3++", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "++",
			Order:     ast.PostfixOrder,
		}),
		Entry("-- postfix", "3--", &ast.UnaryExpr{
			Operand:   &ast.IntExpr{Value: 3, Size: 64},
			Operation: "--",
			Order:     ast.PostfixOrder,
		}),
	)
})

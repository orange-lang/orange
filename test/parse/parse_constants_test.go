package test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse"
	"github.com/orange-lang/orange/parse/lexer"
)

var _ = Describe("Parsing constants", func() {
	Describe("should return an expr for", func() {
		It("strings", func() {
			expectNode(`"hello, world"`, &ast.StringExpr{
				Value: "hello, world",
			})
		})

		It("booleans", func() {
			expectNode("true", &ast.BoolExpr{Value: true})
		})

		DescribeTable("numbers", expectNode,
			Entry("uint", "8u", &ast.UIntExpr{Value: 8, Size: 64}),
			Entry("uint8", "8u8", &ast.UIntExpr{Value: 8, Size: 8}),
			Entry("uint16", "8u16", &ast.UIntExpr{Value: 8, Size: 16}),
			Entry("uint32", "8u32", &ast.UIntExpr{Value: 8, Size: 32}),
			Entry("uint64", "8u64", &ast.UIntExpr{Value: 8, Size: 64}),
			Entry("int", "8i", &ast.IntExpr{Value: 8, Size: 64}),
			Entry("int8", "8i8", &ast.IntExpr{Value: 8, Size: 8}),
			Entry("int16", "8i16", &ast.IntExpr{Value: 8, Size: 16}),
			Entry("int32", "8i32", &ast.IntExpr{Value: 8, Size: 32}),
			Entry("int64", "8i64", &ast.IntExpr{Value: 8, Size: 64}),
			Entry("double", "32.0", &ast.DoubleExpr{Value: 32.0}),
			Entry("float", "32.0f", &ast.FloatExpr{Value: 32.0}),
		)

		DescribeTable("arrays", expectNode,
			Entry("empty array", "[]", &ast.ArrayExpr{Members: []ast.Expression{}}),
			Entry("array with one member", "[1]", &ast.ArrayExpr{
				Members: []ast.Expression{
					&ast.IntExpr{Value: 1, Size: 64},
				}},
			),
			Entry("array with multiple members", "[1,2,3]", &ast.ArrayExpr{
				Members: []ast.Expression{
					&ast.IntExpr{Value: 1, Size: 64},
					&ast.IntExpr{Value: 2, Size: 64},
					&ast.IntExpr{Value: 3, Size: 64},
				}},
			),
			Entry("nested arrays", "[[1,2],[3,4],[5,6]]", &ast.ArrayExpr{
				Members: []ast.Expression{
					&ast.ArrayExpr{
						Members: []ast.Expression{
							&ast.IntExpr{Value: 1, Size: 64},
							&ast.IntExpr{Value: 2, Size: 64},
						},
					},
					&ast.ArrayExpr{
						Members: []ast.Expression{
							&ast.IntExpr{Value: 3, Size: 64},
							&ast.IntExpr{Value: 4, Size: 64},
						},
					},
					&ast.ArrayExpr{
						Members: []ast.Expression{
							&ast.IntExpr{Value: 5, Size: 64},
							&ast.IntExpr{Value: 6, Size: 64},
						},
					},
				}},
			),
		)

		It("characters", func() {
			expectNode("'t'", &ast.CharExpr{Value: 't'})
		})
	})
})

func expectNode(input string, expect ast.Node) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	p, errs := parse.Parse(&l)

	Expect(errs).To(Equal([]error{}))

	Expect(len(p.Nodes)).To(BeNumerically(">", 0))
	Expect(p.Nodes[0]).To(Equal(expect))
}

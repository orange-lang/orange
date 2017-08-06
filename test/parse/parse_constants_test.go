package test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
)

var _ = Describe("Parsing constants", func() {
	Describe("should parse", func() {
		It("constant ifs", func() {
			expectNode(`const if (false) {

			} elif (true) {
				
			} else {}`, &ast.ConstIfStmt{
				Condition: &ast.BoolExpr{Value: false},
				Body:      ast.NewBlockStmt(),
				Else: &ast.ConstIfStmt{
					Condition: &ast.BoolExpr{Value: true},
					Body:      ast.NewBlockStmt(),
					Else:      ast.NewBlockStmt(),
				},
			})
		})
	})

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
			CEntry("[]", &ast.ArrayExpr{Members: []ast.Expression{}}),
			CEntry("[1]", &ast.ArrayExpr{
				Members: []ast.Expression{
					&ast.IntExpr{Value: 1, Size: 64},
				}},
			),
			CEntry("[1,2,3]", &ast.ArrayExpr{
				Members: []ast.Expression{
					&ast.IntExpr{Value: 1, Size: 64},
					&ast.IntExpr{Value: 2, Size: 64},
					&ast.IntExpr{Value: 3, Size: 64},
				}},
			),
			CEntry("[[1,2],[3,4],[5,6]]", &ast.ArrayExpr{
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

		It("this", func() {
			expectNode("this", &ast.ThisExpr{})
		})

		It("super", func() {
			expectNode("super", &ast.SuperExpr{})
		})
	})
})

package test

import (
	"fmt"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse"
	"github.com/orange-lang/orange/parse/lexer"
)

var _ = Describe("Parsing Types", func() {
	DescribeTable("should be able to parse a", expectType,
		Entry("void", "void", &ast.VoidType{}),
		Entry("int", "int", &ast.IntType{Size: 64, Signed: true}),
		Entry("int8", "int8", &ast.IntType{Size: 8, Signed: true}),
		Entry("int16", "int16", &ast.IntType{Size: 16, Signed: true}),
		Entry("int32", "int32", &ast.IntType{Size: 32, Signed: true}),
		Entry("int64", "int64", &ast.IntType{Size: 64, Signed: true}),
		Entry("uint", "uint", &ast.IntType{Size: 64, Signed: false}),
		Entry("uint8", "uint8", &ast.IntType{Size: 8, Signed: false}),
		Entry("uint16", "uint16", &ast.IntType{Size: 16, Signed: false}),
		Entry("uint32", "uint32", &ast.IntType{Size: 32, Signed: false}),
		Entry("uint64", "uint64", &ast.IntType{Size: 64, Signed: false}),
		Entry("float", "float", &ast.FloatType{}),
		Entry("double", "double", &ast.DoubleType{}),
		Entry("char", "char", &ast.CharType{}),
		Entry("string", "string", &ast.NamedType{Name: "string"}),
		Entry("bool", "bool", &ast.BoolType{}),

		Entry("int*", "int*", &ast.PointerType{
			InnerType: &ast.IntType{Size: 64, Signed: true},
		}),

		Entry("int**", "int**", &ast.PointerType{
			InnerType: &ast.PointerType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		Entry("int[]", "int[]", &ast.ArrayType{
			InnerType: &ast.IntType{Size: 64, Signed: true},
		}),

		Entry("int[][]", "int[][]", &ast.ArrayType{
			InnerType: &ast.ArrayType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		Entry("int[]*", "int[]*", &ast.PointerType{
			InnerType: &ast.ArrayType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		Entry("int*[]", "int*[]", &ast.ArrayType{
			InnerType: &ast.PointerType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		Entry("const int[]", "const int[]", &ast.ConstType{
			InnerType: &ast.ArrayType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),
	)
})

func expectType(input string, expect ast.Type) {
	fullInput := fmt.Sprintf("var a: %v", input)
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: fullInput,
	}}

	p, errs := parse.Parse(&l)

	Expect(errs).To(Equal([]error{}))

	Expect(len(p.Nodes)).To(BeNumerically(">", 0))

	node, ok := p.Nodes[0].(*ast.VarDecl)
	Expect(ok).To(Equal(true))
	Expect(node.Type).To(Equal(expect))
}

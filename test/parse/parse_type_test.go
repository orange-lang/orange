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
		CEntry("void", &ast.VoidType{}),
		CEntry("int", &ast.IntType{Size: 64, Signed: true}),
		CEntry("int8", &ast.IntType{Size: 8, Signed: true}),
		CEntry("int16", &ast.IntType{Size: 16, Signed: true}),
		CEntry("int32", &ast.IntType{Size: 32, Signed: true}),
		CEntry("int64", &ast.IntType{Size: 64, Signed: true}),
		CEntry("uint", &ast.IntType{Size: 64, Signed: false}),
		CEntry("uint8", &ast.IntType{Size: 8, Signed: false}),
		CEntry("uint16", &ast.IntType{Size: 16, Signed: false}),
		CEntry("uint32", &ast.IntType{Size: 32, Signed: false}),
		CEntry("uint64", &ast.IntType{Size: 64, Signed: false}),
		CEntry("float", &ast.FloatType{}),
		CEntry("double", &ast.DoubleType{}),
		CEntry("char", &ast.CharType{}),
		CEntry("string", &ast.NamedType{Name: "string"}),
		CEntry("bool", &ast.BoolType{}),

		CEntry("List<string>", &ast.GenericAnnotation{
			Type: &ast.NamedType{Name: "List"},
			Annotations: []ast.Type{
				&ast.NamedType{Name: "string"},
			},
		}),

		CEntry("Map<bool, string>", &ast.GenericAnnotation{
			Type: &ast.NamedType{Name: "Map"},
			Annotations: []ast.Type{
				&ast.BoolType{},
				&ast.NamedType{Name: "string"},
			},
		}),

		CEntry("int*", &ast.PointerType{
			InnerType: &ast.IntType{Size: 64, Signed: true},
		}),

		CEntry("int**", &ast.PointerType{
			InnerType: &ast.PointerType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		CEntry("int[]", &ast.ArrayType{
			InnerType: &ast.IntType{Size: 64, Signed: true},
		}),

		CEntry("int[][]", &ast.ArrayType{
			InnerType: &ast.ArrayType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		CEntry("int[]*", &ast.PointerType{
			InnerType: &ast.ArrayType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		CEntry("int*[]", &ast.ArrayType{
			InnerType: &ast.PointerType{
				InnerType: &ast.IntType{Size: 64, Signed: true},
			},
		}),

		CEntry("const int[]", &ast.ArrayType{
			TypeBase: ast.TypeBase{ast.FlagConst},
			InnerType: &ast.IntType{
				Size:   64,
				Signed: true,
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

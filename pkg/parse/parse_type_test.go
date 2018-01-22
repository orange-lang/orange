package parse

import (
	"fmt"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/lexer"
	"github.com/orange-lang/orange/pkg/types"
)

var _ = Describe("Parsing Types", func() {
	DescribeTable("should be able to parse a", expectType,
		CEntry("void", &types.Void{}),
		CEntry("int", &types.Int{Size: 64, Signed: true}),
		CEntry("int8", &types.Int{Size: 8, Signed: true}),
		CEntry("int16", &types.Int{Size: 16, Signed: true}),
		CEntry("int32", &types.Int{Size: 32, Signed: true}),
		CEntry("int64", &types.Int{Size: 64, Signed: true}),
		CEntry("uint", &types.Int{Size: 64, Signed: false}),
		CEntry("uint8", &types.Int{Size: 8, Signed: false}),
		CEntry("uint16", &types.Int{Size: 16, Signed: false}),
		CEntry("uint32", &types.Int{Size: 32, Signed: false}),
		CEntry("uint64", &types.Int{Size: 64, Signed: false}),
		CEntry("float", &types.Float{}),
		CEntry("double", &types.Double{}),
		CEntry("char", &types.Char{}),
		CEntry("string", &types.Named{Name: "string"}),
		CEntry("bool", &types.Bool{}),

		CEntry("List<string>", &types.Annotation{
			Type: &types.Named{Name: "List"},
			Annotations: []types.Type{
				&types.Named{Name: "string"},
			},
		}),

		CEntry("Map<bool, string>", &types.Annotation{
			Type: &types.Named{Name: "Map"},
			Annotations: []types.Type{
				&types.Bool{},
				&types.Named{Name: "string"},
			},
		}),

		CEntry("int*", &types.Pointer{
			InnerType: &types.Int{Size: 64, Signed: true},
		}),

		CEntry("int**", &types.Pointer{
			InnerType: &types.Pointer{
				InnerType: &types.Int{Size: 64, Signed: true},
			},
		}),

		CEntry("int[]", &types.Array{
			InnerType: &types.Int{Size: 64, Signed: true},
		}),

		CEntry("int[][]", &types.Array{
			InnerType: &types.Array{
				InnerType: &types.Int{Size: 64, Signed: true},
			},
		}),

		CEntry("int[]*", &types.Pointer{
			InnerType: &types.Array{
				InnerType: &types.Int{Size: 64, Signed: true},
			},
		}),

		CEntry("int[]&", &types.Reference{
			InnerType: &types.Array{
				InnerType: &types.Int{Size: 64, Signed: true},
			},
		}),

		CEntry("int*[]", &types.Array{
			InnerType: &types.Pointer{
				InnerType: &types.Int{Size: 64, Signed: true},
			},
		}),

		CEntry("const int[]", &types.Array{
			Base: types.MakeBase(types.FlagConst),
			InnerType: &types.Int{
				Size:   64,
				Signed: true,
			},
		}),
	)
})

func expectType(input string, expect types.Type) {
	fullInput := fmt.Sprintf("var a: %v", input)
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: fullInput,
	}}

	p, errs := Parse(&l)

	Expect(errs).To(Equal([]error{}))

	Expect(len(p.Nodes)).To(BeNumerically(">", 0))

	node, ok := p.Nodes[0].(*ast.VarDecl)
	Expect(ok).To(Equal(true))
	Expect(node.Type).To(Equal(expect))
}

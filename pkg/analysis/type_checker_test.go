package analysis

import (
	"fmt"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

func resolveType(node ast.Node) (types.Type, error) {
	scope := NewScope(node)
	ti := NewTypeInfo(scope)

	if err := ti.Resolve(); err != nil {
		return nil, err
	}

	return ti.Types[node], nil
}

var _ = Describe("Type Detection", func() {
	Describe("BinOpExpr", func() {
		getBinOpType := func(lhs types.Type, op string,
			rhs types.Type) (types.Type, error) {
			node := &ast.BinaryExpr{
				LHS: newMockExpr(lhs),
				RHS: newMockExpr(rhs),

				Operation: op,
			}

			return resolveType(node)
		}

		DescribeTable("Disallow binary operations on void type",
			func(op string) {
				_, err := getBinOpType(&types.Void{}, op, &types.Void{})
				Expect(err).NotTo(BeNil())
				Expect(err).To(Equal(fmt.Errorf(BinOpOnVoid)))
			},

			Entry("+", "+"),
			Entry("-", "-"),
			Entry("<", "<"),
			Entry(">", ">"),
			Entry("==", "=="),
			Entry("*", "*"),
			Entry("/", "/"),
		)

		DescribeTable("Arithmetic ops must be number types",
			func(lhs types.Type, op string, rhs types.Type) {
				_, err := getBinOpType(lhs, op, rhs)
				Expect(err).NotTo(BeNil())
				Expect(err).To(Equal(fmt.Errorf(BinOpInvalid, op, lhs, rhs)))
			},

			// All ops
			Entry("+", &types.Char{}, "+", &types.Char{}),
			Entry("-", &types.Char{}, "-", &types.Char{}),
			Entry("*", &types.Char{}, "*", &types.Char{}),
			Entry("/", &types.Char{}, "/", &types.Char{}),

			// Other types
			Entry("bool", &types.Bool{}, "+", &types.Bool{}),
			Entry("named type", &types.Named{Name: "ok"}, "+", &types.Named{Name: "ok"}),
			Entry("array type",
				&types.Array{InnerType: &types.Int{}},
				"+",
				&types.Array{InnerType: &types.Int{}}),
			Entry("pointer type",
				&types.Pointer{InnerType: &types.Int{}},
				"+",
				&types.Pointer{InnerType: &types.Int{}}),
		)

		Describe("Binary logical operations", func() {
			It("Must be boolean types", func() {
				logicalOps := []string{"||", "&&"}
				nonBooleanTypes := []types.Type{
					&types.Int{},
					&types.Char{},
					&types.Pointer{InnerType: &types.Int{}},
				}

				for _, ty := range nonBooleanTypes {
					lhsTy := ty.Clone()
					rhsTy := ty.Clone()

					for _, op := range logicalOps {
						_, err := getBinOpType(lhsTy, op, rhsTy)
						Expect(err).To(Equal(fmt.Errorf(BinOpLogicalOpErr, op)))
					}
				}
			})
		})

		Describe("Operator", func() {
			It("Must exist", func() {
				_, err := getBinOpType(&types.Int{}, "1", &types.Int{})
				Expect(err).NotTo(BeNil())
				Expect(err).To(Equal(fmt.Errorf(InvalidBinOp, "1")))
			})
		})
	})

	Describe("StringExpr", func() {
		It("Must be a char[]", func() {
			ty, _ := resolveType(&ast.StringExpr{})
			Expect(ty).To(Equal(&types.Array{InnerType: &types.Char{}}))
		})
	})

	Describe("BoolExpr", func() {
		It("Must be a bool", func() {
			ty, _ := resolveType(&ast.BoolExpr{})
			Expect(ty).To(Equal(&types.Bool{}))
		})
	})

	Describe("CharExpr", func() {
		It("Must be a char", func() {
			ty, _ := resolveType(&ast.CharExpr{})
			Expect(ty).To(Equal(&types.Char{}))
		})
	})

	Describe("DoubleExpr", func() {
		It("Must be a double", func() {
			ty, _ := resolveType(&ast.DoubleExpr{})
			Expect(ty).To(Equal(&types.Double{}))
		})
	})

	Describe("FloatExpr", func() {
		It("Must be a float", func() {
			ty, _ := resolveType(&ast.FloatExpr{})
			Expect(ty).To(Equal(&types.Float{}))
		})
	})

	Describe("IntExpr", func() {
		DescribeTable("Should keep precision",
			func(prec int) {
				ty, _ := resolveType(&ast.IntExpr{Size: prec})
				Expect(ty).To(Equal(&types.Int{Size: prec, Signed: true}))
			},
			Entry("8 bits", 8),
			Entry("16 bits", 16),
			Entry("32 bits", 32),
			Entry("64 bits", 64),
		)
	})

	Describe("UIntExpr", func() {
		DescribeTable("Should keep precision",
			func(prec int) {
				ty, _ := resolveType(&ast.UIntExpr{Size: prec})
				Expect(ty).To(Equal(&types.Int{Size: prec, Signed: false}))
			},
			Entry("8 bits", 8),
			Entry("16 bits", 16),
			Entry("32 bits", 32),
			Entry("64 bits", 64),
		)
	})
})

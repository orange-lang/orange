package analysis

import (
	"errors"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

var _ = Describe("Type Detection", func() {
	Describe("BinOpExpr", func() {
		getBinOpType := func(lhs types.Type, op string,
			rhs types.Type) (types.Type, []error) {
			node := &ast.BinaryExpr{
				LHS: newMockNode(lhs),
				RHS: newMockNode(rhs),

				Operation: op,
			}

			return getType(node)
		}

		DescribeTable("Disallow binary operations on void type",
			func(op string) {
				_, errs := getBinOpType(&types.Void{}, op, &types.Void{})
				Expect(len(errs)).NotTo(BeZero())
				Expect(errs[0]).To(Equal(errors.New("Cannot perform binary operation on void types")))
			},

			// TODO: could test for all the ops here instead of a subset
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
				_, errs := getBinOpType(lhs, op, rhs)
				Expect(len(errs)).NotTo(BeZero())
			},

			// All ops
			Entry("+", &types.Char{}, "+", &types.Char{}),
			Entry("-", &types.Char{}, "-", &types.Char{}),
			Entry("*", &types.Char{}, "*", &types.Char{}),
			Entry("/", &types.Char{}, "/", &types.Char{}),

			// Other types
			Entry("bool", &types.Bool{}, "+", &types.Bool{}),
			Entry("named type", &types.Named{Name: "ok"}, "+", &types.Named{Name: "ok"}),
			Entry("void type", &types.Void{}, "+", &types.Void{}),
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
			XIt("Must be boolean types")
		})

		Describe("Operator", func() {
			It("Must exist", func() {
				_, errs := getBinOpType(&types.Int{}, "1", &types.Int{})
				Expect(len(errs)).NotTo(BeZero())
				Expect(errs[0]).To(Equal(errors.New("1 is not a valid binary operation")))
			})
		})
	})

	Describe("StringExpr", func() {
		It("Must be a char[]", func() {
			ty, _ := getType(&ast.StringExpr{})
			Expect(ty).To(Equal(&types.Array{InnerType: &types.Char{}}))
		})
	})

	Describe("BoolExpr", func() {
		It("Must be a bool", func() {
			ty, _ := getType(&ast.BoolExpr{})
			Expect(ty).To(Equal(&types.Bool{}))
		})
	})

	Describe("CharExpr", func() {
		It("Must be a char", func() {
			ty, _ := getType(&ast.CharExpr{})
			Expect(ty).To(Equal(&types.Char{}))
		})
	})

	Describe("DoubleExpr", func() {
		It("Must be a double", func() {
			ty, _ := getType(&ast.DoubleExpr{})
			Expect(ty).To(Equal(&types.Double{}))
		})
	})

	Describe("FloatExpr", func() {
		It("Must be a float", func() {
			ty, _ := getType(&ast.FloatExpr{})
			Expect(ty).To(Equal(&types.Float{}))
		})
	})

	Describe("IntExpr", func() {
		DescribeTable("Should keep precision",
			func(prec int) {
				ty, _ := getType(&ast.IntExpr{Size: prec})
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
				ty, _ := getType(&ast.UIntExpr{Size: prec})
				Expect(ty).To(Equal(&types.Int{Size: prec, Signed: false}))
			},
			Entry("8 bits", 8),
			Entry("16 bits", 16),
			Entry("32 bits", 32),
			Entry("64 bits", 64),
		)
	})
})

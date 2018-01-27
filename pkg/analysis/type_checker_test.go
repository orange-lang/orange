package analysis

import (
	"fmt"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

var _ = Describe("ParamDecl", func() {
	var node *ast.ParamDecl

	BeforeEach(func() {
		node = &ast.ParamDecl{Type: &types.Bool{}}
	})

	Context("named type", func() {
		BeforeEach(func() {
			node.Type = &types.Named{Name: "Number"}
		})

		It("must resolve to alias", func() {
			block := &ast.BlockStmt{Nodes: []ast.Node{
				&ast.AliasDecl{Name: "Number", Type: &types.Bool{}},
				node,
			}}

			ty, err := resolveForType(block, node)
			Expect(err).NotTo(HaveOccurred())
			Expect(ty).To(HaveFlag(types.FlagLValue))
			ExpectTypesToMatch(ty, &types.Bool{})
		})
	})

	It("must have an lvalue type", func() {
		ty, _ := resolveType(node)
		Expect(ty).To(HaveFlag(types.FlagLValue))
		ExpectTypesToMatch(ty, &types.Bool{})
	})
})

var _ = Describe("ExternFuncStmt", func() {
	var stmt *ast.ExternFuncStmt

	BeforeEach(func() {
		stmt = &ast.ExternFuncStmt{
			Name: "foo",
			Parameters: []*ast.ParamDecl{
				{Name: "a", Type: &types.Bool{}},
			},
			RetType: &types.Float{},
		}
	})

	It("must turn into a Function type", func() {
		ty, err := resolveType(stmt)
		Expect(err).NotTo(HaveOccurred())
		ExpectTypesToMatch(ty, &types.Function{
			Parameters: []types.Type{&types.Bool{}},
			ReturnType: &types.Float{},
		})
	})

	It("must have a return type", func() {
		stmt.RetType = nil

		_, err := resolveType(stmt)
		Expect(err).To(Equal(fmt.Errorf(MissingReturnType)))
	})

	It("must lookup named types", func() {
		stmt.Parameters[0].Type = &types.Named{Name: "Number"}
		stmt.RetType = &types.Named{Name: "Number"}

		alias := &ast.AliasDecl{Name: "Number", Type: &types.Bool{}}
		block := &ast.BlockStmt{Nodes: []ast.Node{alias, stmt}}

		ty, err := resolveForType(block, stmt)
		Expect(err).NotTo(HaveOccurred())
		ExpectTypesToMatch(ty, &types.Function{
			Parameters: []types.Type{
				&types.Alias{Name: "Number", OriginalType: &types.Bool{}},
			},
			ReturnType: &types.Alias{Name: "Number", OriginalType: &types.Bool{}},
		})
	})
})

var _ = Describe("ArrayAccessExpr", func() {
	var node *ast.ArrayAccessExpr

	BeforeEach(func() {
		node = &ast.ArrayAccessExpr{
			Object: newMockExpr(&types.Array{
				InnerType: &types.Bool{},
			}),
			Index: newMockExpr(&types.Int{}),
		}
	})

	It("must resolve to the array member type", func() {
		ty, _ := resolveType(node)
		Expect(ty).To(Equal(&types.Bool{}))
	})

	Context("object", func() {
		It("must be an array", func() {
			node.Object = newMockExpr(&types.Int{})

			_, err := resolveType(node)
			Expect(err).To(Equal(fmt.Errorf(ArrayAccessNotArray,
				&types.Int{})))
		})
	})

	Context("index", func() {
		It("must be an integer", func() {
			node.Index = newMockExpr(&types.Bool{})

			_, err := resolveType(node)
			Expect(err).To(Equal(fmt.Errorf(ArrayAccessIndexNonInt,
				&types.Bool{})))
		})
	})
})

var _ = Describe("ArrayExpr", func() {
	var expr *ast.ArrayExpr

	BeforeEach(func() {
		expr = &ast.ArrayExpr{
			Members: []ast.Expression{newMockExpr(&types.Bool{})},
		}
	})

	Context("no members", func() {
		BeforeEach(func() {
			expr.Members = nil
		})

		// TODO: this should be unresolved[] and receive type hints from parent nodes
		It("should fail", func() {
			_, err := resolveType(expr)
			Expect(err).To(Equal(fmt.Errorf(NoMembers)))
		})
	})

	Context("one member", func() {
		It("should be an array of the member type", func() {
			ty, err := resolveType(expr)
			Expect(err).To(BeNil())
			Expect(ty).To(Equal(&types.Array{InnerType: &types.Bool{}}))
		})
	})

	Context("multiple members", func() {
		BeforeEach(func() {
			expr.Members = []ast.Expression{
				newMockExpr(&types.Bool{}),
				newMockExpr(&types.Bool{}),
			}
		})

		Context("same type", func() {
			It("should be an array of the same type", func() {
				ty, err := resolveType(expr)
				Expect(err).To(BeNil())
				Expect(ty).To(Equal(&types.Array{InnerType: &types.Bool{}}))
			})
		})

		Context("different types", func() {
			BeforeEach(func() {
				expr.Members[1] = newMockExpr(&types.Int{})
			})

			It("should fail", func() {
				_, err := resolveType(expr)
				Expect(err).To(Equal(fmt.Errorf(InconsistentMemberTypes)))
			})
		})
	})
})

var _ = Describe("UnaryExpr", func() {
	Context("bitwise not operator", func() {
		operator := "~"

		Context("integer operand", func() {
			operand := newMockExpr(&types.Int{})
			ty, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should not have an error", func() {
				Expect(err).To(BeNil())
			})

			It("should return the original type", func() {
				Expect(ty).To(Equal(&types.Int{}))
			})
		})

		Context("non-integer operand", func() {
			operand := newMockExpr(&types.Bool{})
			_, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should fail", func() {
				Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid, operator,
					&types.Bool{})))
			})
		})
	})

	Context("logical not operator", func() {
		operator := "!"

		Context("boolean operand", func() {
			operand := newMockExpr(&types.Bool{})
			ty, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should not have an error", func() {
				Expect(err).To(BeNil())
			})

			It("should return the original type", func() {
				Expect(ty).To(Equal(&types.Bool{}))
			})
		})

		Context("non-boolean operand", func() {
			operand := newMockExpr(&types.Int{})
			_, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should fail", func() {
				Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid, operator,
					&types.Int{})))
			})
		})
	})

	Context("unary negation operator", func() {
		operator := "-"

		Context("numeric operand", func() {
			operand := newMockExpr(&types.Double{})
			ty, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should not have an error", func() {
				Expect(err).To(BeNil())
			})

			It("should return the original type", func() {
				Expect(ty).To(Equal(&types.Double{}))
			})
		})

		Context("non-numeric operand", func() {
			operand := newMockExpr(&types.Bool{})
			_, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should fail", func() {
				Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid, operator,
					&types.Bool{})))
			})
		})
	})

	Context("increment operator", func() {
		operator := "++"

		Context("lvalue", func() {
			Context("numeric operand", func() {
				operandTy := &types.Double{}
				operandTy.SetFlag(types.FlagLValue)

				operand := newMockExpr(operandTy)
				ty, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should not have an error", func() {
					Expect(err).To(BeNil())
				})

				It("should return the original type", func() {
					Expect(ty).To(Equal(operandTy.Clone()))
				})
			})

			Context("non-numeric operand", func() {
				operandTy := &types.Bool{}
				operandTy.SetFlag(types.FlagLValue)

				operand := newMockExpr(operandTy)
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid,
						operator, operandTy)))
				})
			})
		})

		Context("non-lvalue", func() {
			Context("numeric operand", func() {
				operand := newMockExpr(&types.Double{})
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpNonLvalue,
						operator)))
				})
			})

			Context("non-numeric operand", func() {
				operand := newMockExpr(&types.Bool{})
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpNonLvalue,
						operator)))
				})
			})
		})
	})

	Context("decrement operator", func() {
		operator := "--"

		Context("lvalue", func() {
			Context("numeric operand", func() {
				operandTy := &types.Double{}
				operandTy.SetFlag(types.FlagLValue)

				operand := newMockExpr(operandTy)
				ty, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should not have an error", func() {
					Expect(err).To(BeNil())
				})

				It("should return the original type", func() {
					Expect(ty).To(Equal(operandTy.Clone()))
				})
			})

			Context("non-numeric operand", func() {
				operandTy := &types.Bool{}
				operandTy.SetFlag(types.FlagLValue)

				operand := newMockExpr(operandTy)
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid,
						operator, operandTy)))
				})
			})
		})

		Context("non-lvalue", func() {
			Context("numeric operand", func() {
				operand := newMockExpr(&types.Double{})
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpNonLvalue,
						operator)))
				})
			})

			Context("non-numeric operand", func() {
				operand := newMockExpr(&types.Bool{})
				_, err := resolveType(&ast.UnaryExpr{
					Operation: operator,
					Operand:   operand,
				})

				It("should fail", func() {
					Expect(err).To(Equal(fmt.Errorf(UnaryOpNonLvalue,
						operator)))
				})
			})
		})
	})

	Context("address-of operator", func() {
		operator := "&"

		Context("lvalue", func() {
			operandTy := &types.Double{}
			operandTy.SetFlag(types.FlagLValue)

			operand := newMockExpr(operandTy)
			ty, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should not have an error", func() {
				Expect(err).To(BeNil())
			})

			It("should return a pointer to the original type", func() {
				Expect(ty).To(Equal(&types.Pointer{
					InnerType: operandTy.Clone(),
				}))
			})
		})

		Context("non-lvalue", func() {
			operand := newMockExpr(&types.Double{})
			_, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should fail", func() {
				Expect(err).To(Equal(fmt.Errorf(UnaryOpNonLvalue,
					operator)))
			})
		})
	})

	Context("address inderection operator", func() {
		operator := "*"

		Context("pointer operand", func() {
			operand := newMockExpr(&types.Pointer{
				InnerType: &types.Double{},
			})

			ty, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should not have an error", func() {
				Expect(err).To(BeNil())
			})

			It("should return the pointed-to type", func() {
				Expect(ty).To(Equal(&types.Double{}))
			})
		})

		Context("non-pointer operand", func() {
			operand := newMockExpr(&types.Bool{})
			_, err := resolveType(&ast.UnaryExpr{
				Operation: operator,
				Operand:   operand,
			})

			It("should fail", func() {
				Expect(err).To(Equal(fmt.Errorf(UnaryOpInvalid, operator,
					&types.Bool{})))
			})
		})
	})
})

var _ = Describe("BinOpExpr", func() {
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
		Entry("!=", "!="),
		Entry(">=", ">="),
		Entry("<=", "<="),
		Entry("*", "*"),
		Entry("/", "/"),
	)

	DescribeTable("Assignment ops require LHS to be lvalue",
		func(op string) {
			instances := []struct {
				lhsLval, rhsLval, accept bool
			}{
				{false, false, false},
				{false, true, false},
				{true, false, true},
				{true, true, true},
			}

			for _, instance := range instances {
				lhsTy := &types.Int{}
				if instance.lhsLval {
					lhsTy.SetFlag(types.FlagLValue)
				}

				rhsTy := &types.Int{}
				if instance.rhsLval {
					rhsTy.SetFlag(types.FlagLValue)
				}

				_, err := getBinOpType(lhsTy, op, rhsTy)

				if !instance.accept {
					Expect(err).To(Equal(fmt.Errorf(InvalidAssignment, op)))
				} else {
					Expect(err).To(BeNil())
				}
			}
		},

		Entry("=", "="),
		Entry("+=", "+="),
		Entry("-=", "-="),
		Entry("*=", "*="),
		Entry("/=", "/="),
		Entry("^=", "^="),
		Entry("&=", "&="),
		Entry("|=", "|="),
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
		Entry("%", &types.Char{}, "%", &types.Char{}),

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

var _ = Describe("StringExpr", func() {
	It("Must be a char[]", func() {
		ty, _ := resolveType(&ast.StringExpr{})
		Expect(ty).To(Equal(&types.Array{InnerType: &types.Char{}}))
	})
})

var _ = Describe("BoolExpr", func() {
	It("Must be a bool", func() {
		ty, _ := resolveType(&ast.BoolExpr{})
		Expect(ty).To(Equal(&types.Bool{}))
	})
})

var _ = Describe("CharExpr", func() {
	It("Must be a char", func() {
		ty, _ := resolveType(&ast.CharExpr{})
		Expect(ty).To(Equal(&types.Char{}))
	})
})

var _ = Describe("DoubleExpr", func() {
	It("Must be a double", func() {
		ty, _ := resolveType(&ast.DoubleExpr{})
		Expect(ty).To(Equal(&types.Double{}))
	})
})

var _ = Describe("FloatExpr", func() {
	It("Must be a float", func() {
		ty, _ := resolveType(&ast.FloatExpr{})
		Expect(ty).To(Equal(&types.Float{}))
	})
})

var _ = Describe("IntExpr", func() {
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

var _ = Describe("UIntExpr", func() {
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

var _ = Describe("VarDecl", func() {
	var node *ast.VarDecl

	BeforeEach(func() {
		node = &ast.VarDecl{
			Name:  "foobar",
			Value: newMockExpr(&types.Int{}),
		}
	})

	It("should take on the type of the expression", func() {
		ty, err := resolveType(node)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Int{})))
	})

	It("cannot have a void type", func() {
		node.Type = &types.Void{}
		node.Value = nil

		_, err := resolveType(node)
		Expect(err).To(Equal(fmt.Errorf(VarVoidType)))
	})

	It("cannot have a void value", func() {
		node.Value = newMockExpr(&types.Void{})
		_, err := resolveType(node)
		Expect(err).To(Equal(fmt.Errorf(VarVoidType)))
	})

	It("should take on the type of the type hint (no expr)", func() {
		node.Type = &types.Int{}
		node.Value = nil

		ty, err := resolveType(node)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Int{})))
	})

	It("should be an lvalue", func() {
		ty, _ := resolveType(node)
		Expect(ty).To(HaveFlag(types.FlagLValue))
	})

	It("should take on the type of the type hint (w/ expr)", func() {
		node.Type = &types.Int{}

		ty, err := resolveType(node)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Int{})))
	})

	It("should require expression and type hint to be the same type", func() {
		node.Type = &types.Bool{}
		_, err := resolveType(node)
		Expect(err).To(Equal(fmt.Errorf(VarTypeMismatch, node.Type, &types.Int{})))
	})

	It("should require one type hint or expression", func() {
		node.Type = nil
		node.Value = nil

		_, err := resolveType(node)
		Expect(err).To(Equal(fmt.Errorf(VarIncomplete)))
	})

	It("should be able to shadow a definition in a nested scope", func() {
		block := &ast.BlockStmt{Nodes: []ast.Node{
			&ast.VarDecl{Name: "foobar", Type: &types.Bool{}},
			&ast.BlockStmt{Nodes: []ast.Node{node}},
		}}

		ty, err := resolveForType(block, node)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Int{})))
	})

	It("should not be able to shadow a definition in the same scope", func() {
		block := &ast.BlockStmt{Nodes: []ast.Node{
			&ast.VarDecl{Name: "foobar", Type: &types.Bool{}},
			node,
		}}

		_, err := resolveForType(block, node)
		Expect(err).To(Equal(fmt.Errorf(VarRedeclared, node)))
	})

	XIt("should be able to shadow a function parameter deeply nested", func() {
		block := &ast.FunctionStmt{
			Name: "fun",
			Parameters: []*ast.ParamDecl{
				{Name: "foobar", Type: &types.Float{}},
			},
			RetType: &types.Void{},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.BlockStmt{Nodes: []ast.Node{node}},
			}},
		}

		_, err := resolveForType(block, node)
		Expect(err).NotTo(HaveOccurred())
	})

	XIt("should not be able to shadow a function parameter as an immediate child", func() {
		block := &ast.FunctionStmt{
			Name: "fun",
			Parameters: []*ast.ParamDecl{
				{Name: "foobar", Type: &types.Float{}},
			},
			RetType: &types.Void{},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				node,
			}},
		}

		_, err := resolveForType(block, node)
		Expect(err).To(Equal(fmt.Errorf(VarRedeclared, node)))
	})
})

var _ = Describe("NamedIDExpr", func() {
	var node *ast.NamedIDExpr
	var original *ast.VarDecl

	BeforeEach(func() {
		node = &ast.NamedIDExpr{Name: "foobar"}
		original = &ast.VarDecl{Name: "foobar", Type: &types.Bool{}}
	})

	It("should be able to look up type from VarDecl", func() {
		block := &ast.BlockStmt{Nodes: []ast.Node{original, node}}

		ty, err := resolveForType(block, node)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Bool{})))
	})

	It("requires the reference to exist", func() {
		block := &ast.BlockStmt{Nodes: []ast.Node{node}}

		_, err := resolveForType(block, node)
		Expect(err).To(Equal(fmt.Errorf(ReferenceNotFound, "foobar")))
	})

	It("requires the reference to have the same name", func() {
		node.Name = "fizzbuzz"
		block := &ast.BlockStmt{Nodes: []ast.Node{original, node}}

		_, err := resolve(block)
		Expect(err).To(Equal(fmt.Errorf(ReferenceNotFound, "fizzbuzz")))
	})
})

var _ = Describe("AliasDecl", func() {
	alias := &ast.AliasDecl{Name: "Number", Type: &types.Int{}}

	It("should resolve to an Alias type", func() {
		ty, err := resolveType(alias)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(&types.Alias{
			Name: "Number", OriginalType: &types.Int{},
		}))
	})

	It("should resolve to an Alias type from a var decl", func() {
		varDecl := &ast.VarDecl{Name: "foobar", Type: &types.Named{Name: "Number"}}
		block := &ast.BlockStmt{Nodes: []ast.Node{alias, varDecl}}

		ty, err := resolveForType(block, varDecl)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Alias{
			Name: "Number", OriginalType: &types.Int{},
		})))
	})

	It("should resolve to an Alias type from nested Aliases", func() {
		alias2 := &ast.AliasDecl{Name: "Number2", Type: &types.Named{Name: "Number"}}
		varDecl := &ast.VarDecl{Name: "foobar", Type: &types.Named{Name: "Number2"}}
		block := &ast.BlockStmt{Nodes: []ast.Node{alias, alias2, varDecl}}

		ty, err := resolveForType(block, varDecl)
		Expect(err).To(BeNil())
		Expect(ty).To(Equal(makeLvalue(&types.Alias{
			Name: "Number2", OriginalType: &types.Alias{
				Name: "Number", OriginalType: &types.Int{},
			},
		})))
	})
})

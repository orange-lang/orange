package analysis

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

func getType(node ast.Node) (types.Type, []error) {
	visitor := NewTypeResolutionVisitor()

	node.Accept(visitor)

	return visitor.GetType(), visitor.GetErrors()
}

type typeResolutionVisitor struct {
	ast.DefaultNodeVisitor

	Type   types.Type
	Errors []error
}

func (v *typeResolutionVisitor) GetType() types.Type { return v.Type }
func (v *typeResolutionVisitor) GetErrors() []error  { return v.Errors }

func isBinOp(op string) bool {
	switch op {
	case "||", "&&", "!", "==", "!=", "<=", ">=", "<", ">", "+",
		"-", "/", "*", "%", "|", "&", "^", "<<", ">>", "=", "+=", "-=",
		"/=", "*=", "%=", "|=", "&=", "^=", "<<=", ">>=":
		return true
	default:
		return false
	}
}

func isArithmeticOp(op string) bool {
	return op == "+" || op == "-" || op == "/" || op == "*"
}

func isNumericType(ty types.Type) bool {
	switch ty.(type) {
	case *types.Int:
		return true
	case *types.Float:
		return true
	case *types.Double:
		return true
	default:
		return false
	}
}

func isVoidType(ty types.Type) bool {
	_, isVoid := ty.(*types.Void)
	return isVoid
}

func (v *typeResolutionVisitor) VisitBinaryExpr(node *ast.BinaryExpr) {
	lhsType, lhsErrors := getType(node.LHS)
	rhsType, rhsErrors := getType(node.RHS)

	v.Errors = append(v.Errors, lhsErrors...)
	v.Errors = append(v.Errors, rhsErrors...)

	if !isBinOp(node.Operation) {
		v.Errors = append(v.Errors,
			fmt.Errorf("%v is not a valid binary operation", node.Operation))
	}

	if isVoidType(lhsType) || isVoidType(rhsType) {
		v.Errors = append(v.Errors, errors.New("Cannot perform binary operation on void types"))
	}

	if !lhsType.Equals(rhsType, false) {
		v.Errors = append(v.Errors, errors.New("LHS and RHS do not match"))
	}

	if isArithmeticOp(node.Operation) &&
		!(isNumericType(lhsType) && isNumericType(rhsType)) {
		v.Errors = append(v.Errors, fmt.Errorf("Operation %v not valid for types %v and %v",
			node.Operation, lhsType, rhsType))
	}

	v.Type = lhsType.Clone()
	v.Type.UnsetFlag(types.FlagConst | types.FlagLValue)
}

func (v *typeResolutionVisitor) VisitStringExpr(node *ast.StringExpr) {
	v.Type = &types.Array{InnerType: &types.Char{}}
}

func (v *typeResolutionVisitor) VisitBoolExpr(node *ast.BoolExpr) {
	v.Type = &types.Bool{}
}

func (v *typeResolutionVisitor) VisitCharExpr(node *ast.CharExpr) {
	v.Type = &types.Char{}
}

func (v *typeResolutionVisitor) VisitIntExpr(node *ast.IntExpr) {
	v.Type = &types.Int{Signed: true, Size: node.Size}
}

func (v *typeResolutionVisitor) VisitUIntExpr(node *ast.UIntExpr) {
	v.Type = &types.Int{Signed: false, Size: node.Size}
}

func (v *typeResolutionVisitor) VisitDoubleExpr(node *ast.DoubleExpr) {
	v.Type = &types.Double{}
}

func (v *typeResolutionVisitor) VisitFloatExpr(node *ast.FloatExpr) {
	v.Type = &types.Float{}
}

func NewTypeResolutionVisitor() *typeResolutionVisitor {
	return &typeResolutionVisitor{
		Type:   &types.Unresolved{},
		Errors: []error{},
	}
}

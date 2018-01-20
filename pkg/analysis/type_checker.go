package analysis

import (
	"fmt"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

type typeChecker struct {
	ast.DefaultNodeVisitor

	currentScope *Scope
	typeInfo     *TypeInfo

	firstError error

	Error func(e error)
}

func (v *typeChecker) GetError() error { return v.firstError }

func (v *typeChecker) addError(str string, args ...interface{}) {
	err := fmt.Errorf(str, args...)

	if v.firstError == nil {
		v.firstError = err
	}

	if v.Error != nil {
		v.Error(err)
	}
}

// getType walks a node and looks up its type in the cache if it
// doesn't already exist
func (v *typeChecker) getType(node ast.Node) (types.Type, bool) {
	if ty, ok := v.typeInfo.Types[node]; ok {
		return ty, true
	}

	node.Accept(v)
	ty, ok := v.typeInfo.Types[node]
	return ty, ok
}

func (v *typeChecker) SetType(node ast.Node, ty types.Type) {
	v.typeInfo.Types[node] = ty
}

func (v *typeChecker) VisitBinaryExpr(node *ast.BinaryExpr) {
	lhsType, lhsOk := v.getType(node.LHS)
	rhsType, rhsOk := v.getType(node.RHS)

	if !lhsOk || !rhsOk {
		return
	}

	hadError := false

	reportError := func(str string, args ...interface{}) {
		v.addError(str, args...)
		hadError = true
	}

	if !isBinOp(node.Operation) {
		reportError(InvalidBinOp, node.Operation)
	}

	if isVoidType(lhsType) || isVoidType(rhsType) {
		reportError(BinOpOnVoid)
	}

	if !lhsType.Equals(rhsType, false) {
		reportError(BinOpMismatch)
	}

	if isArithmeticOp(node.Operation) {
		if !isNumericType(lhsType) || !isNumericType(rhsType) {
			reportError(BinOpInvalid, node.Operation, lhsType, rhsType)
		}
	}

	if isLogicalOp(node.Operation) {
		if !isBooleanType(lhsType) || !isBooleanType(rhsType) {
			reportError(BinOpLogicalOpErr, node.Operation)
		}
	}

	if isAssignmentOp(node.Operation) && !lhsType.GetFlag(types.FlagLValue) {
		reportError(InvalidAssignment, node.Operation)
	}

	if !hadError {
		ty := lhsType.Clone()
		ty.UnsetFlag(types.FlagConst | types.FlagLValue)
		v.SetType(node, ty)
	}
}

func (v *typeChecker) VisitStringExpr(node *ast.StringExpr) {
	v.SetType(node, &types.Array{InnerType: &types.Char{}})
}

func (v *typeChecker) VisitBoolExpr(node *ast.BoolExpr) {
	v.SetType(node, &types.Bool{})
}

func (v *typeChecker) VisitCharExpr(node *ast.CharExpr) {
	v.SetType(node, &types.Char{})
}

func (v *typeChecker) VisitIntExpr(node *ast.IntExpr) {
	v.SetType(node, &types.Int{Signed: true, Size: node.Size})
}

func (v *typeChecker) VisitUIntExpr(node *ast.UIntExpr) {
	v.SetType(node, &types.Int{Signed: false, Size: node.Size})
}

func (v *typeChecker) VisitDoubleExpr(node *ast.DoubleExpr) {
	v.SetType(node, &types.Double{})
}

func (v *typeChecker) VisitFloatExpr(node *ast.FloatExpr) {
	v.SetType(node, &types.Float{})
}

func (v *typeChecker) VisitVarDecl(node *ast.VarDecl) {
	var valueTy, hintTy, varType types.Type

	if node.Type != nil {
		hintTy = node.Type
		varType = hintTy
	}

	if node.Value != nil {
		valueTy, _ = v.getType(node.Value)
		varType = valueTy
	}

	if valueTy != nil && hintTy != nil && !valueTy.Equals(hintTy, false) {
		v.addError(VarTypeMismatch, hintTy, valueTy)
	} else if node.Type == nil && node.Value == nil {
		v.addError(VarIncomplete)
	} else if _, isVoid := varType.(*types.Void); isVoid {
		v.addError(VarVoidType)
	} else if varType != nil {
		v.SetType(node, varType.Clone())
	}
}

func (v *typeChecker) VisitNamedIDExpr(node *ast.NamedIDExpr) {
	ref, err := v.currentScope.FindDecl(v.typeInfo.hierarchy, node.Name, node)

	if err != nil {
		v.addError(err.Error())
		return
	} else if ref == nil {
		v.addError(ReferenceNotFound, node.Name)
		return
	}

	if _, isVar := ref.(*ast.VarDecl); !isVar {
		panic("cannot handle references to non-variables yet")
	}

	refTy, _ := v.getType(ref)
	v.SetType(node, refTy.Clone())
}

func newTypeChecker(scope *Scope, ti *TypeInfo) *typeChecker {
	return &typeChecker{
		currentScope: scope,
		typeInfo:     ti,
	}
}

package analysis

const (
	// BinaryExpr
	InvalidBinOp      = "%v is not a valid binary operation"
	BinOpOnVoid       = "cannot perform binary operations on void types"
	BinOpMismatch     = "types of LHS and RHS do not match"
	BinOpInvalid      = "operation %v not valid for types %v and %v"
	BinOpLogicalOpErr = "operation %v only valid when both LHS and RHS are boolean types"
)

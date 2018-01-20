package analysis

const (
	// BinaryExpr
	InvalidBinOp      = "%v is not a valid binary operation"
	BinOpOnVoid       = "cannot perform binary operations on void types"
	BinOpMismatch     = "types of LHS and RHS do not match"
	BinOpInvalid      = "operation %v not valid for types %v and %v"
	BinOpLogicalOpErr = "operation %v only valid when both LHS and RHS are boolean types"

	// Referencs
	UseBeforeDeclared = "expression %v is using identifier %v before it is declared"

	// Internal Error
	InvalidSearchUser = "node searching for declaration outside of the scope where it is declared"
)

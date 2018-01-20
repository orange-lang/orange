package analysis

const (
	// BinaryExpr
	InvalidBinOp      = "%v is not a valid binary operation"
	BinOpOnVoid       = "cannot perform binary operations on void types"
	BinOpMismatch     = "types of LHS and RHS do not match"
	BinOpInvalid      = "operation %v not valid for types %v and %v"
	BinOpLogicalOpErr = "operation %v only valid when both LHS and RHS are boolean types"
	InvalidAssignment = "LHS of assignment operator %v must be an lvalue"

	// Referencs
	UseBeforeDeclared = "expression %v is using identifier %v before it is declared"

	// VarDecl
	VarVoidType     = "variables cannot be type void"
	VarTypeMismatch = "variable declared as type %v but assigned initial value of type %v"
	VarIncomplete   = "variable declarations require at least a type or an initial value"

	// Internal Error
	InvalidSearchUser = "node searching for declaration outside of the scope where it is declared"
)

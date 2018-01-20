package analysis

import "github.com/orange-lang/orange/pkg/types"

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

func isLogicalOp(op string) bool {
	return op == "&&" || op == "||"
}

func isAssignmentOp(op string) bool {
	return op == "=" || op == "+=" || op == "-=" || op == "/=" ||
		op == "*=" || op == "&=" || op == "^=" || op == "|="
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

func isBooleanType(ty types.Type) bool {
	if _, ok := ty.(*types.Bool); ok {
		return true
	}

	return false
}

func isVoidType(ty types.Type) bool {
	_, isVoid := ty.(*types.Void)
	return isVoid
}

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
	switch getRealType(ty).(type) {
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

func isIntegerType(ty types.Type) bool {
	switch getRealType(ty).(type) {
	case *types.Int:
		return true
	default:
		return false
	}
}

func getRealType(ty types.Type) types.Type {
	if casted, ok := ty.(*types.Alias); ok {
		return getRealType(casted.OriginalType)
	}

	return ty
}

func isPointerType(ty types.Type) bool {
	if _, ok := getRealType(ty).(*types.Pointer); ok {
		return true
	}

	return false
}

func isBooleanType(ty types.Type) bool {
	if _, ok := getRealType(ty).(*types.Bool); ok {
		return true
	}

	return false
}

func isVoidType(ty types.Type) bool {
	if _, isVoid := getRealType(ty).(*types.Void); isVoid {
		return true
	}

	return false
}

package token

type Token int16

const (
	EOF Token = iota

	//
	// Values
	//

	IntVal
	Int8Val
	Int16Val
	Int32Val
	Int64Val
	UIntVal
	UInt8Val
	UInt16Val
	UInt32Val
	UInt64Val
	FloatVal
	DoubleVal
	StringVal
	CharVal
	BoolVal

	//
	// Type Names
	//

	Int
	Int8
	Int16
	Int32
	Int64
	UInt
	UInt8
	UInt16
	UInt32
	UInt64
	Float
	Double
	String
	Char
	Bool
	Void

	//
	// Statement endings
	//

	Newline
	Semicolon

	//
	// Keywords
	//

	Var
	Enum
	Class
	Public
	Protected
	Private
	If
	Elif
	Else
	For
	While
	Do
	Break
	Continue
	Def
	Extern
	Interface
	Package
	Import
	New
	Delete
	Get
	Set
	Virtual
	Final
	Where
	Data
	Extend
	Static
	Const
	Try
	Catch
	Finally
	Throw
	Of
	Property
	This
	Super
	Alias
	Return

	//
	// Operators
	//

	OpenParen
	CloseParen
	OpenCurly
	CloseCurly
	OpenBracket
	CloseBracket
	Dot
	Comma
	Colon
	Arrow
	Elipsis

	//
	// Comparison operators
	//

	LogicalOr
	LogicalAnd
	LogicalNot
	Question
	EQ
	NEQ
	LE
	GE
	LT
	GT

	//
	// Mathematical operators
	//

	Plus
	Minus
	Divide
	Times
	Mod
	BitOr
	BitAnd
	BitXor
	BitNot
	ShiftLeft
	ShiftRight

	Assign
	PlusAssign
	MinusAssign
	DivideAssign
	TimesAssign
	ModAssign
	BitOrAssign
	BitAndAssign
	BitXorAssign
	ShiftLeftAssign
	ShiftRightAssign

	Increment
	Decrement

	//
	// Other
	//

	Identifier
)

// SignedValue returns true if the token represents a signed integer value
func (t Token) SignedValue() bool {
	signedTokens := []Token{
		IntVal, Int8Val, Int16Val, Int32Val, Int64Val,
		Int, Int8, Int16, Int32, Int64,
	}

	for _, signedToken := range signedTokens {
		if signedToken == t {
			return true
		}
	}

	return false
}

// IntegerSize returns the bitsize of the token if it's an integer, -1 otherwise
func (t Token) IntegerSize() int {
	if t == IntVal || t == UIntVal || t == Int || t == UInt {
		return 64
	} else if t == Int8Val || t == UInt8Val || t == Int8 || t == UInt8 {
		return 8
	} else if t == Int16Val || t == UInt16Val || t == Int16 || t == UInt16 {
		return 16
	} else if t == Int32Val || t == UInt32Val || t == Int32 || t == UInt32 {
		return 32
	} else if t == Int64Val || t == UInt64Val || t == Int64 || t == UInt64 {
		return 64
	}

	return -1
}

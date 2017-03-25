package ast

type Type uint8

const (
	IntType Type = iota + 1
	FloatType
	DoubleType
	BoolType
	CharType
	ArrayType
	PointerType
	NamedType
)

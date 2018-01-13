package ast

type UnaryOrder int8

const (
	PrefixOrder UnaryOrder = iota
	PostfixOrder
)

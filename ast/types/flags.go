package types

type Flag int

const (
	FlagNone  Flag = 0
	FlagConst      = 1 << iota
	FlagLValue
)

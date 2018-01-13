package ast

type LoopConditionTime int8

const (
	CheckBefore LoopConditionTime = iota + 1
	CheckAfter
)

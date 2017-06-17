package ast

type Type interface {
	isType()
}

type VoidType struct{}

type IntType struct {
	Size   int
	Signed bool
}

type NamedType struct {
	Name string
}

type FloatType struct{}

type DoubleType struct{}

type BoolType struct{}

type CharType struct{}

type ArrayType struct {
	InnerType Type
}

type PointerType struct {
	InnerType Type
}

type ConstType struct {
	InnerType Type
}

func (t VoidType) isType()    {}
func (t IntType) isType()     {}
func (t NamedType) isType()   {}
func (t FloatType) isType()   {}
func (t DoubleType) isType()  {}
func (t BoolType) isType()    {}
func (t CharType) isType()    {}
func (t ArrayType) isType()   {}
func (t PointerType) isType() {}
func (t ConstType) isType()   {}

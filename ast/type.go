package ast

type TypeFlags int

const (
	FlagConst TypeFlags = 1 << iota
	FlagLValue
)

type TypeBase struct{ Flags TypeFlags }

func (b *TypeBase) GetFlag(flags TypeFlags) bool { return (b.Flags & flags) > 0 }
func (b *TypeBase) SetFlag(flags TypeFlags)      { b.Flags |= flags }
func (b *TypeBase) UnsetFlags(flags TypeFlags)   { b.Flags = (b.Flags | flags) ^ flags }

type Type interface {
	IsType()

	Clone() Type
	Equals(to Type) bool

	SetFlag(flags TypeFlags)
	UnsetFlags(flags TypeFlags)
	GetFlag(flags TypeFlags) bool
}

type UnresolvedType struct{ TypeBase }

type VoidType struct{ TypeBase }

type IntType struct {
	TypeBase
	Size   int
	Signed bool
}

type NamedType struct {
	TypeBase
	Name string
}

type GenericAnnotation struct {
	TypeBase
	Type        *NamedType
	Annotations []Type
}

type FloatType struct{ TypeBase }

type DoubleType struct{ TypeBase }

type BoolType struct{ TypeBase }

type CharType struct{ TypeBase }

type ArrayType struct {
	TypeBase
	InnerType Type
}

type PointerType struct {
	TypeBase
	InnerType Type
}

func (t GenericAnnotation) IsType() {}
func (t UnresolvedType) IsType()    {}
func (t VoidType) IsType()          {}
func (t IntType) IsType()           {}
func (t NamedType) IsType()         {}
func (t FloatType) IsType()         {}
func (t DoubleType) IsType()        {}
func (t BoolType) IsType()          {}
func (t CharType) IsType()          {}
func (t ArrayType) IsType()         {}
func (t PointerType) IsType()       {}

func (t GenericAnnotation) Clone() Type { return &t }
func (t UnresolvedType) Clone() Type    { return &t }
func (t VoidType) Clone() Type          { return &t }
func (t IntType) Clone() Type           { return &t }
func (t NamedType) Clone() Type         { return &t }
func (t FloatType) Clone() Type         { return &t }
func (t DoubleType) Clone() Type        { return &t }
func (t BoolType) Clone() Type          { return &t }
func (t CharType) Clone() Type          { return &t }
func (t ArrayType) Clone() Type         { return &t }
func (t PointerType) Clone() Type       { return &t }

func (t GenericAnnotation) Equals(to Type) bool {
	otherTy, ok := to.(*GenericAnnotation)

	if !ok || !otherTy.Type.Equals(t.Type) ||
		len(otherTy.Annotations) != len(t.Annotations) {
		return false
	}

	for i := range t.Annotations {
		if !t.Annotations[i].Equals(otherTy.Annotations[i]) {
			return false
		}
	}

	return true
}

func (t UnresolvedType) Equals(to Type) bool {
	other, ok := to.(*UnresolvedType)
	return ok && other.Flags == t.Flags
}

func (t VoidType) Equals(to Type) bool {
	other, ok := to.(*VoidType)
	return ok && other.Flags == t.Flags
}

func (t IntType) Equals(to Type) bool {
	intTy, ok := to.(*IntType)
	return ok && intTy.Signed == t.Signed && intTy.Size == t.Size &&
		intTy.Flags == t.Flags
}

func (t NamedType) Equals(to Type) bool {
	otherTy, ok := to.(*NamedType)
	return ok && otherTy.Name == t.Name && otherTy.Flags == t.Flags
}

func (t FloatType) Equals(to Type) bool {
	other, ok := to.(*FloatType)
	return ok && other.Flags == t.Flags
}

func (t DoubleType) Equals(to Type) bool {
	other, ok := to.(*DoubleType)
	return ok && other.Flags == t.Flags
}

func (t BoolType) Equals(to Type) bool {
	other, ok := to.(*BoolType)
	return ok && other.Flags == t.Flags
}

func (t CharType) Equals(to Type) bool {
	other, ok := to.(*CharType)
	return ok && other.Flags == t.Flags
}

func (t ArrayType) Equals(to Type) bool {
	otherTy, ok := to.(*ArrayType)
	return ok && otherTy.InnerType.Equals(t.InnerType) && otherTy.Flags == t.Flags
}

func (t PointerType) Equals(to Type) bool {
	otherTy, ok := to.(*PointerType)
	return ok && otherTy.InnerType.Equals(t.InnerType) && otherTy.Flags == t.Flags
}

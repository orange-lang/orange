package types

type Type interface {
	IsType()

	Clone() Type
	Equals(to Type, compareFlags bool) bool

	SetFlag(f Flag)
	UnsetFlag(f Flag)
	GetFlag(f Flag) bool
	Flags() Flag
}

type Unresolved struct{ Base }

type Void struct{ Base }

type Int struct {
	Base
	Size   int
	Signed bool
}

type Named struct {
	Base
	Name string
}

type Annotation struct {
	Base
	Type        *Named
	Annotations []Type
}

type Float struct{ Base }

type Double struct{ Base }

type Bool struct{ Base }

type Char struct{ Base }

type Array struct {
	Base
	InnerType Type
}

type Pointer struct {
	Base
	InnerType Type
}

type Reference struct {
	Base
	InnerType Type
}

type Alias struct {
	Base
	Name         string
	OriginalType Type
}

type Function struct {
	Base
	Parameters []Type
	ReturnType Type
}

func (t Annotation) IsType() {}
func (t Unresolved) IsType() {}
func (t Void) IsType()       {}
func (t Int) IsType()        {}
func (t Named) IsType()      {}
func (t Float) IsType()      {}
func (t Double) IsType()     {}
func (t Bool) IsType()       {}
func (t Char) IsType()       {}
func (t Array) IsType()      {}
func (t Pointer) IsType()    {}
func (t Reference) IsType()  {}
func (t Alias) IsType()      {}
func (t Function) IsType()   {}

func (t Annotation) Clone() Type { return &t }
func (t Unresolved) Clone() Type { return &t }
func (t Void) Clone() Type       { return &t }
func (t Int) Clone() Type        { return &t }
func (t Named) Clone() Type      { return &t }
func (t Float) Clone() Type      { return &t }
func (t Double) Clone() Type     { return &t }
func (t Bool) Clone() Type       { return &t }
func (t Char) Clone() Type       { return &t }
func (t Array) Clone() Type      { return &t }
func (t Pointer) Clone() Type    { return &t }
func (t Reference) Clone() Type  { return &t }
func (t Alias) Clone() Type      { return &t }
func (t Function) Clone() Type   { return &t }

func (t Annotation) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	otherTy, ok := getRealType(to).(*Annotation)

	if !ok || !otherTy.Type.Equals(t.Type, compareFlags) ||
		len(otherTy.Annotations) != len(t.Annotations) {
		return false
	}

	for i := range t.Annotations {
		if !t.Annotations[i].Equals(otherTy.Annotations[i], compareFlags) {
			return false
		}
	}

	return true
}

func (t Unresolved) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Unresolved)
	return ok
}

func (t Void) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Void)
	return ok
}

func (t Int) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	other, ok := getRealType(to).(*Int)
	return ok && other.Signed == t.Signed && other.Size == t.Size
}

func (t Named) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	otherTy, ok := getRealType(to).(*Named)
	return ok && otherTy.Name == t.Name
}

func (t Float) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Float)
	return ok
}

func (t Double) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Double)
	return ok
}

func (t Bool) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Bool)
	return ok
}

func (t Char) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	_, ok := getRealType(to).(*Char)
	return ok
}

func (t Array) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	otherTy, ok := getRealType(to).(*Array)
	return ok && otherTy.InnerType.Equals(t.InnerType, compareFlags)
}

func (t Pointer) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	otherTy, ok := getRealType(to).(*Pointer)
	return ok && otherTy.InnerType.Equals(t.InnerType, compareFlags)
}

func (t Reference) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	otherTy, ok := getRealType(to).(*Reference)
	return ok && otherTy.InnerType.Equals(t.InnerType, compareFlags)
}

func (t Alias) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	return getRealType(&t).Equals(getRealType(to), compareFlags)
}

func (t Function) Equals(to Type, compareFlags bool) bool {
	if compareFlags && to.Flags() != t.Flags() {
		return false
	}

	if otherTy, ok := getRealType(to).(*Function); !ok {
		return false
	} else if len(t.Parameters) != len(otherTy.Parameters) {
		return false
	} else if !otherTy.ReturnType.Equals(t.ReturnType, compareFlags) {
		return false
	} else {
		for i := range t.Parameters {
			ourParam := t.Parameters[i]
			theirParam := otherTy.Parameters[i]

			if !ourParam.Equals(theirParam, compareFlags) {
				return false
			}
		}
	}

	return true
}

// getRealType will return the original type if the type is an alias;
// otherwise just returns the source type.
func getRealType(source Type) Type {
	if ty, isAlias := source.(*Alias); isAlias {
		return getRealType(ty.OriginalType)
	}

	return source
}

package types

type Base struct{ flags Flag }

func MakeBase(flags Flag) Base {
	return Base{flags}
}

func (b *Base) GetFlag(f Flag) bool {
	return (b.flags & f) > 0
}

func (b *Base) SetFlag(f Flag) {
	b.flags |= f
}

func (b *Base) UnsetFlag(f Flag) {
	b.flags = (b.flags | f) ^ f
}

func (b *Base) Flags() Flag {
	return b.flags
}

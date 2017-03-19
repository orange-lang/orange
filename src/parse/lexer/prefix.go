package lexer

type prefix int8

const (
	NoPrefix prefix = iota
	HexadecimalPrefix
	OctalPrefix
	BinaryPrefix
)

func (p prefix) GetBase() int {
	switch p {
	case HexadecimalPrefix:
		return 16
	case BinaryPrefix:
		return 2
	case OctalPrefix:
		return 8
	default:
		return -1
	}
}

func makePrefix(r rune) prefix {
	switch r {
	case 'b':
		return BinaryPrefix
	case 'o':
		return OctalPrefix
	case 'x':
		return HexadecimalPrefix
	default:
		return NoPrefix
	}
}

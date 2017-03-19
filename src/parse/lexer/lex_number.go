package lexer

import (
	"errors"
	"fmt"
	"parse/lexer/token"
	"strconv"
	"strings"
	"unicode"
)

type prefix int8

const (
	NoPrefix prefix = iota
	HexadecimalPrefix
	OctalPrefix
	BinaryPrefix
)

func lexPrefix(s RuneStream) (prefix, error) {
	lookahead := s.Lookahead(2)
	if lookahead[0] != '0' || lookahead[1] == '.' {
		return NoPrefix, nil
	}

	if validPrefix(lookahead[1]) {
		s.Get(2)
		return getPrefixFromRune(lookahead[1]), nil
	} else if !validSuffixStarter(lookahead[0]) {
		return NoPrefix, fmt.Errorf("Invalid numeric prefix %v", lookahead[0])
	}

	return NoPrefix, nil
}

func validPrefix(r rune) bool {
	return r == 'o' || r == 'x' || r == 'b'
}

func getPrefixFromRune(r rune) prefix {
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

func validSuffixStarter(r rune) bool {
	return r == 'i' || r == 'f' || r == 'd' || r == 'u'
}

func isHexDigit(r rune) bool {
	return (r >= '0' && r <= '9') || (r >= 'a' && r <= 'f') ||
		(r >= 'A' && r <= 'F')
}

func prefixToBase(p prefix) int {
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

func validNumberForBase(n string, b int) bool {
	for _, c := range n {
		if c == '.' && b == 10 {
			continue
		}

		if !isBaseDigit(c, b) {
			return false
		}
	}

	return true
}

func isBaseDigit(r rune, b int) bool {
	if b == 2 {
		return r == '0' || r == '1'
	} else if b == 8 {
		return r >= '0' && r <= '7'
	} else if b == 10 {
		return r >= '0' && r <= '9'
	} else if b == 16 {
		return isHexDigit(r)
	}

	return false
}

func lexNumberSuffix(s RuneStream) (token.Token, error) {
	suffix := ""

	for unicode.IsLetter(s.Peek()) || unicode.IsDigit(s.Peek()) {
		suffix += string(s.Next())
	}

	suffixTable := map[string]token.Token{
		"f":   token.FloatVal,
		"d":   token.DoubleVal,
		"u":   token.UIntVal,
		"u8":  token.UInt8Val,
		"u16": token.UInt16Val,
		"u32": token.UInt32Val,
		"u64": token.UInt64Val,
		"i":   token.IntVal,
		"i8":  token.Int8Val,
		"i16": token.Int16Val,
		"i32": token.Int32Val,
		"i64": token.Int64Val,
	}

	tok, ok := suffixTable[suffix]
	if !ok && suffix != "" {
		return token.EOF, fmt.Errorf("Invalid suffix %v", suffix)
	}

	return tok, nil
}

func signedValue(t token.Token) bool {
	switch t {
	case token.IntVal:
		return true
	case token.Int8Val:
		return true
	case token.Int16Val:
		return true
	case token.Int32Val:
		return true
	case token.Int64Val:
		return true
	default:
		return false
	}
}

func lexNumber(s RuneStream) (Lexeme, error) {
	base := 10
	l := Lexeme{Token: token.IntVal}
	shouldParseSuffix := true

	p, err := lexPrefix(s)

	if err != nil {
		return l, err
	}

	if p != NoPrefix {
		base = prefixToBase(p)
		l.Token = token.UIntVal
	}

	for isHexDigit(s.Peek()) {
		val := s.Peek()

		if (val == 'f' || val == 'd') && base != 16 {
			break
		}

		l.Value += string(s.Next())

		// Consume all separators
		for s.Peek() == '_' {
			s.Next()
		}

		// Next sequence is .[character]
		next := s.Lookahead(2)
		if next[0] == '.' && isHexDigit(next[1]) == false {
			shouldParseSuffix = false
			break
		} else if next[0] == '.' && l.Token != token.DoubleVal {
			// If the next character is a period and we're
			// not already a double, let's consume it now

			l.Value += string(s.Next())
			l.Token = token.DoubleVal
		}
	}

	if !validNumberForBase(l.Value, base) {
		return l, fmt.Errorf("Invalid number %v for base %v", l.Value, base)
	}

	if shouldParseSuffix {
		tokFromSuffix, err := lexNumberSuffix(s)
		if err != nil {
			return l, err
		}

		if tokFromSuffix != token.EOF {
			l.Token = tokFromSuffix
		}

		if base != 10 && (l.Token == token.FloatVal || l.Token == token.Double) {
			return l, errors.New("Number of non-decimal base cannot be floating-point")
		}

		if base != 10 && signedValue(l.Token) {
			return l, errors.New("Number of non-decimal base cannot be signed")
		}
	}

	if l.Token != token.FloatVal && l.Token != token.DoubleVal {
		if strings.Contains(l.Value, ".") {
			return l, errors.New("Floating-point value cannot have integral suffix")
		}
	}

	if base != 10 {
		// convert the number to decimal for the string
		i, err := strconv.ParseInt(l.Value, base, 64)
		if err != nil {
			return l, errors.New("Number out of range")
		}

		l.Value = fmt.Sprintf("%v", i)
	}

	return l, nil
}

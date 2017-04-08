package lexer

import (
	"errors"
	"fmt"
	"strconv"
	"strings"
	"unicode"

	"github.com/orange-lang/orange/parse/lexer/token"
)

func lexNumber(s RuneStream) (Lexeme, error) {
	l := Lexeme{Token: token.IntVal}
	l.SetStartPosition(s)

	base := 10
	shouldParseSuffix := true

	// Get the prefix so we can get the base of the number
	if p, err := lexPrefix(s); err != nil {
		consumeUntilWhitespace(s)
		return l, err
	} else if p != NoPrefix {
		base = p.GetBase()
		l.Token = token.UIntVal
	}

	// Get the "body" of the number.
	for isHexDigit(s.Peek()) {
		val := s.Peek()

		// f and d are suffixes, but we may have peeked them
		// here thinking they were numbers.
		if base != 16 && isFloatingPointSuffix(val) {
			break
		}

		l.Value += string(s.Next())

		consumeSeparators(s)

		// Next sequence is .[character]
		if next := s.Lookahead(2); next[0] == '.' && !isHexDigit(next[1]) {
			shouldParseSuffix = false
			break
		} else if next[0] == '.' && l.Token != token.DoubleVal {
			// We've come across the first .; let's consume
			// and change to being a Double
			l.Value += string(s.Next())
			l.Token = token.DoubleVal
		}
	}

	if !validStringForBase(l.Value, base) {
		err := NewError(s, "Invalid number %v for base %v", l.Value, base)
		consumeUntilWhitespace(s)

		return l, err
	}

	if shouldParseSuffix {
		if tokFromSuffix, err := lexNumberSuffix(s); err != nil {
			return l, err
		} else if tokFromSuffix != token.EOF {
			l.Token = tokFromSuffix
		}

		if base != 10 && (l.Token == token.FloatVal || l.Token == token.Double) {
			return l, NewError(s, "Number of non-decimal base cannot be floating-point")
		}

		if base != 10 && l.Token.SignedValue() {
			return l, NewError(s, "Number of non-decimal base cannot be signed")
		}
	}

	if l.Token != token.FloatVal && l.Token != token.DoubleVal &&
		strings.Contains(l.Value, ".") {
		return l, NewError(s, "Floating-point value cannot have integral suffix")
	}

	val, err := convertNumber(l.Value, base)
	if err != nil {
		err = NewError(s, err.Error())
	}

	l.Value = val
	l.SetEndPosition(s)
	return l, err
}

func convertNumber(s string, b int) (string, error) {
	if b == 10 {
		return s, nil
	}

	i, err := strconv.ParseInt(s, b, 64)
	if err != nil {
		return s, errors.New("Number out of range")
	}

	return fmt.Sprintf("%v", i), nil
}

func lexPrefix(s RuneStream) (prefix, error) {
	if lookahead := s.Lookahead(2); lookahead[0] != '0' || !unicode.IsLetter(lookahead[1]) {
		return NoPrefix, nil
	} else if prefix := makePrefix(lookahead[1]); prefix != NoPrefix {
		s.Get(2)
		return prefix, nil
	} else if !validSuffixStarter(lookahead[1]) {
		// If the character that we're treating as a prefix would be valid
		// for a suffix, then we can ignore it. Otherwise, it's an
		// invalid suffix.
		err := NewError(s, "Invalid numeric prefix %v", string(lookahead[:2]))
		return NoPrefix, err
	}

	return NoPrefix, nil
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
		return token.EOF, NewError(s, "Invalid suffix %v", suffix)
	}

	return tok, nil
}

func consumeSeparators(s RuneStream) {
	for s.Peek() == '_' {
		s.Next()
	}
}

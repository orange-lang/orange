package lexer

import (
	"fmt"
	"unicode"
)

func (l *Lexer) lex() (Lexeme, error) {
	if l.EOF() {
		return Lexeme{}, nil
	}

	for isIgnoreableSpace(l.Stream.Peek()) {
		_ = l.Stream.Next()
	}

	next := l.Stream.Peek()

	switch true {
	case unicode.IsDigit(next):
		return lexNumber(l.Stream)
	default:
		return Lexeme{}, fmt.Errorf("Unexpected character %v", next)
	}
}

func isIgnoreableSpace(r rune) bool {
	// We can ignore anything that's not a newline
	return r != '\n' && unicode.IsSpace(r)
}

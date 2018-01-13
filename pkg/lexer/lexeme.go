package lexer

import "github.com/orange-lang/orange/pkg/token"

// Lexeme is a single unit of code retrieved from a RuneStream
type Lexeme struct {
	SourceFile string

	LineNumber      int
	ColumnNumber    int
	EndLineNumber   int
	EndColumnNumber int

	Token token.Token

	Value string
}

// SetStartPosition looks at the current position of a RuneStream and
// sets the start position values on the lexeme
func (l *Lexeme) SetStartPosition(s RuneStream) {
	pos := s.Position()
	l.LineNumber = pos.Row
	l.ColumnNumber = pos.Column
}

// SetEndPosition looks at the current position of a RuneStream and
// sets the start position values on the lexeme
func (l *Lexeme) SetEndPosition(s RuneStream) {
	pos := s.Position()

	l.EndLineNumber = pos.Row
	l.EndColumnNumber = pos.Column - 1
}

// NewLexeme returns a new Lexeme, inheriting the start position from the RuneStream
func NewLexeme(s RuneStream) Lexeme {
	pos := s.Position()

	return Lexeme{
		LineNumber:   pos.Row,
		ColumnNumber: pos.Column,
	}
}

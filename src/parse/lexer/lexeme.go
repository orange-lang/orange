package lexer

import "parse/lexer/token"

type Lexeme struct {
	SourceFile string

	LineNumber   int
	ColumnNumber int

	Token token.Token

	Value string
}

package parse

import (
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

// Parse takes a lexeme stream and returns an AST. Consumes the entire
// lexeme stream, and returns a list of errors for each parsing error.
func Parse(s lexer.LexemeStream) (ast ast.AST, errors []error) {
	for !s.EOF() {
		node, err := parseNode(s)

		if err != nil {
			errors = append(errors, err)
		} else {
			ast.Nodes = append(ast.Nodes, node)
		}
	}

	return ast, errors
}

func parseNode(s lexer.LexemeStream) (ast.Node, error) {
	lexeme, err := s.Peek()
	if err != nil {
		s.Next()
		return nil, err
	}

	switch true {
	case lexeme.Token == token.StringVal:
		return parseString(s)
	case lexeme.Token == token.BoolVal:
		return parseBoolean(s)
	case numberToken(lexeme.Token):
		return parseNumber(s)
	case lexeme.Token == token.CharVal:
		return parseChar(s)
	}

	s.Next()
	return nil, fmt.Errorf("Unexpected lexeme %v", lexeme)
}

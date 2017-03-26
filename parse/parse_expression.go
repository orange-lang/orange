package parse

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isExpressionToken(t token.Token) bool {
	return isConstantToken(t)
}

func parseExpr(s lexer.LexemeStream) (ast.Expression, error) {
	lexeme, err := s.Peek()
	if err != nil {
		s.Next()
		return nil, err
	} else if !isExpressionToken(lexeme.Token) {
		return nil, errors.New("Expected expression")
	}

	switch true {
	case isConstantToken(lexeme.Token):
		return parseConstant(s)
	}

	s.Next()
	return nil, fmt.Errorf("Unexpected lexeme %v", lexeme)
}

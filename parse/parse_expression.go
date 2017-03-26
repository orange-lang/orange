package parse

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isExpressionToken(t token.Token) bool {
	return isConstantToken(t) || t == token.OpenParen
}

func parseExpr(s lexer.LexemeStream) (ast.Expression, error) {
	node, err := parseUnary(s)
	if err != nil {
		return nil, err
	}

	// Try parsing a binary operation now
	if lexeme, err := s.Peek(); err == nil && isBinOpToken(lexeme.Token) {
		node, err = parseBinary(s, node, 0)
	}

	return node, nil
}

func parsePrimary(s lexer.LexemeStream) (ast.Expression, error) {
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
	case lexeme.Token == token.OpenParen:
		s.Next()
		expr, err := parseExpr(s)
		if err != nil {
			return nil, err
		}

		if lexeme, err := s.Next(); err != nil || lexeme.Token != token.CloseParen {
			return nil, errors.New("Expected close parenthesis")
		}

		return expr, nil
	default:
		return nil, fmt.Errorf("Unexpected lexeme %v; expected expression", lexeme.Value)
	}
}

func parseUnary(s lexer.LexemeStream) (ast.Expression, error) {
	// Placeholder. Prefix unary operators will be parsed here.
	return parseOperation(s)
}

func parseOperation(s lexer.LexemeStream) (ast.Expression, error) {
	// Placeholder. Postfix unary operators, functions, member accessing,
	// and array access will be parsed here.
	return parsePrimary(s)
}

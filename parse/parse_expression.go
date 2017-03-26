package parse

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isExpressionToken(t token.Token) bool {
	return isConstantToken(t) || t == token.OpenParen || t == token.Identifier
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

func parseUnary(s lexer.LexemeStream) (ast.Expression, error) {
	// Placeholder. Prefix unary operators will be parsed here.
	return parseOperation(s)
}

func isOperationToken(t token.Token) bool {
	return t == token.Dot
}

func parseOperation(s lexer.LexemeStream) (ast.Expression, error) {
	// Placeholder. Postfix unary operators, functions, member accessing,
	// and array access will be parsed here.
	expr, err := parsePrimary(s)
	if err != nil {
		return nil, err
	}

	lexeme, _ := s.Peek()
	for isOperationToken(lexeme.Token) {
		switch lexeme.Token {
		case token.Dot:
			expr, err = parseMemberAccess(s, expr)
			if err != nil {
				return nil, err
			}
		}

		lexeme, _ = s.Peek()
	}

	return expr, nil
}

func parseMemberAccess(s lexer.LexemeStream, lhs ast.Expression) (*ast.MemberAccessExpr, error) {
	lexeme, err := s.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.Dot {
		return nil, errors.New("Expected dot")
	}

	ident, err := s.Next()
	if err != nil || ident.Token != token.Identifier {
		return nil, errors.New("Expected identifier")
	}

	return &ast.MemberAccessExpr{Object: lhs, Name: ident.Value}, nil
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
	case lexeme.Token == token.Identifier:
		return parseIdentifier(s)
	case lexeme.Token == token.OpenParen:
		return parseParethentizedExpr(s)
	default:
		return nil, fmt.Errorf("Unexpected lexeme %v; expected expression", lexeme.Value)
	}
}

func parseIdentifier(s lexer.LexemeStream) (ast.Identifier, error) {
	lexeme, err := s.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.Identifier {
		return nil, errors.New("Expected identifier")
	}

	return &ast.NamedIDExpr{Name: lexeme.Value}, nil
}

func parseParethentizedExpr(s lexer.LexemeStream) (ast.Expression, error) {
	lexeme, err := s.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.OpenParen {
		return nil, errors.New("Expected open parenthesis")
	}

	expr, err := parseExpr(s)
	if err != nil {
		return nil, err
	}

	if lexeme, err := s.Next(); err != nil || lexeme.Token != token.CloseParen {
		return nil, errors.New("Expected close parenthesis")
	}

	return expr, nil
}

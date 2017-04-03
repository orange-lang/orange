package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isUnaryToken(t token.Token) bool {
	return t == token.Minus || t == token.LogicalNot ||
		t == token.BitNot || t == token.BitAnd || t == token.Times ||
		t == token.Increment || t == token.Decrement
}

func (p parser) parseUnary() (ast.Expression, error) {
	lexeme, err := p.expectFrom(isUnaryToken)
	if err != nil {
		return nil, err
	}

	operand, err := p.parseSingle()
	if err != nil {
		return nil, err
	}

	switch lexeme.Token {
	case token.Minus:
		return &ast.UnaryExpr{Operand: operand, Operation: "-",
			Order: ast.PrefixOrder}, nil
	case token.LogicalNot:
		return &ast.UnaryExpr{Operand: operand, Operation: "!",
			Order: ast.PrefixOrder}, nil
	case token.BitNot:
		return &ast.UnaryExpr{Operand: operand, Operation: "~",
			Order: ast.PrefixOrder}, nil
	case token.BitAnd:
		return &ast.UnaryExpr{Operand: operand, Operation: "&",
			Order: ast.PrefixOrder}, nil
	case token.Times:
		return &ast.UnaryExpr{Operand: operand, Operation: "*",
			Order: ast.PrefixOrder}, nil
	case token.Increment:
		return &ast.UnaryExpr{Operand: operand, Operation: "++",
			Order: ast.PrefixOrder}, nil
	case token.Decrement:
		return &ast.UnaryExpr{Operand: operand, Operation: "--",
			Order: ast.PrefixOrder}, nil
	default:
		return nil, errors.New("Unexpected unary token")
	}
}

func (p parser) parseUnaryPostfix(lhs ast.Expression) (*ast.UnaryExpr, error) {
	lexeme, err := p.expectFrom(isIncrementOrDecrement)
	if err != nil {
		return nil, err
	}

	return &ast.UnaryExpr{
		Operand:   lhs,
		Operation: lexeme.Value,
		Order:     ast.PostfixOrder,
	}, nil
}

func isIncrementOrDecrement(t token.Token) bool {
	return t == token.Increment || t == token.Decrement
}

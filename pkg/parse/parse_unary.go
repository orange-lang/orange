package parse

import (
	"errors"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/token"
)

func isUnaryToken(t token.Token) bool {
	return t == token.Minus || t == token.LogicalNot ||
		t == token.BitNot || t == token.BitAnd || t == token.Times ||
		t == token.Increment || t == token.Decrement
}

func (p parser) parseUnary() ast.Expression {
	lexeme := p.expectFrom(isUnaryToken)

	operand := p.parseSingle()

	switch lexeme.Token {
	case token.Minus:
		return &ast.UnaryExpr{Operand: operand, Operation: "-",
			Order: ast.PrefixOrder}
	case token.LogicalNot:
		return &ast.UnaryExpr{Operand: operand, Operation: "!",
			Order: ast.PrefixOrder}
	case token.BitNot:
		return &ast.UnaryExpr{Operand: operand, Operation: "~",
			Order: ast.PrefixOrder}
	case token.BitAnd:
		return &ast.UnaryExpr{Operand: operand, Operation: "&",
			Order: ast.PrefixOrder}
	case token.Times:
		return &ast.UnaryExpr{Operand: operand, Operation: "*",
			Order: ast.PrefixOrder}
	case token.Increment:
		return &ast.UnaryExpr{Operand: operand, Operation: "++",
			Order: ast.PrefixOrder}
	case token.Decrement:
		return &ast.UnaryExpr{Operand: operand, Operation: "--",
			Order: ast.PrefixOrder}
	default:
		panic(errors.New("Unexpected unary token"))
	}
}

func (p parser) parseUnaryPostfix(lhs ast.Expression) *ast.UnaryExpr {
	lexeme := p.expectFrom(isIncrementOrDecrement)

	return &ast.UnaryExpr{
		Operand:   lhs,
		Operation: lexeme.Value,
		Order:     ast.PostfixOrder,
	}
}

func isIncrementOrDecrement(t token.Token) bool {
	return t == token.Increment || t == token.Decrement
}

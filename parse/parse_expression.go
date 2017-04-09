package parse

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isExpressionToken(t token.Token) bool {
	return isConstantToken(t) || t == token.OpenParen || t == token.Identifier ||
		isUnaryToken(t) || t == token.OpenBracket
}

func (p parser) parseExpr() (ast.Expression, error) {
	node, err := p.parseSingle()
	if err != nil {
		return nil, err
	}

	// Try parsing a binary operation now
	if lexeme, err := p.stream.Peek(); err == nil && isBinOpToken(lexeme.Token) {
		node, err = p.parseBinary(node, 0)
	}

	return node, nil
}

func (p parser) parseSingle() (ast.Expression, error) {
	if next, _ := p.stream.Peek(); isUnaryToken(next.Token) {
		return p.parseUnary()
	}

	return p.parseOperation()
}

func isOperationToken(t token.Token) bool {
	return t == token.Dot || t == token.OpenBracket || t == token.Increment ||
		t == token.Decrement || t == token.OpenParen
}

func (p parser) parseOperation() (ast.Expression, error) {
	// Placeholder. Postfix unary operators, functions, member accessing,
	// and array access will be parsed here.
	expr, err := p.parsePrimary()
	if err != nil {
		return nil, err
	}

	lexeme, _ := p.stream.Peek()
	for isOperationToken(lexeme.Token) {
		switch lexeme.Token {
		case token.Dot:
			expr, err = p.parseMemberAccess(expr)
		case token.OpenBracket:
			expr, err = p.parseArrayAccess(expr)
		case token.Increment:
			expr, err = p.parseUnaryPostfix(expr)
		case token.Decrement:
			expr, err = p.parseUnaryPostfix(expr)
		case token.OpenParen:
			expr, err = p.parseFuncCall(expr)
		}

		if err != nil {
			return nil, err
		}

		lexeme, _ = p.stream.Peek()
	}

	return expr, nil
}

func (p parser) parseFuncCall(lhs ast.Expression) (*ast.CallExpr, error) {
	if _, err := p.expect(token.OpenParen); err != nil {
		return nil, err
	}

	// Check for a zero-argument function call
	if ok, _ := p.allow(token.CloseParen); ok {
		return &ast.CallExpr{
			Object:    lhs,
			Arguments: []ast.Expression{},
		}, nil
	}

	// Parse arguments
	args, err := p.parseExprList()
	if err != nil {
		return nil, err
	}

	if _, err := p.expect(token.CloseParen); err != nil {
		return nil, err
	}

	return &ast.CallExpr{
		Object:    lhs,
		Arguments: args,
	}, nil
}

func (p parser) parseArrayAccess(lhs ast.Expression) (*ast.ArrayAccessExpr, error) {
	if _, err := p.expect(token.OpenBracket); err != nil {
		return nil, err
	}

	expr, err := p.parseExpr()
	if err != nil {
		return nil, err
	}

	if lexeme, err := p.stream.Next(); err != nil || lexeme.Token != token.CloseBracket {
		return nil, errors.New("Expected close bracket")
	}

	return &ast.ArrayAccessExpr{Object: lhs, Index: expr}, nil
}

func (p parser) parseMemberAccess(lhs ast.Expression) (*ast.MemberAccessExpr, error) {
	if _, err := p.expect(token.Dot); err != nil {
		return nil, err
	}

	ident, err := p.stream.Next()
	if err != nil || ident.Token != token.Identifier {
		return nil, errors.New("Expected identifier")
	}

	return &ast.MemberAccessExpr{Object: lhs, Name: ident.Value}, nil
}

func (p parser) parsePrimary() (ast.Expression, error) {
	lexeme, err := p.stream.Peek()
	if err != nil {
		p.stream.Next()
		return nil, err
	} else if !isExpressionToken(lexeme.Token) {
		return nil, errors.New("Expected expression")
	}

	switch true {
	case isConstantToken(lexeme.Token):
		return p.parseConstant()
	case lexeme.Token == token.Identifier:
		return p.parseIdentifier()
	case lexeme.Token == token.OpenBracket:
		return p.parseArray()
	case lexeme.Token == token.OpenParen:
		return p.parseParethentizedExpr()
	default:
		return nil, fmt.Errorf("Unexpected lexeme %v; expected expression", lexeme.Value)
	}
}

func (p parser) parseIdentifier() (ast.Identifier, error) {
	lexeme, err := p.expect(token.Identifier)
	if err != nil {
		return nil, err
	}

	return &ast.NamedIDExpr{Name: lexeme.Value}, nil
}

func (p parser) parseArray() (*ast.ArrayExpr, error) {
	// Parse opening
	if _, err := p.expect(token.OpenBracket); err != nil {
		return nil, err
	}

	// Check for empty array
	if ok, _ := p.allow(token.CloseBracket); ok {
		return &ast.ArrayExpr{Members: []ast.Expression{}}, nil
	}

	// Parse members
	exprs, err := p.parseExprList()
	if err != nil {
		return nil, err
	}

	// Parse close bracket
	if _, err := p.expect(token.CloseBracket); err != nil {
		return nil, err
	}

	return &ast.ArrayExpr{Members: exprs}, nil
}

func (p parser) parseExprList() ([]ast.Expression, error) {
	exprs := []ast.Expression{}

	// expr (COMMA expr)*
	for true {
		expr, err := p.parseExpr()
		if err != nil {
			return nil, err
		}

		exprs = append(exprs, expr)

		if foundComma, _ := p.allow(token.Comma); !foundComma {
			break
		}
	}

	return exprs, nil
}

func (p parser) parseParethentizedExpr() (ast.Expression, error) {
	if _, err := p.expect(token.OpenParen); err != nil {
		return nil, err
	}

	expr, err := p.parseExpr()
	if err != nil {
		return nil, err
	}

	if lexeme, err := p.stream.Next(); err != nil || lexeme.Token != token.CloseParen {
		return nil, errors.New("Expected close parenthesis")
	}

	return expr, nil
}

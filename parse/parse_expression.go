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

func (p parser) parseExpr() ast.Expression {
	node := p.parseSingle()

	// Try parsing a binary operation now
	if lexeme, _ := p.stream.Peek(); isBinOpToken(lexeme.Token) {
		node = p.parseBinary(node, 0)
	}

	return node
}

func (p parser) parseSingle() ast.Expression {
	if next, _ := p.stream.Peek(); isUnaryToken(next.Token) {
		return p.parseUnary()
	}

	return p.parseOperation()
}

func isOperationToken(t token.Token) bool {
	return t == token.Dot || t == token.OpenBracket || t == token.Increment ||
		t == token.Decrement || t == token.OpenParen
}

func (p parser) parseOperation() ast.Expression {
	// Placeholder. Postfix unary operators, functions, member accessing,
	// and array access will be parsed here.
	expr := p.parsePrimary()

	lexeme, _ := p.stream.Peek()
	for isOperationToken(lexeme.Token) {
		switch lexeme.Token {
		case token.Dot:
			expr = p.parseMemberAccess(expr)
		case token.OpenBracket:
			expr = p.parseArrayAccess(expr)
		case token.Increment:
			expr = p.parseUnaryPostfix(expr)
		case token.Decrement:
			expr = p.parseUnaryPostfix(expr)
		case token.OpenParen:
			expr = p.parseFuncCall(expr)
		}

		lexeme, _ = p.stream.Peek()
	}

	return expr
}

func (p parser) parseFuncCall(lhs ast.Expression) *ast.CallExpr {
	p.expect(token.OpenParen)

	// Check for a zero-argument function call
	if ok := p.allow(token.CloseParen); ok {
		return &ast.CallExpr{
			Object:    lhs,
			Arguments: []ast.Expression{},
		}
	}

	// Parse arguments
	args := p.parseExprList()

	p.expect(token.CloseParen)

	return &ast.CallExpr{
		Object:    lhs,
		Arguments: args,
	}
}

func (p parser) parseArrayAccess(lhs ast.Expression) *ast.ArrayAccessExpr {
	p.expect(token.OpenBracket)

	expr := p.parseExpr()

	if lexeme, _ := p.stream.Next(); lexeme.Token != token.CloseBracket {
		panic(errors.New("Expected close bracket"))
	}

	return &ast.ArrayAccessExpr{Object: lhs, Index: expr}
}

func (p parser) parseMemberAccess(lhs ast.Expression) *ast.MemberAccessExpr {
	p.expect(token.Dot)

	ident := p.expect(token.Identifier)
	return &ast.MemberAccessExpr{Object: lhs, Name: ident.Value}
}

func (p parser) parsePrimary() ast.Expression {
	lexeme, err := p.stream.Peek()
	if err != nil {
		p.stream.Next()
		panic(err)
	} else if !isExpressionToken(lexeme.Token) {
		panic(errors.New("Expected expression"))
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
		panic(fmt.Errorf("Unexpected lexeme %v; expected expression", lexeme.Value))
	}
}

func (p parser) parseIdentifier() ast.Identifier {
	lexeme := p.expect(token.Identifier)
	return &ast.NamedIDExpr{Name: lexeme.Value}
}

func (p parser) parseArray() *ast.ArrayExpr {
	// Parse opening
	p.expect(token.OpenBracket)

	// Check for empty array
	if ok := p.allow(token.CloseBracket); ok {
		return &ast.ArrayExpr{Members: []ast.Expression{}}
	}

	// Parse members
	exprs := p.parseExprList()

	// Parse close bracket
	p.expect(token.CloseBracket)

	return &ast.ArrayExpr{Members: exprs}
}

func (p parser) parseExprList() []ast.Expression {
	exprs := []ast.Expression{}

	// expr (COMMA expr)*
	for true {
		expr := p.parseExpr()
		exprs = append(exprs, expr)

		if foundComma := p.allow(token.Comma); !foundComma {
			break
		}
	}

	return exprs
}

func (p parser) parseParethentizedExpr() ast.Expression {
	p.expect(token.OpenParen)

	expr := p.parseExpr()

	if lexeme, _ := p.stream.Next(); lexeme.Token != token.CloseParen {
		panic(errors.New("Expected close parenthesis"))
	}

	return expr
}

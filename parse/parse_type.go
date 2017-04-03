package parse

import (
	"errors"
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isTypeToken(t token.Token) bool {
	typeTokens := []token.Token{
		token.Int, token.Int8, token.Int16, token.Int32, token.Int64,
		token.UInt, token.UInt8, token.UInt16, token.UInt32, token.UInt64,
		token.Float, token.Double, token.Char, token.String, token.Bool,
	}

	for _, typeToken := range typeTokens {
		if t == typeToken {
			return true
		}
	}

	return false
}

func (p parser) parseType() (ast.Type, error) {
	lexeme, err := p.expectFrom(isTypeToken)
	if err != nil {
		return nil, fmt.Errorf("Expected type, got %v", lexeme.Value)
	}

	var ty ast.Type

	if intSize := lexeme.Token.IntegerSize(); intSize > 0 {
		signed := lexeme.Token.SignedValue()
		ty = &ast.IntType{Size: intSize, Signed: signed}
	}

	switch lexeme.Token {
	case token.Double:
		ty = &ast.DoubleType{}
	case token.Float:
		ty = &ast.FloatType{}
	case token.Char:
		ty = &ast.CharType{}
	case token.String:
		ty = &ast.NamedType{Name: "string"}
	case token.Bool:
		ty = &ast.BoolType{}
	}

	// Parse pointer and array types
	for {
		lexeme, _ = p.stream.Peek()
		if lexeme.Token == token.Times {
			p.stream.Next()
			ty = &ast.PointerType{InnerType: ty}
		} else if lexeme.Token == token.OpenBracket {
			p.stream.Next()
			if _, err := p.expect(token.CloseBracket); err != nil {
				return ty, err
			}

			ty = &ast.ArrayType{InnerType: ty}
		} else {
			break
		}
	}

	if ty == nil {
		return nil, errors.New("Unexpected type")
	}

	return ty, nil
}

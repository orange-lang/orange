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
	lexeme, err := p.stream.Next()
	if err != nil {
		return nil, nil
	} else if !isTypeToken(lexeme.Token) {
		return nil, fmt.Errorf("Expected type, got %v", lexeme.Value)
	}

	var ty ast.Type

	switch lexeme.Token {
	case token.Int:
		ty = &ast.IntType{Size: 64, Signed: true}
	case token.Int8:
		ty = &ast.IntType{Size: 8, Signed: true}
	case token.Int16:
		ty = &ast.IntType{Size: 16, Signed: true}
	case token.Int32:
		ty = &ast.IntType{Size: 32, Signed: true}
	case token.Int64:
		ty = &ast.IntType{Size: 64, Signed: true}
	case token.UInt:
		ty = &ast.IntType{Size: 64, Signed: false}
	case token.UInt8:
		ty = &ast.IntType{Size: 8, Signed: false}
	case token.UInt16:
		ty = &ast.IntType{Size: 16, Signed: false}
	case token.UInt32:
		ty = &ast.IntType{Size: 32, Signed: false}
	case token.UInt64:
		ty = &ast.IntType{Size: 64, Signed: false}
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

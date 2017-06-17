package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isTypeToken(t token.Token) bool {
	typeTokens := []token.Token{
		token.Int, token.Int8, token.Int16, token.Int32, token.Int64,
		token.UInt, token.UInt8, token.UInt16, token.UInt32, token.UInt64,
		token.Float, token.Double, token.Char, token.String, token.Bool,
		token.Identifier, token.Void,
	}

	for _, typeToken := range typeTokens {
		if t == typeToken {
			return true
		}
	}

	return false
}

func (p parser) parseType() ast.Type {
	var isConst bool
	var ty ast.Type

	if p.allow(token.Const) {
		isConst = true
	}

	lexeme := p.expectFrom(isTypeToken)

	if intSize := lexeme.Token.IntegerSize(); intSize > 0 {
		signed := lexeme.Token.SignedValue()
		ty = &ast.IntType{Size: intSize, Signed: signed}
	}

	switch lexeme.Token {
	case token.Void:
		ty = &ast.VoidType{}
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
	case token.Identifier:
		ty = &ast.NamedType{Name: lexeme.Value}
		ty = p.tryParseGenericAnnotation(ty.(*ast.NamedType))
	}

	// Parse pointer and array types
	for {
		lexeme, _ = p.stream.Peek()
		if lexeme.Token == token.Times {
			p.stream.Next()
			ty = &ast.PointerType{InnerType: ty}
		} else if lexeme.Token == token.OpenBracket {
			p.stream.Next()
			p.expect(token.CloseBracket)

			ty = &ast.ArrayType{InnerType: ty}
		} else {
			break
		}
	}

	if ty == nil {
		panic(errors.New("Unexpected type"))
	}

	if isConst {
		return &ast.ConstType{InnerType: ty}
	}

	return ty
}

func (p parser) tryParseGenericAnnotation(ty *ast.NamedType) ast.Type {
	if !p.allow(token.LT) {
		return ty
	}

	annotations := []ast.Type{p.parseType()}

	for p.allow(token.Comma) {
		annotations = append(annotations, p.parseType())
	}

	p.expect(token.GT)
	return &ast.GenericAnnotation{
		Type:        ty,
		Annotations: annotations,
	}
}

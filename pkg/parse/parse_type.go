package parse

import (
	"errors"

	"github.com/orange-lang/orange/pkg/token"
	"github.com/orange-lang/orange/pkg/types"
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

func (p parser) parseType() types.Type {
	var isConst bool
	var ty types.Type

	if p.allow(token.Const) {
		isConst = true
	}

	lexeme := p.expectFrom(isTypeToken)

	if intSize := lexeme.Token.IntegerSize(); intSize > 0 {
		signed := lexeme.Token.SignedValue()
		ty = &types.Int{Size: intSize, Signed: signed}
	}

	switch lexeme.Token {
	case token.Void:
		ty = &types.Void{}
	case token.Double:
		ty = &types.Double{}
	case token.Float:
		ty = &types.Float{}
	case token.Char:
		ty = &types.Char{}
	case token.String:
		ty = &types.Named{Name: "string"}
	case token.Bool:
		ty = &types.Bool{}
	case token.Identifier:
		ty = &types.Named{Name: lexeme.Value}
		ty = p.tryParseGenericAnnotation(ty.(*types.Named))
	}

	// Parse pointer and array types
	for {
		lexeme, _ = p.stream.Peek()
		if lexeme.Token == token.Times {
			p.stream.Next()
			ty = &types.Pointer{InnerType: ty}
		} else if lexeme.Token == token.OpenBracket {
			p.stream.Next()
			p.expect(token.CloseBracket)

			ty = &types.Array{InnerType: ty}
		} else {
			break
		}
	}

	if lexeme, _ := p.stream.Peek(); lexeme.Token == token.BitAnd {
		p.stream.Next()
		ty = &types.Reference{InnerType: ty}
	}

	if ty == nil {
		panic(errors.New("Unexpected type"))
	}

	if isConst {
		ty.SetFlag(types.FlagConst)
	}

	return ty
}

func (p parser) tryParseGenericAnnotation(ty *types.Named) types.Type {
	if !p.allow(token.LT) {
		return ty
	}

	annotations := []types.Type{p.parseType()}

	for p.allow(token.Comma) {
		annotations = append(annotations, p.parseType())
	}

	p.expect(token.GT)
	return &types.Annotation{
		Type:        ty,
		Annotations: annotations,
	}
}

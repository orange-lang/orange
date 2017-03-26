package parse

import (
	"errors"
	"fmt"
	"strconv"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isConstantToken(t token.Token) bool {
	return t == token.StringVal || t == token.BoolVal ||
		numberToken(t) || t == token.CharVal
}

func (p parser) parseConstant() (ast.Expression, error) {
	lexeme, err := p.stream.Peek()
	if err != nil {
		p.stream.Next()
		return nil, err
	} else if !isConstantToken(lexeme.Token) {
		return nil, errors.New("Expected constant")
	}

	switch true {
	case lexeme.Token == token.StringVal:
		return p.parseString()
	case lexeme.Token == token.BoolVal:
		return p.parseBoolean()
	case numberToken(lexeme.Token):
		return p.parseNumber()
	case lexeme.Token == token.CharVal:
		return p.parseChar()
	}

	p.stream.Next()
	return nil, fmt.Errorf("Unexpected lexeme %v; expected constant", lexeme)
}

func (p parser) parseChar() (ast.Expression, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.CharVal {
		return nil, errors.New("Expected char")
	}

	return &ast.CharExpr{Value: lexeme.Value[0]}, nil
}

func numberToken(t token.Token) bool {
	numberTokens := []token.Token{
		token.UIntVal, token.UInt8Val, token.UInt16Val, token.UInt32Val, token.UInt64Val,
		token.IntVal, token.Int8Val, token.Int16Val, token.Int32Val, token.Int64Val,
		token.FloatVal, token.DoubleVal,
	}

	for _, tok := range numberTokens {
		if tok == t {
			return true
		}
	}

	return false
}

func (p parser) parseNumber() (ast.Expression, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return nil, err
	}

	if sz := lexeme.Token.IntegerSize(); sz > 0 {
		if lexeme.Token.SignedValue() {
			v, _ := strconv.ParseInt(lexeme.Value, 10, sz)
			return &ast.IntExpr{Value: v, Size: sz}, nil
		}

		v, _ := strconv.ParseUint(lexeme.Value, 10, sz)
		return &ast.UIntExpr{Value: v, Size: sz}, nil
	} else if lexeme.Token == token.FloatVal {
		v, _ := strconv.ParseFloat(lexeme.Value, 32)
		return &ast.FloatExpr{Value: float32(v)}, nil
	} else if lexeme.Token == token.DoubleVal {
		v, _ := strconv.ParseFloat(lexeme.Value, 64)
		return &ast.DoubleExpr{Value: v}, nil
	}

	return nil, errors.New("Expected number")
}

func (p parser) parseBoolean() (ast.Expression, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.BoolVal {
		return nil, errors.New("Expected boolean")
	}

	val, _ := strconv.ParseBool(lexeme.Value)
	return &ast.BoolExpr{Value: val}, nil
}

func (p parser) parseString() (ast.Expression, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return nil, err
	} else if lexeme.Token != token.StringVal {
		return nil, errors.New("Expected string")
	}

	return &ast.StringExpr{Value: lexeme.Value}, nil
}

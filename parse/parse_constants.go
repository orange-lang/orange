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
		numberToken(t) || t == token.CharVal || t == token.This ||
		t == token.Super
}

func (p parser) parseConstant() ast.Expression {
	if ok := p.peekFrom(isConstantToken); !ok {
		panic(errors.New("Expected constant"))
	}

	lexeme, _ := p.stream.Peek()

	switch true {
	case lexeme.Token == token.StringVal:
		return p.parseString()
	case lexeme.Token == token.BoolVal:
		return p.parseBoolean()
	case numberToken(lexeme.Token):
		return p.parseNumber()
	case lexeme.Token == token.CharVal:
		return p.parseChar()
	case lexeme.Token == token.Super:
		p.stream.Next()
		return &ast.SuperExpr{}
	case lexeme.Token == token.This:
		p.stream.Next()
		return &ast.ThisExpr{}
	}

	p.stream.Next()
	panic(fmt.Errorf("Unexpected lexeme %v; expected constant", lexeme))
}

func (p parser) parseChar() ast.Expression {
	lexeme := p.expect(token.CharVal)
	return &ast.CharExpr{Value: lexeme.Value[0]}
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

func (p parser) parseNumber() ast.Expression {
	lexeme, err := p.stream.Next()
	if err != nil {
		panic(err)
	}

	if sz := lexeme.Token.IntegerSize(); sz > 0 {
		if lexeme.Token.SignedValue() {
			v, _ := strconv.ParseInt(lexeme.Value, 10, sz)
			return &ast.IntExpr{Value: v, Size: sz}
		}

		v, _ := strconv.ParseUint(lexeme.Value, 10, sz)
		return &ast.UIntExpr{Value: v, Size: sz}
	} else if lexeme.Token == token.FloatVal {
		v, _ := strconv.ParseFloat(lexeme.Value, 32)
		return &ast.FloatExpr{Value: float32(v)}
	} else if lexeme.Token == token.DoubleVal {
		v, _ := strconv.ParseFloat(lexeme.Value, 64)
		return &ast.DoubleExpr{Value: v}
	}

	panic(errors.New("Expected number"))
}

func (p parser) parseBoolean() ast.Expression {
	lexeme := p.expect(token.BoolVal)

	val, _ := strconv.ParseBool(lexeme.Value)
	return &ast.BoolExpr{Value: val}
}

func (p parser) parseString() ast.Expression {
	lexeme := p.expect(token.StringVal)

	return &ast.StringExpr{Value: lexeme.Value}
}

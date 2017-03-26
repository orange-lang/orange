package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isBinOpToken(t token.Token) bool {
	binOpTokens := []token.Token{
		token.LogicalOr, token.LogicalAnd, token.LogicalNot, token.Question,
		token.EQ, token.NEQ, token.LE, token.GE, token.LT, token.GT, token.Plus,
		token.Minus, token.Divide, token.Times, token.Mod, token.BitOr,
		token.BitAnd, token.BitXor, token.BitNot, token.ShiftLeft,
		token.ShiftRight, token.Assign, token.PlusAssign, token.MinusAssign,
		token.DivideAssign, token.TimesAssign, token.ModAssign, token.BitOrAssign,
		token.BitAndAssign, token.BitXorAssign, token.ShiftLeftAssign,
		token.ShiftRightAssign,
	}

	for _, tok := range binOpTokens {
		if tok == t {
			return true
		}
	}

	return false
}

func parseBinary(s lexer.LexemeStream, lhs ast.Expression, minPrec int) (ast.Expression, error) {
	next, err := s.Peek()
	if err != nil {
		return nil, err
	} else if !isBinOpToken(next.Token) {
		return nil, errors.New("Expected binary operator")
	}

	for getOperatorPrecedence(next.Token) >= minPrec {
		op := next
		s.Next()

		rhs, err := parseUnary(s)
		if err != nil {
			return nil, err
		}

		next, err = s.Peek()

		for (getAssociativity(next.Token) == token.LeftAssociativity &&
			getOperatorPrecedence(next.Token) > getOperatorPrecedence(op.Token)) ||
			(getAssociativity(next.Token) == token.RightAssociativity &&
				getOperatorPrecedence(next.Token) == getOperatorPrecedence(op.Token)) {
			rhs, err = parseBinary(s, rhs, getOperatorPrecedence(next.Token))
			if err != nil {
				return nil, err
			}

			next, err = s.Peek()
			if err != nil {
				return nil, err
			}
		}

		lhs = &ast.BinaryExpr{LHS: lhs, Operation: op.Value, RHS: rhs}
	}

	return lhs, nil
}

func getOperatorPrecedence(tok token.Token) int {
	precedenceMap := map[token.Token]int{
		token.Times:            12,
		token.Divide:           12,
		token.Mod:              12,
		token.Plus:             11,
		token.Minus:            11,
		token.ShiftLeft:        10,
		token.ShiftRight:       10,
		token.LT:               9,
		token.GT:               9,
		token.LE:               8,
		token.GE:               8,
		token.EQ:               7,
		token.NEQ:              7,
		token.BitAnd:           6,
		token.BitXor:           5,
		token.BitOr:            4,
		token.LogicalAnd:       3,
		token.LogicalOr:        2,
		token.Question:         1,
		token.Assign:           1,
		token.PlusAssign:       1,
		token.MinusAssign:      1,
		token.TimesAssign:      1,
		token.DivideAssign:     1,
		token.ModAssign:        1,
		token.ShiftLeftAssign:  1,
		token.ShiftRightAssign: 1,
		token.BitOrAssign:      1,
		token.BitAndAssign:     1,
		token.BitXorAssign:     1,
	}

	for token, prec := range precedenceMap {
		if token == tok {
			return prec
		}
	}

	return -1
}

func getAssociativity(tok token.Token) token.Associativity {
	prec := getOperatorPrecedence(tok)

	if prec == 1 {
		return token.RightAssociativity
	}

	return token.LeftAssociativity
}

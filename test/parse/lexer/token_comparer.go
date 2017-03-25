package test

import (
	"fmt"

	"github.com/onsi/gomega/types"
	"github.com/orange-lang/orange/parse/lexer/token"
)

var tokenLookup = map[token.Token]string{
	token.EOF:              "EOF",
	token.IntVal:           "IntVal",
	token.Int8Val:          "Int8Val",
	token.Int16Val:         "Int16Val",
	token.Int32Val:         "Int32Val",
	token.Int64Val:         "Int64Val",
	token.UIntVal:          "UIntVal",
	token.UInt8Val:         "UInt8Val",
	token.UInt16Val:        "UInt16Val",
	token.UInt32Val:        "UInt32Val",
	token.UInt64Val:        "UInt64Val",
	token.FloatVal:         "FloatVal",
	token.DoubleVal:        "DoubleVal",
	token.StringVal:        "StringVal",
	token.CharVal:          "CharVal",
	token.BoolVal:          "BoolVal",
	token.Int:              "Int",
	token.Int8:             "Int8",
	token.Int16:            "Int16",
	token.Int32:            "Int32",
	token.Int64:            "Int64",
	token.UInt:             "UInt",
	token.UInt8:            "UInt8",
	token.UInt16:           "UInt16",
	token.UInt32:           "UInt32",
	token.UInt64:           "UInt64",
	token.Float:            "Float",
	token.Double:           "Double",
	token.String:           "String",
	token.Char:             "Char",
	token.Bool:             "Bool",
	token.Void:             "Void",
	token.Newline:          "Newline",
	token.Semicolon:        "Semicolon",
	token.Var:              "Var",
	token.Enum:             "Enum",
	token.Class:            "Class",
	token.Public:           "Public",
	token.Protected:        "Protected",
	token.Private:          "Private",
	token.If:               "If",
	token.Elif:             "Elif",
	token.Else:             "Else",
	token.For:              "For",
	token.While:            "While",
	token.Do:               "Do",
	token.Break:            "Break",
	token.Continue:         "Continue",
	token.Def:              "Def",
	token.Extern:           "Extern",
	token.Interface:        "Interface",
	token.Package:          "Package",
	token.Import:           "Import",
	token.New:              "New",
	token.Delete:           "Delete",
	token.Get:              "Get",
	token.Set:              "Set",
	token.Virtual:          "Virtual",
	token.Final:            "Final",
	token.Where:            "Where",
	token.Data:             "Data",
	token.Extend:           "Extend",
	token.Const:            "Const",
	token.Try:              "Try",
	token.Catch:            "Catch",
	token.Finally:          "Finally",
	token.Throw:            "Throw",
	token.Of:               "Of",
	token.Property:         "Property",
	token.This:             "This",
	token.OpenParen:        "OpenParen",
	token.CloseParen:       "CloseParen",
	token.OpenCurly:        "OpenCurly",
	token.CloseCurly:       "CloseCurly",
	token.OpenBracket:      "OpenBracket",
	token.CloseBracket:     "CloseBracket",
	token.Dot:              "Dot",
	token.Comma:            "Comma",
	token.Colon:            "Colon",
	token.Arrow:            "Arrow",
	token.LogicalOr:        "LogicalOr",
	token.LogicalAnd:       "LogicalAnd",
	token.LogicalNot:       "LogicalNot",
	token.Question:         "Question",
	token.EQ:               "EQ",
	token.NEQ:              "NEQ",
	token.LE:               "LE",
	token.GE:               "GE",
	token.LT:               "LT",
	token.GT:               "GT",
	token.Plus:             "Plus",
	token.Minus:            "Minus",
	token.Divide:           "Divide",
	token.Times:            "Times",
	token.Mod:              "Mod",
	token.BitOr:            "BitOr",
	token.BitAnd:           "BitAnd",
	token.BitXor:           "BitXor",
	token.BitNot:           "BitNot",
	token.ShiftLeft:        "ShiftLeft",
	token.ShiftRight:       "ShiftRight",
	token.Assign:           "Assign",
	token.PlusAssign:       "PlusAssign",
	token.MinusAssign:      "MinusAssign",
	token.DivideAssign:     "DivideAssign",
	token.TimesAssign:      "TimesAssign",
	token.ModAssign:        "ModAssign",
	token.BitOrAssign:      "BitOrAssign",
	token.BitAndAssign:     "BitAndAssign",
	token.BitXorAssign:     "BitXorAssign",
	token.ShiftLeftAssign:  "ShiftLeftAssign",
	token.ShiftRightAssign: "ShiftRightAssign",
	token.Increment:        "Increment",
	token.Decrement:        "Decrement",
	token.Identifier:       "Identifier",
}

type tokenComparer struct {
	Expect token.Token
}

func equalToken(expect token.Token) types.GomegaMatcher {
	return tokenComparer{Expect: expect}
}

func (c tokenComparer) Match(actual interface{}) (success bool, err error) {
	return actual.(token.Token) == c.Expect, nil
}

func (c tokenComparer) FailureMessage(actual interface{}) (message string) {
	actualTok := actual.(token.Token)
	var expectedPrintable interface{}
	var actualPrintable interface{}

	if v, ok := tokenLookup[c.Expect]; ok {
		expectedPrintable = v
	} else {
		expectedPrintable = c.Expect
	}

	if v, ok := tokenLookup[actualTok]; ok {
		actualPrintable = v
	} else {
		actualPrintable = actualTok
	}

	return fmt.Sprintf("Expected\n\t%v\nto equal\n\t%v", actualPrintable,
		expectedPrintable)
}

func (c tokenComparer) NegatedFailureMessage(actual interface{}) (message string) {
	actualTok := actual.(token.Token)
	var expectedPrintable interface{}
	var actualPrintable interface{}

	if v, ok := tokenLookup[c.Expect]; ok {
		expectedPrintable = v
	} else {
		expectedPrintable = c.Expect
	}

	if v, ok := tokenLookup[actualTok]; ok {
		actualPrintable = v
	} else {
		actualPrintable = c.Expect
	}

	return fmt.Sprintf("Expected\n\t%v\nnot to equal\n\t%v", actualPrintable,
		expectedPrintable)
}

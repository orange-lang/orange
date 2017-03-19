package test

import (
	"fmt"
	"parse/lexer/token"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
)

var _ = Describe("Operators", func() {
	DescribeTable("should get lexed when the operator is", expectToken,
		Entry("\\n", fmt.Sprintf("\n"), token.Newline),
		Entry(";", ";", token.Semicolon),
		Entry("(", "(", token.OpenParen),
		Entry(")", ")", token.CloseParen),
		Entry("{", "{", token.OpenCurly),
		Entry("}", "}", token.CloseCurly),
		Entry("[", "[", token.OpenBracket),
		Entry("]", "]", token.CloseBracket),
		Entry(".", ".", token.Dot),
		Entry(",", ",", token.Comma),
		Entry(":", ":", token.Colon),
		Entry("->", "->", token.Arrow),
		Entry("||", "||", token.LogicalOr),
		Entry("&&", "&&", token.LogicalAnd),
		Entry("!", "!", token.LogicalNot),
		Entry("?", "?", token.Question),
		Entry("==", "==", token.EQ),
		Entry("!=", "!=", token.NEQ),
		Entry("<", "<", token.LT),
		Entry(">", ">", token.GT),
		Entry("<=", "<=", token.LE),
		Entry("+", "+", token.Plus),
		Entry("-", "-", token.Minus),
		Entry("/", "/", token.Divide),
		Entry("*", "*", token.Times),
		Entry("%", "%", token.Mod),
		Entry("|", "|", token.BitOr),
		Entry("&", "&", token.BitAnd),
		Entry("^", "^", token.BitXor),
		Entry("~", "~", token.BitNot),
		Entry("<<", "<<", token.ShiftLeft),
		Entry(">>", ">>", token.ShiftRight),
		Entry("=", "=", token.Assign),
		Entry("+=", "+=", token.PlusAssign),
		Entry("-=", "-=", token.MinusAssign),
		Entry("/=", "/=", token.DivideAssign),
		Entry("*=", "*=", token.TimesAssign),
		Entry("%=", "%=", token.ModAssign),
		Entry("|=", "|=", token.BitOrAssign),
		Entry("&=", "&=", token.BitAndAssign),
		Entry("^=", "^=", token.BitXorAssign),
		Entry("<<=", "<<=", token.ShiftLeftAssign),
		Entry(">>=", ">>=", token.ShiftRightAssign),
		Entry("++", "++", token.Increment),
		Entry("--", "--", token.Decrement),
	)
})

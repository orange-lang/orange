package lexer

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
)

var _ = Describe("Lexeme position", func() {
	It("should be correct after parsing a number", func() {
		input := "mykeyword 0xDEADBEEFu16"

		expectPosition(input, 2, lexemePosition{
			LineNumber: 1, EndLineNumber: 1,
			ColumnNumber: 11, EndColumnNumber: 23,
		})
	})

	It("should be correct after parsing a identifier", func() {
		input := "mykeyword foobar"

		expectPosition(input, 2, lexemePosition{
			LineNumber: 1, EndLineNumber: 1,
			ColumnNumber: 11, EndColumnNumber: 16,
		})
	})

	It("should be correct after parsing a string", func() {
		input := "mykeyword \"hello, world!\""

		expectPosition(input, 2, lexemePosition{
			LineNumber: 1, EndLineNumber: 1,
			ColumnNumber: 11, EndColumnNumber: 25,
		})
	})

	It("should be correct after parsing a char", func() {
		input := "mykeyword 'c'"

		expectPosition(input, 2, lexemePosition{
			LineNumber: 1, EndLineNumber: 1,
			ColumnNumber: 11, EndColumnNumber: 13,
		})
	})

	It("should be correct after parsing a operator", func() {
		input := "mykeyword <<="

		expectPosition(input, 2, lexemePosition{
			LineNumber: 1, EndLineNumber: 1,
			ColumnNumber: 11, EndColumnNumber: 13,
		})
	})
})

type lexemePosition struct {
	LineNumber      int
	EndLineNumber   int
	ColumnNumber    int
	EndColumnNumber int
}

func expectPosition(input string, lexeme int, expect lexemePosition) {
	l := getLexer(input)

	// Skip over (lexeme - 1) lexemes so we get to the one we want
	l.Get(lexeme - 1)

	next, err := l.Next()

	actual := lexemePosition{
		LineNumber:      next.LineNumber,
		EndLineNumber:   next.EndLineNumber,
		ColumnNumber:    next.ColumnNumber,
		EndColumnNumber: next.EndColumnNumber,
	}

	Expect(err).To(BeNil())
	Expect(actual).To(Equal(expect))
}

package test

import (
	"parse/lexer/token"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
)

var _ = Describe("Lexeme errors", func() {
	Describe("should handle", func() {
		It("unterminated strings", func() {
			expectError("\"foo")
		})

		It("unterminated characters", func() {
			expectError("'f")
		})
	})

	Describe("should continue lexing after", func() {
		Describe("an invalid number with", func() {
			It("an unknown suffix", func() {
				input := "0x51s8 myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})

			It("an invalid suffix", func() {
				input := "0.58u8 myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})

			It("an unknown prefix", func() {
				input := "0s58u16 myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})

			It("an invalid number for base", func() {
				input := "0b0120u16 myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})
		})

		Describe("an invalid string with", func() {
			It("an unknown escape sequence", func() {
				input := "\"my \\dog is a good dog\" myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})
		})

		Describe("an invalid char with", func() {
			It("more than one character", func() {
				input := "'invalid' myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})

			It("an unknown escape sequence", func() {
				input := "'\\d' myidentifier"
				l := getLexer(input)

				_, err := l.Next()
				Expect(err).ToNot(BeNil())

				lexeme, err := l.Next()
				Expect(err).To(BeNil())
				Expect(lexeme.Token).To(Equal(token.Identifier))
				Expect(lexeme.Value).To(Equal("myidentifier"))
			})
		})

		It("an unknown operator", func() {
			input := "@myidentifier"
			l := getLexer(input)

			_, err := l.Next()
			Expect(err).ToNot(BeNil())

			lexeme, err := l.Next()
			Expect(err).To(BeNil())
			Expect(lexeme.Token).To(Equal(token.Identifier))
			Expect(lexeme.Value).To(Equal("myidentifier"))
		})
	})
})

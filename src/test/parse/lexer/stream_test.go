package test

import (
	"parse/lexer"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
)

var _ = Describe("String Rune String", func() {
	getStream := func(input string) *lexer.StringRuneStream {
		return &lexer.StringRuneStream{Source: input}
	}

	Describe("EOF", func() {
		It("should be true when the string is empty", func() {
			s := getStream("")
			Expect(s.EOF()).To(BeTrue())
		})

		It("should be true after reading the whole string", func() {
			s := getStream("input")

			for i := 0; i < len(s.Source); i++ {
				s.Next()
			}

			Expect(s.EOF()).To(BeTrue())
		})
	})

	Describe("Next", func() {
		It("should return each character in sequence", func() {
			s := getStream("input")
			Expect(s.Next()).To(Equal('i'))
			Expect(s.Next()).To(Equal('n'))
			Expect(s.Next()).To(Equal('p'))
			Expect(s.Next()).To(Equal('u'))
			Expect(s.Next()).To(Equal('t'))
		})

		It("should consume from the lookahead, if the lookahead > 1", func() {
			s := getStream("input")
			s.Peek()

			Expect(s.Next()).To(Equal('i'))
			Expect(s.Next()).To(Equal('n'))
			Expect(s.Next()).To(Equal('p'))
			Expect(s.Next()).To(Equal('u'))
			Expect(s.Next()).To(Equal('t'))
		})
	})

	Describe("Get", func() {
		It("should get n characters in sequence", func() {
			s := getStream("input!")
			Expect(s.Get(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Get(3)).To(Equal([]rune{'u', 't', '!'}))
		})

		It("should consume from the lookahead if the lookahead < n", func() {
			s := getStream("input!")
			s.Lookahead(2)

			Expect(s.Get(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Get(3)).To(Equal([]rune{'u', 't', '!'}))
		})

		It("should consume from the lookahead if the lookahead == n", func() {
			s := getStream("input!")
			s.Lookahead(3)

			Expect(s.Get(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Get(3)).To(Equal([]rune{'u', 't', '!'}))
		})

		It("should consume from the lookahead if the lookahead > n", func() {
			s := getStream("input!")
			s.Lookahead(5)

			Expect(s.Get(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Get(3)).To(Equal([]rune{'u', 't', '!'}))
		})
	})

	Describe("Peek", func() {
		It("should continously give the same character", func() {
			s := getStream("input")

			Expect(s.Peek()).To(Equal('i'))
			Expect(s.Peek()).To(Equal('i'))
			Expect(s.Peek()).To(Equal('i'))
			Expect(s.Peek()).To(Equal('i'))
		})
	})

	Describe("Lookahead", func() {
		It("should continously give the same n characters", func() {
			s := getStream("input!")

			Expect(s.Lookahead(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Lookahead(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Lookahead(3)).To(Equal([]rune{'i', 'n', 'p'}))
			Expect(s.Lookahead(3)).To(Equal([]rune{'i', 'n', 'p'}))
		})
	})

	Describe("Position", func() {
		It("should be correct", func() {
			s := getStream("foo\nbar")
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 1, Column: 1}))

			s.Peek()
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 1, Column: 1}))

			s.Lookahead(3)
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 1, Column: 1}))

			s.Next()
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 1, Column: 2}))

			s.Get(2)
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 1, Column: 4}))

			s.Get(4)
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 2, Column: 4}))

			s = getStream("foo\n\nbar")
			s.Get(6)
			Expect(s.Position()).To(Equal(lexer.RuneStreamPosition{Row: 3, Column: 2}))
		})
	})

})

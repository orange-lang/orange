package lexer

// LexemeStream provides a constant stream of lexemes, allowing
// for an n-Lookahead
type LexemeStream interface {
	EOF() bool

	Next() (Lexeme, error)
	Get(n int) ([]Lexeme, []error)

	Peek() (Lexeme, error)
	Lookahead(n int) ([]Lexeme, error)
}

// ByteStream provides a constant stream of bytes, potentially from a file
type RuneStream interface {
	EOF() bool

	Next() rune
	Get(n int) []rune

	Peek() rune
	Lookahead(n int) []rune
}

//
// ByteStream for string
//

type StringRuneStream struct {
	Source    string
	at        int
	lookahead []rune
}

func (s *StringRuneStream) EOF() bool {
	return len(s.lookahead) == 0 && s.at >= len(s.Source)
}

func (s *StringRuneStream) getOne() rune {
	if s.at >= len(s.Source) {
		return 0
	}

	next := []rune(s.Source)[s.at]
	s.at++
	return next
}

func (s *StringRuneStream) getN(n int) []rune {
	bytes := make([]rune, n)

	for i := 0; i < n; i++ {
		bytes[i] = s.getOne()
	}

	return bytes
}

func (s *StringRuneStream) Next() rune {
	if len(s.lookahead) > 0 {
		next := s.lookahead[0]
		s.lookahead = s.lookahead[1:]
		return next
	}

	return s.getOne()
}

func (s *StringRuneStream) Get(n int) []rune {
	bytes := make([]rune, n)

	for i := 0; i < n; i++ {
		bytes[i] = s.Next()
	}

	return bytes
}

func (s *StringRuneStream) Peek() rune {
	return s.Lookahead(1)[0]
}

func (s *StringRuneStream) Lookahead(n int) []rune {
	rem := n - len(s.lookahead)

	if rem > 0 {
		s.lookahead = append(s.lookahead, s.getN(rem)...)
	}

	return s.lookahead[0:n]
}

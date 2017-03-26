package lexer

// LexemeStream provides a constant stream of lexemes, allowing
// for an n-Lookahead
type LexemeStream interface {
	EOF() bool

	Next() (Lexeme, error)
	Get(n int) ([]Lexeme, []error)

	Peek() (Lexeme, error)
	Lookahead(n int) ([]Lexeme, []error)
}

// RuneStreamPosition represents some column and row in the
// rune stream
type RuneStreamPosition struct {
	Row    int
	Column int
}

// RuneStream provides a constant stream of bytes, potentially from a file
type RuneStream interface {
	EOF() bool

	Next() rune
	Get(n int) []rune

	Peek() rune
	Lookahead(n int) []rune

	Position() RuneStreamPosition
}

//
// ByteStream for string
//

type StringRuneStream struct {
	Source string

	at        int
	lookahead []rune
	x         int
	y         int
}

// Position returns the current column the row is pointed at; e.g.,
// the rune returned at Peek() would be at this location.
func (s *StringRuneStream) Position() RuneStreamPosition {
	return RuneStreamPosition{Row: s.y + 1, Column: s.x + 1}
}

func (s *StringRuneStream) updatePosition(r rune) {
	if r == '\n' {
		s.y++
		s.x = 0
	} else {
		s.x++
	}
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
		s.updatePosition(next)
		return next
	}

	next := s.getOne()
	s.updatePosition(next)
	return next
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

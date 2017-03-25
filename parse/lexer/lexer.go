package lexer

type lookaheadPair struct {
	Lexeme Lexeme
	Error  error
}

// Lexer takes a stream of bytes and provides a stream of lexemes
type Lexer struct {
	Stream RuneStream

	lookahead []lookaheadPair
}

// EOF returns true if there is no more lookahead and if the
// byte stream has been consumed
func (l *Lexer) EOF() bool {
	return len(l.lookahead) == 0 && l.Stream.EOF()
}

// Get returns the very next lexeme from the byte stream
func (l *Lexer) Get(n int) ([]Lexeme, []error) {
	lexemes := make([]Lexeme, n)
	errors := make([]error, n)

	for i := 0; i < n; i++ {
		lexeme, err := l.Next()
		lexemes[i] = lexeme
		errors[i] = err
	}

	return lexemes, errors
}

// Peek does a lookahead at the very next lexeme
func (l *Lexer) Peek() (Lexeme, error) {
	lexemes, errors := l.Lookahead(1)
	return lexemes[0], errors[0]
}

// Lookahead peeks at the next n lexemes
func (l *Lexer) Lookahead(n int) ([]Lexeme, []error) {
	rem := n - len(l.lookahead)

	if rem > 0 {
		lexemes, errors := l.getN(rem)

		for i := 0; i < rem; i++ {
			l.lookahead = append(l.lookahead, lookaheadPair{
				Lexeme: lexemes[i],
				Error:  errors[i],
			})
		}
	}

	lookahead := l.lookahead[0:n]
	lexemes := make([]Lexeme, n)
	errors := make([]error, n)

	for i := 0; i < n; i++ {
		lexemes[i] = lookahead[i].Lexeme
		errors[i] = lookahead[i].Error
	}

	return lexemes, errors
}

// Next returns the very next lexeme from the byte stream
func (l *Lexer) Next() (Lexeme, error) {
	if len(l.lookahead) > 0 {
		pair := l.lookahead[0]
		l.lookahead = l.lookahead[1:]
		return pair.Lexeme, pair.Error
	}

	return l.lex()
}

func (l *Lexer) getN(n int) ([]Lexeme, []error) {
	lexemes := make([]Lexeme, n)
	errors := []error{}

	for i := 0; i < n; i++ {
		lexeme, err := l.lex()
		lexemes[i] = lexeme

		if err != nil {
			errors = append(errors, err)
		}
	}

	return lexemes, errors
}

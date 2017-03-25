package lexer

import "fmt"

// Error represents an error encountered during lexing. It
// contains the position in the file when the error occured.
type Error struct {
	Row    int
	Column int

	Message string
}

// Error displays the lexer error message and the position in the
// file where it ocurred
func (e Error) Error() string {
	return fmt.Sprintf("%v:%v %v", e.Row, e.Column, e.Message)
}

// NewError returns a new lexer error
func NewError(s RuneStream, message string, args ...interface{}) Error {
	pos := s.Position()
	return Error{
		Row:     pos.Row,
		Column:  pos.Column,
		Message: fmt.Sprintf(message, args...),
	}
}

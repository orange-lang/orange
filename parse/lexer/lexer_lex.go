package lexer

import (
	"fmt"
	"sort"
	"unicode"

	"github.com/orange-lang/orange/parse/lexer/token"
)

func (l *Lexer) lex() (Lexeme, error) {
	if l.EOF() {
		return Lexeme{Token: token.EOF}, nil
	}

	for isIgnoreableSpace(l.Stream.Peek()) {
		_ = l.Stream.Next()
	}

	if lookahead := string(l.Stream.Lookahead(2)); isCommentStarter(lookahead) {
		if lookahead == "//" {
			consumeSingleLineComment(l.Stream)
		} else {
			consumeBlockComment(l.Stream)
		}
	}

	next := l.Stream.Peek()

	switch true {
	case unicode.IsDigit(next):
		return lexNumber(l.Stream)
	case unicode.IsLetter(next):
		return lexKeywordOrIdentifier(l.Stream)
	case next == '\'':
		return lexCharacter(l.Stream)
	case next == '"':
		return lexString(l.Stream)
	default:
		return lexOperator(l.Stream)
	}
}

func lexString(s RuneStream) (Lexeme, error) {
	l := Lexeme{}
	l.SetStartPosition(s)

	var value string

	s.Next()

	for !s.EOF() && s.Peek() != '"' {
		if s.Peek() == '\\' {
			seq, err := lexEscapeSequence(s)
			if err != nil {
				consumeUntilCharacter(s, '"')
				return l, err
			}

			value += seq
			continue
		}

		value += string(s.Next())
	}

	// Finish consuming the string
	if val := s.Next(); val != '"' {
		return l, NewError(s, "Unterminated string constant")
	}

	l.Value = value
	l.Token = token.StringVal
	l.SetEndPosition(s)

	return l, nil
}

func lexEscapeSequence(s RuneStream) (string, error) {
	value := ""

	s.Next()

	switch s.Peek() {
	case 'n':
		value = fmt.Sprintf("\n")
	case 't':
		value = fmt.Sprintf("\t")
	case '\\':
		value = fmt.Sprintf("\\")
	case '\'':
		value = "'"
	case '"':
		value = "\""
	default:
		return "", NewError(s, "Unexpected escape sequence %v", string(s.Peek()))
	}

	// Consume full escape sequence
	s.Next()
	return value, nil
}

func lexCharacter(s RuneStream) (Lexeme, error) {
	l := Lexeme{}
	l.SetStartPosition(s)

	var value string

	s.Next()

	for !s.EOF() && s.Peek() != '\'' {
		if s.Peek() == '\\' {
			seq, err := lexEscapeSequence(s)
			if err != nil {
				consumeUntilCharacter(s, '\'')
				return l, err
			}

			value += seq
			continue
		}

		value += string(s.Next())
	}

	// Finish consuming the character
	if val := s.Next(); val != '\'' {
		return l, NewError(s, "Unterminated character constant")
	}

	if len(value) > 1 {
		return l, NewError(s, "Too many characters in character constant")
	}

	l.Value = value
	l.Token = token.CharVal
	l.SetEndPosition(s)

	return l, nil
}

func lexOperator(s RuneStream) (Lexeme, error) {
	operatorTable := map[string]token.Token{
		fmt.Sprintf("\n"): token.Newline,

		";":   token.Semicolon,
		"(":   token.OpenParen,
		")":   token.CloseParen,
		"{":   token.OpenCurly,
		"}":   token.CloseCurly,
		"[":   token.OpenBracket,
		"]":   token.CloseBracket,
		".":   token.Dot,
		",":   token.Comma,
		":":   token.Colon,
		"!":   token.LogicalNot,
		"?":   token.Question,
		"<":   token.LT,
		">":   token.GT,
		"+":   token.Plus,
		"-":   token.Minus,
		"/":   token.Divide,
		"*":   token.Times,
		"%":   token.Mod,
		"|":   token.BitOr,
		"&":   token.BitAnd,
		"^":   token.BitXor,
		"~":   token.BitNot,
		"=":   token.Assign,
		"->":  token.Arrow,
		"||":  token.LogicalOr,
		"&&":  token.LogicalAnd,
		"==":  token.EQ,
		"!=":  token.NEQ,
		"<=":  token.LE,
		"<<":  token.ShiftLeft,
		">>":  token.ShiftRight,
		"+=":  token.PlusAssign,
		"-=":  token.MinusAssign,
		"/=":  token.DivideAssign,
		"*=":  token.TimesAssign,
		"%=":  token.ModAssign,
		"|=":  token.BitOrAssign,
		"&=":  token.BitAndAssign,
		"^=":  token.BitXorAssign,
		"++":  token.Increment,
		"--":  token.Decrement,
		"<<=": token.ShiftLeftAssign,
		">>=": token.ShiftRightAssign,
	}

	l := Lexeme{}
	l.SetStartPosition(s)

	operators := getPotentialOperators(operatorTable)

	for _, op := range operators {
		lookahead := string(s.Lookahead(len(op)))
		if tok, ok := operatorTable[lookahead]; ok {
			s.Get(len(op))

			l.Token = tok
			l.Value = lookahead
			l.SetEndPosition(s)

			return l, nil
		}
	}

	err := NewError(s, "Unepxected character %v", string(s.Peek()))
	s.Next()
	return l, err
}

// getPotentialOperators returns a slice of operators ordered by
// length descending, allowing for looking ahead by length incrementally
// to determine if that specific operator is being lexed, rather than
// another operator that is a substring of the longer one
func getPotentialOperators(table map[string]token.Token) []string {
	var operators []string
	for k := range table {
		operators = append(operators, k)
	}
	sort.Sort(byLength(operators))
	return operators
}

func lexKeywordOrIdentifier(s RuneStream) (Lexeme, error) {
	l := Lexeme{}
	l.SetStartPosition(s)

	keywordTable := map[string]token.Token{
		"int":       token.Int,
		"int8":      token.Int8,
		"int16":     token.Int16,
		"int32":     token.Int32,
		"int64":     token.Int64,
		"uint":      token.UInt,
		"uint8":     token.UInt8,
		"uint16":    token.UInt16,
		"uint32":    token.UInt32,
		"uint64":    token.UInt64,
		"var":       token.Var,
		"enum":      token.Enum,
		"class":     token.Class,
		"public":    token.Public,
		"protected": token.Protected,
		"private":   token.Private,
		"if":        token.If,
		"elif":      token.Elif,
		"else":      token.Else,
		"for":       token.For,
		"while":     token.While,
		"do":        token.Do,
		"break":     token.Break,
		"continue":  token.Continue,
		"def":       token.Def,
		"extern":    token.Extern,
		"interface": token.Interface,
		"package":   token.Package,
		"import":    token.Import,
		"new":       token.New,
		"delete":    token.Delete,
		"get":       token.Get,
		"set":       token.Set,
		"virtual":   token.Virtual,
		"final":     token.Final,
		"where":     token.Where,
		"data":      token.Data,
		"extend":    token.Extend,
		"const":     token.Const,
		"try":       token.Try,
		"catch":     token.Catch,
		"finally":   token.Finally,
		"throw":     token.Throw,
		"of":        token.Of,
		"property":  token.Property,
		"this":      token.This,
		"false":     token.BoolVal,
		"true":      token.BoolVal,
	}

	value := ""

	for isIdentifierCharacter(s.Peek()) {
		value += string(s.Next())
	}

	if tok, ok := keywordTable[value]; ok {
		l.Token = tok
	} else {
		l.Token = token.Identifier
	}

	l.Value = value
	l.SetEndPosition(s)
	return l, nil
}

func consumeUntilCharacter(s RuneStream, c rune) {
	for !s.EOF() && s.Peek() != c {
		_ = s.Next()
	}

	// Then consume the character
	s.Next()
}

func consumeUntilWhitespace(s RuneStream) {
	for !s.EOF() && !isIgnoreableSpace(s.Peek()) {
		_ = s.Next()
	}
}

func consumeSingleLineComment(s RuneStream) {
	s.Get(2)

	for s.Peek() != '\n' {
		s.Next()
	}

	// Consume the newline
	s.Next()
}

func consumeBlockComment(s RuneStream) {
	s.Get(2)

	level := 1

	for level > 0 {
		// Nested comment
		if lookahead := string(s.Lookahead(2)); lookahead == "/*" {
			s.Get(2)
			level++
			continue
		} else if lookahead == "*/" {
			s.Get(2)
			level--
			continue
		}

		s.Next()
	}
}

func isIdentifierCharacter(r rune) bool {
	return unicode.IsLetter(r) || unicode.IsDigit(r) || r == '_'
}

func isIgnoreableSpace(r rune) bool {
	// We can ignore anything that's not a newline
	return r != '\n' && unicode.IsSpace(r)
}

func isCommentStarter(s string) bool {
	return s == "//" || s == "/*"
}

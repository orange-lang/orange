package parse

import (
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

type parser struct {
	stream lexer.LexemeStream
}

// Parse takes a lexeme stream and returns an AST. Consumes the entire
// lexeme stream, and returns a list of errors for each parsing error.
func Parse(s lexer.LexemeStream) (ast ast.AST, errors []error) {
	p := parser{stream: s}
	return p.parse()
}

func (p parser) parse() (ast ast.AST, errors []error) {
	errors = []error{}

	for !p.stream.EOF() {
		node, err := p.parseNode()

		if err != nil {
			errors = append(errors, err)
		} else {
			ast.Nodes = append(ast.Nodes, node)
		}
	}

	return ast, errors

}

func (p parser) parseNode() (ast.Node, error) {
	lexeme, err := p.stream.Peek()
	if err != nil {
		p.stream.Next()
		return nil, err
	}

	var node ast.Node

	switch true {
	case isExpressionToken(lexeme.Token):
		node, err = p.parseExpr()
	case isStatementToken(lexeme.Token):
		node, err = p.parseStatement()
	default:
		p.consumeUntilTerminator()
		return nil, fmt.Errorf("Unexpected lexeme %v; expected statement", lexeme.Value)
	}

	if err != nil {
		p.consumeUntilTerminator()
		return nil, err
	} else if err := p.parseTerminator(); err != nil {
		p.consumeUntilTerminator()
		return nil, err
	}

	return node, nil
}

func isStatementTerminator(t token.Token) bool {
	return t == token.Semicolon || t == token.Newline
}

func (p parser) parseTerminator() error {
	if p.stream.EOF() {
		return nil
	}

	lexeme, err := p.stream.Next()
	if err != nil {
		return err
	} else if !isStatementTerminator(lexeme.Token) {
		return fmt.Errorf("Expected statement terminator, got %v", lexeme.Value)
	}

	return nil
}

func (p parser) consumeUntilTerminator() {
	lexeme, _ := p.stream.Peek()

	for !p.stream.EOF() && !isStatementTerminator(lexeme.Token) {
		p.stream.Next()
	}
}

func (p parser) peekFrom(c func(token.Token) bool) (ok bool, err error) {
	if lexeme, err := p.stream.Peek(); err != nil {
		return false, err
	} else if c(lexeme.Token) {
		return true, nil
	}

	return false, nil
}

func (p parser) peek(t token.Token) (ok bool, err error) {
	if lexeme, err := p.stream.Peek(); err != nil {
		return false, err
	} else if lexeme.Token == t {
		return true, nil
	}

	return false, nil
}

func (p parser) allowFrom(c func(token.Token) bool) (ok bool, err error) {
	if lexeme, err := p.stream.Peek(); err != nil {
		return false, err
	} else if c(lexeme.Token) {
		p.stream.Next()
		return true, nil
	}

	return false, nil
}

func (p parser) allow(t token.Token) (ok bool, err error) {
	if lexeme, err := p.stream.Peek(); err != nil {
		return false, err
	} else if lexeme.Token == t {
		p.stream.Next()
		return true, nil
	}

	return false, nil
}

func (p parser) expectFrom(c func(token.Token) bool) (lexer.Lexeme, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return lexeme, err
	} else if !c(lexeme.Token) {
		return lexeme, fmt.Errorf("Unexpected %v", lexeme.Token)
	}

	return lexeme, nil
}

func (p parser) expect(t token.Token) (lexer.Lexeme, error) {
	lexeme, err := p.stream.Next()
	if err != nil {
		return lexeme, err
	} else if lexeme.Token != t {
		return lexeme, fmt.Errorf("Expected %v, got %v", t, lexeme.Token)
	}

	return lexeme, nil
}

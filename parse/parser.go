package parse

import (
	"errors"
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

func (p parser) parse() (ast ast.AST, errs []error) {
	errs = []error{}

	for !p.stream.EOF() {
		if ok, _ := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		node, err := p.parseNode()

		if err != nil {
			errs = append(errs, err)
			continue
		}

		if _, err := p.expectFrom(isStatementTerminator); err != nil {
			p.consumeUntilTerminator()
			err = errors.New("Expected statement terminator or EOF")
			errs = append(errs, err)
			continue
		}

		ast.Nodes = append(ast.Nodes, node)
	}

	return
}

func (p parser) parseBlock() (*ast.BlockStmt, error) {
	if _, err := p.expect(token.OpenCurly); err != nil {
		return nil, errors.New("Expected open curly brace")
	}

	nodes := []ast.Node{}

	for !p.stream.EOF() {
		if ok, _ := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		if ok, _ := p.peekFrom(isNodeToken); !ok {
			break
		}

		node, err := p.parseNode()
		if err != nil {
			return nil, err
		}

		nodes = append(nodes, node)

		if ok, _ := p.peek(token.CloseCurly); ok {
			break
		}

		if _, err := p.expectFrom(isStatementTerminator); err != nil {
			p.consumeUntilTerminator()
			return nil, errors.New("Expected statement terminator or EOF")
		}
	}

	if _, err := p.expect(token.CloseCurly); err != nil {
		return nil, errors.New("Expected close curly brace")
	}

	return &ast.BlockStmt{Nodes: nodes}, nil
}

func isNodeToken(t token.Token) bool {
	return isExpressionToken(t) || isStatementToken(t)
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
	}

	return node, nil
}

func isStatementTerminator(t token.Token) bool {
	return t == token.Semicolon || t == token.Newline || t == token.EOF
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

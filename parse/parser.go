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

func (p parser) parse() (ast ast.AST, errs []error) {
	errs = []error{}

	for !p.stream.EOF() {
		if ok := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		node, err := p.parseNodeWithRecovery()

		if err != nil {
			errs = append(errs, err)
			continue
		}

		ast.Nodes = append(ast.Nodes, node)
	}

	return
}

func (p parser) parseNodeWithRecovery() (node ast.Node, err error) {
	defer func() {
		if r := recover(); r != nil {
			err = r.(error)
		}
	}()

	node = p.parseNode()
	p.expectFrom(isStatementTerminator)
	return node, err
}

func (p parser) parseBlock() *ast.BlockStmt {
	p.nextConcrete(token.OpenCurly)

	nodes := []ast.Node{}

	for !p.stream.EOF() {
		if ok := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		if ok := p.peekFrom(isNodeToken); !ok {
			break
		}

		nodes = append(nodes, p.parseNode())

		if ok := p.peek(token.CloseCurly); ok {
			break
		}

		p.expectFrom(isStatementTerminator)
	}

	p.expect(token.CloseCurly)

	return &ast.BlockStmt{Nodes: nodes}
}

func isNodeToken(t token.Token) bool {
	return isExpressionToken(t) || isStatementToken(t)
}

func (p parser) parseNode() ast.Node {
	lexeme, _ := p.stream.Peek()

	var node ast.Node

	switch true {
	case isExpressionToken(lexeme.Token):
		node = p.parseExpr()
	case isStatementToken(lexeme.Token):
		node = p.parseStatement()
	default:
		p.consumeUntilTerminator()
		panic(fmt.Errorf("Unexpected lexeme %v; expected statement", lexeme.Value))
	}

	return node
}

func isStatementTerminator(t token.Token) bool {
	return t == token.Semicolon || t == token.Newline || t == token.EOF
}

func (p parser) consumeTerminators() {
	for p.allowFrom(isStatementTerminator) {
		// Do nothing
	}
}

func (p parser) consumeUntilTerminator() {
	lexeme, _ := p.stream.Peek()

	for !p.stream.EOF() && !isStatementTerminator(lexeme.Token) {
		p.stream.Next()
	}
}

func (p parser) peekFrom(c func(token.Token) bool) bool {
	lexeme, _ := p.stream.Peek()

	if c(lexeme.Token) {
		return true
	}

	return false
}

func (p parser) peek(t token.Token) bool {
	lexeme, _ := p.stream.Peek()

	if lexeme.Token == t {
		return true
	}

	return false
}

func (p parser) allowFrom(c func(token.Token) bool) bool {
	lexeme, _ := p.stream.Peek()

	if c(lexeme.Token) {
		p.stream.Next()
		return true
	}

	return false
}

func (p parser) allow(t token.Token) bool {
	lexeme, _ := p.stream.Peek()

	if lexeme.Token == t {
		p.stream.Next()
		return true
	}

	return false
}

func (p parser) expectFrom(c func(token.Token) bool) lexer.Lexeme {
	lexeme, err := p.stream.Next()

	if err != nil {
		panic(err)
	} else if !c(lexeme.Token) {
		panic(fmt.Errorf("Unexpected %v", lexeme.Token))
	}

	return lexeme
}

func (p parser) expect(t token.Token) lexer.Lexeme {
	lexeme, err := p.stream.Next()

	if err != nil {
		panic(err)
	} else if lexeme.Token != t {
		panic(fmt.Errorf("Expected %v, got %v", t, lexeme.Token))
	}

	return lexeme
}

// Gets the next non-whitespace token.
func (p parser) nextConcrete(t token.Token) lexer.Lexeme {
	lexeme, err := p.stream.Next()

	for lexeme.Token == token.Newline {
		lexeme, err = p.stream.Next()
	}

	if err != nil {
		panic(err)
	} else if lexeme.Token != t {
		panic(fmt.Errorf("Expected %v, got %v", t, lexeme.Token))
	}

	return lexeme
}

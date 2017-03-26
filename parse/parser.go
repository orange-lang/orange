package parse

import (
	"fmt"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
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

	switch true {
	case isExpressionToken(lexeme.Token):
		return p.parseExpr()
	}

	p.stream.Next()
	return nil, fmt.Errorf("Unexpected lexeme %v; expected node", lexeme.Value)
}

package parse

import (
	"errors"

	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/token"
)

func isExtensionStmtToken(t token.Token) bool {
	return t == token.Def || t == token.Static
}

func (p parser) parseExtension() *ast.ExtensionDecl {
	node := &ast.ExtensionDecl{}

	p.expect(token.Extend)

	if p.peek(token.LT) {
		node.GenericTypes = p.parseGenericList()
	}

	node.Original = p.parseType()

	if p.allow(token.Colon) {
		node.Supers = p.parseTypeList()
	}

	node.Body = p.parseExtensionBody()
	return node
}

func (p parser) parseExtensionBody() *ast.BlockStmt {
	p.nextConcrete(token.OpenCurly)

	nodes := []ast.Node{}

	for !p.stream.EOF() {
		if ok := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		if ok := p.peekFrom(isExtensionStmtToken); !ok {
			break
		}

		nodes = append(nodes, p.parseExtensionStmt())

		if ok := p.peek(token.CloseCurly); ok {
			break
		}

		p.expectFrom(isStatementTerminator)
	}

	p.expect(token.CloseCurly)
	return &ast.BlockStmt{Nodes: nodes}
}

func (p parser) parseExtensionStmt() ast.Node {
	if ok := p.peekFrom(isExtensionStmtToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Def, token.Static:
		return p.parseFunc()
	}

	panic(errors.New("Unexpected lexeme"))
}

package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isExtensionStmtToken(t token.Token) bool {
	return t == token.Def
}

func (p parser) parseExtension() *ast.ExtensionDecl {
	var original ast.Type
	var supers []ast.Type
	var genericParams []ast.Type
	var body *ast.BlockStmt

	p.expect(token.Extend)

	if p.peek(token.LT) {
		genericParams = p.parseGenericList()
	}

	original = p.parseType()

	if p.allow(token.Colon) {
		supers = p.parseTypeList()
	}

	body = p.parseExtensionBody()

	return &ast.ExtensionDecl{
		Original:     original,
		GenericTypes: genericParams,
		Supers:       supers,
		Body:         body,
	}
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
	case token.Def:
		return p.parseFunc()
	}

	panic(errors.New("Unexpected lexeme"))
}

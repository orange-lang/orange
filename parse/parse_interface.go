package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/ast/types"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isInterfaceToken(t token.Token) bool {
	return t == token.Def
}

func (p parser) parseInterface() *ast.InterfaceDecl {
	node := &ast.InterfaceDecl{}

	p.expect(token.Interface)

	if p.peek(token.LT) {
		node.GenericTypes = p.parseGenericList()
	}

	node.Name = p.expect(token.Identifier).Value

	if p.allow(token.Colon) {
		node.Supers = p.parseTypeList()
	}

	node.Body = p.parseInterfaceBody()
	return node
}

func (p parser) parseInterfaceBody() *ast.BlockStmt {
	p.nextConcrete(token.OpenCurly)

	nodes := []ast.Node{}

	for !p.stream.EOF() {
		if ok := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		if ok := p.peekFrom(isInterfaceToken); !ok {
			break
		}

		nodes = append(nodes, p.parseInterfaceStmt())

		if ok := p.peek(token.CloseCurly); ok {
			break
		}

		p.expectFrom(isStatementTerminator)
	}

	p.expect(token.CloseCurly)
	return &ast.BlockStmt{Nodes: nodes}
}

func (p parser) parseInterfaceStmt() ast.Node {
	if ok := p.peekFrom(isInterfaceToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Def:
		return p.parseInterfaceMethod()
	}

	panic(errors.New("Unexpected lexeme"))
}

func (p parser) parseInterfaceMethod() *ast.FunctionStmt {
	node := &ast.FunctionStmt{}

	p.expect(token.Def)

	if p.peek(token.LT) {
		node.GenericTypes = p.parseGenericList()
	}

	node.Name = p.expect(token.Identifier).Value

	p.expect(token.OpenParen)
	node.Parameters, _ = p.parseVarDeclList(false)
	p.expect(token.CloseParen)

	if p.allow(token.Arrow) {
		node.RetType = p.parseType()
	} else {
		node.RetType = &types.Void{}
	}

	return node
}

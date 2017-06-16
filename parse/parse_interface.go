package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isInterfaceToken(t token.Token) bool {
	return t == token.Def
}

func (p parser) parseInterface() *ast.InterfaceDecl {
	var name string
	var supers []ast.Type
	var genericParams []ast.Type
	var body *ast.BlockStmt

	p.expect(token.Interface)

	if p.peek(token.LT) {
		genericParams = p.parseGenericList()
	}

	name = p.expect(token.Identifier).Value

	if p.allow(token.Colon) {
		supers = p.parseTypeList()
	}

	body = p.parseInterfaceBody()

	return &ast.InterfaceDecl{
		Name:         name,
		GenericTypes: genericParams,
		Supers:       supers,
		Body:         body,
	}
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
	var name string
	var params []*ast.ParamDecl
	var retTy ast.Type
	var genericParams []ast.Type

	p.expect(token.Def)

	if p.peek(token.LT) {
		genericParams = p.parseGenericList()
	}

	name = p.expect(token.Identifier).Value

	p.expect(token.OpenParen)
	params, _ = p.parseVarDeclList(false)
	p.expect(token.CloseParen)

	if p.allow(token.Arrow) {
		retTy = p.parseType()
	} else {
		retTy = &ast.VoidType{}
	}

	return &ast.FunctionStmt{
		Name:         name,
		GenericTypes: genericParams,
		Parameters:   params,
		RetType:      retTy,
		Body:         nil,
	}
}

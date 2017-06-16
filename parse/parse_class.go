package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isClassStmtToken(t token.Token) bool {
	return t == token.Var || t == token.Property || t == token.Def
}

func (p parser) parseClass() *ast.ClassDecl {
	var name string
	var supers []ast.Type
	var genericParams []ast.Type
	var body *ast.BlockStmt

	p.expect(token.Class)

	if p.peek(token.LT) {
		genericParams = p.parseGenericList()
	}

	name = p.expect(token.Identifier).Value

	if p.allow(token.Colon) {
		supers = p.parseTypeList()
	}

	body = p.parseClassBody()

	return &ast.ClassDecl{
		Name:         name,
		GenericTypes: genericParams,
		Supers:       supers,
		Body:         body,
	}
}

func (p parser) parseClassBody() *ast.BlockStmt {
	p.nextConcrete(token.OpenCurly)

	nodes := []ast.Node{}

	for !p.stream.EOF() {
		if ok := p.allowFrom(isStatementTerminator); ok {
			continue
		}

		if ok := p.peekFrom(isClassStmtToken); !ok {
			break
		}

		nodes = append(nodes, p.parseClassStmt())

		if ok := p.peek(token.CloseCurly); ok {
			break
		}

		p.expectFrom(isStatementTerminator)
	}

	p.expect(token.CloseCurly)
	return &ast.BlockStmt{Nodes: nodes}
}

func (p parser) parseClassStmt() ast.Node {
	if ok := p.peekFrom(isClassStmtToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Var:
		return p.parseMemberDecl()
	case token.Property:
		return p.parseProperty()
	case token.Def:
		return p.parseFunc()
	}

	panic(errors.New("Unexpected lexeme"))
}

func (p parser) parseMemberDecl() *ast.MemberDecl {
	varDecl := p.parseVarDecl()

	return &ast.MemberDecl{
		Name:  varDecl.Name,
		Type:  varDecl.Type,
		Value: varDecl.Value,
	}
}

func (p parser) parseProperty() *ast.PropertyDecl {
	var name string
	var propType ast.Type
	var getter *ast.GetterStmt
	var setter *ast.SetterStmt

	p.expect(token.Property)

	name = p.expect(token.Identifier).Value

	if p.allow(token.Arrow) {
		propType = p.parseType()
	}

	p.nextConcrete(token.OpenCurly)

	p.consumeTerminators()
	if p.peek(token.Get) {
		getter = p.parseGetter()
	}

	p.consumeTerminators()
	if p.peek(token.Set) {
		setter = p.parseSetter()
	}

	p.nextConcrete(token.CloseCurly)

	return &ast.PropertyDecl{
		Name:   name,
		Type:   propType,
		Getter: getter,
		Setter: setter,
	}
}

func (p parser) parseGetter() *ast.GetterStmt {
	p.expect(token.Get)
	body := p.parseBlock()

	return &ast.GetterStmt{
		Body: body,
	}
}

func (p parser) parseSetter() *ast.SetterStmt {
	p.expect(token.Set)

	p.expect(token.OpenParen)
	varDecl := p.parseParam()
	p.expect(token.CloseParen)

	body := p.parseBlock()

	return &ast.SetterStmt{
		SetterVariable: varDecl,
		Body:           body,
	}
}

func (p parser) parseTypeList() (tys []ast.Type) {
	ty := p.parseType()
	tys = append(tys, ty)

	for p.allow(token.Comma) {
		ty := p.parseType()
		tys = append(tys, ty)
	}

	return
}

package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isClassStmtToken(t token.Token) bool {
	return isClassComponentToken(t) || isPrivacyToken(t)
}

func isClassComponentToken(t token.Token) bool {
	return t == token.Var || t == token.Property || t == token.Def ||
		t == token.Const
}

func (p parser) parseClass() *ast.ClassDecl {
	node := &ast.ClassDecl{}

	p.expect(token.Class)

	if p.peek(token.LT) {
		node.GenericTypes = p.parseGenericList()
	}

	node.Name = p.expect(token.Identifier).Value

	if p.allow(token.Colon) {
		node.Supers = p.parseTypeList()
	}

	node.Body = p.parseClassBody()

	return node
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

	if p.peekFrom(isPrivacyToken) {
		return p.parseClassPrivacy()
	}

	return p.parseClassComponent()
}

func (p parser) parseClassComponent() ast.PrivacyFlag {
	if ok := p.peekFrom(isClassComponentToken); !ok {
		panic(errors.New("Expected declaration"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Const:
		fallthrough
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
	isConst := p.allow(token.Const)

	varDecl := p.parseVarDecl()
	ty := varDecl.Type

	if isConst {
		ty = &ast.ConstType{InnerType: ty}
	}

	return &ast.MemberDecl{
		Name:  varDecl.Name,
		Type:  ty,
		Value: varDecl.Value,
	}
}

func (p parser) parseProperty() *ast.PropertyDecl {
	node := &ast.PropertyDecl{}

	p.expect(token.Property)

	node.Name = p.expect(token.Identifier).Value

	if p.allow(token.Arrow) {
		node.Type = p.parseType()
	}

	p.nextConcrete(token.OpenCurly)

	p.consumeTerminators()
	if p.peek(token.Get) {
		node.Getter = p.parseGetter()
	}

	p.consumeTerminators()
	if p.peek(token.Set) {
		node.Setter = p.parseSetter()
	}

	p.nextConcrete(token.CloseCurly)

	return node
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

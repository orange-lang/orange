package parse

import (
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func (p parser) parseExternFunc() *ast.ExternFuncStmt {
	var name string
	var params []*ast.VarDecl
	var retTy ast.Type

	p.expect(token.Extern)
	p.expect(token.Def)

	name = p.expect(token.Identifier).Value

	p.expect(token.OpenParen)
	params, varArg := p.parseVarDeclList()
	p.expect(token.CloseParen)

	if p.allow(token.Arrow) {
		retTy = p.parseType()
	} else {
		retTy = &ast.VoidType{}
	}

	return &ast.ExternFuncStmt{
		Name:             name,
		Parameters:       params,
		RetType:          retTy,
		VariableArgument: varArg,
	}
}

func (p parser) parseVarDeclList() (params []*ast.VarDecl, isVarArg bool) {
	params = []*ast.VarDecl{}

	if !p.peek(token.Identifier) {
		return
	}

	params = append(params, p.parseParam())

	for p.allow(token.Comma) {
		if p.allow(token.Elipsis) {
			isVarArg = true
			break
		}

		params = append(params, p.parseParam())
	}

	return
}

func (p parser) parseParam() *ast.VarDecl {
	name := p.expect(token.Identifier).Value

	p.expect(token.Colon)
	ty := p.parseType()

	return &ast.VarDecl{Name: name, Type: ty}
}

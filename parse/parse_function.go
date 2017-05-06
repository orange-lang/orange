package parse

import (
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func (p parser) parseFunc() *ast.FunctionStmt {
	var name string
	var params []*ast.VarDecl
	var retTy ast.Type
	var genericParams []ast.Type
	var body *ast.BlockStmt
	var isDtor bool

	p.expect(token.Def)

	if p.peek(token.LT) {
		genericParams = p.parseGenericList()
	}

	if p.allow(token.BitNot) {
		isDtor = true
	}

	name = p.expect(token.Identifier).Value

	p.expect(token.OpenParen)
	params, _ = p.parseVarDeclList(false)
	p.expect(token.CloseParen)

	if p.allow(token.Arrow) {
		retTy = p.parseType()
	}

	body = p.parseBlock()

	return &ast.FunctionStmt{
		Name:         name,
		GenericTypes: genericParams,
		Parameters:   params,
		RetType:      retTy,
		Body:         body,
		Destructor:   isDtor,
	}
}

func (p parser) parseGenericList() (types []ast.Type) {
	p.expect(token.LT)

	tyName := p.expect(token.Identifier).Value
	types = append(types, &ast.NamedType{Name: tyName})

	for p.allow(token.Comma) {
		tyName = p.expect(token.Identifier).Value
		types = append(types, &ast.NamedType{Name: tyName})
	}

	p.expect(token.GT)

	return
}

func (p parser) parseExternFunc() *ast.ExternFuncStmt {
	var name string
	var params []*ast.VarDecl
	var retTy ast.Type

	p.expect(token.Extern)
	p.expect(token.Def)

	name = p.expect(token.Identifier).Value

	p.expect(token.OpenParen)
	params, varArg := p.parseVarDeclList(true)
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

func (p parser) parseVarDeclList(allowVarArg bool) (params []*ast.VarDecl, isVarArg bool) {
	params = []*ast.VarDecl{}

	if !p.peek(token.Identifier) {
		return
	}

	params = append(params, p.parseParam())

	for p.allow(token.Comma) {
		if allowVarArg && p.allow(token.Elipsis) {
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

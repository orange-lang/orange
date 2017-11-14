package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/ast/types"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isStatementToken(t token.Token) bool {
	return t == token.Var || t == token.Package || t == token.Import ||
		t == token.If || t == token.Alias || isLoopToken(t) || t == token.Enum ||
		t == token.Try || t == token.Extern || t == token.Def || t == token.Return ||
		t == token.Class || t == token.Extend || t == token.Interface ||
		isPrivacyToken(t) || t == token.Const
}

func isDeclarationToken(t token.Token) bool {
	return t == token.Enum || t == token.Def || t == token.Class ||
		t == token.Interface
}

func (p parser) parseStatement() ast.Statement {
	if ok := p.peekFrom(isStatementToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Const:
		return p.parseConst()
	case token.Var:
		return p.parseVarDecl()
	case token.Package:
		return p.parsePackageDecl()
	case token.Import:
		return p.parseImportDecl()
	case token.If:
		return p.parseIf()
	case token.Alias:
		return p.parseAlias()
	case token.For:
		return p.parseForLoop()
	case token.While:
		return p.parseWhileLoop()
	case token.Do:
		return p.parseDoWhileLoop()
	case token.Try:
		return p.parseTry()
	case token.Extern:
		return p.parseExternFunc()
	case token.Return:
		return p.parseReturnStmt()
	case token.Extend:
		return p.parseExtension()
	default:
		if isPrivacyToken(lexeme.Token) {
			return p.parsePrivacy()
		}
	}

	return p.parseDeclaration()
}

func (p parser) parseDeclaration() ast.PrivacyFlag {
	if ok := p.peekFrom(isDeclarationToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Enum:
		return p.parseEnum()
	case token.Def:
		return p.parseFunc()
	case token.Class:
		return p.parseClass()
	case token.Interface:
		return p.parseInterface()
	}

	panic(errors.New("Unexpected lexeme"))
}

func (p parser) parseConst() ast.Statement {
	lookahead, _ := p.stream.Lookahead(2)

	switch lookahead[1].Token {
	case token.Var:
		return p.parseVarDecl()
	case token.If:
		return p.parseConstIf()
	}

	panic(errors.New("Unexpected lexeme"))
}

func (p parser) parseReturnStmt() *ast.ReturnStmt {
	var value ast.Expression

	p.expect(token.Return)

	if p.peekFrom(isExpressionToken) {
		value = p.parseExpr()
	}

	return &ast.ReturnStmt{Value: value}
}

func (p parser) parseTry() *ast.TryStmt {
	var tryBlock *ast.BlockStmt
	var finallyBlock *ast.BlockStmt
	catches := []*ast.CatchStmt{}

	p.expect(token.Try)

	tryBlock = p.parseBlock()
	catchBlock := p.parseCatch()

	catches = append(catches, catchBlock)

	nextLexeme, _ := p.stream.Peek()
	for nextLexeme.Token == token.Catch {
		catchBlock := p.parseCatch()
		catches = append(catches, catchBlock)

		nextLexeme, _ = p.stream.Peek()
	}

	if ok := p.allow(token.Finally); ok {
		finallyBlock = p.parseBlock()
	}

	return &ast.TryStmt{
		Body:    tryBlock,
		Catch:   catches,
		Finally: finallyBlock,
	}
}

func (p parser) parseCatch() *ast.CatchStmt {
	p.expect(token.Catch)

	p.expect(token.OpenParen)
	exVar := p.parseParam()
	p.expect(token.CloseParen)

	catchBlock := p.parseBlock()

	return &ast.CatchStmt{
		Variable: exVar,
		Body:     catchBlock,
	}
}

func (p parser) parseEnum() *ast.EnumDecl {
	p.expect(token.Enum)

	name := p.expect(token.Identifier).Value

	p.nextConcrete(token.OpenCurly)
	members := p.parseEnumMembers()
	p.nextConcrete(token.CloseCurly)

	return &ast.EnumDecl{Name: name, Members: members}
}

// identifier (, identifier)*
func (p parser) parseEnumMembers() []string {
	members := []string{}

	lexeme := p.nextConcrete(token.Identifier)

	members = append(members, lexeme.Value)

	lexeme, _ = p.stream.Peek()
	for lexeme.Token == token.Comma {
		p.stream.Next()

		lexeme = p.nextConcrete(token.Identifier)

		members = append(members, lexeme.Value)

		lexeme, _ = p.stream.Peek()
	}

	return members
}

func (p parser) parseAlias() *ast.AliasDecl {
	p.expect(token.Alias)

	nameLexeme := p.expect(token.Identifier)

	p.expect(token.Assign)

	targetType := p.parseType()
	return &ast.AliasDecl{Name: nameLexeme.Value, Type: targetType}
}

func (p parser) parseIf() *ast.IfStmt {
	p.expect(token.If)

	mainCondition := p.parseCondition()
	return mainCondition
}

// Parses the condition part of an if statement, and then
// elif or else.
func (p parser) parseCondition() *ast.IfStmt {
	node := &ast.IfStmt{}

	p.expect(token.OpenParen)
	node.Condition = p.parseExpr()
	p.expect(token.CloseParen)

	node.Body = p.parseBlock()

	if ok := p.allow(token.Elif); ok {
		node.Else = p.parseCondition()
	} else if ok := p.allow(token.Else); ok {
		node.Else = p.parseBlock()
	}

	return node
}

func (p parser) parseConstIf() *ast.ConstIfStmt {
	p.expect(token.Const)
	p.expect(token.If)

	return p.parseConstCondition()
}

func (p parser) parseConstCondition() *ast.ConstIfStmt {
	node := &ast.ConstIfStmt{}

	p.expect(token.OpenParen)
	node.Condition = p.parseExpr()
	p.expect(token.CloseParen)

	node.Body = p.parseBlock()

	if p.allow(token.Elif) {
		node.Else = p.parseConstCondition()
	} else if p.allow(token.Else) {
		node.Else = p.parseBlock()
	}

	return node
}

func (p parser) parseImportDecl() *ast.ImportDecl {
	var fullPackageName string

	p.expect(token.Import)

	for true {
		name := p.expect(token.Identifier)

		fullPackageName += name.Value

		if ok := p.allow(token.Dot); !ok {
			break
		}

		fullPackageName += "."
	}

	return &ast.ImportDecl{Name: fullPackageName}
}

func (p parser) parsePackageDecl() *ast.PackageDecl {
	var fullPackageName string

	p.expect(token.Package)

	for true {
		name := p.expect(token.Identifier)

		fullPackageName += name.Value

		if ok := p.allow(token.Dot); !ok {
			break
		}

		fullPackageName += "."
	}

	return &ast.PackageDecl{Name: fullPackageName}
}

func (p parser) parseVarDecl() *ast.VarDecl {
	isConst := p.allow(token.Const)
	node := &ast.VarDecl{}

	p.expect(token.Var)

	node.Name = p.expect(token.Identifier).Value

	if p.allow(token.Colon) {
		node.Type = p.parseType()
	} else {
		node.Type = &types.Unresolved{}
	}

	if p.allow(token.Assign) {
		node.Value = p.parseExpr()
	}

	if isConst {
		node.Type.SetFlag(types.FlagConst)
	}

	return node
}

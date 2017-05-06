package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isStatementToken(t token.Token) bool {
	return t == token.Var || t == token.Package || t == token.Import ||
		t == token.If || t == token.Alias || isLoopToken(t) || t == token.Enum ||
		t == token.Try || t == token.Extern || t == token.Def || t == token.Return ||
		t == token.Class
}

func (p parser) parseStatement() ast.Statement {
	if ok := p.peekFrom(isStatementToken); !ok {
		panic(errors.New("Expected statement"))
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
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
	case token.Enum:
		return p.parseEnum()
	case token.Try:
		return p.parseTry()
	case token.Extern:
		return p.parseExternFunc()
	case token.Def:
		return p.parseFunc()
	case token.Return:
		return p.parseReturnStmt()
	case token.Class:
		return p.parseClass()
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

	exVar := p.parseVarDecl()

	p.expect(token.CloseParen)

	catchBlock := p.parseBlock()

	return &ast.CatchStmt{
		Variable: exVar,
		Body:     catchBlock,
	}
}

func (p parser) parseEnum() *ast.EnumDecl {
	name := ""

	p.expect(token.Enum)

	nameLexeme := p.expect(token.Identifier)

	name = nameLexeme.Value

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
	var condition ast.Expression
	var ifPart *ast.BlockStmt
	var elsePart ast.Node

	p.expect(token.OpenParen)

	condition = p.parseExpr()

	p.expect(token.CloseParen)

	ifPart = p.parseBlock()

	if ok := p.allow(token.Elif); ok {
		elsePart = p.parseCondition()
	} else if ok := p.allow(token.Else); ok {
		elsePart = p.parseBlock()
	}

	return &ast.IfStmt{
		Condition: condition,
		Body:      ifPart,
		Else:      elsePart,
	}
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
	var idLexeme lexer.Lexeme
	var nodeType ast.Type
	var nodeValue ast.Expression

	p.expect(token.Var)

	idLexeme = p.expect(token.Identifier)

	nodeType = p.tryParseColonType()

	nodeValue = p.tryParseEqualValue()

	return &ast.VarDecl{
		Name:  idLexeme.Value,
		Type:  nodeType,
		Value: nodeValue,
	}
}

func (p parser) tryParseColonType() ast.Type {
	if ok := p.allow(token.Colon); ok {
		return p.parseType()
	}

	return nil
}

func (p parser) tryParseEqualValue() ast.Expression {
	if ok := p.allow(token.Assign); ok {
		return p.parseExpr()
	}

	return nil
}

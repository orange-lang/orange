package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isStatementToken(t token.Token) bool {
	return t == token.Var || t == token.Package || t == token.Import
}

func (p parser) parseStatement() (ast.Statement, error) {
	if ok, _ := p.peekFrom(isStatementToken); !ok {
		return nil, errors.New("Expected statement")
	}

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Var:
		return p.parseVarDecl()
	case token.Package:
		return p.parsePackageDecl()
	case token.Import:
		return p.parseImportDecl()
	}

	return nil, errors.New("Unexpected lexeme")
}

func (p parser) parseImportDecl() (*ast.ImportDecl, error) {
	var fullPackageName string

	if _, err := p.expect(token.Import); err != nil {
		return nil, err
	}

	for true {
		name, err := p.expect(token.Identifier)
		if err != nil {
			return nil, err
		}

		fullPackageName += name.Value

		if ok, _ := p.allow(token.Dot); !ok {
			break
		}

		fullPackageName += "."
	}

	return &ast.ImportDecl{Name: fullPackageName}, nil
}

func (p parser) parsePackageDecl() (*ast.PackageDecl, error) {
	var fullPackageName string

	if _, err := p.expect(token.Package); err != nil {
		return nil, err
	}

	for true {
		name, err := p.expect(token.Identifier)
		if err != nil {
			return nil, err
		}

		fullPackageName += name.Value

		if ok, _ := p.allow(token.Dot); !ok {
			break
		}

		fullPackageName += "."
	}

	return &ast.PackageDecl{Name: fullPackageName}, nil
}

func (p parser) parseVarDecl() (*ast.VarDecl, error) {
	var idLexeme lexer.Lexeme
	var nodeType ast.Type
	var nodeValue ast.Expression
	var err error

	if _, err := p.expect(token.Var); err != nil {
		return nil, err
	}

	if idLexeme, err = p.expect(token.Identifier); err != nil {
		return nil, err
	}

	if nodeType, err = p.tryParseColonType(); err != nil {
		return nil, err
	}

	if nodeValue, err = p.tryParseEqualValue(); err != nil {
		return nil, err
	}

	return &ast.VarDecl{
		Name:  idLexeme.Value,
		Type:  nodeType,
		Value: nodeValue,
	}, nil
}

func (p parser) tryParseColonType() (ast.Type, error) {
	if ok, err := p.allow(token.Colon); err != nil {
		return nil, err
	} else if ok {
		return p.parseType()
	}

	return nil, nil
}

func (p parser) tryParseEqualValue() (ast.Expression, error) {
	if ok, err := p.allow(token.Assign); err != nil {
		return nil, err
	} else if ok {
		return p.parseExpr()
	}

	return nil, nil
}

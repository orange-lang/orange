package parse

import (
	"errors"

	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func isPrivacyToken(t token.Token) bool {
	return t == token.Public || t == token.Protected || t == token.Private ||
		t == token.Package
}

func isPrivacyStatement(t token.Token) bool {
	return t == token.Enum || t == token.Def || t == token.Class ||
		t == token.Interface
}

func isClassPrivacyStatement(t token.Token) bool {
	return t == token.Var || t == token.Property || t == token.Def ||
		t == token.Const
}

func (p parser) parsePrivacy() ast.Statement {
	privacyLevel := p.parsePrivacyLevel()

	if ok := p.peekFrom(isPrivacyStatement); !ok {
		panic(errors.New("Expected declaration"))
	}

	var declaration ast.PrivacyFlag

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Enum:
		declaration = p.parseEnum()
	case token.Def:
		declaration = p.parseFunc()
	case token.Class:
		declaration = p.parseClass()
	case token.Interface:
		declaration = p.parseInterface()
	default:
		panic(errors.New("Unexpected lexeme"))
	}

	declaration.SetPrivacyLevel(privacyLevel)
	return declaration
}

func (p parser) parseClassPrivacy() ast.Statement {
	privacyLevel := p.parsePrivacyLevel()

	if ok := p.peekFrom(isClassPrivacyStatement); !ok {
		panic(errors.New("Expected declaration"))
	}

	var declaration ast.PrivacyFlag

	switch lexeme, _ := p.stream.Peek(); lexeme.Token {
	case token.Const:
		fallthrough
	case token.Var:
		declaration = p.parseMemberDecl()
	case token.Property:
		declaration = p.parseProperty()
	case token.Def:
		declaration = p.parseFunc()
	default:
		panic(errors.New("Unexpected lexeme"))
	}

	declaration.SetPrivacyLevel(privacyLevel)
	return declaration
}

func (p parser) parsePrivacyLevel() ast.PrivacyLevel {
	level := p.expectFrom(isPrivacyToken).Token

	switch level {
	case token.Public:
		return ast.PrivacyPublic
	case token.Protected:
		return ast.PrivacyProtected
	case token.Private:
		return ast.PrivacyPrivate
	}

	panic(errors.New("Unexpected privacy level"))
}

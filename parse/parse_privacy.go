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

func (p parser) parsePrivacy() ast.Statement {
	privacyLevel := p.parsePrivacyLevel()

	if ok := p.peekFrom(isDeclarationToken); !ok {
		panic(errors.New("Expected declaration"))
	}

	var declaration ast.PrivacyFlag = p.parseDeclaration()
	declaration.SetPrivacyLevel(privacyLevel)

	return declaration
}

func (p parser) parseClassPrivacy() ast.Statement {
	privacyLevel := p.parsePrivacyLevel()

	var declaration ast.PrivacyFlag = p.parseClassComponent()
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

package parse

import (
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/token"
)

func isLoopToken(t token.Token) bool {
	return t == token.For || t == token.While || t == token.Do
}

func (p parser) parseDoWhileLoop() *ast.LoopStmt {
	p.expect(token.Do)
	body := p.parseBlock()
	p.expect(token.While)

	p.expect(token.OpenParen)
	condition := p.parseExpr()
	p.expect(token.CloseParen)

	return &ast.LoopStmt{
		Condition: condition,
		Body:      body,
		CheckTime: ast.CheckAfter,
	}
}

func (p parser) parseWhileLoop() *ast.LoopStmt {
	p.expect(token.While)

	p.expect(token.OpenParen)
	condition := p.parseExpr()
	p.expect(token.CloseParen)

	body := p.parseBlock()

	return &ast.LoopStmt{
		Condition: condition,
		Body:      body,
		CheckTime: ast.CheckBefore,
	}
}

func (p parser) parseForLoop() *ast.LoopStmt {
	node := &ast.LoopStmt{CheckTime: ast.CheckBefore}

	p.expect(token.For)

	p.expect(token.OpenParen)

	if ok := p.peek(token.Var); ok {
		node.Initializer = p.parseVarDecl()
	}

	p.expect(token.Semicolon)

	if ok := p.peekFrom(isExpressionToken); ok {
		node.Condition = p.parseExpr()
	}

	p.expect(token.Semicolon)

	if ok := p.peekFrom(isExpressionToken); ok {
		node.Afterthought = p.parseExpr()
	}

	p.expect(token.CloseParen)

	node.Body = p.parseBlock()
	return node
}

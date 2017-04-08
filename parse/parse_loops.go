package parse

import (
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse/lexer/token"
)

func (p parser) parseDoWhileLoop() (*ast.LoopStmt, error) {
	if _, err := p.expect(token.Do); err != nil {
		return nil, err
	}

	body, err := p.parseBlock()
	if err != nil {
		return nil, err
	}

	if _, err := p.expect(token.While); err != nil {
		return nil, err
	}

	if _, err := p.expect(token.OpenParen); err != nil {
		return nil, err
	}

	condition, err := p.parseExpr()
	if err != nil {
		return nil, err
	}

	if _, err := p.expect(token.CloseParen); err != nil {
		return nil, err
	}

	return &ast.LoopStmt{
		Condition: condition,
		Body:      body,
		CheckTime: ast.CheckAfter,
	}, nil
}

func (p parser) parseWhileLoop() (*ast.LoopStmt, error) {
	if _, err := p.expect(token.While); err != nil {
		return nil, err
	}

	if _, err := p.expect(token.OpenParen); err != nil {
		return nil, err
	}

	condition, err := p.parseExpr()
	if err != nil {
		return nil, err
	}

	if _, err := p.expect(token.CloseParen); err != nil {
		return nil, err
	}

	body, err := p.parseBlock()
	if err != nil {
		return nil, err
	}

	return &ast.LoopStmt{
		Condition: condition,
		Body:      body,
		CheckTime: ast.CheckBefore,
	}, nil
}

func (p parser) parseForLoop() (*ast.LoopStmt, error) {
	var initializer *ast.VarDecl
	var condition ast.Expression
	var afterthought ast.Expression
	var err error

	if _, err = p.expect(token.For); err != nil {
		return nil, err
	}

	if _, err = p.expect(token.OpenParen); err != nil {
		return nil, err
	}

	if ok, _ := p.peek(token.Var); ok {
		initializer, err = p.parseVarDecl()
		if err != nil {
			return nil, err
		}
	}

	if _, err := p.expect(token.Semicolon); err != nil {
		return nil, err
	}

	if ok, _ := p.peekFrom(isExpressionToken); ok {
		condition, err = p.parseExpr()
		if err != nil {
			return nil, err
		}
	}

	if _, err := p.expect(token.Semicolon); err != nil {
		return nil, err
	}

	if ok, _ := p.peekFrom(isExpressionToken); ok {
		afterthought, err = p.parseExpr()
		if err != nil {
			return nil, err
		}
	}

	if _, err = p.expect(token.CloseParen); err != nil {
		return nil, err
	}

	body, err := p.parseBlock()
	if err != nil {
		return nil, err
	}

	return &ast.LoopStmt{
		Initializer:  initializer,
		Condition:    condition,
		Afterthought: afterthought,
		Body:         body,
		CheckTime:    ast.CheckBefore,
	}, nil
}

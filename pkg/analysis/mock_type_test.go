package analysis

import (
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

type mockNode struct{ visited bool }

func (*mockNode) IsNode()       {}
func (*mockNode) IsExpression() {}
func (*mockNode) IsIdentifier() {}
func (*mockNode) IsStatement()  {}

func (n *mockNode) Accept(visitor ast.NodeVisitor) { n.visited = true }

type mockExpr struct{ nodeType types.Type }

func (*mockExpr) IsNode()       {}
func (*mockExpr) IsExpression() {}
func (*mockExpr) IsIdentifier() {}
func (*mockExpr) IsStatement()  {}

func (n *mockExpr) Accept(visitor ast.NodeVisitor) {
	visitor.(*typeChecker).SetType(n, n.nodeType)
}

func newMockExpr(ty types.Type) *mockExpr {
	return &mockExpr{nodeType: ty}
}

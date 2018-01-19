package analysis

import "github.com/orange-lang/orange/pkg/ast"

func (v *typeChecker) VisitBlockStmt(node *ast.BlockStmt) {
	for _, node := range node.Nodes {
		node.Accept(v)
	}
}

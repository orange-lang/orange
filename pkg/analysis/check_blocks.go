package analysis

import "github.com/orange-lang/orange/pkg/ast"

func (v *typeChecker) getScopeForNode(node ast.Node) *Scope {
	scope, hasScope := v.typeInfo.Scopes[node]
	if hasScope {
		return scope
	}

	scope = NewScope(node)
	v.currentScope.AddScope(scope)
	v.typeInfo.Scopes[node] = scope

	return scope
}

func (v *typeChecker) VisitBlockStmt(node *ast.BlockStmt) {
	prevScope := v.currentScope
	v.currentScope = v.getScopeForNode(node)

	for _, node := range node.Nodes {
		v.tryResolve(node)
	}

	v.currentScope = prevScope
}

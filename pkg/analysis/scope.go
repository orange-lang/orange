package analysis

import (
	"github.com/orange-lang/orange/pkg/ast"
)

// Scope encompasses the scope for statements and expressions that involve
// code blocks. For example, functions and if statements would both have their
// own scope.
type Scope struct {
	// Node is tied to the node that this scope is representative of
	Node ast.Node

	// Children of this scope - nested functions, if statements, etc.
	Children []*Scope
}

// Resolve typechecks the entire scope and its children scopes. During
// this process, the tree of this scope's AST will be typechecked,
// and new scopes may be added as children to this one.
func (s *Scope) Resolve(ti *TypeInfo) error {
	visitor := newTypeChecker(s, ti)

	s.Node.Accept(visitor)
	return visitor.GetError()
}

func NewScope(node ast.Node) *Scope {
	return &Scope{
		Node:     node,
		Children: []*Scope{},
	}
}

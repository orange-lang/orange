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

	// Parent of this Scope
	Parent *Scope

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

// AddScope adds a scope as a scope as a child and sets its parent to
// this scope.
func (s *Scope) AddScope(child *Scope) {
	child.Parent = s
	s.Children = append(s.Children, child)
}

// NewScope creates a new scope given a node to represent it.
func NewScope(node ast.Node) *Scope {
	return &Scope{
		Node:     node,
		Children: []*Scope{},
	}
}

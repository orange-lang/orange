package analysis

import (
	"fmt"

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

// nodeDefines returns true if a node defines something by a given name
func (s *Scope) nodeDefines(node ast.Node, name string) bool {
	switch declNode := node.(type) {
	case *ast.VarDecl:
		if declNode.Name == name {
			return true
		}
	}

	return false
}

// isPositionalDecl returns true if a node can only be used after it is
// declared
func (s *Scope) isPositionalDecl(node ast.Node) bool {
	_, ok := node.(*ast.VarDecl)
	return ok
}

// FindDecl searches up the list of scopes until a name declared by a specific
// name is found. A user is passed to determine whether or not the user can
// access a node before it is declared.
func (s *Scope) FindDecl(hier *ast.Hierarchy, name string, user ast.Node) (ast.Node, error) {
	originalUser := user

	peekScope := s

	for peekScope != nil {
		userIdx := hier.ChildIdx(peekScope.Node, user)
		if userIdx == -1 {
			return nil, fmt.Errorf(InvalidSearchUser)
		}

		children := hier.Children(peekScope.Node)
		for childIdx, child := range children {
			if s.nodeDefines(child, name) {
				if s.isPositionalDecl(child) && childIdx > userIdx {
					return nil, fmt.Errorf(UseBeforeDeclared, originalUser, child)
				}

				return child, nil
			}
		}

		// Go up the tree. The new user is the scope's node and we're looking
		// at the children of the scope's parent.
		user = peekScope.Node
		peekScope = peekScope.Parent
	}

	return nil, nil
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

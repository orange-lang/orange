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
		return declNode.Name == name
	case *ast.AliasDecl:
		return declNode.Name == name
	case *ast.ParamDecl:
		return declNode.Name == name
	}

	return false
}

// isPositionalDecl returns true if a node can only be used after it is
// declared
func (s *Scope) isPositionalDecl(node ast.Node) bool {
	if decl, ok := node.(*ast.VarDecl); ok {
		return !decl.Static
	}

	return false
}

func (s *Scope) IsUnique(hier *ast.Hierarchy, user ast.Node) bool {
	switch node := user.(type) {
	case *ast.VarDecl:
		return s.isUniqueVarDecl(hier, node)
	}

	return true
}

func (s *Scope) isUniqueVarDecl(hier *ast.Hierarchy, node *ast.VarDecl) bool {
	parent, _ := hier.Parent(node)
	if parent == nil {
		return true
	}

	nodeIdx := hier.ChildIdx(parent, node)

	// Check direct siblings first
	for _, sibling := range hier.Siblings(node) {
		siblingIdx := hier.ChildIdx(parent, sibling)

		if siblingIdx < nodeIdx && s.nodeDefines(sibling, node.Name) {
			return false
		}
	}

	isFuncNode := func(node ast.Node) bool {
		_, ok := node.(*ast.FunctionStmt)
		return ok
	}

	findFuncScope := func() *Scope {
		peekScope := s

		for peekScope != nil && !isFuncNode(peekScope.Node) {
			peekScope = peekScope.Parent
		}

		return peekScope
	}

	// Check to see if any of our parent scopes is a function - if it is,
	// we have to make sure none of the parameters of that function
	// declare something of the same name.
	if funcScope := findFuncScope(); funcScope != nil {
		funcNode := funcScope.Node.(*ast.FunctionStmt)
		for _, param := range funcNode.Parameters {
			if s.nodeDefines(param, node.Name) {
				return false
			}
		}
	}

	return true
}

// FindDecl searches up the list of scopes until a name declared by a specific
// name is found. A user is passed to determine whether or not the user can
// access a node before it is declared.
func (s *Scope) FindDecl(hier *ast.Hierarchy, name string, user ast.Node) (ast.Node, error) {
	originalUser := user

	peekScope := s

	var leftFunction *ast.FunctionStmt

	for peekScope != nil {
		userIdx := hier.ChildIdx(peekScope.Node, user)

		// The user is currently set to the literal node which is finding the
		// declaration, however in many circumstances we require to find the "true"
		// user, which the node that is the immediate child of the peekScope.Node.
		// Climb the tree of parentage until this node is found.
		for userIdx == -1 {
			ok := false

			if user, ok = hier.Parent(user); !ok {
				return nil, fmt.Errorf(InvalidSearchUser)
			}

			userIdx = hier.ChildIdx(peekScope.Node, user)
		}

		if userIdx == -1 {
			return nil, fmt.Errorf(InvalidSearchUser)
		}

		children := hier.Children(peekScope.Node)
		for childIdx, child := range children {
			if s.nodeDefines(child, name) {
				if s.isPositionalDecl(child) && childIdx > userIdx {
					return nil, fmt.Errorf(UseBeforeDeclared, originalUser, child)
				} else if s.isPositionalDecl(child) && leftFunction != nil {
					return nil, fmt.Errorf(OutOfScope, child, leftFunction)
				}

				return child, nil
			}
		}

		if fn, isFunction := peekScope.Node.(*ast.FunctionStmt); isFunction {
			leftFunction = fn
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

package analysis

import (
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

// TypeInfo holds type information for the entirety of a program.
type TypeInfo struct {
	GlobalScope *Scope

	// Types is a map of nodes to the types they are representative of.
	// Not all nodes will have types.
	Types map[ast.Node]types.Type

	// Scopes is a map of nodes to the Scope that was created for them.
	// Not all nodes will have scopes.
	Scopes map[ast.Node]*Scope
}

func (i *TypeInfo) Resolve() error {
	return i.GlobalScope.Resolve(i)
}

// NewTypeInfo creates a new instance of TypeInfo given a global scope.
// The global scope is automatically added to the Scopes map.
func NewTypeInfo(globalScope *Scope) *TypeInfo {
	ti := &TypeInfo{
		GlobalScope: globalScope,

		Types:  make(map[ast.Node]types.Type),
		Scopes: make(map[ast.Node]*Scope),
	}

	ti.Scopes[globalScope.Node] = globalScope

	return ti
}

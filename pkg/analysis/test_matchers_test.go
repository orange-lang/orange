package analysis

import (
	"fmt"

	. "github.com/onsi/gomega"

	types2 "github.com/onsi/gomega/types"
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

func ExpectTypesToMatch(actual types.Type, expected types.Type) {
	equal := actual.Equals(expected, false)
	ExpectWithOffset(1, equal).To(BeTrue())
}

type flagMatcher struct{ expected types.Flag }

func (m flagMatcher) Match(actual interface{}) (success bool, err error) {
	if actual, ok := actual.(types.Type); ok {
		return actual.GetFlag(m.expected), nil
	}

	return false, fmt.Errorf("provided object was not an types.Type")
}

func (m flagMatcher) FailureMessage(actual interface{}) (message string) {
	return fmt.Sprintf("Expected\n\t%v\nto equal\n\t%v", actual, m.expected)
}

func (m flagMatcher) NegatedFailureMessage(actual interface{}) (message string) {
	return fmt.Sprintf("Expected\n\t%v\nnot to equal\n\t%v", actual, m.expected)
}

func HaveFlag(expected types.Flag) types2.GomegaMatcher {
	return &flagMatcher{expected}
}

func resolveType(node ast.Node) (types.Type, error) {
	scope := NewScope(node)
	ti := NewTypeInfo(scope)

	if err := ti.Resolve(); err != nil {
		return nil, err
	}

	return ti.Types[node], nil
}

func resolveForType(block ast.Node, node ast.Node) (types.Type, error) {
	scope := NewScope(block)
	ti := NewTypeInfo(scope)

	if err := ti.Resolve(); err != nil {
		return nil, err
	}

	return ti.Types[node], nil
}

func resolve(node ast.Node) (*TypeInfo, error) {
	scope := NewScope(node)
	ti := NewTypeInfo(scope)

	if err := ti.Resolve(); err != nil {
		return nil, err
	}

	return ti, nil
}

func makeLvalue(ty types.Type) types.Type {
	ty.SetFlag(types.FlagLValue)
	return ty
}

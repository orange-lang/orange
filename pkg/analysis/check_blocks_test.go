package analysis

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
)

var _ = Describe("Type Detection", func() {
	Describe("BlockStmt", func() {
		It("must visit nodes", func() {
			mocks := []ast.Node{
				&mockNode{},
				&mockNode{},
				&mockNode{},
			}

			block := &ast.BlockStmt{Nodes: mocks}

			scope := NewScope(block)
			Expect(NewTypeInfo(scope).Resolve()).To(BeNil())
			Expect(len(scope.Children)).To(Equal(0))

			for _, node := range mocks {
				mock := node.(*mockNode)
				Expect(mock.visited).To(BeTrue())
			}
		})

		It("must create a scope for children", func() {
			block := &ast.BlockStmt{Nodes: []ast.Node{
				&ast.BlockStmt{},
			}}

			scope := NewScope(block)
			Expect(NewTypeInfo(scope).Resolve()).To(BeNil())
			Expect(len(scope.Children)).To(Equal(1))
		})
	})
})

package analysis

import (
	"fmt"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"

	"github.com/orange-lang/orange/pkg/ast"
)

var _ = Describe("Scope", func() {
	It("should be able to find variables", func() {
		decl := &ast.VarDecl{Name: "foobar"}
		searcher := &mockNode{}

		block := &ast.BlockStmt{Nodes: []ast.Node{
			decl,
			searcher,
		}}

		scope := NewScope(block)
		hier := ast.NewHierarchy(block)

		foundDecl, err := scope.FindDecl(hier, "foobar", searcher)
		Expect(foundDecl).NotTo(BeNil())
		Expect(err).To(BeNil())
		Expect(foundDecl).To(Equal(decl))
	})

	It("should not be able to find variables that don't exist", func() {
		searcher := &mockNode{}

		block := &ast.BlockStmt{Nodes: []ast.Node{searcher}}

		scope := NewScope(block)
		hier := ast.NewHierarchy(block)

		foundDecl, err := scope.FindDecl(hier, "foobar", searcher)
		Expect(foundDecl).To(BeNil())
		Expect(err).To(BeNil())
	})

	It("should not be able to find variables before they're declared", func() {
		decl := &ast.VarDecl{Name: "foobar"}
		searcher := &mockNode{}

		block := &ast.BlockStmt{Nodes: []ast.Node{
			searcher,
			decl,
		}}

		scope := NewScope(block)
		hier := ast.NewHierarchy(block)

		foundDecl, err := scope.FindDecl(hier, "foobar", searcher)
		Expect(foundDecl).To(BeNil())
		Expect(err).To(Equal(fmt.Errorf(UseBeforeDeclared, searcher, decl)))
	})

	It("should be able to find variables in nested scopes", func() {
		decl := &ast.VarDecl{Name: "foobar"}
		searcher := &mockNode{}

		innerBlock := &ast.BlockStmt{Nodes: []ast.Node{
			searcher,
		}}

		outerBlock := &ast.BlockStmt{Nodes: []ast.Node{
			decl,
			innerBlock,
		}}

		outerScope := NewScope(outerBlock)
		innerScope := NewScope(innerBlock)
		outerScope.AddScope(innerScope)

		hier := ast.NewHierarchy(outerBlock)

		foundDecl, err := innerScope.FindDecl(hier, "foobar", searcher)
		Expect(foundDecl).NotTo(BeNil())
		Expect(err).To(BeNil())
		Expect(foundDecl).To(Equal(decl))
	})

	It("should not be able to find variables in nested scopes before they're declared", func() {
		decl := &ast.VarDecl{Name: "foobar"}
		searcher := &mockNode{}

		innerBlock := &ast.BlockStmt{Nodes: []ast.Node{
			searcher,
		}}

		outerBlock := &ast.BlockStmt{Nodes: []ast.Node{
			innerBlock,
			decl,
		}}

		outerScope := NewScope(outerBlock)
		innerScope := NewScope(innerBlock)
		outerScope.AddScope(innerScope)

		hier := ast.NewHierarchy(outerBlock)

		foundDecl, err := innerScope.FindDecl(hier, "foobar", searcher)
		Expect(foundDecl).To(BeNil())
		Expect(err).To(Equal(fmt.Errorf(UseBeforeDeclared, searcher, decl)))
	})
})

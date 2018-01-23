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

	It("should be able to find global variables outside of a function", func() {
		decl := &ast.VarDecl{Name: "foobar", Static: true}

		searcher := &mockNode{}

		innerFunction := &ast.FunctionStmt{
			Name: "fun_inner",
			Body: &ast.BlockStmt{Nodes: []ast.Node{searcher}},
		}

		outerBlock := &ast.BlockStmt{Nodes: []ast.Node{decl, innerFunction}}

		scopes := map[string]*Scope{
			"global":   NewScope(outerBlock),
			"function": NewScope(innerFunction),
			"fun_body": NewScope(innerFunction.Body),
		}

		scopes["global"].AddScope(scopes["function"])
		scopes["function"].AddScope(scopes["fun_body"])

		hier := ast.NewHierarchy(outerBlock)

		foundDecl, err := scopes["fun_body"].FindDecl(hier, "foobar", searcher)
		Expect(err).To(BeNil())
		Expect(foundDecl).To(Equal(decl))
	})

	It("should not be able to find variables outside of a nested function", func() {
		decl := &ast.VarDecl{Name: "foobar"}
		searcher := &mockNode{}

		innerFunction := &ast.FunctionStmt{
			Name: "fun_inner",
			Body: &ast.BlockStmt{Nodes: []ast.Node{searcher}},
		}

		outerFunction := &ast.FunctionStmt{
			Name: "fun_outer",
			Body: &ast.BlockStmt{Nodes: []ast.Node{decl, innerFunction}},
		}

		scopes := map[string]*Scope{
			"outer_fun":      NewScope(outerFunction),
			"outer_fun_body": NewScope(outerFunction.Body),
			"inner_fun":      NewScope(innerFunction),
			"inner_fun_body": NewScope(innerFunction.Body),
		}

		scopes["outer_fun"].AddScope(scopes["outer_fun_body"])
		scopes["outer_fun_body"].AddScope(scopes["inner_fun"])
		scopes["inner_fun"].AddScope(scopes["inner_fun_body"])

		hier := ast.NewHierarchy(outerFunction)

		_, err := scopes["inner_fun_body"].FindDecl(hier, "foobar", searcher)
		Expect(err).To(Equal(fmt.Errorf(OutOfScope, decl, innerFunction)))
	})
})

package test

import (
	"github.com/orange-lang/orange/ast"
	"github.com/orange-lang/orange/parse"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
	"github.com/orange-lang/orange/parse/lexer"

	"testing"
)

func TestParser(t *testing.T) {
	RegisterFailHandler(Fail)
	RunSpecs(t, "Parser Suite")
}

func expectNodes(input string, expect []ast.Node) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	p, errs := parse.Parse(&l)

	Expect(errs).To(Equal([]error{}))

	Expect(p.Nodes).To(Equal(expect))
}

func expectNode(input string, expect ast.Node) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	p, errs := parse.Parse(&l)

	Expect(errs).To(Equal([]error{}))

	Expect(len(p.Nodes)).To(BeNumerically(">", 0))
	Expect(p.Nodes[0]).To(Equal(expect))
}

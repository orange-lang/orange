package test

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/ast"
)

var _ = DescribeTable("Parsing classes", expectNode,
	//
	// Empty classes
	//

	Entry("empty class same line body", "class TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("empty class } new line", `class TestClass { 

	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("empty class { new line", `class TestClass 
	{ 

	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Generics
	//

	Entry("one generic", "class<T> TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple generics", "class<T,V,U> TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		GenericTypes: []ast.Type{
			&ast.NamedType{Name: "T"},
			&ast.NamedType{Name: "V"},
			&ast.NamedType{Name: "U"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	Entry("one super", "class TestClass : Super1 { }", &ast.ClassDecl{
		Name: "TestClass",
		Supers: []ast.Type{
			&ast.NamedType{Name: "Super1"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	Entry("multiple supers", "class TestClass : Super1, Super2, Super3 { }", &ast.ClassDecl{
		Name: "TestClass",
		Supers: []ast.Type{
			&ast.NamedType{Name: "Super1"},
			&ast.NamedType{Name: "Super2"},
			&ast.NamedType{Name: "Super3"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Members
	//

	Entry("single class member", `class TestClass {
		var a: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &ast.BoolType{}},
		}},
	}),

	Entry("const class member", `class TestClass {
		const var a: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &ast.ConstType{
				InnerType: &ast.BoolType{},
			}},
		}},
	}),

	Entry("multiple class members", `class TestClass {
		var a: bool
		var b: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &ast.BoolType{}},
			&ast.MemberDecl{Name: "b", Type: &ast.BoolType{}},
		}},
	}),

	Entry("multiple class members w/ semicolons", `class TestClass {
		var a: bool; var b: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &ast.BoolType{}},
			&ast.MemberDecl{Name: "b", Type: &ast.BoolType{}},
		}},
	}),

	//
	// Properties
	//

	Entry("property with getter", `class TestClass {
		property Prop -> bool {
			get { true; }
		}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.PropertyDecl{
				Name: "Prop",
				Type: &ast.BoolType{},
				Getter: &ast.GetterStmt{
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
			},
		}},
	}),

	Entry("property with getter and setter", `class TestClass {
		property Prop -> bool {
			get { true; }
			set(value: bool) { true; }
		}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.PropertyDecl{
				Name: "Prop",
				Type: &ast.BoolType{},
				Getter: &ast.GetterStmt{
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
				Setter: &ast.SetterStmt{
					SetterVariable: &ast.ParamDecl{Name: "value", Type: &ast.BoolType{}},
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
			},
		}},
	}),

	Entry("property with implicit type", `class TestClass {
		property Prop {
			get { true; }
			set(value: bool) { true; }
		}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.PropertyDecl{
				Name: "Prop",
				Getter: &ast.GetterStmt{
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
				Setter: &ast.SetterStmt{
					SetterVariable: &ast.ParamDecl{Name: "value", Type: &ast.BoolType{}},
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
			},
		}},
	}),

	//
	// Methods
	//

	Entry("method", `class TestClass {
		def foo() {}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
				Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			},
		}},
	}),

	Entry("this in method", `class TestClass {
		def foo() { return this; }
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				Name:       "foo",
				Parameters: []*ast.ParamDecl{},
				Body: &ast.BlockStmt{Nodes: []ast.Node{
					&ast.ReturnStmt{Value: &ast.ThisExpr{}},
				}},
			},
		}},
	}),

	//
	// Destructors
	//

	Entry("destructor", `class TestClass {
		def ~TestClass() {}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.FunctionStmt{
				Name:       "TestClass",
				Destructor: true,
				Parameters: []*ast.ParamDecl{},
				Body:       &ast.BlockStmt{Nodes: []ast.Node{}},
			},
		}},
	}),
)

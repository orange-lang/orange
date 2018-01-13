package parse

import (
	. "github.com/onsi/ginkgo/extensions/table"
	"github.com/orange-lang/orange/pkg/ast"
	"github.com/orange-lang/orange/pkg/types"
)

var _ = DescribeTable("Parsing classes", expectNode,
	//
	// Empty classes
	//

	CEntry("class TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`class TestClass {

	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry(`class TestClass
	{

	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Generics
	//

	CEntry("class<T> TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("class<T,V,U> TestClass { }", &ast.ClassDecl{
		Name: "TestClass",
		GenericTypes: []types.Type{
			&types.Named{Name: "T"},
			&types.Named{Name: "V"},
			&types.Named{Name: "U"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Supers
	//

	CEntry("class TestClass : Super1 { }", &ast.ClassDecl{
		Name: "TestClass",
		Supers: []types.Type{
			&types.Named{Name: "Super1"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	CEntry("class TestClass : Super1, Super2, Super3 { }", &ast.ClassDecl{
		Name: "TestClass",
		Supers: []types.Type{
			&types.Named{Name: "Super1"},
			&types.Named{Name: "Super2"},
			&types.Named{Name: "Super3"},
		},
		Body: &ast.BlockStmt{Nodes: []ast.Node{}},
	}),

	//
	// Members
	//

	CEntry(`class TestClass {
		var a: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &types.Bool{}},
		}},
	}),

	CEntry(`class TestClass {
		const var a: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &types.Bool{
				Base: types.MakeBase(types.FlagConst),
			}},
		}},
	}),

	CEntry(`class TestClass {
		var a: bool
		var b: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &types.Bool{}},
			&ast.MemberDecl{Name: "b", Type: &types.Bool{}},
		}},
	}),

	CEntry(`class TestClass {
		var a: bool; var b: bool
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.MemberDecl{Name: "a", Type: &types.Bool{}},
			&ast.MemberDecl{Name: "b", Type: &types.Bool{}},
		}},
	}),

	//
	// Properties
	//

	CEntry(`class TestClass {
		property Prop -> bool {
			get { true; }
		}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.PropertyDecl{
				Name: "Prop",
				Type: &types.Bool{},
				Getter: &ast.GetterStmt{
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
			},
		}},
	}),

	CEntry(`class TestClass {
		property Prop -> bool {
			get { true; }
			set(value: bool) { true; }
		}
	}`, &ast.ClassDecl{
		Name: "TestClass",
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.PropertyDecl{
				Name: "Prop",
				Type: &types.Bool{},
				Getter: &ast.GetterStmt{
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
				Setter: &ast.SetterStmt{
					SetterVariable: &ast.ParamDecl{Name: "value", Type: &types.Bool{}},
					Body: &ast.BlockStmt{Nodes: []ast.Node{
						&ast.BoolExpr{Value: true},
					}},
				},
			},
		}},
	}),

	CEntry(`class TestClass {
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
					SetterVariable: &ast.ParamDecl{Name: "value", Type: &types.Bool{}},
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

	CEntry(`class TestClass {
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

	CEntry(`class TestClass {
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

	CEntry(`class TestClass {
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

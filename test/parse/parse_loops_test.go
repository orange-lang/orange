package test

import (
	. "github.com/onsi/ginkgo/extensions/table"

	"github.com/orange-lang/orange/ast"
)

var _ = DescribeTable("should be able to handle loops", expectNode,
	CEntry("for(;;){5}", &ast.LoopStmt{
		CheckTime: ast.CheckBefore,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),

	CEntry("for(var i=0;;){5}", &ast.LoopStmt{
		Initializer: &ast.VarDecl{Name: "i", Value: &ast.IntExpr{Value: 0, Size: 64}},
		CheckTime:   ast.CheckBefore,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),

	CEntry("for(var i=0;i<5;){5}", &ast.LoopStmt{
		Initializer: &ast.VarDecl{Name: "i", Value: &ast.IntExpr{Value: 0, Size: 64}},
		Condition: &ast.BinaryExpr{
			LHS:       &ast.NamedIDExpr{Name: "i"},
			Operation: "<",
			RHS:       &ast.IntExpr{Value: 5, Size: 64},
		},
		CheckTime: ast.CheckBefore,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),

	CEntry("for(var i =0;i<5;i++){5}", &ast.LoopStmt{
		Initializer: &ast.VarDecl{Name: "i", Value: &ast.IntExpr{Value: 0, Size: 64}},
		Condition: &ast.BinaryExpr{
			LHS:       &ast.NamedIDExpr{Name: "i"},
			Operation: "<",
			RHS:       &ast.IntExpr{Value: 5, Size: 64},
		},
		Afterthought: &ast.UnaryExpr{
			Operand:   &ast.NamedIDExpr{Name: "i"},
			Operation: "++",
			Order:     ast.PostfixOrder,
		},
		CheckTime: ast.CheckBefore,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),

	CEntry("while(true){5}", &ast.LoopStmt{
		Condition: &ast.BoolExpr{Value: true},
		CheckTime: ast.CheckBefore,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),

	CEntry("do{5}while(true)", &ast.LoopStmt{
		Condition: &ast.BoolExpr{Value: true},
		CheckTime: ast.CheckAfter,
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 5, Size: 64},
		}},
	}),
)

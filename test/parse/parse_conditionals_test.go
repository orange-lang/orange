package test

import (
	. "github.com/onsi/ginkgo/extensions/table"

	"github.com/orange-lang/orange/ast"
)

var _ = DescribeTable("Parsing conditionals", expectNode,
	CEntry(`if (5) {
			1
			2
		}`, &ast.IfStmt{
		Condition: &ast.IntExpr{Value: 5, Size: 64},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 1, Size: 64},
			&ast.IntExpr{Value: 2, Size: 64},
		}},
	}),

	CEntry(`if (5) {
			1
			2
		} elif (6) {
			3
			4
	  } elif (7) {
		  5
			6	
		}`, &ast.IfStmt{
		Condition: &ast.IntExpr{Value: 5, Size: 64},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 1, Size: 64},
			&ast.IntExpr{Value: 2, Size: 64},
		}},
		Else: &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 6, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 3, Size: 64},
				&ast.IntExpr{Value: 4, Size: 64},
			}},
			Else: &ast.IfStmt{
				Condition: &ast.IntExpr{Value: 7, Size: 64},
				Body: &ast.BlockStmt{Nodes: []ast.Node{
					&ast.IntExpr{Value: 5, Size: 64},
					&ast.IntExpr{Value: 6, Size: 64},
				}},
			},
		},
	}),

	CEntry(`if (5) {
			1
		} elif (6) {
			2
	  } else {
		  3
		}`, &ast.IfStmt{
		Condition: &ast.IntExpr{Value: 5, Size: 64},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 1, Size: 64},
		}},
		Else: &ast.IfStmt{
			Condition: &ast.IntExpr{Value: 6, Size: 64},
			Body: &ast.BlockStmt{Nodes: []ast.Node{
				&ast.IntExpr{Value: 2, Size: 64},
			}},
			Else: &ast.BlockStmt{
				Nodes: []ast.Node{&ast.IntExpr{Value: 3, Size: 64}},
			},
		},
	}),

	CEntry(`if (5) {
			1
		} else {
		  2
		}`, &ast.IfStmt{
		Condition: &ast.IntExpr{Value: 5, Size: 64},
		Body: &ast.BlockStmt{Nodes: []ast.Node{
			&ast.IntExpr{Value: 1, Size: 64},
		}},
		Else: &ast.BlockStmt{
			Nodes: []ast.Node{&ast.IntExpr{Value: 2, Size: 64}},
		},
	}),
)

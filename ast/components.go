package ast

type componentVisitor struct {
	DefaultNodeVisitor
	components []Node
}

func (v *componentVisitor) AddComponents(nodes ...Node) {
	if nodes == nil {
		return
	}

	for _, node := range nodes {
		if node == nil {
			continue
		}

		v.components = append(v.components, node)
	}
}

func (v *componentVisitor) VisitBlockStmt(node *BlockStmt) {
	v.AddComponents(node.Nodes...)
}

func (v *componentVisitor) VisitClassDecl(node *ClassDecl) {
	v.AddComponents(node.Body)
}

func (v *componentVisitor) VisitVarDecl(node *VarDecl) {
	v.AddComponents(node.Value)
}

func (v *componentVisitor) VisitMemberDecl(node *MemberDecl) {
	v.AddComponents(node.Value)
}

func (v *componentVisitor) VisitGetterStmt(node *GetterStmt) {
	v.AddComponents(node.Body)
}

func (v *componentVisitor) VisitSetterStmt(node *SetterStmt) {
	v.AddComponents(node.SetterVariable, node.Body)
}

func (v *componentVisitor) VisitIfStmt(node *IfStmt) {
	v.AddComponents(node.Condition, node.Body, node.Else)
}

func (v *componentVisitor) VisitConstIfStmt(node *ConstIfStmt) {
	v.AddComponents(node.Condition, node.Body, node.Else)
}

func (v *componentVisitor) VisitLoopStmt(node *LoopStmt) {
	v.AddComponents(
		node.Initializer,
		node.Condition,
		node.Afterthought,
		node.Body,
	)
}

func (v *componentVisitor) VisitPropertyDecl(node *PropertyDecl) {
	v.AddComponents(node.Getter, node.Setter)
}

func (v *componentVisitor) VisitExtensionDecl(node *ExtensionDecl) {
	v.AddComponents(node.Body)
}

func (v *componentVisitor) VisitInterfaceDecl(node *InterfaceDecl) {
	v.AddComponents(node.Body)
}

func (v *componentVisitor) VisitTryStmt(node *TryStmt) {
	v.AddComponents(node.Body)

	if node.Catch != nil {
		for _, element := range node.Catch {
			v.AddComponents(element)
		}
	}

	v.AddComponents(node.Finally)
}

func (v *componentVisitor) VisitCatchStmt(node *CatchStmt) {
	v.AddComponents(node.Variable, node.Body)
}

func (v *componentVisitor) VisitFunctionStmt(node *FunctionStmt) {
	if node.Parameters != nil {
		for _, element := range node.Parameters {
			v.AddComponents(element)
		}
	}

	v.AddComponents(node.Body)
}

func (v *componentVisitor) VisitExternFuncStmt(node *ExternFuncStmt) {
	if node.Parameters != nil {
		for _, element := range node.Parameters {
			v.AddComponents(element)
		}
	}
}

func (v *componentVisitor) VisitReturnStmt(node *ReturnStmt) {
	v.AddComponents(node.Value)
}

func (v *componentVisitor) VisitArrayExpr(node *ArrayExpr) {
	if node.Members != nil {
		for _, element := range node.Members {
			v.AddComponents(element)
		}
	}
}

func (v *componentVisitor) VisitUnaryExpr(node *UnaryExpr) {
	v.AddComponents(node.Operand)
}

func (v *componentVisitor) VisitBinaryExpr(node *BinaryExpr) {
	v.AddComponents(node.LHS, node.RHS)
}

func (v *componentVisitor) VisitCallExpr(node *CallExpr) {
	v.AddComponents(node.Object)

	if node.Arguments != nil {
		for _, element := range node.Arguments {
			v.AddComponents(element)
		}
	}
}

func (v *componentVisitor) VisitArrayAccessExpr(node *ArrayAccessExpr) {
	v.AddComponents(node.Object, node.Index)
}

func (v *componentVisitor) VisitMemberAccessExpr(node *MemberAccessExpr) {
	v.AddComponents(node.Object)
}

func (v *componentVisitor) VisitGenericInst(node *GenericInst) {
	v.AddComponents(node.Object)
}

func GetComponents(node Node) []Node {
	visitor := &componentVisitor{}
	visitor.components = []Node{}

	node.Accept(visitor)

	return visitor.components
}

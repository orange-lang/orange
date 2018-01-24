package ast

// Hierarchy provides helper methods to access a children's parent node and
// some node's children nodes.
type Hierarchy struct {
	root     Node
	visitor  NodeVisitor
	parents  map[Node]Node
	children map[Node][]Node
}

func (h *Hierarchy) Root() Node {
	return h.root
}

// Parent finds the parent node of some child node.
// Rewalks the root node of the hierarchy if there was no parent
// previously found. Returns the parent (if any) and a boolean
// indicating whether or not the tree was successfully walked.
func (h *Hierarchy) Parent(node Node) (Node, bool) {
	if parent, ok := h.parents[node]; ok {
		return parent, true
	}

	// Rewalk the root node in case this node is new to the AST
	h.root.Accept(h.visitor)

	if parent, ok := h.parents[node]; ok {
		return parent, true
	}

	return nil, false
}

// Siblings gets all the direct siblings of a specific node, not
// including the node itself.
func (h *Hierarchy) Siblings(node Node) []Node {
	var siblings []Node
	var parent Node

	if parent, _ = h.Parent(node); parent == nil {
		return siblings
	}

	for _, child := range h.Children(parent) {
		if child == node {
			continue
		}

		siblings = append(siblings, child)
	}

	return siblings
}

// Children gets all the direct children nodes of a certain node.
// Rewalks the root node of the hierarchy if the children could not
// be found, then returns nil if the node could not be walked.
func (h *Hierarchy) Children(node Node) []Node {
	if children, ok := h.children[node]; ok {
		return children
	}

	// Rewalk the node in case it's a new node and needs to be cached
	node.Accept(h.visitor)
	return h.children[node]
}

func (h *Hierarchy) ChildIdx(parent Node, child Node) int {
	children := h.Children(parent)
	for i, node := range children {
		if node == child {
			return i
		}
	}

	return -1
}

func NewHierarchy(root Node) *Hierarchy {
	hier := &Hierarchy{
		root:     root,
		parents:  make(map[Node]Node),
		children: make(map[Node][]Node),
	}

	hier.visitor = &hierarchyVisitor{hier}

	hier.root.Accept(hier.visitor)
	return hier
}

type hierarchyVisitor struct {
	hierarchy *Hierarchy
}

func (v *hierarchyVisitor) setParent(parent Node, child Node) {
	v.hierarchy.parents[child] = parent
}

func (v *hierarchyVisitor) setChildren(parent Node, children []Node) {
	for _, child := range children {
		child.Accept(v)
		v.setParent(parent, child)
	}

	v.hierarchy.children[parent] = children
}

func (v *hierarchyVisitor) noChildren(parent Node) {
	v.setChildren(parent, []Node{})
}

func (v *hierarchyVisitor) VisitBlockStmt(node *BlockStmt) {
	children := []Node{}

	for _, child := range node.Nodes {
		children = append(children, child)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitAliasDecl(node *AliasDecl) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitClassDecl(node *ClassDecl) {
	v.setChildren(node, []Node{node.Body})
}

func (v *hierarchyVisitor) VisitVarDecl(node *VarDecl) {
	children := []Node{}

	if node.Value != nil {
		children = append(children, node.Value)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitParamDecl(node *ParamDecl) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitMemberDecl(node *MemberDecl) {
	children := []Node{}

	if node.Value != nil {
		children = append(children, node.Value)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitGetterStmt(node *GetterStmt) {
	v.setChildren(node, []Node{node.Body})
}

func (v *hierarchyVisitor) VisitSetterStmt(node *SetterStmt) {
	v.setChildren(node, []Node{
		node.SetterVariable,
		node.Body,
	})
}

func (v *hierarchyVisitor) VisitIfStmt(node *IfStmt) {
	children := []Node{
		node.Condition,
		node.Body,
	}

	if node.Else != nil {
		children = append(children, node.Else)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitConstIfStmt(node *ConstIfStmt) {
	children := []Node{
		node.Condition,
		node.Body,
	}

	if node.Else != nil {
		children = append(children, node.Else)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitLoopStmt(node *LoopStmt) {
	children := []Node{}

	if node.Initializer != nil {
		children = append(children, node.Initializer)
	}

	if node.Condition != nil {
		children = append(children, node.Condition)
	}

	if node.Afterthought != nil {
		children = append(children, node.Afterthought)
	}

	children = append(children, node.Body)
	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitPropertyDecl(node *PropertyDecl) {
	children := []Node{}

	if node.Getter != nil {
		children = append(children, node.Getter)
	}

	if node.Setter != nil {
		children = append(children, node.Setter)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitEnumDecl(node *EnumDecl) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitExtensionDecl(node *ExtensionDecl) {
	v.setChildren(node, []Node{
		node.Body,
	})
}

func (v *hierarchyVisitor) VisitInterfaceDecl(node *InterfaceDecl) {
	v.setChildren(node, []Node{
		node.Body,
	})
}

func (v *hierarchyVisitor) VisitPackageDecl(node *PackageDecl) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitImportDecl(node *ImportDecl) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitTryStmt(node *TryStmt) {
	children := []Node{node.Body}

	for _, catchStmt := range node.Catch {
		children = append(children, catchStmt)
	}

	if node.Finally != nil {
		children = append(children, node.Finally)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitCatchStmt(node *CatchStmt) {
	v.setChildren(node, []Node{
		node.Variable,
		node.Body,
	})
}

func (v *hierarchyVisitor) VisitFunctionStmt(node *FunctionStmt) {
	children := []Node{}

	for _, child := range node.Parameters {
		children = append(children, child)
	}

	children = append(children, node.Body)
	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitExternFuncStmt(node *ExternFuncStmt) {
	children := []Node{}

	for _, child := range node.Parameters {
		children = append(children, child)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitReturnStmt(node *ReturnStmt) {
	children := []Node{}

	if node.Value != nil {
		children = append(children, node.Value)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitArrayExpr(node *ArrayExpr) {
	children := []Node{}

	for _, child := range node.Members {
		children = append(children, child)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitUnaryExpr(node *UnaryExpr) {
	v.setChildren(node, []Node{node.Operand})
}

func (v *hierarchyVisitor) VisitBinaryExpr(node *BinaryExpr) {
	v.setChildren(node, []Node{node.LHS, node.RHS})
}

func (v *hierarchyVisitor) VisitCallExpr(node *CallExpr) {
	children := []Node{node.Object}

	for _, arg := range node.Arguments {
		children = append(children, arg)
	}

	v.setChildren(node, children)
}

func (v *hierarchyVisitor) VisitArrayAccessExpr(node *ArrayAccessExpr) {
	v.setChildren(node, []Node{node.Object, node.Index})
}

func (v *hierarchyVisitor) VisitMemberAccessExpr(node *MemberAccessExpr) {
	v.setChildren(node, []Node{node.Object})
}

func (v *hierarchyVisitor) VisitGenericInst(node *GenericInst) {
	v.setChildren(node, []Node{node.Object})
}

func (v *hierarchyVisitor) VisitThisExpr(node *ThisExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitSuperExpr(node *SuperExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitStringExpr(node *StringExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitBoolExpr(node *BoolExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitCharExpr(node *CharExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitIntExpr(node *IntExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitUIntExpr(node *UIntExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitDoubleExpr(node *DoubleExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitFloatExpr(node *FloatExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitNamedIDExpr(node *NamedIDExpr) {
	v.noChildren(node)
}

func (v *hierarchyVisitor) VisitIDAccessExpr(node *IDAccessExpr) {
	v.setChildren(node, []Node{node.LHS})
}

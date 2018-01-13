package ast

type NodeVisitor interface {
	VisitBlockStmt(node *BlockStmt)
	VisitAliasDecl(node *AliasDecl)
	VisitClassDecl(node *ClassDecl)
	VisitVarDecl(node *VarDecl)
	VisitParamDecl(node *ParamDecl)
	VisitMemberDecl(node *MemberDecl)
	VisitGetterStmt(node *GetterStmt)
	VisitSetterStmt(node *SetterStmt)
	VisitIfStmt(node *IfStmt)
	VisitConstIfStmt(node *ConstIfStmt)
	VisitLoopStmt(node *LoopStmt)
	VisitPropertyDecl(node *PropertyDecl)
	VisitEnumDecl(node *EnumDecl)
	VisitExtensionDecl(node *ExtensionDecl)
	VisitInterfaceDecl(node *InterfaceDecl)
	VisitPackageDecl(node *PackageDecl)
	VisitImportDecl(node *ImportDecl)
	VisitTryStmt(node *TryStmt)
	VisitCatchStmt(node *CatchStmt)
	VisitFunctionStmt(node *FunctionStmt)
	VisitExternFuncStmt(node *ExternFuncStmt)
	VisitReturnStmt(node *ReturnStmt)
	VisitArrayExpr(node *ArrayExpr)
	VisitUnaryExpr(node *UnaryExpr)
	VisitBinaryExpr(node *BinaryExpr)
	VisitCallExpr(node *CallExpr)
	VisitArrayAccessExpr(node *ArrayAccessExpr)
	VisitMemberAccessExpr(node *MemberAccessExpr)
	VisitGenericInst(node *GenericInst)
	VisitThisExpr(node *ThisExpr)
	VisitSuperExpr(node *SuperExpr)
	VisitStringExpr(node *StringExpr)
	VisitBoolExpr(node *BoolExpr)
	VisitCharExpr(node *CharExpr)
	VisitIntExpr(node *IntExpr)
	VisitUIntExpr(node *UIntExpr)
	VisitDoubleExpr(node *DoubleExpr)
	VisitFloatExpr(node *FloatExpr)
	VisitNamedIDExpr(node *NamedIDExpr)
	VisitIDAccessExpr(node *IDAccessExpr)
}

func (s *BlockStmt) Accept(visitor NodeVisitor)        { visitor.VisitBlockStmt(s) }
func (s *AliasDecl) Accept(visitor NodeVisitor)        { visitor.VisitAliasDecl(s) }
func (s *ClassDecl) Accept(visitor NodeVisitor)        { visitor.VisitClassDecl(s) }
func (s *VarDecl) Accept(visitor NodeVisitor)          { visitor.VisitVarDecl(s) }
func (s *ParamDecl) Accept(visitor NodeVisitor)        { visitor.VisitParamDecl(s) }
func (s *MemberDecl) Accept(visitor NodeVisitor)       { visitor.VisitMemberDecl(s) }
func (s *GetterStmt) Accept(visitor NodeVisitor)       { visitor.VisitGetterStmt(s) }
func (s *SetterStmt) Accept(visitor NodeVisitor)       { visitor.VisitSetterStmt(s) }
func (s *PropertyDecl) Accept(visitor NodeVisitor)     { visitor.VisitPropertyDecl(s) }
func (s *EnumDecl) Accept(visitor NodeVisitor)         { visitor.VisitEnumDecl(s) }
func (s *ExtensionDecl) Accept(visitor NodeVisitor)    { visitor.VisitExtensionDecl(s) }
func (s *InterfaceDecl) Accept(visitor NodeVisitor)    { visitor.VisitInterfaceDecl(s) }
func (s *PackageDecl) Accept(visitor NodeVisitor)      { visitor.VisitPackageDecl(s) }
func (s *ImportDecl) Accept(visitor NodeVisitor)       { visitor.VisitImportDecl(s) }
func (s *IfStmt) Accept(visitor NodeVisitor)           { visitor.VisitIfStmt(s) }
func (s *ConstIfStmt) Accept(visitor NodeVisitor)      { visitor.VisitConstIfStmt(s) }
func (s *LoopStmt) Accept(visitor NodeVisitor)         { visitor.VisitLoopStmt(s) }
func (s *TryStmt) Accept(visitor NodeVisitor)          { visitor.VisitTryStmt(s) }
func (s *CatchStmt) Accept(visitor NodeVisitor)        { visitor.VisitCatchStmt(s) }
func (s *FunctionStmt) Accept(visitor NodeVisitor)     { visitor.VisitFunctionStmt(s) }
func (s *ExternFuncStmt) Accept(visitor NodeVisitor)   { visitor.VisitExternFuncStmt(s) }
func (s *ReturnStmt) Accept(visitor NodeVisitor)       { visitor.VisitReturnStmt(s) }
func (e *ArrayExpr) Accept(visitor NodeVisitor)        { visitor.VisitArrayExpr(e) }
func (e *UnaryExpr) Accept(visitor NodeVisitor)        { visitor.VisitUnaryExpr(e) }
func (e *BinaryExpr) Accept(visitor NodeVisitor)       { visitor.VisitBinaryExpr(e) }
func (e *CallExpr) Accept(visitor NodeVisitor)         { visitor.VisitCallExpr(e) }
func (e *ArrayAccessExpr) Accept(visitor NodeVisitor)  { visitor.VisitArrayAccessExpr(e) }
func (e *MemberAccessExpr) Accept(visitor NodeVisitor) { visitor.VisitMemberAccessExpr(e) }
func (e *GenericInst) Accept(visitor NodeVisitor)      { visitor.VisitGenericInst(e) }
func (e *StringExpr) Accept(visitor NodeVisitor)       { visitor.VisitStringExpr(e) }
func (e *BoolExpr) Accept(visitor NodeVisitor)         { visitor.VisitBoolExpr(e) }
func (e *CharExpr) Accept(visitor NodeVisitor)         { visitor.VisitCharExpr(e) }
func (e *IntExpr) Accept(visitor NodeVisitor)          { visitor.VisitIntExpr(e) }
func (e *UIntExpr) Accept(visitor NodeVisitor)         { visitor.VisitUIntExpr(e) }
func (e *DoubleExpr) Accept(visitor NodeVisitor)       { visitor.VisitDoubleExpr(e) }
func (e *FloatExpr) Accept(visitor NodeVisitor)        { visitor.VisitFloatExpr(e) }
func (e *ThisExpr) Accept(visitor NodeVisitor)         { visitor.VisitThisExpr(e) }
func (e *SuperExpr) Accept(visitor NodeVisitor)        { visitor.VisitSuperExpr(e) }
func (i *NamedIDExpr) Accept(visitor NodeVisitor)      { visitor.VisitNamedIDExpr(i) }
func (i *IDAccessExpr) Accept(visitor NodeVisitor)     { visitor.VisitIDAccessExpr(i) }

package ast

type DefaultNodeVisitor struct{}

func (DefaultNodeVisitor) VisitBlockStmt(node *BlockStmt)               {}
func (DefaultNodeVisitor) VisitAliasDecl(node *AliasDecl)               {}
func (DefaultNodeVisitor) VisitClassDecl(node *ClassDecl)               {}
func (DefaultNodeVisitor) VisitVarDecl(node *VarDecl)                   {}
func (DefaultNodeVisitor) VisitParamDecl(node *ParamDecl)               {}
func (DefaultNodeVisitor) VisitMemberDecl(node *MemberDecl)             {}
func (DefaultNodeVisitor) VisitGetterStmt(node *GetterStmt)             {}
func (DefaultNodeVisitor) VisitSetterStmt(node *SetterStmt)             {}
func (DefaultNodeVisitor) VisitIfStmt(node *IfStmt)                     {}
func (DefaultNodeVisitor) VisitConstIfStmt(node *ConstIfStmt)           {}
func (DefaultNodeVisitor) VisitLoopStmt(node *LoopStmt)                 {}
func (DefaultNodeVisitor) VisitPropertyDecl(node *PropertyDecl)         {}
func (DefaultNodeVisitor) VisitEnumDecl(node *EnumDecl)                 {}
func (DefaultNodeVisitor) VisitExtensionDecl(node *ExtensionDecl)       {}
func (DefaultNodeVisitor) VisitInterfaceDecl(node *InterfaceDecl)       {}
func (DefaultNodeVisitor) VisitPackageDecl(node *PackageDecl)           {}
func (DefaultNodeVisitor) VisitImportDecl(node *ImportDecl)             {}
func (DefaultNodeVisitor) VisitTryStmt(node *TryStmt)                   {}
func (DefaultNodeVisitor) VisitCatchStmt(node *CatchStmt)               {}
func (DefaultNodeVisitor) VisitFunctionStmt(node *FunctionStmt)         {}
func (DefaultNodeVisitor) VisitExternFuncStmt(node *ExternFuncStmt)     {}
func (DefaultNodeVisitor) VisitReturnStmt(node *ReturnStmt)             {}
func (DefaultNodeVisitor) VisitArrayExpr(node *ArrayExpr)               {}
func (DefaultNodeVisitor) VisitUnaryExpr(node *UnaryExpr)               {}
func (DefaultNodeVisitor) VisitBinaryExpr(node *BinaryExpr)             {}
func (DefaultNodeVisitor) VisitCallExpr(node *CallExpr)                 {}
func (DefaultNodeVisitor) VisitArrayAccessExpr(node *ArrayAccessExpr)   {}
func (DefaultNodeVisitor) VisitMemberAccessExpr(node *MemberAccessExpr) {}
func (DefaultNodeVisitor) VisitGenericInst(node *GenericInst)           {}
func (DefaultNodeVisitor) VisitThisExpr(node *ThisExpr)                 {}
func (DefaultNodeVisitor) VisitSuperExpr(node *SuperExpr)               {}
func (DefaultNodeVisitor) VisitStringExpr(node *StringExpr)             {}
func (DefaultNodeVisitor) VisitBoolExpr(node *BoolExpr)                 {}
func (DefaultNodeVisitor) VisitCharExpr(node *CharExpr)                 {}
func (DefaultNodeVisitor) VisitIntExpr(node *IntExpr)                   {}
func (DefaultNodeVisitor) VisitUIntExpr(node *UIntExpr)                 {}
func (DefaultNodeVisitor) VisitDoubleExpr(node *DoubleExpr)             {}
func (DefaultNodeVisitor) VisitFloatExpr(node *FloatExpr)               {}
func (DefaultNodeVisitor) VisitNamedIDExpr(node *NamedIDExpr)           {}
func (DefaultNodeVisitor) VisitIDAccessExpr(node *IDAccessExpr)         {}

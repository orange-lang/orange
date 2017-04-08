package ast

// AST represents one module of Orange code
type AST struct {
	Nodes []Node
}

type Node interface {
	isNode()
}

type Statement interface {
	Node
	isStatement()
}

type Expression interface {
	Node
	isExpression()
}

type Identifier interface {
	Expression
	isIdentifier()
}

//
// Statements
//

type BlockStmt struct {
	Nodes []Node
}

type AliasDecl struct {
	Name string
	Type Type
}

type ClassDecl struct {
	Name   string
	Supers []Identifier
	Body   *BlockStmt
}

type VarDecl struct {
	Name  string
	Type  Type
	Value Expression
}

type GetterStmt struct {
	Body *BlockStmt
}

type SetterStmt struct {
	SetterVariable *VarDecl
	Body           *BlockStmt
}

type IfStmt struct {
	Condition Expression
	Body      *BlockStmt
	Else      Node // either nil, IfStmt (elif), or BlockStmt (else)
}

type LoopStmt struct {
	Initializer  Expression
	Condition    Expression
	Afterthought Expression

	CheckTime LoopConditionTime
	Body      *BlockStmt
}

type PropertyDecl struct {
	Name   string
	Type   Type
	Getter *GetterStmt
	Setter *SetterStmt
}

type EnumDecl struct {
	Name    string
	Members []string
}

type ExtensionDecl struct {
	Name   string
	Supers []Identifier
	Body   *BlockStmt
}

type InterfaceDecl struct {
	Name   string
	Supers []Identifier
	Body   *BlockStmt
}

type PackageDecl struct {
	Name string
}

type ImportDecl struct {
	Name string
}

//
// Expressions
//

type FunctionExpr struct {
	Name       string
	Parameters []*VarDecl
	RetType    Type
	Body       *BlockStmt
}

type ExternFuncExpr struct {
	Name       string
	Parameters []*VarDecl
	RetType    Type
}

type ArrayExpr struct {
	Members []Expression
}

type UnaryExpr struct {
	Operation string
	Operand   Expression
	Order     UnaryOrder
}

type BinaryExpr struct {
	LHS       Expression
	Operation string
	RHS       Expression
}

type CallExpr struct {
	Object    Expression
	Arguments []Expression
}

type ArrayAccessExpr struct {
	Object Expression
	Index  Expression
}

type MemberAccessExpr struct {
	Object Expression
	Name   string
}

type StringExpr struct {
	Value string
}

type BoolExpr struct {
	Value bool
}

type CharExpr struct {
	Value byte
}

type IntExpr struct {
	Value int64
	Size  int
}

type UIntExpr struct {
	Value uint64
	Size  int
}

type DoubleExpr struct {
	Value float64
}

type FloatExpr struct {
	Value float32
}

//
// Identifiers
//

type NamedIDExpr struct {
	Name string
}

type IDAccessExpr struct {
	LHS Identifier
	RHS string
}

//
// Implement interfaces to enforce types
//

func (s BlockStmt) isNode()        {}
func (s AliasDecl) isNode()        {}
func (s ClassDecl) isNode()        {}
func (s VarDecl) isNode()          {}
func (s GetterStmt) isNode()       {}
func (s SetterStmt) isNode()       {}
func (s PropertyDecl) isNode()     {}
func (s EnumDecl) isNode()         {}
func (s ExtensionDecl) isNode()    {}
func (s InterfaceDecl) isNode()    {}
func (s PackageDecl) isNode()      {}
func (s ImportDecl) isNode()       {}
func (s IfStmt) isNode()           {}
func (s LoopStmt) isNode()         {}
func (e FunctionExpr) isNode()     {}
func (e ExternFuncExpr) isNode()   {}
func (e ArrayExpr) isNode()        {}
func (e UnaryExpr) isNode()        {}
func (e BinaryExpr) isNode()       {}
func (e CallExpr) isNode()         {}
func (e ArrayAccessExpr) isNode()  {}
func (e MemberAccessExpr) isNode() {}
func (e StringExpr) isNode()       {}
func (e BoolExpr) isNode()         {}
func (e CharExpr) isNode()         {}
func (e IntExpr) isNode()          {}
func (e UIntExpr) isNode()         {}
func (e DoubleExpr) isNode()       {}
func (e FloatExpr) isNode()        {}
func (i NamedIDExpr) isNode()      {}
func (i IDAccessExpr) isNode()     {}

func (s BlockStmt) isStatement()     {}
func (s AliasDecl) isStatement()     {}
func (s ClassDecl) isStatement()     {}
func (s VarDecl) isStatement()       {}
func (s GetterStmt) isStatement()    {}
func (s SetterStmt) isStatement()    {}
func (s PropertyDecl) isStatement()  {}
func (s EnumDecl) isStatement()      {}
func (s ExtensionDecl) isStatement() {}
func (s InterfaceDecl) isStatement() {}
func (s PackageDecl) isStatement()   {}
func (s ImportDecl) isStatement()    {}
func (s LoopStmt) isStatement()      {}
func (s IfStmt) isStatement()        {}

func (e FunctionExpr) isExpression()     {}
func (e ExternFuncExpr) isExpression()   {}
func (e ArrayExpr) isExpression()        {}
func (e UnaryExpr) isExpression()        {}
func (e BinaryExpr) isExpression()       {}
func (e CallExpr) isExpression()         {}
func (e ArrayAccessExpr) isExpression()  {}
func (e MemberAccessExpr) isExpression() {}
func (e StringExpr) isExpression()       {}
func (e BoolExpr) isExpression()         {}
func (e CharExpr) isExpression()         {}
func (e IntExpr) isExpression()          {}
func (e UIntExpr) isExpression()         {}
func (e DoubleExpr) isExpression()       {}
func (e FloatExpr) isExpression()        {}
func (i NamedIDExpr) isExpression()      {}
func (i IDAccessExpr) isExpression()     {}

func (i NamedIDExpr) isIdentifier()  {}
func (i IDAccessExpr) isIdentifier() {}

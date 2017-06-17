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

type PrivacyFlag interface {
	Statement
	SetPrivacyLevel(level PrivacyLevel)
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
	Name         string
	GenericTypes []Type
	Supers       []Type
	Body         *BlockStmt
	Privacy      PrivacyLevel
}

type VarDecl struct {
	Name  string
	Type  Type
	Value Expression
}

// ParamDecl is similar to VarDecl but is only found as a parameter to a function
// or method
type ParamDecl struct {
	Name string
	Type Type
}

// MemberDecl is similar to a VarDecl but is only found in the body of a class
// (i.e., is it a declaration of a class member)
type MemberDecl struct {
	Name    string
	Type    Type
	Value   Expression
	Privacy PrivacyLevel
}

type GetterStmt struct {
	Body *BlockStmt
}

type SetterStmt struct {
	SetterVariable *ParamDecl
	Body           *BlockStmt
}

type IfStmt struct {
	Condition Expression
	Body      *BlockStmt
	Else      Node // either nil, IfStmt (elif), or BlockStmt (else)
}

// ConstIfStmt represents an if statement evaluated on compile time
type ConstIfStmt struct {
	Condition Expression
	Body      *BlockStmt
	Else      Node // either nil, ConstIfStmt (elif), or BlockStmt (else)
}

type LoopStmt struct {
	Initializer  *VarDecl
	Condition    Expression
	Afterthought Expression

	CheckTime LoopConditionTime
	Body      *BlockStmt
}

type PropertyDecl struct {
	Name    string
	Type    Type
	Getter  *GetterStmt
	Setter  *SetterStmt
	Privacy PrivacyLevel
}

type EnumDecl struct {
	Name    string
	Members []string
	Privacy PrivacyLevel
}

type ExtensionDecl struct {
	Original     Type
	GenericTypes []Type
	Supers       []Type
	Body         *BlockStmt
}

type InterfaceDecl struct {
	Name         string
	GenericTypes []Type
	Supers       []Type
	Body         *BlockStmt
	Privacy      PrivacyLevel
}

type PackageDecl struct {
	Name string
}

type ImportDecl struct {
	Name string
}

type TryStmt struct {
	Body    *BlockStmt
	Catch   []*CatchStmt
	Finally *BlockStmt
}

type CatchStmt struct {
	Variable *ParamDecl
	Body     *BlockStmt
}

type FunctionStmt struct {
	Name         string
	Destructor   bool
	GenericTypes []Type
	Parameters   []*ParamDecl
	RetType      Type
	Body         *BlockStmt
	Privacy      PrivacyLevel
}

type ExternFuncStmt struct {
	Name             string
	Parameters       []*ParamDecl
	RetType          Type
	VariableArgument bool
}

type ReturnStmt struct {
	Value Expression
}

//
// Expressions
//

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

// GenericInst represents an explicit type annotation on an expression
// which has a generic type
type GenericInst struct {
	Object      Expression
	Annotations []Type
}

type ThisExpr struct {
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
func (s ParamDecl) isNode()        {}
func (s MemberDecl) isNode()       {}
func (s GetterStmt) isNode()       {}
func (s SetterStmt) isNode()       {}
func (s PropertyDecl) isNode()     {}
func (s EnumDecl) isNode()         {}
func (s ExtensionDecl) isNode()    {}
func (s InterfaceDecl) isNode()    {}
func (s PackageDecl) isNode()      {}
func (s ImportDecl) isNode()       {}
func (s IfStmt) isNode()           {}
func (s ConstIfStmt) isNode()      {}
func (s LoopStmt) isNode()         {}
func (s TryStmt) isNode()          {}
func (s CatchStmt) isNode()        {}
func (s FunctionStmt) isNode()     {}
func (s ExternFuncStmt) isNode()   {}
func (s ReturnStmt) isNode()       {}
func (e ArrayExpr) isNode()        {}
func (e UnaryExpr) isNode()        {}
func (e BinaryExpr) isNode()       {}
func (e CallExpr) isNode()         {}
func (e ArrayAccessExpr) isNode()  {}
func (e MemberAccessExpr) isNode() {}
func (e GenericInst) isNode()      {}
func (e StringExpr) isNode()       {}
func (e BoolExpr) isNode()         {}
func (e CharExpr) isNode()         {}
func (e IntExpr) isNode()          {}
func (e UIntExpr) isNode()         {}
func (e DoubleExpr) isNode()       {}
func (e FloatExpr) isNode()        {}
func (e ThisExpr) isNode()         {}
func (i NamedIDExpr) isNode()      {}
func (i IDAccessExpr) isNode()     {}

func (s BlockStmt) isStatement()      {}
func (s AliasDecl) isStatement()      {}
func (s ClassDecl) isStatement()      {}
func (s VarDecl) isStatement()        {}
func (s ParamDecl) isStatement()      {}
func (s MemberDecl) isStatement()     {}
func (s GetterStmt) isStatement()     {}
func (s SetterStmt) isStatement()     {}
func (s PropertyDecl) isStatement()   {}
func (s EnumDecl) isStatement()       {}
func (s ExtensionDecl) isStatement()  {}
func (s InterfaceDecl) isStatement()  {}
func (s PackageDecl) isStatement()    {}
func (s ImportDecl) isStatement()     {}
func (s LoopStmt) isStatement()       {}
func (s IfStmt) isStatement()         {}
func (s ConstIfStmt) isStatement()    {}
func (s TryStmt) isStatement()        {}
func (s CatchStmt) isStatement()      {}
func (s FunctionStmt) isStatement()   {}
func (s ExternFuncStmt) isStatement() {}
func (s ReturnStmt) isStatement()     {}

func (e ArrayExpr) isExpression()        {}
func (e UnaryExpr) isExpression()        {}
func (e BinaryExpr) isExpression()       {}
func (e CallExpr) isExpression()         {}
func (e ArrayAccessExpr) isExpression()  {}
func (e MemberAccessExpr) isExpression() {}
func (e GenericInst) isExpression()      {}
func (e StringExpr) isExpression()       {}
func (e BoolExpr) isExpression()         {}
func (e CharExpr) isExpression()         {}
func (e IntExpr) isExpression()          {}
func (e UIntExpr) isExpression()         {}
func (e DoubleExpr) isExpression()       {}
func (e FloatExpr) isExpression()        {}
func (e ThisExpr) isExpression()         {}
func (i NamedIDExpr) isExpression()      {}
func (i IDAccessExpr) isExpression()     {}

func (i NamedIDExpr) isIdentifier()  {}
func (i IDAccessExpr) isIdentifier() {}

//
// Privacy levels
//

func (s *EnumDecl) SetPrivacyLevel(l PrivacyLevel)      { s.Privacy = l }
func (s *FunctionStmt) SetPrivacyLevel(l PrivacyLevel)  { s.Privacy = l }
func (s *ClassDecl) SetPrivacyLevel(l PrivacyLevel)     { s.Privacy = l }
func (s *InterfaceDecl) SetPrivacyLevel(l PrivacyLevel) { s.Privacy = l }
func (s *MemberDecl) SetPrivacyLevel(l PrivacyLevel)    { s.Privacy = l }
func (s *PropertyDecl) SetPrivacyLevel(l PrivacyLevel)  { s.Privacy = l }

//
// Helper functions
//

func NewBlockStmt() *BlockStmt {
	return &BlockStmt{Nodes: []Node{}}
}

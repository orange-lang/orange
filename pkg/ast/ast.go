package ast

import "github.com/orange-lang/orange/pkg/types"

// AST represents one module of Orange code
type AST struct {
	Nodes []Node
}

type Node interface {
	IsNode()
	Accept(visitor NodeVisitor)
}

type Statement interface {
	Node
	IsStatement()
}

type PrivacyFlag interface {
	Statement
	SetPrivacyLevel(level PrivacyLevel)
}

type Expression interface {
	Node
	IsExpression()
}

type Identifier interface {
	Expression
	IsIdentifier()
}

//
// Statements
//

type BlockStmt struct {
	Nodes []Node
}

type AliasDecl struct {
	Name string
	Type types.Type
}

type ClassDecl struct {
	Name         string
	GenericTypes []types.Type
	Supers       []types.Type
	Body         *BlockStmt
	Privacy      PrivacyLevel
}

type VarDecl struct {
	Name  string
	Type  types.Type
	Value Expression
}

// ParamDecl is similar to VarDecl but is only found as a parameter to a function
// or method
type ParamDecl struct {
	Name string
	Type types.Type
}

// MemberDecl is similar to a VarDecl but is only found in the body of a class
// (i.e., is it a declaration of a class member)
type MemberDecl struct {
	Name    string
	Type    types.Type
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
	Type    types.Type
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
	Original     types.Type
	GenericTypes []types.Type
	Supers       []types.Type
	Body         *BlockStmt
}

type InterfaceDecl struct {
	Name         string
	GenericTypes []types.Type
	Supers       []types.Type
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
	GenericTypes []types.Type
	Parameters   []*ParamDecl
	RetType      types.Type
	Body         *BlockStmt
	Privacy      PrivacyLevel
}

type ExternFuncStmt struct {
	Name             string
	Parameters       []*ParamDecl
	RetType          types.Type
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
	Annotations []types.Type
}

type ThisExpr struct{}

type SuperExpr struct{}

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

func (s BlockStmt) IsNode()        {}
func (s AliasDecl) IsNode()        {}
func (s ClassDecl) IsNode()        {}
func (s VarDecl) IsNode()          {}
func (s ParamDecl) IsNode()        {}
func (s MemberDecl) IsNode()       {}
func (s GetterStmt) IsNode()       {}
func (s SetterStmt) IsNode()       {}
func (s PropertyDecl) IsNode()     {}
func (s EnumDecl) IsNode()         {}
func (s ExtensionDecl) IsNode()    {}
func (s InterfaceDecl) IsNode()    {}
func (s PackageDecl) IsNode()      {}
func (s ImportDecl) IsNode()       {}
func (s IfStmt) IsNode()           {}
func (s ConstIfStmt) IsNode()      {}
func (s LoopStmt) IsNode()         {}
func (s TryStmt) IsNode()          {}
func (s CatchStmt) IsNode()        {}
func (s FunctionStmt) IsNode()     {}
func (s ExternFuncStmt) IsNode()   {}
func (s ReturnStmt) IsNode()       {}
func (e ArrayExpr) IsNode()        {}
func (e UnaryExpr) IsNode()        {}
func (e BinaryExpr) IsNode()       {}
func (e CallExpr) IsNode()         {}
func (e ArrayAccessExpr) IsNode()  {}
func (e MemberAccessExpr) IsNode() {}
func (e GenericInst) IsNode()      {}
func (e StringExpr) IsNode()       {}
func (e BoolExpr) IsNode()         {}
func (e CharExpr) IsNode()         {}
func (e IntExpr) IsNode()          {}
func (e UIntExpr) IsNode()         {}
func (e DoubleExpr) IsNode()       {}
func (e FloatExpr) IsNode()        {}
func (e ThisExpr) IsNode()         {}
func (e SuperExpr) IsNode()        {}
func (i NamedIDExpr) IsNode()      {}
func (i IDAccessExpr) IsNode()     {}

func (s BlockStmt) IsStatement()      {}
func (s AliasDecl) IsStatement()      {}
func (s ClassDecl) IsStatement()      {}
func (s VarDecl) IsStatement()        {}
func (s ParamDecl) IsStatement()      {}
func (s MemberDecl) IsStatement()     {}
func (s GetterStmt) IsStatement()     {}
func (s SetterStmt) IsStatement()     {}
func (s PropertyDecl) IsStatement()   {}
func (s EnumDecl) IsStatement()       {}
func (s ExtensionDecl) IsStatement()  {}
func (s InterfaceDecl) IsStatement()  {}
func (s PackageDecl) IsStatement()    {}
func (s ImportDecl) IsStatement()     {}
func (s LoopStmt) IsStatement()       {}
func (s IfStmt) IsStatement()         {}
func (s ConstIfStmt) IsStatement()    {}
func (s TryStmt) IsStatement()        {}
func (s CatchStmt) IsStatement()      {}
func (s FunctionStmt) IsStatement()   {}
func (s ExternFuncStmt) IsStatement() {}
func (s ReturnStmt) IsStatement()     {}

func (e ArrayExpr) IsExpression()        {}
func (e UnaryExpr) IsExpression()        {}
func (e BinaryExpr) IsExpression()       {}
func (e CallExpr) IsExpression()         {}
func (e ArrayAccessExpr) IsExpression()  {}
func (e MemberAccessExpr) IsExpression() {}
func (e GenericInst) IsExpression()      {}
func (e StringExpr) IsExpression()       {}
func (e BoolExpr) IsExpression()         {}
func (e CharExpr) IsExpression()         {}
func (e IntExpr) IsExpression()          {}
func (e UIntExpr) IsExpression()         {}
func (e DoubleExpr) IsExpression()       {}
func (e FloatExpr) IsExpression()        {}
func (e ThisExpr) IsExpression()         {}
func (e SuperExpr) IsExpression()        {}
func (i NamedIDExpr) IsExpression()      {}
func (i IDAccessExpr) IsExpression()     {}

func (i NamedIDExpr) IsIdentifier()  {}
func (i IDAccessExpr) IsIdentifier() {}

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

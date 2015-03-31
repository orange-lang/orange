%{
// c stuff 
	#include <iostream>
	#include <gen/gen.h>
	#include <gen/generator.h>

	extern int yylex();
	void yyerror(const char *s) { std::cerr << s << std::endl; exit(1); }

	Block *globalBlock = nullptr; 
	typedef CodeGenerator CG;
%}

%union {
	IfStatement *ifstmt;
	CondBlock *cblock;
	Block *block; 
	Statement *stmt; 
	ArgList *arglist;
	AnyType *anytype;
	ExprList *exprlist;
	ArgExpr *argexpr;
	SymTable *symtab;
	FunctionStatement *fstmt;
	Expression *expr;
	std::string *str;
	int token; 
	int number;
}

%start start 

%token DEF END IF ELIF ELSE TYPE_ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ COMP_LT COMP_GT MOD VALUE STRING EXTERN VARARG EQUALS NEQUALS

%type <ifstmt> if_statement opt_else
%type <block> statements
%type <stmt> statement extern
%type <expr> expression expr_eq expr2 expr3 primary VALUE opt_expr declaration opt_eq
%type <fstmt> function opt_id 
%type <argexpr> opt_arg arg_end
%type <arglist> opt_args arg_list opt_parens
%type <exprlist> expr_list optexprlist
%type <str> TYPE_ID DEF END TYPE TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%type <str> TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR basic_type STRING
%type <anytype> type
%type <number> var_ptrs

%left ASSIGN 
%right PLUS MINUS TIMES DIVIDE COMMA


%%
// we need to start populating symtab...
	
start 			:			{ $<symtab>$ = CodeGenerator::Symtab; } { auto s = new SymTable(); CG::Symtab = s; $<symtab>$ = s; } 
									statements 
									{ globalBlock = $3; globalBlock->symtab = $<symtab>2; CodeGenerator::Symtab = $<symtab>1; } 
						;

statements	: 		statements statement { if ($2) $1->statements.push_back($2); } 
						| 		statement { $$ = new Block(); if ($1) $$->statements.push_back($1); }
						;

statement 	: 		function term { $$ = $1; } 
						|			extern term { $$ = (Statement *)$1; }
						| 		expression term { $$ = (Statement *)$1; } 
						|			declaration term { $$ = (Statement *)$1; }
						|			RETURN opt_expr term { $$ = (Statement *)(new ReturnExpr($2)); }
						| 		term { $$ = nullptr; } 
						;

opt_expr 		:			expression { $$ = $1; }
						|			{ $$ = nullptr; }

term 				:			NEWLINE | SEMICOLON ;

extern 			:			EXTERN type TYPE_ID OPEN_PAREN opt_args CLOSE_PAREN { $$ = new ExternFunction($2, *$3, $5); }

function		:	 		{ $<symtab>$ = CodeGenerator::Symtab; } 
									{ auto s = new SymTable(); CG::Symtab = s; $<symtab>$ = s; s->parent = $<symtab>1; }
									DEF opt_id term statements END 
									{ $$ = $4; $$->body = $6; $$->body->symtab = $<symtab>2; CodeGenerator::Symtab = $<symtab>1; };

opt_id			:			TYPE_ID opt_parens { $$ = new FunctionStatement($1, $2, nullptr); } 
						| 		opt_parens { $$ = new FunctionStatement(nullptr, $1, nullptr); } ;

opt_parens 	: 		OPEN_PAREN opt_args CLOSE_PAREN { $$ = $2; } 
						| 		{ $$ = nullptr; };

opt_args 		:			arg_list { $$ = $1; }
						|			{ $$ = nullptr; }

arg_list 		:			arg_list COMMA arg_end { if ($3) { $1->push_back($3); } else { $1->isVarArg = true; } } 	
						| 		opt_arg { $$ = new ArgList(); $$->push_back($1); }

arg_end			:			VARARG { $$ = nullptr; }
						|			opt_arg { $$ = $1; }

opt_arg 		:			type TYPE_ID { $$ = new ArgExpr($1, $2); } 
						| 		TYPE_ID { $$ = new ArgExpr(nullptr, $1); } 

// type: get any number of TIMES for pointers 
type 				: 		basic_type var_ptrs { $$ = new AnyType($1, $2); }
var_ptrs 		: 		var_ptrs TIMES { $$ = $1 + 1; }
						|			{ $$ = 0; };

basic_type  :			TYPE_INT | TYPE_UINT | TYPE_FLOAT | TYPE_DOUBLE | TYPE_INT8 | TYPE_INT16 
						|			TYPE_INT32 | TYPE_INT64 | TYPE_UINT8 | TYPE_UINT16 | TYPE_UINT32 | TYPE_UINT64 | TYPE_CHAR				

declaration	:			type TYPE_ID opt_eq { $$ = new VarDeclExpr($1, $2, $3); }
opt_eq 			:			ASSIGN expression { $$ = $2; } 
						|			{ $$ = nullptr; }

expression  :			expr_eq ASSIGN expression { $$ = new BinOpExpr($1, "=", $3); }
						|			expr_eq PLUS_ASSIGN expression { $$ = new BinOpExpr($1, "+=", $3); }
						|			expr_eq MINUS_ASSIGN expression { $$ = new BinOpExpr($1, "-=", $3); }
						|			expr_eq TIMES_ASSIGN expression { $$ = new BinOpExpr($1, "*=", $3); }
						|			expr_eq DIVIDE_ASSIGN expression { $$ = new BinOpExpr($1, "/=", $3); }		
						|			expr_eq { $$ = $1; }

expr_eq 		:			expr_eq COMP_LT expr2 { $$ = new BinOpExpr($1, "<", $3); }
						|			expr_eq COMP_GT expr2 { $$ = new BinOpExpr($1, ">", $3); }
						|			expr_eq LEQ expr2	{ $$ = new BinOpExpr($1, "<=", $3); }
						|			expr_eq GEQ expr2 { $$ = new BinOpExpr($1, ">=", $3); }
						|			expr_eq EQUALS expr2 { $$ = new BinOpExpr($1, "==", $3); }
						|			expr_eq NEQUALS expr2 { $$ = new BinOpExpr($1, "!=", $3); }
						|			expr2 { $$ = $1; }

expr2 			:			expr2 PLUS expr3 { $$ = new BinOpExpr($1, "+", $3); }
						| 		expr2 MINUS expr3 { $$ = new BinOpExpr($1, "-", $3); }
						|			expr3 { $$ = $1; }

expr3 			:			expr3 TIMES primary { $$ = new BinOpExpr($1, "*", $3); } 
						| 		expr3 DIVIDE primary { $$ = new BinOpExpr($1, "/", $3); }
						|			primary { $$ = $1; }

primary			: 		OPEN_PAREN expression CLOSE_PAREN { $$ = $2; } 
						| 		VALUE { $$ = $1; }
						| 		TYPE_ID OPEN_PAREN optexprlist CLOSE_PAREN { $$ = new FuncCallExpr(*$1, $3); }
						|			TYPE_ID { $$ = new VarExpr(*$1); }
						|			STRING { $$ = new StrVal(*$1); }
						|			if_statement { $$ = $1; }
						;

if_statement: 		{ $<symtab>$ = CodeGenerator::Symtab; } 
									{ auto s = new SymTable(); CG::Symtab = s; $<symtab>$ = s; s->parent = $<symtab>1; }
									IF expression term statements opt_else 
									{ $$ = $7; CondBlock *b = new CondBlock($4, $6); $$->blocks.insert($$->blocks.begin(), b); b->symtab = $<symtab>2; CodeGenerator::Symtab = $<symtab>1; }

opt_else		: 		{ $<symtab>$ = CodeGenerator::Symtab; } 
									{ auto s = new SymTable(); CG::Symtab = s; $<symtab>$ = s; s->parent = $<symtab>1; }
									ELIF expression term statements opt_else 
									{ $$ = $7; CondBlock *b = new CondBlock($4, $6); $$->blocks.insert($$->blocks.begin(), b); b->symtab = $<symtab>2; CodeGenerator::Symtab = $<symtab>1; }
						|			{ $<symtab>$ = CodeGenerator::Symtab; } 
									{ auto s = new SymTable(); CG::Symtab = s; $<symtab>$ = s; s->parent = $<symtab>1; }
									ELSE term statements END
									{ $$ = new IfStatement; $$->blocks.insert($$->blocks.begin(), $5); $5->symtab = $<symtab>2; CodeGenerator::Symtab = $<symtab>1; }
						|			END { $$ = new IfStatement; }

optexprlist :			expr_list { $$ = $1; }
						|			{ $$ = new ExprList(); }

expr_list		:			expr_list COMMA expression { $1->push_back($3); }
						|			expression { $$ = new ExprList(); $$->push_back($1); }
						 

%%

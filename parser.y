%{
// c stuff 
	#include <iostream>
	#include "AST.h"

	extern int yylex();
	void yyerror(const char *s) { std::cerr << s << std::endl; }

	Block *globalBlock = nullptr; 
%}

%union {
	Block *block; 
	Statement *stmt; 
	ArgList *arglist;
	ExprList *exprlist;
	ArgExpr *argexpr;
	FunctionStatement *fstmt;
	Expression *expr;
	std::string *str;
	int token; 
}

%start start 

%token DEF END ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ LT GT MOD VALUE

%type <block> statements
%type <stmt> statement
%type <expr> expression expr2 expr3 primary VALUE
%type <fstmt> function opt_id
%type <argexpr> opt_arg
%type <arglist> opt_args opt_parens
%type <exprlist> expr_list
%type <str> ID DEF END TYPE TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%type <str> TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 type

%left ASSIGN 
%right PLUS MINUS TIMES DIVIDE COMMA


%%
	
start 			:			statements { globalBlock = $1; } 
						;

statements	: 		statements statement { if ($2) $1->statements.push_back($2); } 
						| 		statement { $$ = new Block(); if ($1) $$->statements.push_back($1); }
						;

statement 	: 		function term { $$ = $1; } 
						| 		expression term { $$ = (Statement *)$1; } 
						|			RETURN expression term { $$ = (Statement *)(new ReturnExpr($2)); }
						| 		term { $$ = nullptr; } 
						;

term 				:			NEWLINE | SEMICOLON ;

function		:	 		DEF opt_id term statements END { $$ = $2; $$->body = $4; };
opt_id			:			ID opt_parens { $$ = new FunctionStatement($1, $2, nullptr); } 
						| 		opt_parens { $$ = new FunctionStatement(nullptr, $1, nullptr) } ;

opt_parens 	: 		OPEN_PAREN opt_args CLOSE_PAREN { $$ = $2; } 
						| 		{ $$ = nullptr; };

opt_args 		:			opt_args COMMA opt_arg { $1->push_back($3); } 	
						| 		opt_arg { $$ = new ArgList(); $$->push_back($1); }; 

opt_arg 		:			type ID { $$ = new ArgExpr($1, $2); } 
						| 		ID { $$ = new ArgExpr(nullptr, $1); } ; 

type  			:			TYPE_INT | TYPE_FLOAT | TYPE_DOUBLE | TYPE_INT8 | TYPE_INT16 
						|			TYPE_INT32 | TYPE_INT64 | TYPE_UINT8 | TYPE_UINT16 | TYPE_UINT32 | TYPE_UINT64				

expression  :			expr2 ASSIGN expression { $$ = new BinOpExpr($1, '=', $3); }
						|			expr2 { $$ = $1; }

expr2 			:			expr2 PLUS expr3 { $$ = new BinOpExpr($1, '+', $3); }
						| 		expr2 MINUS expr3 { $$ = new BinOpExpr($1, '-', $3); }
						|			expr3 { $$ = $1; }

expr3 			:			expr3 TIMES primary { $$ = new BinOpExpr($1, '*', $3); } 
						| 		expr3 DIVIDE primary { $$ = new BinOpExpr($1, '/', $3); }
						|			primary { $$ = $1; }

primary			: 		OPEN_PAREN expression CLOSE_PAREN { $$ = $2; } 
						| 		VALUE { $$ = $1; }
						| 		ID OPEN_PAREN expr_list CLOSE_PAREN { $$ = new FuncCallExpr(*$1, $3); }
						|			ID { $$ = new VarExpr(*$1); }
						;


expr_list		:			expr_list COMMA expression { $1->push_back($3); }
						|			expression { $$ = new ExprList(); $$->push_back($1); }
						 

%%
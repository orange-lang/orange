/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

%{
	#include <iostream>
	#include <orange/orange.h>
	#include <orange/generator.h>
	#include <orange/Block.h>

	extern int yylex();
	extern struct YYLTYPE yyloc;
	extern void yyerror(const char *s);

	#define SET_LOCATION(x) CodeLocation loc = { yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column }; x->setLocation(loc);
%}

%locations
// %error-verbose

%union {
	Expression *expr;
	Statement *stmt;
	StrElement *strele;
	ASTNode *node;
	Block *block;
	std::string *str;
	int token; 
	int number;
}

%start start 

%token DEF END IF ELIF ELSE TYPE_ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR TYPE_VOID
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ COMP_LT COMP_GT MOD VALUE STRING EXTERN VARARG EQUALS NEQUALS WHEN
%token UNLESS LOGICAL_AND LOGICAL_OR BITWISE_AND BITWISE_OR BITWISE_XOR
%token FOR FOREVER LOOP CONTINUE BREAK DO WHILE 
%token CONST

%type <block> statements
%type <node> statement
%type <expr> expression primary VALUE
%type <stmt> return
%type <str> TYPE_ID 
%type <strele> ASSIGN PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN COMP_LT COMP_GT LEQ GEQ EQUALS NEQUALS PLUS MINUS TIMES DIVIDE

%right ASSIGN ARROW_LEFT PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN

%left COMP_LT COMP_GT LEQ GEQ
%left EQUALS NEQUALS 

%left PLUS MINUS
%left TIMES DIVIDE
%left OPEN_PAREN CLOSE_PAREN

%%
	
start
	:	statements
	;

/* Create our list of statements. Find our top block and add statements to it. */
statements 		
	: statements statement { $1->addStatement($2); }
	| statement { $$ = GE::runner()->topBlock(); $$->addStatement($1); }
	;

statement 		
	:	term { $$ = nullptr; }
	| expression term { $$ = $1; SET_LOCATION($$); }
	| return term { $$ = $1; SET_LOCATION($$); }
	;

expression
	: expression ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression PLUS_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression MINUS_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression TIMES_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression DIVIDE_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); }

	|	expression COMP_LT expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression COMP_GT expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression LEQ expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression GEQ expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression EQUALS expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression NEQUALS expression { $$ = new BinOpExpr($1, *$2, $3); }

	|	expression PLUS expression { $$ = new BinOpExpr($1, *$2, $3); }
	|	expression MINUS expression { $$ = new BinOpExpr($1, *$2, $3); }

	|	expression TIMES expression { $$ = new BinOpExpr($1, *$2, $3); } 
	|	expression DIVIDE expression { $$ = new BinOpExpr($1, *$2, $3); }

	| primary { $$ = $1; }
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN { $$ = $2; SET_LOCATION($$); } 
	|	VALUE { $$ = $1; SET_LOCATION($$); }
	|	TYPE_ID { $$ = new VarExpr(*$1); SET_LOCATION($$); }
	;

return
	: RETURN { $$ = new ReturnStmt(); SET_LOCATION($$); }
	| RETURN expression { $$ = new ReturnStmt($2); SET_LOCATION($$); }
	;

term 
	: NEWLINE
	| SEMICOLON
	;
						 
%%

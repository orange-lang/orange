/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <grove/Module.h>
	#include <grove/ASTNode.h>
	#include <grove/Block.h>
	#include <grove/Function.h>
	#include <grove/Value.h>
	#include <grove/Expression.h>
	#include <grove/ReturnStmt.h>
	#include <grove/BinOpCompare.h>
	#include <grove/BinOpArith.h>

	extern struct YYLTYPE yyloc;
	extern void yyerror(Module* mod, const char *s);

	extern int yylex(Module* module);
%}

%locations
%error-verbose
%lex-param { Module* module }
%parse-param { Module* module }

%union {
	std::vector<ASTNode*>* nodes;
	ASTNode* node;
	Block* block;
	Expression* expr;
	Value* val;
	std::string* str;
}

%start start

%token DEF END IF ELIF ELSE TYPE_ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR TYPE_VOID TYPE_VAR
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ COMP_LT COMP_GT MOD VALUE STRING EXTERN VARARG EQUALS NEQUALS WHEN
%token UNLESS LOGICAL_AND LOGICAL_OR BITWISE_AND BITWISE_OR BITWISE_XOR
%token FOR FOREVER LOOP CONTINUE BREAK DO WHILE
%token CONST QUESTION COLON ENUM SIZEOF

%type <nodes> statements
%type <node> statement return controls
%type <expr> expression primary comparison arithmetic
%type <val> VALUE
%type <str> COMP_LT COMP_GT LEQ GEQ PLUS MINUS

/* lowest to highest precedence */
%left COMMA

%right ASSIGN ARROW_LEFT PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN

%right QUESTION COLON

%left LOGICAL_OR
%left LOGICAL_AND

%left EQUALS NEQUALS
%left COMP_LT COMP_GT LEQ GEQ

%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND

%left PLUS MINUS
%left TIMES DIVIDE MOD
%left OPEN_PAREN CLOSE_PAREN INCREMENT DECREMENT OPEN_BRACKET
%right SIZEOF

%%

start
  : statements
	{
		for (auto stmt : *$1)
		{
			module->getMain()->addStatement(stmt);
		}
	}
	;

statements
	: statements statement term
	{
		$$ = $1;

		if ($2 != nullptr)
		{
    		$$->push_back($2);
		}
	}
	| statement term
	{
		$$ = new std::vector<ASTNode *>();

		if ($1 != nullptr)
		{
			$$->push_back($1);
		}
	}
	;

statement
	: { $$ = nullptr; }
//	| structures term  /* structures: if, loops, functions, etc */
	| controls { $$ = $1; } /* controls: return, break, continue */
	| expression { $$ = $1; }
	;

controls
	: return { $$ = $1; }
	;

expression
	: primary { $$ = $1; }
	| comparison { $$ = $1; }
	| arithmetic { $$ = $1; }
	;

comparison
	: expression COMP_LT expression { $$ = new BinOpCompare($1, *$2, $3); }
	| expression COMP_GT expression { $$ = new BinOpCompare($1, *$2, $3); }
	| expression LEQ expression { $$ = new BinOpCompare($1, *$2, $3); }
	| expression GEQ expression { $$ = new BinOpCompare($1, *$2, $3); }
	;

arithmetic
	: expression PLUS expression { $$ = new BinOpArith($1, *$2, $3); }
	| expression MINUS expression { $$ = new BinOpArith($1, *$2, $3); }
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN { $$ = $2; }
	| VALUE { $$ = $1; }
	;

return
	: RETURN
	{
		$$ = new ReturnStmt(nullptr);
	}
	| RETURN expression
	{
		$$ = new ReturnStmt($2);
	}
	;

term
	: NEWLINE
	| SEMICOLON
	;

/*
basic_type
	: TYPE_INT
	| TYPE_UINT
	| TYPE_FLOAT
	| TYPE_DOUBLE
	| TYPE_INT8
	| TYPE_INT16
	| TYPE_INT32
	| TYPE_INT64
	| TYPE_UINT8
	| TYPE_UINT16
	| TYPE_UINT32
	| TYPE_UINT64
	| TYPE_CHAR
	| TYPE_VOID
	| TYPE_VAR
	;
*/

%%

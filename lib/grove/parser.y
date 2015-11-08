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

	extern struct YYLTYPE yyloc;
	extern void yyerror(Module* mod, const char *s);
	
	extern int yylex(Module* module);
%}

%locations
// %error-verbose
%lex-param { Module* module }
%parse-param { Module* module }

%union {
	ASTNode* node;
	Block* block;
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

%type <block> statements
%type <node> statement

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
	;

/* Create our list of statements. Find our top block and add statements to it. */
statements
	: statements statement
    | statement
	{
		$$ = module->getBlock();
		
		if ($1 != nullptr)
		{
    		$$->addStatement($1);
		}
	}
	;

opt_statements
	: statements
	|
	;

statement
	: term
	| expression more_exprs term
	| function term
	| extern_function term
	| return term
	| if_statement term
	| unless_statement term
	| inline_if term
	| inline_unless term
	| variable_decl term
	| const_var term
	| for_loop term
	| inline_loop term
	| loop_breaks term
	| enum_stmt term
	;

more_exprs
	: COMMA expression more_exprs
	|
	;

expression
	: expression ASSIGN expression
	| expression PLUS_ASSIGN expression
	| expression MINUS_ASSIGN expression
	| expression TIMES_ASSIGN expression
	| expression DIVIDE_ASSIGN expression

	| expression COMP_LT expression
	| expression COMP_GT expression
	| expression LEQ expression
	| expression GEQ expression
	| expression EQUALS expression
	| expression NEQUALS expression

	| expression PLUS expression
	| expression MINUS expression

	| expression TIMES expression
	| expression DIVIDE expression
	| expression MOD expression

	| expression LOGICAL_AND expression
	| expression LOGICAL_OR expression

	| expression BITWISE_AND expression
	| expression BITWISE_OR expression
	| expression BITWISE_XOR expression

	| expression QUESTION expression COLON expression

	| TYPE_ID DOT TYPE_ID

	| primary_high
	| OPEN_PAREN any_type CLOSE_PAREN expression
	| BITWISE_AND expression
	;

primary_high
	: primary
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN
	| VALUE
	| STRING
	| TYPE_ID
	| TYPE_ID OPEN_PAREN opt_arg_list CLOSE_PAREN
	| SIZEOF OPEN_PAREN expression CLOSE_PAREN
	| SIZEOF OPEN_PAREN any_type CLOSE_PAREN
	| MINUS expression

	| expression INCREMENT
	| INCREMENT expression

	| expression DECREMENT
	| DECREMENT expression

	| OPEN_BRACKET opt_arg_list CLOSE_BRACKET
	| opt_array OPEN_BRACKET expression CLOSE_BRACKET

	| TIMES expression

	;

opt_array
	: TYPE_ID
	| opt_array OPEN_BRACKET expression CLOSE_BRACKET
	;

function
	: DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN term opt_statements END
	| DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN ARROW any_type term opt_statements END

opt_func_params
	: func_params
	|
	;

func_params
	: func_params COMMA any_type_no_array TYPE_ID
	| func_params COMMA VARARG
	| any_type_no_array TYPE_ID
	;

extern_function
	: EXTERN TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN ARROW any_type
	;

opt_arg_list
	: arg_list
	|
	;

arg_list
	: arg_list COMMA expression
	| expression
	;

if_statement
	: IF expression term statements else_ifs_or_end ;

else_ifs_or_end
	: ELIF expression term statements else_ifs_or_end
	| ELSE term statements END
	| END
	;

inline_if
	: return_or_expr IF expression
	;

unless_statement
	: UNLESS expression term statements END

inline_unless
	: return_or_expr UNLESS expression
	;

for_loop
	: FOR OPEN_PAREN initializer SEMICOLON opt_expr SEMICOLON opt_expr CLOSE_PAREN term statements END
	| WHILE expression term statements END
	| FOREVER DO term statements END
	| DO term statements END WHILE expression
	;

inline_loop
	: return_or_expr FOR OPEN_PAREN initializer SEMICOLON opt_expr SEMICOLON opt_expr CLOSE_PAREN
	| return_or_expr WHILE expression
	| return_or_expr FOREVER

loop_breaks
	: LOOP
	| CONTINUE
	| BREAK
	;

enum_stmt
	: ENUM TYPE_ID term enum_members END

enum_members
	: enum_members TYPE_ID term
	| enum_members TYPE_ID ASSIGN VALUE term
	| TYPE_ID term
	| TYPE_ID ASSIGN VALUE term
	;

initializer
	: variable_decl
	| expression
	;

opt_expr
	: expression
	|

variable_decl
	: any_type TYPE_ID opt_variable_decls
	| any_type TYPE_ID ASSIGN expression opt_variable_decls
	;

opt_variable_decls
	: COMMA opt_variable_decls_impl
	|
	;

opt_variable_decls_impl
	: TYPE_ID COMMA opt_variable_decls
	| TYPE_ID ASSIGN expression COMMA opt_variable_decls
	| TYPE_ID
	| TYPE_ID ASSIGN expression
    ;

const_var
	: CONST any_type TYPE_ID ASSIGN expression
	| CONST TYPE_ID ASSIGN expression
	;

return_or_expr
	: return
	| expression
	| loop_breaks
	;

return
	: RETURN
	| RETURN expression
	;

term
	: NEWLINE
	| SEMICOLON
	;

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

any_type
	: basic_type var_arrays var_ptrs
	;

any_type_no_array
	: basic_type var_arrays_and_ptrs
	;

var_arrays_and_ptrs
	: var_arrays_and_ptrs TIMES
	| var_arrays_and_ptrs OPEN_BRACKET opt_primary CLOSE_BRACKET
	|
	;

opt_primary
	: primary
	|
    ;

var_arrays
	: var_arrays OPEN_BRACKET expression CLOSE_BRACKET
	|
    ;

var_ptrs
	: var_ptrs TIMES
	| OPEN_BRACKET CLOSE_BRACKET
	|
    ;

%%

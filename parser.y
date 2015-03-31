%{
// c stuff 
	#include <iostream>
	extern int yylex();
	void yyerror(const char *s) { std::cerr << s << std::endl; }
%}

%start start 

%token DEF END ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ LT GT MOD 


%%
	
start 			:			statements
statements	: 		statement statements | ;
statement 	: 		function term | expression term | term

term 				:			NEWLINE | SEMICOLON

function		:	 		DEF opt_id END
opt_id			:			ID opt_parens | OPEN_PAREN opt_args CLOSE_PAREN
opt_parens 	: 		OPEN_PAREN opt_args CLOSE_PAREN | ;

opt_args		:			opt_arg opt_comma | ;
opt_comma  	:			COMMA opt_args | ;
opt_arg 		:			opt_type ID 
opt_type 		:			TYPE | ;

expression 	:			expression PLUS expr2 | expression MINUS expr2
						|			expr2 

expr2 			:			expr2 TIMES primary | expr2 DIVIDE primary 
						|			primary

primary			: 		OPEN_PAREN expression CLOSE_PAREN | NUMBER | ID opt_func

opt_func 		:			OPEN_PAREN expr_list CLOSE_PAREN | ;
expr_list 	: 		expression expr_comma | ; 
expr_comma 	: 		COMMA expr_list | ;

%%
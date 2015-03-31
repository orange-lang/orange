/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

%{
	#include <orange/orange.h>
	#include <string.h>
	#include "parser.hh"

	#define STR (std::string(yytext, yyleng))

	ValFactory *factory = nullptr;

	#define MKFACTORY() factory = new ValFactory(); factory->value = yytext;
	#define DOFACTORY(SZ) factory->size = SZ; yylval.expr = factory->produce(); delete factory;
	#define SAVESTR() yylval.str = new std::string(yytext, yyleng);

	// Get column and stuff for line information
	int yycolumn = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

  extern void yyerror(const char *);
%}

%option noyywrap
%option nounistd
%option never-interactive
%option yylineno

%x HEX 

%%

[\ \t\r]								;

"#"[^\r\n]*							yycolumn = 1; // Reset column as we're on a new line.


[0|1]+"b"								MKFACTORY(); DOFACTORY("b"); return VALUE;

"0x"										MKFACTORY(); BEGIN(HEX); 
<HEX>{
	[0-9A-Fa-f]+					factory->value = yytext; DOFACTORY("x"); BEGIN(INITIAL); return VALUE; 
	.											printf("Invalid hex constant 0x%s\n", yytext); BEGIN(INITIAL);
}

[0-9][0-9]*\.[0-9]+"f"	MKFACTORY(); DOFACTORY("f"); return VALUE;
[0-9][0-9]*\.[0-9]+"d"	MKFACTORY(); DOFACTORY("d"); return VALUE;
[0-9][0-9]*\.[0-9]+			MKFACTORY(); DOFACTORY("d"); return VALUE;

[0-9][0-9]*"u8"					MKFACTORY(); DOFACTORY("u8"); return VALUE;
[0-9][0-9]*"i8"					MKFACTORY(); DOFACTORY("i8"); return VALUE;
[0-9][0-9]*"u16"				MKFACTORY(); DOFACTORY("u16"); return VALUE;
[0-9][0-9]*"i16"				MKFACTORY(); DOFACTORY("i16"); return VALUE;
[0-9][0-9]*"u32"				MKFACTORY(); DOFACTORY("u32"); return VALUE;
[0-9][0-9]*"i32"				MKFACTORY(); DOFACTORY("i32"); return VALUE;
[0-9][0-9]*"u64"				MKFACTORY(); DOFACTORY("u64"); return VALUE;
[0-9][0-9]*"i64"				MKFACTORY(); DOFACTORY("i64"); return VALUE;
[0-9][0-9]*"u"					MKFACTORY(); DOFACTORY("u"); return VALUE;
[0-9][0-9]*"i"					MKFACTORY(); DOFACTORY("i"); return VALUE;
[0-9][0-9]*							MKFACTORY(); DOFACTORY("i"); return VALUE;

'.'											MKFACTORY(); DOFACTORY("i8"); return VALUE;

"false"									MKFACTORY(); factory->value = "0"; DOFACTORY("u8"); return VALUE;
"true"									MKFACTORY(); factory->value = "1"; DOFACTORY("u8"); return VALUE;

"def"										return DEF; 
"return"								return RETURN;
"elif"									return ELIF;
"else"									return ELSE;
"end"										return END; 
"if"										return IF;
"for"										return FOR;
"forever"								return FOREVER; 
"loop"									return LOOP;
"continue"							return CONTINUE;
"break"									return BREAK;
"do"										return DO;
"while"									return WHILE;
"when"									return WHEN;
"unless"								return UNLESS;
"class"									return CLASS; 
"using"									return USING; 
"public"								return PUBLIC; 
"private"								return PRIVATE; 
"shared"								return SHARED; 
"extern"								return EXTERN;
"const"									return CONST;

"char"									SAVESTR(); return TYPE_CHAR; 
"int"										SAVESTR(); return TYPE_INT; 
"uint"									SAVESTR(); return TYPE_UINT; 
"float"									SAVESTR(); return TYPE_FLOAT; 
"double"								SAVESTR(); return TYPE_DOUBLE; 
"int8"									SAVESTR(); return TYPE_INT8; 
"uint8"									SAVESTR(); return TYPE_UINT8;
"int16"									SAVESTR(); return TYPE_INT16; 
"uint16"								SAVESTR(); return TYPE_UINT16; 
"int32"									SAVESTR(); return TYPE_INT32; 
"uint32"								SAVESTR(); return TYPE_UINT32; 
"int64"									SAVESTR(); return TYPE_INT64; 
"uint64"								SAVESTR(); return TYPE_UINT64;
"void"									SAVESTR(); return TYPE_VOID;

"("											return OPEN_PAREN; 
")"											return CLOSE_PAREN; 
"{"											return OPEN_BRACE; 
"}"											return CLOSE_BRACE;
"["											return OPEN_BRACKET; 
"]"											return CLOSE_BRACKET; 

"..."										return VARARG;

"++"										return INCREMENT; 
"--"										return DECREMENT; 

"!="										return NEQUALS;
"=="										return EQUALS;

"&&"										return LOGICAL_AND; 
"||"										return LOGICAL_OR;
"and"										return LOGICAL_AND;
"or"										return LOGICAL_OR;

"&"											return BITWISE_AND;
"|"											return BITWISE_OR;
"^"											return BITWISE_XOR;

"="											return ASSIGN;
"+="										return PLUS_ASSIGN;
"-="										return MINUS_ASSIGN;
"*="										return TIMES_ASSIGN;
"/="										return DIVIDE_ASSIGN; 
"%="										return MOD_ASSIGN;

"->"										return ARROW;
"<-"										return ARROW_LEFT;
"."											return DOT;
";"											return SEMICOLON; 
\n 											yycolumn = 1; return NEWLINE; // Reset column as we're on a new line.
","											return COMMA;
	
"<="										return LEQ;
">="										return GEQ; 

"<"											return COMP_LT; 
">"											return COMP_GT;

"+"											return PLUS;
"-"											return MINUS;
"*"											return TIMES; 
"/"											return DIVIDE; 
"%"											return MOD; 

"mod"										return MOD;

[A-Za-z][A-Za-z0-9_]* 	SAVESTR(); return TYPE_ID;

.												yyerror("invalid token");

<<EOF>> { static int once = 0; return once++ ? 0 : NEWLINE; }

%%

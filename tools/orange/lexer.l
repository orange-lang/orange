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

  int yyonce = 0;

  // defining this in here for C++
  void yyflushbuffer() { YY_FLUSH_BUFFER; }

	#define STR_ELEMENT yylval.strele = new StrElement(yytext); yylval.strele->setLocation({ yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column });
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

"("											STR_ELEMENT; return OPEN_PAREN; 
")"											STR_ELEMENT; return CLOSE_PAREN; 
"{"											STR_ELEMENT; return OPEN_BRACE; 
"}"											STR_ELEMENT; return CLOSE_BRACE;
"["											STR_ELEMENT; return OPEN_BRACKET; 
"]"											STR_ELEMENT; return CLOSE_BRACKET; 

"..."										STR_ELEMENT; return VARARG;

"++"										STR_ELEMENT; return INCREMENT; 
"--"										STR_ELEMENT; return DECREMENT; 

"!="										STR_ELEMENT; return NEQUALS;
"=="										STR_ELEMENT; return EQUALS;

"&&"										STR_ELEMENT; return LOGICAL_AND; 
"||"										STR_ELEMENT; return LOGICAL_OR;
"and"										STR_ELEMENT; return LOGICAL_AND;
"or"										STR_ELEMENT; return LOGICAL_OR;

"&"											STR_ELEMENT; return BITWISE_AND;
"|"											STR_ELEMENT; return BITWISE_OR;
"^"											STR_ELEMENT; return BITWISE_XOR;

"="											STR_ELEMENT; return ASSIGN;
"+="										STR_ELEMENT; return PLUS_ASSIGN;
"-="										STR_ELEMENT; return MINUS_ASSIGN;
"*="										STR_ELEMENT; return TIMES_ASSIGN;
"/="										STR_ELEMENT; return DIVIDE_ASSIGN; 
"%="										STR_ELEMENT; return MOD_ASSIGN;

"->"										STR_ELEMENT; return ARROW;
"<-"										STR_ELEMENT; return ARROW_LEFT;
"."											STR_ELEMENT; return DOT;
";"											STR_ELEMENT; return SEMICOLON; 
\n 											yycolumn = 1; return NEWLINE; // Reset column as we're on a new line.
","											STR_ELEMENT; return COMMA;
	
"<="										STR_ELEMENT; return LEQ;
">="										STR_ELEMENT; return GEQ; 

"<"											STR_ELEMENT; return COMP_LT; 
">"											STR_ELEMENT; return COMP_GT;

"+"											STR_ELEMENT; return PLUS;
"-"											STR_ELEMENT; return MINUS;
"*"											STR_ELEMENT; return TIMES; 
"/"											STR_ELEMENT; return DIVIDE; 
"%"											STR_ELEMENT; return MOD; 

"?"											STR_ELEMENT; return QUESTION;
":"											STR_ELEMENT; return COLON;

"mod"										STR_ELEMENT; return MOD;

\"(\\.|[^\\"])*\"				SAVESTR(); return STRING;
[A-Za-z\x80-\xf3][A-Za-z0-9_\x80-\xf3]* 	SAVESTR(); return TYPE_ID;

.												yyerror("invalid token");

<<EOF>> { return yyonce++ ? 0 : NEWLINE; }

%%

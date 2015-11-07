/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <grove/ASTNode.h>
	#include <grove/Block.h>
	
    #include <string.h>
    #include "parser.hh"

    #define STR (std::string(yytext, yyleng))

    // Get column and stuff for line information
    int yycolumn = 1;
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;
	
	#define YY_DECL int yylex(Module* module)

	class Module;
    extern void yyerror(Module* mod, const char *);

    int yyonce = 0;

    // defining this in here for C++
    void yyflushbuffer() { YY_FLUSH_BUFFER; }
%}

%option noyywrap
%option nounistd
%option never-interactive
%option yylineno
%option nounput
%option noinput

%x HEX

%%

[\ \t\r]								;

"#"[^\r\n]*							yycolumn = 1; // Reset column as we're on a new line.

[0|1]+"b"								return VALUE;

"0x"										BEGIN(HEX);
<HEX>{
	[0-9A-Fa-f]+					BEGIN(INITIAL); return VALUE;
	.											printf("Invalid hex constant 0x%s\n", yytext); BEGIN(INITIAL);
}

[0-9][0-9]*\.[0-9]+"f"	return VALUE;
[0-9][0-9]*\.[0-9]+"d"	return VALUE;
[0-9][0-9]*\.[0-9]+			return VALUE;

[0-9][0-9]*"u8"					return VALUE;
[0-9][0-9]*"i8"					return VALUE;
[0-9][0-9]*"u16"				return VALUE;
[0-9][0-9]*"i16"				return VALUE;
[0-9][0-9]*"u32"				return VALUE;
[0-9][0-9]*"i32"				return VALUE;
[0-9][0-9]*"u64"				return VALUE;
[0-9][0-9]*"i64"				return VALUE;
[0-9][0-9]*"u"					return VALUE;
[0-9][0-9]*"i"					return VALUE;
[0-9][0-9]*							return VALUE;

'.'											return VALUE;

"false"									return VALUE;
"true"									return VALUE;

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
"enum"									return ENUM;

"var"										return TYPE_VAR;
"char"									return TYPE_CHAR;
"int"										return TYPE_INT;
"uint"									return TYPE_UINT;
"float"									return TYPE_FLOAT;
"double"								return TYPE_DOUBLE;
"int8"									return TYPE_INT8;
"uint8"									return TYPE_UINT8;
"int16"									return TYPE_INT16;
"uint16"								return TYPE_UINT16;
"int32"									return TYPE_INT32;
"uint32"								return TYPE_UINT32;
"int64"									return TYPE_INT64;
"uint64"								return TYPE_UINT64;
"void"									return TYPE_VOID;

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
\n 											return NEWLINE; // Reset column as we're on a new line.
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

"?"											return QUESTION;
":"											return COLON;

"mod"										return MOD;

"sizeof"								return SIZEOF;

\"(\\.|[^\\"])*\"				return STRING;
[A-Za-z\x80-\xf3][A-Za-z0-9_\x80-\xf3]* 	return TYPE_ID;

.												yyerror(module, "invalid token");

<<EOF>> { return yyonce++ ? 0 : NEWLINE; }

%%

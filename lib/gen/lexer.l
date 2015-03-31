%{
	// c stuff 
	#include "gen/gen.h"
	#include "parser.hh"
	#define STR (std::string(yytext, yyleng))

	ValFactory *factory = nullptr;

	#define MKFACTORY() factory = new ValFactory(); factory->value = yytext;
	#define DOFACTORY(SZ) factory->size = SZ; yylval.expr = factory->produce(); delete factory;
	#define SAVESTR() yylval.str = new std::string(yytext, yyleng);
%}

%option noyywrap
%option nounistd
%option never-interactive

%x COMMENT 
%x BINARY 
%x HEX 

%%

[\ \t\r]								;

"#"[^\r\n]*							;


[0|1]+"b"								MKFACTORY(); DOFACTORY("b"); return VALUE;

"0x"										MKFACTORY(); BEGIN(HEX); 
<HEX>{
	[0-9A-Fa-f]+					factory->value = yytext; DOFACTORY("x"); BEGIN(INITIAL); return VALUE; 
	.											printf("Invalid hex constant 0x%s\n", yytext); BEGIN(INITIAL);
}

"-"?[0-9][0-9]*\.[0-9]+"f"	MKFACTORY(); DOFACTORY("f"); return VALUE;
"-"?[0-9][0-9]*\.[0-9]+"d"	MKFACTORY(); DOFACTORY("d"); return VALUE;
"-"?[0-9][0-9]*\.[0-9]+			MKFACTORY(); DOFACTORY("d"); return VALUE;


"-"?[0-9][0-9]*"u8"			MKFACTORY(); DOFACTORY("u8"); return VALUE;
"-"?[0-9][0-9]*"i8"			MKFACTORY(); DOFACTORY("i8"); return VALUE;
"-"?[0-9][0-9]*"u16"		MKFACTORY(); DOFACTORY("u16"); return VALUE;
"-"?[0-9][0-9]*"i16"		MKFACTORY(); DOFACTORY("i16"); return VALUE;
"-"?[0-9][0-9]*"u32"		MKFACTORY(); DOFACTORY("u32"); return VALUE;
"-"?[0-9][0-9]*"i32"		MKFACTORY(); DOFACTORY("i32"); return VALUE;
"-"?[0-9][0-9]*"u64"		MKFACTORY(); DOFACTORY("u64"); return VALUE;
"-"?[0-9][0-9]*"i64"		MKFACTORY(); DOFACTORY("i64"); return VALUE;
"-"?[0-9][0-9]*"u"			MKFACTORY(); DOFACTORY("u"); return VALUE;
"-"?[0-9][0-9]*"i"			MKFACTORY(); DOFACTORY("i"); return VALUE;
"-"?[0-9][0-9]*					MKFACTORY(); DOFACTORY("i"); return VALUE;

"def"										return DEF; 
"return"								return RETURN;
"end"										return END; 
"class"									return CLASS; 
"using"									return USING; 
"public"								return PUBLIC; 
"private"								return PRIVATE; 
"shared"								return SHARED; 
"extern"								return EXTERN;

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
\n 											return NEWLINE;
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

\"(\\.|[^\\"])*\"				SAVESTR(); return STRING;
[A-Za-z][A-Za-z0-9_]* 	SAVESTR(); return TYPE_ID;

.												printf("ERROR: Unhandled token: %s\n", yytext);

<<EOF>> { static int once = 0; return once++ ? 0 : NEWLINE; }

%%

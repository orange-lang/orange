%{
	// c stuff 
	#include "AST.h"
	#include "parser.hh"
	#define STR (std::string(yytext, yyleng))

	ValFactory *factory = nullptr;

	#define MKFACTORY() factory = new ValFactory(); factory->value = yytext;
	#define DOFACTORY(SZ) factory->size = SZ; yylval.expr = factory->produce(); delete factory;
	#define SAVESTR() yylval.str = new std::string(yytext, yyleng);
%}

%option noyywrap

%x COMMENT 
%x INT
%x BINARY 
%x HEX 

%%

[\ \t\r]								;

"#"[^\r\n]*							;


[0|1]+									MKFACTORY(); BEGIN(BINARY); 
<BINARY>{
	"b"										DOFACTORY("b"); BEGIN(INITIAL); return VALUE;
	.											BEGIN(INT);
}							

"0x"										MKFACTORY(); BEGIN(HEX); 
<HEX>{
	[0-9A-Fa-f]+					factory->value = yytext; DOFACTORY("x"); BEGIN(INITIAL); return VALUE; 
	.											printf("Invalid hex constant 0x%s\n", yytext); BEGIN(INITIAL);
}

"-"?[1-9][0-9]*.[0-9]+	MKFACTORY(); DOFACTORY("d"); return VALUE;

"-"?[1-9][0-9]*					MKFACTORY(); BEGIN(INT);

<INT>{
	"u"										DOFACTORY("u"); BEGIN(INITIAL); return VALUE; 
	"i"										DOFACTORY("i"); BEGIN(INITIAL); return VALUE;
	"u8"									DOFACTORY("u8"); BEGIN(INITIAL); return VALUE; 
	"i8"									DOFACTORY("i8"); BEGIN(INITIAL); return VALUE; 
	"u16"									DOFACTORY("u16"); BEGIN(INITIAL); return VALUE; 
	"i16"									DOFACTORY("i16"); BEGIN(INITIAL); return VALUE; 
	"u32"									DOFACTORY("u32"); BEGIN(INITIAL); return VALUE; 
	"i32"									DOFACTORY("i32"); BEGIN(INITIAL); return VALUE; 
	"u64"									DOFACTORY("u64"); BEGIN(INITIAL); return VALUE; 
	"i64"									DOFACTORY("i64"); BEGIN(INITIAL); return VALUE; 
	.											DOFACTORY("i"); BEGIN(INITIAL); yyless(0); return VALUE; 
}

"def"										printf("def "); return DEF; 
"return"								printf("return "); return RETURN;
"end"										printf("end "); return END; 
"class"									printf("class "); return CLASS; 
"using"									printf("using "); return USING; 
"public"								printf("public "); return PUBLIC; 
"private"								printf("private "); return PRIVATE; 
"shared"								printf("shared "); return SHARED; 

"int"										printf("int "); return TYPE_INT; 
"float"									printf("float "); return TYPE_FLOAT; 
"double"								printf("double "); return TYPE_DOUBLE; 
"int8"									printf("int8 "); return TYPE_INT8; 
"uint8"									printf("uint8 "); return TYPE_UINT8;
"int16"									printf("int16 "); return TYPE_INT16; 
"uint16"								printf("uint16 "); return TYPE_UINT16; 
"int32"									printf("int32 "); return TYPE_INT32; 
"uint32"								printf("uint32 "); return TYPE_UINT32; 
"int64"									printf("int64 "); return TYPE_INT64; 
"uint64"								printf("uint64 "); return TYPE_UINT64;

"("											printf("( "); return OPEN_PAREN; 
")"											printf(") "); return CLOSE_PAREN; 
"{"											printf("{ "); return OPEN_BRACE; 
"}"											printf("} "); return CLOSE_BRACE;
"["											printf("[ "); return OPEN_BRACKET; 
"]"											printf("] "); return CLOSE_BRACKET; 


"++"										printf("++ "); return INCREMENT; 
"--"										printf("-- "); return DECREMENT; 

"="											printf("= "); return ASSIGN;
"+="										printf("+= "); return PLUS_ASSIGN;
"-="										printf("-= "); return MINUS_ASSIGN;
"*="										printf("*= "); return TIMES_ASSIGN;
"/="										printf("/= "); return DIVIDE_ASSIGN; 
"%="										printf("%%= "); return MOD_ASSIGN;

"->"										printf("-> "); return ARROW;
"<-"										printf("<- "); return ARROW_LEFT;
"."											printf(". "); return DOT;
";"											printf("; "); return SEMICOLON; 
\n 											return NEWLINE;
","											printf(", "); return COMMA;
	
"<="										printf("<= "); return LEQ;
">="										printf(">= "); return GEQ; 

"<"											printf("< "); return LT; 
">"											printf("> "); return GT;

"+"											printf("+ "); return PLUS;
"-"											printf("- "); return MINUS;
"*"											printf("* "); return TIMES; 
"/"											printf("/ "); return DIVIDE; 
"%"											printf("%% "); return MOD; 

[A-Za-z][A-Za-z0-9_]* 	printf("%%%s ", yytext); SAVESTR(); return ID;

.												printf("Unhandled: %s\n", yytext);

<<EOF>> { static int once = 0; return once++ ? 0 : NEWLINE; }

%%

%{
	// c stuff 
	#include "parser.hh"
%}

%option noyywrap

%x COMMENT 
%%

[\ \t\r]								;

"#"[^\r\n]*							;

"-"?[1-9][0-9]*"u"			printf("%%%s ", yytext);
"-"?[1-9][0-9]*"i"			printf("%%%s ", yytext);
"-"?[1-9][0-9]*"u8"			printf("%%%s ", yytext);
"-"?[1-9][0-9]*"i8"			printf("%%%s ", yytext);
"-"?[1-9][0-9]*"u16"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*"i16"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*"u32"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*"i32"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*"u64"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*"i64"		printf("%%%s ", yytext);
"-"?[1-9][0-9]*					printf("%%%s ", yytext);
"-"?[1-9][0-9]*.[0-9]+	printf("%%%s ", yytext);
[0|1]+"b"								printf("%%%s ", yytext);
"0x"[0-9A-Fa-f]+				printf("%%%s ", yytext);

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

[A-Za-z][A-Za-z0-9_]* 	printf("%%%s ", yytext);

.												printf("Unhandled: %s\n", yytext);

%%

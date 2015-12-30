/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <grove/ASTNode.h>
	#include <grove/Module.h>
	#include <grove/Block.h>
	#include <grove/Value.h>
	#include <grove/OString.h>

	#include <grove/types/UIntType.h>
	#include <grove/types/IntType.h>
	#include <grove/types/FloatType.h>
	#include <grove/types/DoubleType.h>
	#include <grove/types/BoolType.h>

	#include <grove/Parameter.h>
	#include <grove/Protectable.h>

	#include <string.h>
	#include "parser.hh"

	#define SAVELOC(node) node->setLocation(CodeLocation(module->getFile(), \
		yylloc.first_line, yylloc.last_line, yylloc.first_column, \
		yylloc.last_column));

	#define STR (std::string(yytext, yyleng))
	#define SAVESTR() yylval.str = new OString(std::string(yytext, yyleng)); SAVELOC(yylval.str);
	#define CUSTSTR(custom) yylval.str = new OString(custom); SAVELOC(yylval.str);

	// Get column and stuff for line information
	int yycolumn = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
  yycolumn += yyleng;

	#define CREATE_VAL(ty) yylval.val = new Value(yytext, ty);
	#define CREATE_VAL_BASE(ty, base) yylval.val = new Value(yytext, ty, base);

	#define YY_DECL int yylex(Module* module)

	class Module;
	extern void yyerror(Module* mod, const char *);

	int yyonce = 0;

	// defining this in here for C++
	void yyflushbuffer() { YY_FLUSH_BUFFER; yylineno = 1; }
%}

%option noyywrap
%option nounistd
%option never-interactive
%option yylineno
%option nounput
%option noinput

%x HEX

%%

[\ \t\r]										;

"#"[^\r\n]*										yycolumn = 1; // Reset column as we're on a new line.

[0|1]+"b"										CREATE_VAL_BASE(UIntType::get(module, 64), 2); return VALUE;

"0x"											BEGIN(HEX);
<HEX>{
	[0-9A-Fa-f]+								CREATE_VAL_BASE(UIntType::get(module, 64), 16); BEGIN(INITIAL); return VALUE;
	.											yyerror(module, "Invalid hex constant"); BEGIN(INITIAL);
}

[0-9][0-9]*\.[0-9]+"f" 							CREATE_VAL(FloatType::get(module)); return VALUE;
[0-9][0-9]*\.[0-9]+"d" 							CREATE_VAL(DoubleType::get(module)); return VALUE;
[0-9][0-9]*\.[0-9]+ 							CREATE_VAL(DoubleType::get(module)); return VALUE;

[0-9][0-9]*"u8"									CREATE_VAL(UIntType::get(module, 8)); return VALUE;
[0-9][0-9]*"i8"									CREATE_VAL(IntType::get(module, 8)); return VALUE;
[0-9][0-9]*"u16"								CREATE_VAL(UIntType::get(module, 16)); return VALUE;
[0-9][0-9]*"i16"								CREATE_VAL(IntType::get(module, 16)); return VALUE;
[0-9][0-9]*"u32"								CREATE_VAL(UIntType::get(module, 32)); return VALUE;
[0-9][0-9]*"i32"								CREATE_VAL(IntType::get(module, 32)); return VALUE;
[0-9][0-9]*"u64"								CREATE_VAL(UIntType::get(module, 64)); return VALUE;
[0-9][0-9]*"i64"								CREATE_VAL(IntType::get(module, 64)); return VALUE;
[0-9][0-9]*"u"									CREATE_VAL(UIntType::get(module, 64)); return VALUE;
[0-9][0-9]*"i"									CREATE_VAL(IntType::get(module, 64)); return VALUE;
[0-9][0-9]*										CREATE_VAL(IntType::get(module, 64)); return VALUE;

'.'												yylval.val = new Value(yytext[1]); return VALUE;

"false"											CREATE_VAL(BoolType::get(module)); return VALUE;
"true"											CREATE_VAL(BoolType::get(module)); return VALUE;

"def"											SAVESTR(); return DEF;
"return"										SAVESTR(); return RETURN;
"elif"											SAVESTR(); return ELIF;
"else"											SAVESTR(); return ELSE;
"end"											SAVESTR(); return END;
"if"											SAVESTR(); return IF;
"for"											SAVESTR(); return FOR;
"forever"										SAVESTR(); return FOREVER;
"loop"											SAVESTR(); return LOOP;
"continue"										SAVESTR(); return CONTINUE;
"break"											SAVESTR(); return BREAK;
"do"											SAVESTR(); return DO;
"while"											SAVESTR(); return WHILE;
"when"											SAVESTR(); return WHEN;
"unless"										SAVESTR(); return UNLESS;
"class"											SAVESTR(); return CLASS;
"using"											SAVESTR(); return USING;
"public"										SAVESTR(); return PUBLIC;
"private"										SAVESTR(); return PRIVATE;
"protected"										SAVESTR(); return PROTECTED;
"static"										SAVESTR(); return STATIC;
"extern"										SAVESTR(); return EXTERN;
"const"											SAVESTR(); return CONST_FLAG;
"enum"											SAVESTR(); return ENUM;
"this"											SAVESTR(); return THIS;
"@"												SAVESTR(); return AT;

"var"											SAVESTR(); return TYPE_VAR;
"char"											SAVESTR(); return TYPE_CHAR;
"int"											SAVESTR(); return TYPE_INT;
"uint"											SAVESTR(); return TYPE_UINT;
"float"											SAVESTR(); return TYPE_FLOAT;
"double"										SAVESTR(); return TYPE_DOUBLE;
"int8"											SAVESTR(); return TYPE_INT8;
"uint8"											SAVESTR(); return TYPE_UINT8;
"int16"											SAVESTR(); return TYPE_INT16;
"uint16"										SAVESTR(); return TYPE_UINT16;
"int32"											SAVESTR(); return TYPE_INT32;
"uint32"										SAVESTR(); return TYPE_UINT32;
"int64"											SAVESTR(); return TYPE_INT64;
"uint64"										SAVESTR(); return TYPE_UINT64;
"void"											SAVESTR(); return TYPE_VOID;

"("												SAVESTR(); return OPEN_PAREN;
")"												SAVESTR(); return CLOSE_PAREN;
"{"												SAVESTR(); return OPEN_BRACE;
"}"												SAVESTR(); return CLOSE_BRACE;
"["												SAVESTR(); return OPEN_BRACKET;
"]"												SAVESTR(); return CLOSE_BRACKET;

"..."											SAVESTR(); return VARARG;

"++"											SAVESTR(); return INCREMENT;
"--"											SAVESTR(); return DECREMENT;

"!="											SAVESTR(); return NEQUALS;
"=="											SAVESTR(); return EQUALS;

"&&"											SAVESTR(); return LOGICAL_AND;
"||"											SAVESTR(); return LOGICAL_OR;
"and"											CUSTSTR("&&"); return LOGICAL_AND;
"or"											CUSTSTR("||"); return LOGICAL_OR;

"&"												SAVESTR(); return BITWISE_AND;
"|"												SAVESTR(); return BITWISE_OR;
"^"												SAVESTR(); return BITWISE_XOR;

"="												SAVESTR(); return ASSIGN;
"+="											SAVESTR(); return PLUS_ASSIGN;
"-="											SAVESTR(); return MINUS_ASSIGN;
"*="											SAVESTR(); return TIMES_ASSIGN;
"/="											SAVESTR(); return DIVIDE_ASSIGN;
"%="											SAVESTR(); return MOD_ASSIGN;

"->"											SAVESTR(); return ARROW;
"<-"											SAVESTR(); return ARROW_LEFT;
"."												SAVESTR(); return DOT;
";"												SAVESTR(); return SEMICOLON;
\n 												yycolumn = 1; return NEWLINE; // Reset column as we're on a new line.
","												SAVESTR(); return COMMA;

"<="											SAVESTR(); return LEQ;
">="											SAVESTR(); return GEQ;

"<"												SAVESTR(); return COMP_LT;
">"												SAVESTR(); return COMP_GT;

"+"												SAVESTR(); return PLUS;
"-"												SAVESTR(); return MINUS;
"*"												SAVESTR(); return TIMES;
"/"												SAVESTR(); return DIVIDE;
"%"												SAVESTR(); return MOD;

"?"												SAVESTR(); return QUESTION;
":"												SAVESTR(); return COLON;

"mod"											CUSTSTR("%"); return MOD;

"sizeof"										SAVESTR(); return SIZEOF;

\"(\\.|[^\\"])*\"								SAVESTR(); return STRING;
[A-Za-z\x80-\xf3][A-Za-z0-9_\x80-\xf3]* 		SAVESTR(); {
	if (module->isDefinedTypeName(* yylval.str))
	{
		return TYPE_ID;
	}
	else
	{
		return IDENTIFIER;
	}
}

.												yyerror(module, "invalid token");

<<EOF>> { return yyonce++ ? 0 : NEWLINE; }

%%

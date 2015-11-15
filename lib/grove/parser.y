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
	#include <grove/FunctionCall.h>
	#include <grove/ExternFunction.h>
	#include <grove/Value.h>
	#include <grove/StrValue.h>
	#include <grove/Expression.h>
	#include <grove/ReturnStmt.h>
	#include <grove/BinOpCompare.h>
	#include <grove/BinOpArith.h>
	#include <grove/Parameter.h>
	#include <grove/IDReference.h>
	#include <grove/NegativeExpr.h>

	#include <grove/types/Type.h>
	#include <grove/types/IntType.h>
	#include <grove/types/UIntType.h>
	#include <grove/types/FloatType.h>
	#include <grove/types/DoubleType.h>
	#include <grove/types/VoidType.h>
	#include <grove/types/PointerType.h>

	#include <util/assertions.h>

	extern struct YYLTYPE yyloc;
	extern void yyerror(Module* mod, const char *s);

	extern int yylex(Module* module);
%}

%locations
//%error-verbose
%lex-param { Module* module }
%parse-param { Module* module }

%union {
	std::vector<ASTNode*>* nodes;
	std::vector<Parameter*>* params;
	std::vector<Expression*>* args;
	ASTNode* node;
	Block* block;
	Expression* expr;
	Statement* stmt;
	Value* val;
	std::string* str;
	Type* ty;
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
%type <expr> expression primary comparison arithmetic call
%type <stmt> structures function extern_function
%type <val> VALUE
%type <str> COMP_LT COMP_GT LEQ GEQ PLUS MINUS TYPE_ID STRING TIMES DIVIDE
%type <ty> type basic_type type_hint
%type <params> param_list
%type <args> arg_list

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
	| structures { $$ = $1; } /* structures: if, loops, functions, etc */
	| controls { $$ = $1; } /* controls: return, break, continue */
	| expression { $$ = $1; }
	;

structures
	: function { $$ = $1; }
	| extern_function { $$ = $1; }
	;

function
 	: DEF TYPE_ID OPEN_PAREN CLOSE_PAREN type_hint term statements END
	{
		auto func = new Function(*$2, std::vector<Parameter *>());
		func->setReturnType($5);

		for (auto stmt : *$7)
		{
			func->addStatement(stmt);
		}

		$$ = func;
	}
	| DEF TYPE_ID OPEN_PAREN param_list CLOSE_PAREN type_hint term statements END
	{
		auto func = new Function(*$2, *$4);
		func->setReturnType($6);

		for (auto stmt : *$8)
		{
			func->addStatement(stmt);
		}

		$$ = func;
	}
	;

type_hint
	: ARROW type { $$ = $2; }
	| { $$ = nullptr; }
	;

extern_function
	: EXTERN TYPE_ID OPEN_PAREN CLOSE_PAREN ARROW type
	{
		std::vector<Parameter *> params;
		$$ = new ExternFunction(*$2, params, $6);
	}
	| EXTERN TYPE_ID OPEN_PAREN param_list CLOSE_PAREN ARROW type
	{
		$$ = new ExternFunction(*$2, *$4, $7);
	}

param_list
	: param_list COMMA type TYPE_ID
	{
		$$ = $1;
		$$->push_back(new Parameter($3, *$4));
	}
	| type TYPE_ID
	{
		$$ = new std::vector<Parameter *>();
		$$->push_back(new Parameter($1, *$2));
	}

arg_list
	: arg_list COMMA expression
	{
		$$ = $1;
		$$->push_back($3);
	}
	| expression
	{
		$$ = new std::vector<Expression *>();
		$$->push_back($1);
	}

controls
	: return { $$ = $1; }
	;

expression
	: primary { $$ = $1; }
	| comparison { $$ = $1; }
	| arithmetic { $$ = $1; }
	| call { $$ = $1; }
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
	| expression TIMES expression { $$ = new BinOpArith($1, *$2, $3); }
	| expression DIVIDE expression { $$ = new BinOpArith($1, *$2, $3); }
	;

call
	: TYPE_ID OPEN_PAREN CLOSE_PAREN
	{
		std::vector<Expression *> params;
		$$ = new FunctionCall(*$1, params);
	}
	| TYPE_ID OPEN_PAREN arg_list CLOSE_PAREN
	{
		$$ = new FunctionCall(*$1, *$3);
	}
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN { $$ = $2; }
	| VALUE { $$ = $1; }
	| MINUS expression { $$ = new NegativeExpr($2); }
	| STRING { $$ = new StrValue(*$1); }
	| TYPE_ID { $$ = new IDReference(*$1); }
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

type
	: type TIMES
	{
		$$ = PointerType::get($1);
	}
	| basic_type
	{
		$$ = $1;
	}
	;

basic_type
	: TYPE_INT { $$ = IntType::get(32); }
	| TYPE_UINT { $$ = UIntType::get(32); }
	| TYPE_FLOAT { $$ = FloatType::get(); }
	| TYPE_DOUBLE { $$ = DoubleType::get(); }
	| TYPE_INT8 { $$ = IntType::get(8); }
	| TYPE_INT16 { $$ = IntType::get(16); }
	| TYPE_INT32 { $$ = IntType::get(32); }
	| TYPE_INT64 { $$ = IntType::get(64); }
	| TYPE_UINT8 { $$ = UIntType::get(8); }
	| TYPE_UINT16 { $$ = UIntType::get(16); }
	| TYPE_UINT32 { $$ = UIntType::get(32); }
	| TYPE_UINT64 { $$ = UIntType::get(64); }
	| TYPE_CHAR { $$ = IntType::get(8); }
	| TYPE_VOID { $$ = VoidType::get(); }
	| TYPE_VAR { $$ = nullptr; }
	;

%%

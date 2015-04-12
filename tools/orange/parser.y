/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

%{
	#include <iostream>
	#include <orange/orange.h>
	#include <orange/generator.h>
	#include <orange/Block.h>

	extern int yylex();
	extern struct YYLTYPE yyloc;
	extern void yyerror(const char *s);

	#define SET_LOCATION(x) CodeLocation loc = { yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column }; x->setLocation(loc);
%}

%locations
// %error-verbose

%union {
	Expression *expr;
	Statement *stmt;
	StrElement *strele;
	ASTNode *node;
	Block *block;
	ParamList *paramlist;
	AnyType *anytype;
	ArgList *arglist;
	std::string *str;
	std::vector<Block*>* blocklist;
	int token; 
	int number;
}

%start start 

%token DEF END IF ELIF ELSE TYPE_ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR TYPE_VOID
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ COMP_LT COMP_GT MOD VALUE STRING EXTERN VARARG EQUALS NEQUALS WHEN
%token UNLESS LOGICAL_AND LOGICAL_OR BITWISE_AND BITWISE_OR BITWISE_XOR
%token FOR FOREVER LOOP CONTINUE BREAK DO WHILE 
%token CONST

%type <block> statements
%type <node> statement return_or_expr
%type <expr> expression primary VALUE
%type <stmt> return function extern_function if_statement inline_if unless_statement inline_unless
%type <str> TYPE_ID basic_type 
%type <strele> ASSIGN PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN COMP_LT COMP_GT LEQ GEQ EQUALS NEQUALS PLUS MINUS TIMES DIVIDE LOGICAL_AND LOGICAL_OR BITWISE_AND BITWISE_OR BITWISE_XOR MOD
%type <paramlist> opt_func_params func_params
%type <arglist> opt_arg_list arg_list
%type <str> TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_INT16 TYPE_INT32 TYPE_INT64 TYPE_UINT8 TYPE_UINT16 TYPE_UINT32 TYPE_UINT64 TYPE_CHAR TYPE_VOID STRING
%type <anytype> any_type 
%type <number> var_ptrs
%type <blocklist> else_ifs_or_end

/* lowest to highest precedence */
%right ASSIGN ARROW_LEFT PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN

%left LOGICAL_OR 
%left LOGICAL_AND

%left EQUALS NEQUALS 
%left COMP_LT COMP_GT LEQ GEQ

%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND


%left PLUS MINUS
%left TIMES DIVIDE MOD
%left OPEN_PAREN CLOSE_PAREN

%%
	
start
	:	statements
	;

/* Create our list of statements. Find our top block and add statements to it. */
statements 		
	: statements statement { $1->addStatement($2); }
	| statement { $$ = GE::runner()->topBlock(); $$->addStatement($1); }
	;

statement 		
	:	term { $$ = nullptr; }
	| expression term { $$ = $1; }
	| function term { $$ = $1; }
	| extern_function term { $$ = $1; }
	| return term { $$ = $1; }
	| if_statement term { $$ = $1; }
	| unless_statement term { $$ = $1; }
	| inline_if term { $$ = $1; }
	| inline_unless term { $$ = $1; }
	;

expression
	: expression ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression PLUS_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression MINUS_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression TIMES_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression DIVIDE_ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	|	expression COMP_LT expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression COMP_GT expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression LEQ expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression GEQ expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression EQUALS expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression NEQUALS expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	|	expression PLUS expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	|	expression MINUS expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	|	expression TIMES expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); } 
	|	expression DIVIDE expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	| expression MOD expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	| expression LOGICAL_AND expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	| expression LOGICAL_OR expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	| expression BITWISE_AND expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	| expression BITWISE_OR expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	| expression BITWISE_XOR expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }

	| primary { $$ = $1; }
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN { $$ = $2; SET_LOCATION($$); } 
	|	VALUE { $$ = $1; SET_LOCATION($$); }
	| STRING { $$ = new StrVal(*$1); }
	|	TYPE_ID { $$ = new VarExpr(*$1); SET_LOCATION($$); }
	| TYPE_ID OPEN_PAREN opt_arg_list CLOSE_PAREN { $$ = new FuncCall(*$1, *$3); SET_LOCATION($$); }
	| MINUS expression { $$ = new NegativeExpr($2); }
	;

function
	: DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN term { 
			SymTable *tab = new SymTable(GE::runner()->symtab());
			$<stmt>$ = new FunctionStmt(*$2, *$4, tab);
			GE::runner()->pushBlock((FunctionStmt *)$$);
		} statements END { $$ = $<stmt>7; GE::runner()->popBlock(); SET_LOCATION($$); }
	| DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN ARROW any_type term {
			SymTable *tab = new SymTable(GE::runner()->symtab());
			$<stmt>$ = new FunctionStmt(*$2, $7, *$4, tab);
			GE::runner()->pushBlock((FunctionStmt *)$$);			
		} statements END { $$ = $<stmt>9; GE::runner()->popBlock(); SET_LOCATION($$); }

opt_func_params
	: func_params { $$ = $1; } 
	| { $$ = new ParamList(); }
	;

func_params
	: func_params COMMA any_type TYPE_ID { $1->push_back(new VarExpr(*$4, $3)); }
	| func_params COMMA TYPE_ID { $1->push_back(new VarExpr(*$3)); }
	| func_params COMMA VARARG { $1->setVarArg(true); }
	| any_type TYPE_ID { $$ = new ParamList(); $$->push_back(new VarExpr(*$2, $1)); } 
	| TYPE_ID { $$ = new ParamList(); $$->push_back(new VarExpr(*$1)); }
	;

extern_function
	: EXTERN any_type TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN 
	 	{
	 		$$ = new ExternFunction($2, *$3, *$5);
	 	}
	;

opt_arg_list
	: arg_list { $$ = $1; }
	| { $$ = new ArgList(); }
	;

arg_list
	: arg_list COMMA expression { $1->push_back($3); }
	| expression { $$ = new ArgList(); $$->push_back($1); }
	;

if_statement
	: IF expression term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new CondBlock($2, tab);
		GE::runner()->pushBlock((CondBlock *)$$);
	} statements { GE::runner()->popBlock(); } else_ifs_or_end { 		
		$$ = new IfStmts;

		$7->insert($7->begin(), (CondBlock*)$<stmt>4);
		for (int i = 0; i < $7->size(); i++) { 
			((IfStmts *)$$)->addBlock($7->at(i)); 
		} 

		SET_LOCATION($$);
	}
	;

else_ifs_or_end
	: ELIF expression term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new CondBlock($2, tab);
		GE::runner()->pushBlock((CondBlock *)$$);
	} statements { GE::runner()->popBlock(); } else_ifs_or_end { 		
		$7->insert($7->begin(), (CondBlock*)$<stmt>4);
		$$ = $7;
	}
	| ELSE term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Block(tab);
		GE::runner()->pushBlock((Block *)$$);
	} statements END {
		$$ = new std::vector<Block*>;
		$$->insert($$->begin(), (Block*)$<stmt>3);
		GE::runner()->popBlock();
	}
	| END {
		$$ = new std::vector<Block*>;
	}
	;

inline_if
	: return_or_expr IF expression {
		SymTable* tab = GE::runner()->topBlock()->symtab();
		CondBlock* block = new CondBlock($3, tab);
		block->addStatement($1);
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock(block); 
	}
	;

unless_statement
	: UNLESS expression term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new CondBlock($2, tab, true);
		GE::runner()->pushBlock((CondBlock *)$$);
	} statements END {
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock((CondBlock*)$<stmt>4); 
		SET_LOCATION($$);
	}

inline_unless
	: return_or_expr UNLESS expression {
		SymTable* tab = GE::runner()->topBlock()->symtab();
		CondBlock* block = new CondBlock($3, tab, true);
		block->addStatement($1);
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock(block); 
	}
	;


return_or_expr
	: return { $$ = $1; }
	| expression { $$ = $1; }
	;

return
	: RETURN { $$ = new ReturnStmt(); SET_LOCATION($$); }
	| RETURN expression { $$ = new ReturnStmt($2); SET_LOCATION($$); }
	;

term 
	: NEWLINE
	| SEMICOLON
	;

basic_type
	:	TYPE_INT 
	|	TYPE_UINT 
	|	TYPE_FLOAT 
	|	TYPE_DOUBLE 
	|	TYPE_INT8 
	|	TYPE_INT16 
	|	TYPE_INT32 
	|	TYPE_INT64 
	|	TYPE_UINT8 
	|	TYPE_UINT16 
	|	TYPE_UINT32 
	|	TYPE_UINT64 
	|	TYPE_CHAR
	| TYPE_VOID
	;

any_type
	: basic_type var_ptrs { $$ = new AnyType(*$1, $2); }
	;

var_ptrs 
	: var_ptrs TIMES { $$++; }
	| { $$ = 0; }

						 
%%

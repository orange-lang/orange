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
	std::vector<Expression*>* exprlist;
	std::vector<EnumPair>* enumlist;
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
%token CONST QUESTION COLON ENUM

%type <block> statements opt_statements
%type <node> statement return_or_expr const_var initializer
%type <expr> expression primary VALUE opt_expr primary_high opt_array
%type <stmt> return function extern_function if_statement inline_if unless_statement inline_unless variable_decl for_loop inline_loop loop_breaks enum_stmt
%type <str> TYPE_ID basic_type 
%type <strele> ASSIGN PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN COMP_LT COMP_GT LEQ GEQ EQUALS NEQUALS PLUS MINUS TIMES DIVIDE LOGICAL_AND LOGICAL_OR BITWISE_AND BITWISE_OR BITWISE_XOR MOD 
%type <strele> INCREMENT DECREMENT ARROW_LEFT
%type <paramlist> opt_func_params func_params
%type <arglist> opt_arg_list arg_list
%type <str> TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_INT16 TYPE_INT32 TYPE_INT64 TYPE_UINT8 TYPE_UINT16 TYPE_UINT32 TYPE_UINT64 TYPE_CHAR TYPE_VOID STRING
%type <anytype> any_type any_type_no_array
%type <number> var_ptrs var_arrays_and_ptrs
%type <blocklist> else_ifs_or_end
%type <exprlist> var_arrays
%type <enumlist> enum_members

/* lowest to highest precedence */
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

%%
	
start
	:	statements
	;

/* Create our list of statements. Find our top block and add statements to it. */
statements 		
	: statements statement { $1->addStatement($2); }
	| statement { $$ = GE::runner()->topBlock(); $$->addStatement($1); }
	;

opt_statements
	: statements { $$ = $1; }
	| { $$ = GE::runner()->topBlock(); }
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
	| variable_decl term { $$ = $1; }
	| const_var term { $$ = $1; }
	| for_loop term { $$ = $1; }
	| inline_loop term { $$ = $1; }
	| loop_breaks term { $$ = $1; }	
	| enum_stmt term { $$ = $1; }
	;

expression
	: expression ASSIGN expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
	| expression ARROW_LEFT expression { $$ = new BinOpExpr($1, *$2, $3); SET_LOCATION($$); }
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

	| expression QUESTION expression COLON expression { $$ = new TernaryExpr($1, $3, $5); SET_LOCATION($$); }

	| primary_high { $$ = $1; }
	| OPEN_PAREN any_type CLOSE_PAREN expression { $$ = new CastExpr($2, $4); }
	| BITWISE_AND expression { $$ = new AddressOfExpr($2); }
	;

primary_high
	: primary { $$ = $1; }
	;

primary
	: OPEN_PAREN expression CLOSE_PAREN { $$ = $2; SET_LOCATION($$); } 
	|	VALUE { $$ = $1; SET_LOCATION($$); }
	| STRING { $$ = new StrVal(*$1); }
	|	TYPE_ID { $$ = new VarExpr(*$1); SET_LOCATION($$); }
	| TYPE_ID OPEN_PAREN opt_arg_list CLOSE_PAREN { $$ = new FuncCall(*$1, *$3); SET_LOCATION($$); }
	| MINUS expression { $$ = new NegativeExpr($2); }

	| expression INCREMENT { $$ = new IncrementExpr($1, *$2, false); }
	| INCREMENT expression { $$ = new IncrementExpr($2, *$1, true); }

	| expression DECREMENT { $$ = new IncrementExpr($1, *$2, false); }
	| DECREMENT expression { $$ = new IncrementExpr($2, *$1, true); }

	| OPEN_BRACKET opt_arg_list CLOSE_BRACKET { $$ = new ArrayExpr(*$2); }
	| opt_array OPEN_BRACKET expression CLOSE_BRACKET { $$ = new ArrayAccess($1, $3); }

	| TIMES expression { $$ = new DerefExpr($2); }

	;

opt_array
	: TYPE_ID { $$ = new VarExpr(*$1); }
	| opt_array OPEN_BRACKET expression CLOSE_BRACKET { $$ = new ArrayAccess($1, $3); }
	;

function
	: DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN term { 
			SymTable *tab = new SymTable(nullptr, GE::runner()->symtab());
			$<stmt>$ = new FunctionStmt(*$2, *$4, tab);
			GE::runner()->pushBlock((FunctionStmt *)$<stmt>$);
		} opt_statements END { $$ = $<stmt>7; GE::runner()->popBlock(); SET_LOCATION($$); }
	| DEF TYPE_ID OPEN_PAREN opt_func_params CLOSE_PAREN ARROW any_type term {
			SymTable *tab = new SymTable(nullptr, GE::runner()->symtab());
			$<stmt>$ = new FunctionStmt(*$2, $7, *$4, tab);
			GE::runner()->pushBlock((FunctionStmt *)$<stmt>$);			
		} opt_statements END { $$ = $<stmt>9; GE::runner()->popBlock(); SET_LOCATION($$); }

opt_func_params
	: func_params { $$ = $1; } 
	| { $$ = new ParamList(); }
	;

func_params
	: func_params COMMA any_type_no_array TYPE_ID { $1->push_back(new VarExpr(*$4, $3)); }
	| func_params COMMA TYPE_ID { $1->push_back(new VarExpr(*$3)); }
	| func_params COMMA VARARG { $1->setVarArg(true); }
	| any_type_no_array TYPE_ID { $$ = new ParamList(); $$->push_back(new VarExpr(*$2, $1)); } 
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
		GE::runner()->pushBlock((CondBlock *)$<stmt>$);
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
		GE::runner()->pushBlock((CondBlock *)$<stmt>$);
	} statements { GE::runner()->popBlock(); } else_ifs_or_end { 		
		$7->insert($7->begin(), (CondBlock*)$<stmt>4);
		$$ = $7;
	}
	| ELSE term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Block(tab);
		GE::runner()->pushBlock((Block *)$<stmt>$);
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
		SymTable* tab = new SymTable(GE::runner()->symtab());
		CondBlock* block = new CondBlock($3, tab);
		GE::runner()->pushBlock(block);

		block->addStatement($1);
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock(block); 

		GE::runner()->popBlock();
	}
	;

unless_statement
	: UNLESS expression term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new CondBlock($2, tab, true);
		GE::runner()->pushBlock((CondBlock *)$<stmt>$);
	} statements END {
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock((CondBlock*)$<stmt>4); 
		SET_LOCATION($$);
	}

inline_unless
	: return_or_expr UNLESS expression {
		SymTable* tab = new SymTable(GE::runner()->symtab());
		CondBlock* block = new CondBlock($3, tab, true);
		block->addStatement($1);
		$$ = new IfStmts;
		((IfStmts *)$$)->addBlock(block); 
	}
	;

for_loop
	: FOR OPEN_PAREN initializer SEMICOLON opt_expr SEMICOLON opt_expr CLOSE_PAREN term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Loop($3, $5, $7, tab);
		GE::runner()->pushBlock((Loop *)$<stmt>$);
	} statements END {
		$$ = (Loop *)$<stmt>10;
		GE::runner()->popBlock();
	}
	| WHILE expression term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Loop($2, false, tab);
		GE::runner()->pushBlock((Loop *)$<stmt>$);		
	} statements END {
		$$ = (Loop *)$<stmt>4;
		GE::runner()->popBlock();
	}
	| FOREVER DO term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Loop(tab);
		GE::runner()->pushBlock((Loop *)$<stmt>$);				
	} statements END {
		$$ = (Loop *)$<stmt>4;
		GE::runner()->popBlock();
	}
	| DO term {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$<stmt>$ = new Loop(nullptr, true, tab);
		GE::runner()->pushBlock((Loop *)$<stmt>$);				
	} statements END WHILE expression {
		$$ = (Loop *)$<stmt>3;
		((Loop *)$$)->setCondition($7);
		GE::runner()->popBlock();
	} 
	;

inline_loop
	: return_or_expr FOR OPEN_PAREN initializer SEMICOLON opt_expr SEMICOLON opt_expr CLOSE_PAREN {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$$ = new Loop($4, $6, $8, tab);
		((Loop *)$$)->addStatement($1);		
	}
	| return_or_expr WHILE expression {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$$ = new Loop($3, false, tab);
		((Loop *)$$)->addStatement($1);				
	}
	| return_or_expr FOREVER {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		$$ = new Loop(tab);
		((Loop *)$$)->addStatement($1);
	}

loop_breaks
	: LOOP { $$ = new LoopSkip(true); }
	| CONTINUE { $$ = new LoopSkip(true); }
	| BREAK { $$ = new LoopSkip(false); }
	;

enum_stmt
	: ENUM TYPE_ID term enum_members END {
		EnumStmt* enumStmt = new EnumStmt(*$2);
		for (auto pair : *$4) {
			if (pair.value == nullptr) {
				enumStmt->addEnum(pair.name);
			} else {
				enumStmt->addEnum(pair.name, pair.value);
			}
		}

		$$ = (Statement *)enumStmt;
	}

enum_members
	: enum_members TYPE_ID term { $1->push_back(EnumPair(*$2)); }
	| enum_members TYPE_ID EQUALS VALUE term { $1->push_back(EnumPair(*$2, (BaseVal*)$4)); }
	| TYPE_ID term { $$ = new std::vector<EnumPair>; $$->push_back(EnumPair(*$1)); }
	| TYPE_ID EQUALS VALUE term { $$ = new std::vector<EnumPair>; $$->push_back(EnumPair(*$1, (BaseVal*)$3)); }
	;

initializer
	: variable_decl { $$ = $1; } 
	| expression { $$ = $1; }
	;

opt_expr 
	: expression { $$ = $1; }
	| { $$ = nullptr; }

variable_decl
	: any_type TYPE_ID { $$ = new ExplicitDeclStmt(new VarExpr(*$2, $1)); }
	| any_type TYPE_ID ASSIGN expression  { $$ = new ExplicitDeclStmt(new VarExpr(*$2, $1), $4); }
	;

const_var 
	: CONST any_type TYPE_ID ASSIGN expression { $$ = new ExplicitDeclStmt(new VarExpr(*$3, $2, true), $5); }
	| CONST TYPE_ID ASSIGN expression { $$ = new BinOpExpr(new VarExpr(*$2, true), "=", $4); }
	;

return_or_expr
	: return { $$ = $1; }
	| expression { $$ = $1; }
	| loop_breaks { $$ = $1; }
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
	: basic_type var_arrays var_ptrs { $$ = new AnyType(*$1, *$2, $3); }
	;

any_type_no_array 
	: basic_type var_arrays_and_ptrs { $$ = new AnyType(*$1, std::vector<int>(), $2); }
	;

var_arrays_and_ptrs
	: var_arrays_and_ptrs TIMES { $$++; }
	| var_arrays_and_ptrs OPEN_BRACKET opt_primary CLOSE_BRACKET { $$++; }
	| { $$ = 0; }
	; 

opt_primary
	: primary 
	| ;

var_arrays
	: var_arrays OPEN_BRACKET expression CLOSE_BRACKET { $1->push_back($3); }
	| { $$ = new std::vector<Expression *>(); }

var_ptrs 
	: var_ptrs TIMES { $$++; }
	| { $$ = 0; }
	| OPEN_BRACKET CLOSE_BRACKET { $$ = 1; }

						 
%%

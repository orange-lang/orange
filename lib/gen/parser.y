%{
	// c stuff 
	#include <iostream>
	#include <gen/gen.h>
	#include <gen/generator.h>

	extern int yylex();
	void yyerror(const char *s) { std::cerr << s << std::endl; exit(1); }

	Block *globalBlock = nullptr; 
	typedef CodeGenerator CG;
%}

%union {
	IfStatement *ifstmt;
	CondBlock *cblock;
	DerefId *did;
	Block *block; 
	Statement *stmt; 
	ArgList *arglist;
	AnyType *anytype;
	ExprList *exprlist;
	ArgExpr *argexpr;
	SymTable *symtab;
	FunctionStatement *fstmt;
	Expression *expr;
	std::string *str;
	std::vector<BaseVal *>* values;
	int token; 
	int number;
}

%start start 

%token DEF END IF ELIF ELSE TYPE_ID OPEN_PAREN CLOSE_PAREN TYPE COMMA
%token TIMES NUMBER DIVIDE MINUS PLUS NEWLINE SEMICOLON
%token TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%token TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR
%token RETURN CLASS USING PUBLIC SHARED PRIVATE OPEN_BRACE CLOSE_BRACE 
%token OPEN_BRACKET CLOSE_BRACKET INCREMENT DECREMENT ASSIGN PLUS_ASSIGN
%token MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN ARROW ARROW_LEFT
%token DOT LEQ GEQ COMP_LT COMP_GT MOD VALUE STRING EXTERN VARARG EQUALS NEQUALS WHEN
%token UNLESS LOGICAL_AND LOGICAL_OR

%type <ifstmt> if_statement opt_else inline_if inline_unless unless 
%type <block> statements opt_statements
%type <stmt> statement extern return_stmt expr_or_ret
%type <expr> expression primary VALUE opt_expr declaration opt_eq opt_num
%type <did> dereference
%type <fstmt> function opt_id 
%type <argexpr> opt_arg arg_end
%type <arglist> opt_args arg_list opt_parens
%type <exprlist> expr_list optexprlist
%type <str> TYPE_ID DEF END TYPE TYPE_INT TYPE_UINT TYPE_FLOAT TYPE_DOUBLE TYPE_INT8 TYPE_UINT8 TYPE_INT16
%type <str> TYPE_UINT16 TYPE_INT32 TYPE_UINT32 TYPE_INT64 TYPE_UINT64 TYPE_CHAR basic_type STRING
%type <anytype> type
%type <number> var_ptrs
%type <values> arrays

%right ASSIGN ARROW_LEFT PLUS_ASSIGN MINUS_ASSIGN TIMES_ASSIGN DIVIDE_ASSIGN

%left COMP_LT COMP_GT LEQ GEQ
%left EQUALS NEQUALS 
%left LOGICAL_AND
%left LOGICAL_OR

%left PLUS MINUS
%left TIMES DIVIDE
%left OPEN_PAREN CLOSE_PAREN
%left OPEN_BRACKET

%right IF

%left INCREMENT DECREMENT

%%
	
start
	:	{ auto s = new SymTable(); CG::Symtabs.push(s); } 
		statements 
		{ globalBlock = $2; globalBlock->symtab = CG::Symtabs.top(); CG::Symtabs.pop(); } 
	;

statements 		
	:	statements statement { if ($2) $1->statements.push_back($2); } 
	|	statement { $$ = new Block(); if ($1) $$->statements.push_back($1); }
	;

opt_statements
	: statements { $$ = $1; }
	| { $$ = new Block(); }

statement 		
	:	function term { $$ = $1; }
	|	extern term { $$ = (Statement *)$1; }
	|	expression term { $$ = (Statement *)$1; } 
	| inline_if term { $$ = $1; }
	| inline_unless term { $$ = $1; }
	| unless term { $$ = $1; }
	|	declaration term { $$ = (Statement *)$1; }
	| return_stmt term { $$ = $1; }
	| term { $$ = nullptr; }
	;

return_stmt
	: RETURN opt_expr { $$ = (Statement *)(new ReturnExpr($2)); }

inline_unless 
	: expr_or_ret UNLESS expression
		{
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			CondBlock *b = new CondBlock($3, true); 
			b->statements.push_back($1); 
			b->symtab = CG::Symtabs.top(); 

			CG::Symtabs.pop();

			$$ = new IfStatement;
			$$->blocks.push_back(b);
		}
	;

inline_if
	:	expr_or_ret IF expression
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			CondBlock *b = new CondBlock($3); 
			b->statements.push_back($1); 
			b->symtab = CG::Symtabs.top(); 

			CG::Symtabs.pop();

			$$ = new IfStatement;
			$$->blocks.push_back(b);
		} 
	;

expr_or_ret
	: expression { $$ = $1; }
	| return_stmt { $$ = $1; }

opt_expr			
	:	expression { $$ = $1; }
	| %prec IF { $$ = nullptr; }

term			
	:	NEWLINE 
	|	SEMICOLON 
	;

extern		
	:	EXTERN type TYPE_ID OPEN_PAREN opt_args CLOSE_PAREN 
		{ $$ = new ExternFunction($2, *$3, $5); }
	;

unless 
	: UNLESS expression term opt_statements END 
		{
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			CondBlock *b = new CondBlock($2, $4, true); 
			b->symtab = CG::Symtabs.top(); 

			CG::Symtabs.pop();

			$$ = new IfStatement;
			$$->blocks.insert($$->blocks.begin(), b);
		}

function
	:	DEF opt_id term opt_statements END 
		{ $$ = $2; $$->body = $4; $$->body->symtab = CG::Symtabs.top(); CG::Symtabs.pop(); }
	;

opt_id			
	:	TYPE_ID opt_parens 
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);
			$$ = new FunctionStatement($1, $2, nullptr); 
		} 
	|	opt_parens 
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);
			$$ = new FunctionStatement(nullptr, $1, nullptr); 
		} 
	;

opt_parens
	:	OPEN_PAREN opt_args CLOSE_PAREN { $$ = $2; } 
	|	{ $$ = nullptr; }
	;

opt_args 		
	:	arg_list { $$ = $1; }
	|	{ $$ = nullptr; }
	;

arg_list
	:	arg_list COMMA arg_end { if ($3) { $1->push_back($3); } else { $1->isVarArg = true; } } 	
	|	opt_arg { $$ = new ArgList(); $$->push_back($1); }
	;

arg_end			
	:	VARARG { $$ = nullptr; }
	|	opt_arg { $$ = $1; }
	;

opt_arg
	:	type TYPE_ID { $$ = new ArgExpr($1, $2); } 
	|	TYPE_ID { $$ = new ArgExpr(nullptr, $1); } 
	;

type
	:	basic_type var_ptrs arrays { $$ = new AnyType($1, $2, $3); }
	;

var_ptrs
	:	var_ptrs TIMES { $$ = $1 + 1; }
	|	{ $$ = 0; }
	;

arrays
	:	OPEN_BRACKET opt_num CLOSE_BRACKET arrays { $$ = $4; $$->insert($$->begin(), (BaseVal *)$2); } 
	|	{ $$ = new std::vector<BaseVal *>; }
	;

opt_num
	: VALUE { $$ = $1; }
	| { $$ = nullptr; }

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
	;

declaration	
	:	type TYPE_ID opt_eq { $$ = new VarDeclExpr($1, $2, $3); }
	;

opt_eq 
	:	ASSIGN expression { $$ = $2; } 
	|	{ $$ = nullptr; }
	;

expression 	
	:	expression ASSIGN expression { $$ = new BinOpExpr($1, "=" , $3); } 
	|	expression ARROW_LEFT expression { $$ = new BinOpExpr($1, "<-", $3); }
	|	expression PLUS_ASSIGN expression { $$ = new BinOpExpr($1, "+=", $3); }
	|	expression MINUS_ASSIGN expression { $$ = new BinOpExpr($1, "-=", $3); }
	|	expression TIMES_ASSIGN expression { $$ = new BinOpExpr($1, "*=", $3); }
	|	expression DIVIDE_ASSIGN expression { $$ = new BinOpExpr($1, "/=", $3); }
	| expression %prec INCREMENT INCREMENT { $$ = new IncrementExpr($1, "++", false); }
	| expression %prec DECREMENT DECREMENT { $$ = new IncrementExpr($1, "--", false); }
	| %prec INCREMENT INCREMENT expression { $$ = new IncrementExpr($2, "++", true); }
	| %prec DECREMENT DECREMENT expression { $$ = new IncrementExpr($2, "--", true); } 

	|	expression COMP_LT expression { $$ = new BinOpExpr($1, "<" , $3); }
	|	expression COMP_GT expression { $$ = new BinOpExpr($1, ">" , $3); }
	|	expression LEQ expression { $$ = new BinOpExpr($1, "<=", $3); }
	|	expression GEQ expression { $$ = new BinOpExpr($1, ">=", $3); }
	|	expression EQUALS expression { $$ = new BinOpExpr($1, "==", $3); }
	|	expression NEQUALS expression { $$ = new BinOpExpr($1, "!=", $3); }

	| expression LOGICAL_AND expression { $$ = new BinOpExpr($1, "&&", $3); }
	| expression LOGICAL_OR expression { $$ = new BinOpExpr($1, "||", $3); }
	
	|	expression PLUS expression { $$ = new BinOpExpr($1, "+" , $3); }
	|	expression MINUS expression { $$ = new BinOpExpr($1, "-" , $3); }

	|	expression TIMES expression { $$ = new BinOpExpr($1, "*" , $3); } 
	|	expression DIVIDE expression { $$ = new BinOpExpr($1, "/" , $3); }

	|	primary { $$ = $1; }
	;


primary			
	:	OPEN_PAREN expression CLOSE_PAREN { $$ = $2; } 
	|	OPEN_PAREN type CLOSE_PAREN primary { $$ = new CastExpr($2, $4); }
	|	VALUE { $$ = $1; }
	|	TYPE_ID OPEN_PAREN optexprlist CLOSE_PAREN { $$ = new FuncCallExpr(*$1, $3); }
	|	TYPE_ID { $$ = new VarExpr(*$1); }
	|	STRING { $$ = new StrVal(*$1); }
	|	if_statement { $$ = $1; }
	|	TIMES dereference { $$ = $2; $<did>$->pointers++; }
	|	MINUS primary { $$ = new NegativeExpr($2); }
	| OPEN_BRACKET expr_list CLOSE_BRACKET { $$ = new ArrayExpr($2); }
	| primary OPEN_BRACKET expression CLOSE_BRACKET { $$ = new ArrayAccess($1, $3); }
	;

dereference 
	:	TIMES dereference { $$ = $2; $$->pointers++; } 
	|	TYPE_ID { $$ = new DerefId(new VarExpr(*$1)); }
	;

if_statement
	: IF expression term opt_statements opt_else 
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			$$ = $5; 
			CondBlock *b = new CondBlock($2, $4); 
			$$->blocks.insert($$->blocks.begin(), b);
			b->symtab = CG::Symtabs.top(); 
			CG::Symtabs.pop(); 
		}
	;

opt_else
	:	ELIF expression term opt_statements opt_else 
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			$$ = $5; 
			CondBlock *b = new CondBlock($2, $4); 
			$$->blocks.insert($$->blocks.begin(), b);
			b->symtab = CG::Symtabs.top(); 
			CG::Symtabs.pop(); 
		}	
	|	ELSE term opt_statements END
		{ 
			auto s = new SymTable(); s->parent = CG::Symtabs.top(); CG::Symtabs.push(s);

			$$ = new IfStatement; 
			$$->blocks.insert($$->blocks.begin(), $3); 
			
			$3->symtab = CG::Symtabs.top(); 
			CG::Symtabs.pop(); 
		}
	|	END { $$ = new IfStatement; }
	;

optexprlist 
	:	expr_list { $$ = $1; }
	|	{ $$ = new ExprList(); }
	;

expr_list		
	:	expr_list COMMA expression { $1->push_back($3); }	
	|	expression { $$ = new ExprList(); $$->push_back($1); }
	;
						 
%%

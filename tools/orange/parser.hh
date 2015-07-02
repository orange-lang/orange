/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_USERS_ROBERT_DEV_ORANGE_TOOLS_ORANGE_PARSER_HH_INCLUDED
# define YY_YY_USERS_ROBERT_DEV_ORANGE_TOOLS_ORANGE_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DEF = 258,
    END = 259,
    IF = 260,
    ELIF = 261,
    ELSE = 262,
    TYPE_ID = 263,
    OPEN_PAREN = 264,
    CLOSE_PAREN = 265,
    TYPE = 266,
    COMMA = 267,
    TIMES = 268,
    NUMBER = 269,
    DIVIDE = 270,
    MINUS = 271,
    PLUS = 272,
    NEWLINE = 273,
    SEMICOLON = 274,
    TYPE_INT = 275,
    TYPE_UINT = 276,
    TYPE_FLOAT = 277,
    TYPE_DOUBLE = 278,
    TYPE_INT8 = 279,
    TYPE_UINT8 = 280,
    TYPE_INT16 = 281,
    TYPE_UINT16 = 282,
    TYPE_INT32 = 283,
    TYPE_UINT32 = 284,
    TYPE_INT64 = 285,
    TYPE_UINT64 = 286,
    TYPE_CHAR = 287,
    TYPE_VOID = 288,
    TYPE_VAR = 289,
    RETURN = 290,
    CLASS = 291,
    USING = 292,
    PUBLIC = 293,
    SHARED = 294,
    PRIVATE = 295,
    OPEN_BRACE = 296,
    CLOSE_BRACE = 297,
    OPEN_BRACKET = 298,
    CLOSE_BRACKET = 299,
    INCREMENT = 300,
    DECREMENT = 301,
    ASSIGN = 302,
    PLUS_ASSIGN = 303,
    MINUS_ASSIGN = 304,
    TIMES_ASSIGN = 305,
    DIVIDE_ASSIGN = 306,
    MOD_ASSIGN = 307,
    ARROW = 308,
    ARROW_LEFT = 309,
    DOT = 310,
    LEQ = 311,
    GEQ = 312,
    COMP_LT = 313,
    COMP_GT = 314,
    MOD = 315,
    VALUE = 316,
    STRING = 317,
    EXTERN = 318,
    VARARG = 319,
    EQUALS = 320,
    NEQUALS = 321,
    WHEN = 322,
    UNLESS = 323,
    LOGICAL_AND = 324,
    LOGICAL_OR = 325,
    BITWISE_AND = 326,
    BITWISE_OR = 327,
    BITWISE_XOR = 328,
    FOR = 329,
    FOREVER = 330,
    LOOP = 331,
    CONTINUE = 332,
    BREAK = 333,
    DO = 334,
    WHILE = 335,
    CONST = 336,
    QUESTION = 337,
    COLON = 338,
    ENUM = 339,
    SIZEOF = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1915  */

	Expression *expr;
	Statement *stmt;
	StrElement *strele;
	ASTNode *node;
	Block *block;
	ParamList *paramlist;
	OrangeTy *orangety;
	ArgList *arglist;
	std::string *str;
	std::vector<Block*>* blocklist;
	std::vector<Expression*>* exprlist;
	std::vector<EnumPair>* enumlist;
	std::vector<DeclPair>* declpairlist;
	int token; 
	int number;

#line 158 "/Users/robert/dev/orange/tools/orange/parser.hh" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_USERS_ROBERT_DEV_ORANGE_TOOLS_ORANGE_PARSER_HH_INCLUDED  */

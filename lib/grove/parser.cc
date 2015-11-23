/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
/* Tokens.  */
#define DEF 258
#define END 259
#define IF 260
#define ELIF 261
#define ELSE 262
#define TYPE_ID 263
#define OPEN_PAREN 264
#define CLOSE_PAREN 265
#define TYPE 266
#define COMMA 267
#define TIMES 268
#define NUMBER 269
#define DIVIDE 270
#define MINUS 271
#define PLUS 272
#define NEWLINE 273
#define SEMICOLON 274
#define TYPE_INT 275
#define TYPE_UINT 276
#define TYPE_FLOAT 277
#define TYPE_DOUBLE 278
#define TYPE_INT8 279
#define TYPE_UINT8 280
#define TYPE_INT16 281
#define TYPE_UINT16 282
#define TYPE_INT32 283
#define TYPE_UINT32 284
#define TYPE_INT64 285
#define TYPE_UINT64 286
#define TYPE_CHAR 287
#define TYPE_VOID 288
#define TYPE_VAR 289
#define RETURN 290
#define CLASS 291
#define USING 292
#define PUBLIC 293
#define SHARED 294
#define PRIVATE 295
#define OPEN_BRACE 296
#define CLOSE_BRACE 297
#define OPEN_BRACKET 298
#define CLOSE_BRACKET 299
#define INCREMENT 300
#define DECREMENT 301
#define ASSIGN 302
#define PLUS_ASSIGN 303
#define MINUS_ASSIGN 304
#define TIMES_ASSIGN 305
#define DIVIDE_ASSIGN 306
#define MOD_ASSIGN 307
#define ARROW 308
#define ARROW_LEFT 309
#define DOT 310
#define LEQ 311
#define GEQ 312
#define COMP_LT 313
#define COMP_GT 314
#define MOD 315
#define VALUE 316
#define STRING 317
#define EXTERN 318
#define VARARG 319
#define EQUALS 320
#define NEQUALS 321
#define WHEN 322
#define UNLESS 323
#define LOGICAL_AND 324
#define LOGICAL_OR 325
#define BITWISE_AND 326
#define BITWISE_OR 327
#define BITWISE_XOR 328
#define FOR 329
#define FOREVER 330
#define LOOP 331
#define CONTINUE 332
#define BREAK 333
#define DO 334
#define WHILE 335
#define CONST 336
#define QUESTION 337
#define COLON 338
#define ENUM 339
#define SIZEOF 340




/* Copy the first part of user declarations.  */
#line 9 "/Users/robert/dev/orange/lib/grove/parser.y"

	#include <grove/Module.h>
	#include <grove/ASTNode.h>
	#include <grove/Block.h>
	#include <grove/CondBlock.h>
	#include <grove/Function.h>
	#include <grove/IfStmt.h>
	#include <grove/FunctionCall.h>
	#include <grove/ExternFunction.h>
	#include <grove/Value.h>
	#include <grove/StrValue.h>
	#include <grove/Expression.h>
	#include <grove/ReturnStmt.h>
	#include <grove/BinOpCompare.h>
	#include <grove/BinOpArith.h>
	#include <grove/BinOpAssign.h>
	#include <grove/BinOpAndOr.h>
	#include <grove/Parameter.h>
	#include <grove/IDReference.h>
	#include <grove/NegativeExpr.h>
	#include <grove/VarDecl.h>
	#include <grove/IncrementExpr.h>
	#include <grove/Loop.h>
	#include <grove/LoopTerminator.h>
	#include <grove/DerefExpr.h>
	#include <grove/ReferenceExpr.h>
	#include <grove/CastExpr.h>
	#include <grove/ArrayValue.h>
	#include <grove/ArrayAccessExpr.h>
	#include <grove/TernaryExpr.h>

	#include <grove/types/Type.h>
	#include <grove/types/IntType.h>
	#include <grove/types/UIntType.h>
	#include <grove/types/FloatType.h>
	#include <grove/types/DoubleType.h>
	#include <grove/types/VoidType.h>
	#include <grove/types/PointerType.h>
	#include <grove/types/VarType.h>
	#include <grove/types/ArrayType.h>
	#include <grove/types/VariadicArrayType.h>

	#include <util/assertions.h>

	extern struct YYLTYPE yyloc;
	extern void yyerror(Module* mod, const char *s);

	extern int yylex(Module* module);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 64 "/Users/robert/dev/orange/lib/grove/parser.y"
{
	std::vector<ASTNode*>* nodes;
	std::vector<Parameter*>* params;
	std::vector<Expression*>* args;
	std::vector<Block*>* blocks;
	std::vector<Expression*>* exprs;
	std::vector<std::tuple<std::string, Expression*>>* pairs;
	ASTNode* node;
	Block* block;
	Expression* expr;
	Statement* stmt;
	Value* val;
	std::string* str;
	Type* ty;
}
/* Line 193 of yacc.c.  */
#line 332 "/Users/robert/dev/orange/lib/grove/parser.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 357 "/Users/robert/dev/orange/lib/grove/parser.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1660

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  139
/* YYNRULES -- Number of states.  */
#define YYNSTATES  278

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    18,
      21,    24,    27,    29,    32,    34,    36,    38,    40,    42,
      44,    46,    48,    50,    52,    61,    71,    74,    75,    82,
      90,   100,   106,   112,   117,   119,   125,   129,   133,   137,
     141,   153,   159,   165,   172,   182,   192,   196,   200,   203,
     206,   208,   209,   211,   212,   217,   220,   224,   226,   228,
     230,   232,   234,   236,   238,   240,   242,   244,   246,   250,
     254,   258,   262,   266,   270,   274,   278,   282,   286,   290,
     294,   298,   302,   306,   310,   314,   318,   322,   326,   330,
     334,   337,   340,   343,   346,   352,   356,   361,   365,   367,
     370,   372,   374,   377,   380,   385,   389,   394,   398,   400,
     402,   405,   408,   412,   418,   420,   424,   426,   428,   431,
     433,   436,   439,   443,   448,   452,   454,   456,   458,   460,
     462,   464,   466,   468,   470,   472,   474,   476,   478,   480
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,    88,    -1,    88,    90,    -1,    88,    91,
      -1,    90,    -1,    91,    -1,    88,    -1,    -1,    93,   120,
      -1,   108,   120,    -1,   109,   120,    -1,   120,    -1,   118,
     120,    -1,   118,    -1,   109,    -1,    94,    -1,    96,    -1,
      97,    -1,    99,    -1,   100,    -1,   101,    -1,   102,    -1,
     103,    -1,     3,     8,     9,    10,    95,   120,    89,     4,
      -1,     3,     8,     9,   106,    10,    95,   120,    89,     4,
      -1,    53,   121,    -1,    -1,    63,     8,     9,    10,    53,
     121,    -1,    63,     8,     9,   106,    10,    53,   121,    -1,
      63,     8,     9,   106,    12,    64,    10,    53,   121,    -1,
       5,   109,   120,    88,    98,    -1,     6,   109,   120,    88,
      98,    -1,     7,   120,    88,     4,    -1,     4,    -1,    68,
     109,   120,    88,     4,    -1,   108,     5,   109,    -1,   109,
       5,   109,    -1,   108,    68,   109,    -1,   109,    68,   109,
      -1,    74,     9,   104,    19,   105,    19,   105,    10,   120,
      88,     4,    -1,    80,   109,   120,    88,     4,    -1,    75,
      79,   120,    88,     4,    -1,    79,   120,    88,     4,    80,
     109,    -1,   108,    74,     9,   104,    19,   105,    19,   105,
      10,    -1,   109,    74,     9,   104,    19,   105,    19,   105,
      10,    -1,   108,    80,   109,    -1,   109,    80,   109,    -1,
     108,    75,    -1,   109,    75,    -1,    92,    -1,    -1,   109,
      -1,    -1,   106,    12,   121,     8,    -1,   121,     8,    -1,
     107,    12,   109,    -1,   109,    -1,   117,    -1,    77,    -1,
      78,    -1,    76,    -1,   115,    -1,   110,    -1,   111,    -1,
     114,    -1,   112,    -1,   113,    -1,   109,    58,   109,    -1,
     109,    59,   109,    -1,   109,    56,   109,    -1,   109,    57,
     109,    -1,   109,    65,   109,    -1,   109,    66,   109,    -1,
     109,    69,   109,    -1,   109,    70,   109,    -1,   109,    17,
     109,    -1,   109,    16,   109,    -1,   109,    13,   109,    -1,
     109,    15,   109,    -1,   109,    60,   109,    -1,   109,    71,
     109,    -1,   109,    72,   109,    -1,   109,    73,   109,    -1,
     109,    47,   109,    -1,   109,    48,   109,    -1,   109,    49,
     109,    -1,   109,    50,   109,    -1,   109,    51,   109,    -1,
     109,    52,   109,    -1,   109,    45,    -1,   109,    46,    -1,
      45,   109,    -1,    46,   109,    -1,   109,    82,   109,    83,
     109,    -1,     8,     9,    10,    -1,     8,     9,   107,    10,
      -1,     9,   109,    10,    -1,    61,    -1,    16,   109,    -1,
      62,    -1,     8,    -1,    13,   109,    -1,    71,   109,    -1,
       9,   121,    10,   109,    -1,    43,   116,    44,    -1,   109,
      43,   109,    44,    -1,   116,    12,   109,    -1,   109,    -1,
      35,    -1,    35,   109,    -1,   121,   119,    -1,   119,    12,
       8,    -1,   119,    12,     8,    47,   109,    -1,     8,    -1,
       8,    47,   109,    -1,    18,    -1,    19,    -1,   121,    13,
      -1,   123,    -1,    81,   121,    -1,   123,   122,    -1,   123,
      43,    44,    -1,   122,    43,   109,    44,    -1,    43,   109,
      44,    -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    26,    -1,    28,    -1,    30,    -1,    25,    -1,
      27,    -1,    29,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   149,   158,   168,   177,   190,   191,   195,
     196,   197,   198,   202,   209,   213,   220,   221,   222,   223,
     224,   225,   226,   227,   231,   243,   258,   259,   263,   268,
     272,   279,   302,   315,   327,   334,   349,   359,   372,   382,
     395,   407,   418,   429,   443,   450,   457,   463,   469,   475,
     487,   488,   492,   493,   497,   502,   509,   514,   521,   522,
     523,   524,   528,   529,   530,   531,   532,   533,   537,   538,
     539,   540,   541,   542,   544,   545,   549,   550,   551,   552,
     553,   555,   556,   557,   559,   560,   561,   562,   563,   564,
     568,   569,   570,   571,   575,   582,   587,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   603,   607,   612,   621,
     625,   632,   645,   650,   655,   660,   667,   668,   672,   676,
     680,   684,   716,   723,   728,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   750
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEF", "END", "IF", "ELIF", "ELSE",
  "TYPE_ID", "OPEN_PAREN", "CLOSE_PAREN", "TYPE", "COMMA", "TIMES",
  "NUMBER", "DIVIDE", "MINUS", "PLUS", "NEWLINE", "SEMICOLON", "TYPE_INT",
  "TYPE_UINT", "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_INT8", "TYPE_UINT8",
  "TYPE_INT16", "TYPE_UINT16", "TYPE_INT32", "TYPE_UINT32", "TYPE_INT64",
  "TYPE_UINT64", "TYPE_CHAR", "TYPE_VOID", "TYPE_VAR", "RETURN", "CLASS",
  "USING", "PUBLIC", "SHARED", "PRIVATE", "OPEN_BRACE", "CLOSE_BRACE",
  "OPEN_BRACKET", "CLOSE_BRACKET", "INCREMENT", "DECREMENT", "ASSIGN",
  "PLUS_ASSIGN", "MINUS_ASSIGN", "TIMES_ASSIGN", "DIVIDE_ASSIGN",
  "MOD_ASSIGN", "ARROW", "ARROW_LEFT", "DOT", "LEQ", "GEQ", "COMP_LT",
  "COMP_GT", "MOD", "VALUE", "STRING", "EXTERN", "VARARG", "EQUALS",
  "NEQUALS", "WHEN", "UNLESS", "LOGICAL_AND", "LOGICAL_OR", "BITWISE_AND",
  "BITWISE_OR", "BITWISE_XOR", "FOR", "FOREVER", "LOOP", "CONTINUE",
  "BREAK", "DO", "WHILE", "CONST", "QUESTION", "COLON", "ENUM", "SIZEOF",
  "$accept", "start", "statements", "opt_statements", "statement",
  "compound_statement", "valued", "structures", "function", "type_hint",
  "extern_function", "ifs", "else_if_or_end", "unless", "inline_if",
  "inline_unless", "for_loop", "inline_for_loop", "opt_valued",
  "opt_expression", "param_list", "arg_list", "controls", "expression",
  "comparison", "arithmetic", "increment", "ternary", "call", "primary",
  "expr_list", "return", "var_decl", "var_decl_list", "term", "type",
  "array_def_list", "basic_type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    88,    88,    89,    89,    90,
      90,    90,    90,    91,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    98,    98,    98,    99,   100,   100,   101,   101,
     102,   102,   102,   102,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   117,
     117,   118,   119,   119,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     0,     2,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     8,     9,     2,     0,     6,     7,
       9,     5,     5,     4,     1,     5,     3,     3,     3,     3,
      11,     5,     5,     6,     9,     9,     3,     3,     2,     2,
       1,     0,     1,     0,     4,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     5,     3,     4,     3,     1,     2,
       1,     1,     2,     2,     4,     3,     4,     3,     1,     1,
       2,     2,     3,     5,     1,     3,     1,     1,     2,     1,
       2,     2,     3,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   101,     0,     0,     0,   116,   117,   125,
     126,   127,   128,   129,   133,   130,   134,   131,   135,   132,
     136,   137,   138,   139,   109,     0,     0,     0,    98,   100,
       0,     0,     0,     0,     0,    61,    59,    60,     0,     0,
       0,     0,     2,     5,     6,     0,    16,    17,    18,    19,
      20,    21,    22,    23,     0,     0,    63,    64,    66,    67,
      65,    62,    58,     0,    12,     0,   119,     0,     0,     0,
       0,     0,   102,    99,   110,   108,     0,    92,    93,     0,
       0,   103,    51,     0,     0,     0,   120,     1,     3,     4,
       9,     0,     0,     0,    48,     0,    10,     0,     0,     0,
       0,     0,     0,    90,    91,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,    11,    13,
     114,   118,   111,     0,   121,     0,     0,    95,     0,    57,
      97,     0,     0,   105,     0,     0,    50,     0,    15,    14,
       0,     0,     0,    36,    38,    51,    46,    37,    78,    79,
      77,    76,     0,    84,    85,    86,    87,    88,    89,    70,
      71,    68,    69,    80,    72,    73,    39,    74,    75,    81,
      82,    83,    51,    47,     0,     0,     0,   122,     0,     0,
      27,     0,     0,     0,    96,     0,   104,   107,     0,     0,
       0,    53,     0,     0,     0,     0,   106,     0,     0,   115,
     112,   124,     0,     0,     0,    27,     0,    55,    34,     0,
       0,    31,    56,     0,     0,     0,    35,     0,    52,    42,
       0,    41,    53,    53,    94,     0,   123,    26,     8,     0,
       0,     0,     0,    28,     0,     0,    53,    43,     0,     0,
     113,     7,     0,     8,    54,     0,     0,    29,     0,     0,
      53,    53,    24,     0,     0,    33,     0,     0,     0,     0,
      25,    32,    30,     0,    44,    45,     0,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    41,   251,   252,    43,    44,   146,    45,    46,   214,
      47,    48,   221,    49,    50,    51,    52,    53,   147,   227,
     191,   138,    54,    55,    56,    57,    58,    59,    60,    61,
      76,    62,    63,   132,    64,    65,   134,    66
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const yytype_int16 yypact[] =
{
     882,     5,  1256,    38,   989,  1256,  1256,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  1256,  1256,  1256,  1256,  -175,  -175,
      43,  1256,  1256,    46,   -33,  -175,  -175,  -175,    23,  1256,
    1362,    56,   882,  -175,  -175,    23,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,    25,   921,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,    23,  -175,    -1,    17,    62,  1177,   186,
    1026,    -7,    61,   108,  1421,  1421,    -8,  -175,  -175,    72,
    1177,    18,   989,    23,   882,  1177,    60,  -175,  -175,  -175,
    -175,  1256,  1256,    76,  -175,  1256,  -175,  1256,  1256,  1256,
    1256,  1256,  1256,  -175,  -175,  1256,  1256,  1256,  1256,  1256,
    1256,  1256,  1256,  1256,  1256,  1256,  1256,  1256,  1256,  1256,
    1256,  1256,  1256,  1256,    85,  -175,  1256,  1256,  -175,  -175,
      51,  -175,    89,  1195,    69,    -5,   882,  -175,    -2,  1421,
    -175,  1256,  1256,  -175,  1090,   882,  -175,    95,  1421,  -175,
     882,   408,   882,  1421,  1421,   989,  1421,  1421,    61,    61,
     108,   108,  1238,  1421,  1421,  1421,  1421,  1421,  1421,  1584,
    1584,  1584,  1584,    61,  1536,  1536,  1421,  1518,  1500,    18,
      37,  1589,   989,  1421,  1116,  1256,   107,  -175,  1299,  1256,
      63,    55,     1,   329,  -175,  1256,  -175,  1421,    65,   101,
     487,  1256,   566,    39,   645,    98,  -175,   103,  1256,  1421,
      73,  -175,  1360,  1362,    23,    63,  1362,  -175,  -175,  1256,
      23,  -175,  1421,  1362,    71,  1119,  -175,   106,  1421,  -175,
    1256,  -175,  1256,  1256,  1439,  1256,  -175,    60,   882,    23,
      32,  1177,   882,    60,  1362,   116,  1256,  1421,   109,   110,
    1421,   882,   123,   882,  -175,   882,   724,    60,    77,   121,
    1256,  1256,  -175,   130,   329,  -175,  1362,    23,   125,   127,
    -175,  -175,    60,   882,  -175,  -175,   803,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,     0,  -115,    50,    67,  -175,  -175,  -175,   -76,
    -175,  -175,  -124,  -175,  -175,  -175,  -175,  -175,  -144,  -174,
       3,  -175,  -175,    64,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,   -80,  -175,    -6,    -3,  -175,  -175
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      42,    71,   149,   141,   142,   190,   131,   130,   194,   217,
     195,   205,   131,    67,   131,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      91,    98,    84,    99,   100,   101,   143,    86,   207,    90,
     254,     7,     8,     7,     8,   131,    83,    69,    96,   128,
      98,    79,    99,   100,   101,    82,    87,   129,   248,   249,
     133,   102,   136,   103,   104,   215,    68,   216,    70,    72,
      73,   135,   259,   131,   145,   149,    40,   150,   115,   152,
     102,   144,   103,   104,   151,   155,   268,   269,    74,    75,
      77,    78,    88,    92,   182,    80,    81,   115,   185,    93,
      94,   186,   149,    85,   102,    95,   103,   104,   121,    89,
     123,   224,   189,   225,   201,   210,   213,   232,   223,   230,
     235,    98,   233,    99,   244,   246,   258,   262,   260,   261,
     266,   267,   192,   139,   270,   274,   193,   275,   263,   239,
     271,   192,     0,     0,     0,   200,   148,   199,     0,     0,
     202,   102,   204,   103,   104,   153,   154,     0,     0,   156,
       0,   157,   158,   159,   160,   161,   162,     0,   115,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,     0,     0,
     183,   184,     0,     0,     3,     4,   137,   188,     0,     5,
       0,    88,     6,     0,     0,   196,   197,     0,   238,     0,
     237,     0,     0,   240,   242,     0,     0,     0,    89,   148,
     243,     0,   240,     0,     0,     0,     0,     0,     0,    25,
       0,    26,    27,   253,     0,   255,     0,     0,     0,     0,
       0,   257,   256,    88,     0,     0,   148,    28,    29,   209,
      88,     0,    88,   212,    88,   264,     0,    32,     0,   222,
      89,   273,     0,   272,     0,   228,     0,    89,     0,    89,
       0,    89,   234,   276,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   241,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   247,     0,   228,   228,     0,   250,
       0,    88,     0,     0,     0,     0,    88,     0,     0,     0,
     228,     0,     0,     0,    88,     0,     0,     0,    89,     0,
       0,     0,     0,    89,   228,   228,    88,     0,     0,     0,
       0,    89,     1,   218,     2,   219,   220,     3,     4,     0,
       0,     0,     5,    89,     0,     6,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,    25,     0,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    30,     0,     0,     0,     0,    31,     0,     0,
      32,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      40,     1,   203,     2,     0,     0,     3,     4,     0,     0,
       0,     5,     0,     0,     6,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,    25,     0,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    30,     0,     0,     0,     0,    31,     0,     0,    32,
       0,     0,    33,    34,    35,    36,    37,    38,    39,    40,
       1,   226,     2,     0,     0,     3,     4,     0,     0,     0,
       5,     0,     0,     6,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,     0,     0,     0,     0,
      25,     0,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
      30,     0,     0,     0,     0,    31,     0,     0,    32,     0,
       0,    33,    34,    35,    36,    37,    38,    39,    40,     1,
     229,     2,     0,     0,     3,     4,     0,     0,     0,     5,
       0,     0,     6,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,     0,    31,     0,     0,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,    40,     1,   231,
       2,     0,     0,     3,     4,     0,     0,     0,     5,     0,
       0,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,    25,     0,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    30,     0,
       0,     0,     0,    31,     0,     0,    32,     0,     0,    33,
      34,    35,    36,    37,    38,    39,    40,     1,   265,     2,
       0,     0,     3,     4,     0,     0,     0,     5,     0,     0,
       6,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,     0,     0,    25,     0,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,     0,     0,
       0,     0,    31,     0,     0,    32,     0,     0,    33,    34,
      35,    36,    37,    38,    39,    40,     1,   277,     2,     0,
       0,     3,     4,     0,     0,     0,     5,     0,     0,     6,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,    25,     0,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,     0,     0,
       0,    31,     0,     0,    32,     0,     0,    33,    34,    35,
      36,    37,    38,    39,    40,     1,     0,     2,     0,     0,
       3,     4,     0,     0,     0,     5,     0,     0,     6,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    25,    97,    26,    27,     0,
       0,     0,     0,     0,    98,     0,    99,   100,   101,     7,
       8,     0,     0,    28,    29,    30,     0,     0,     0,     0,
      31,     0,     0,    32,     0,     0,    33,    34,    35,    36,
      37,    38,    39,    40,   102,     0,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   111,   112,   113,
     114,   115,     0,     0,     0,     0,   116,   117,     0,   118,
     119,   120,   121,   122,   123,   124,   125,     3,     4,     0,
       0,   126,     5,   127,     0,     6,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,     0,     0,     0,     0,     0,
       0,     0,    25,     0,    26,    27,   140,     0,     0,    98,
       0,    99,   100,   101,     0,     0,     0,     0,     0,     0,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,     0,     0,   102,
      40,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,   111,   112,   113,   114,   115,     0,     0,     0,
       0,   116,   117,     0,     0,   119,   120,   121,   122,   123,
     198,     0,     0,     0,     0,     0,     0,     0,   127,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,    98,
       0,    99,   100,   101,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,     0,     0,     0,     0,   102,
       0,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,    40,   111,   112,   113,   114,   115,     0,     0,     0,
       0,   116,   117,   245,     0,   119,   120,   121,   122,   123,
      98,     0,    99,   100,   101,     7,     8,     0,   127,   208,
      40,     0,     0,     3,     4,     0,     0,     0,     5,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
     102,     0,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,   111,   112,   113,   114,   115,    25,   187,
      26,    27,   116,   117,     0,     0,   119,   120,   121,   122,
     123,    98,     0,    99,   100,   101,    28,    29,     0,   127,
       0,     0,     0,     0,     3,     4,    32,     0,     0,     5,
       0,     0,     6,     0,     0,     0,     0,     0,     0,     0,
       0,   102,   206,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,   111,   112,   113,   114,   115,    25,
       0,    26,    27,   116,   117,     0,     0,   119,   120,   121,
     122,   123,    98,     0,    99,   100,   101,    28,    29,     0,
     127,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   211,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,   111,   112,   113,   114,   115,
       0,     0,     0,     0,   116,   117,     0,     0,   119,   120,
     121,   122,   123,    98,     0,    99,   100,   101,     0,     0,
       0,   127,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,     0,     0,
       0,     0,     0,   102,   236,   103,   104,   105,   106,   107,
     108,   109,   110,     0,     0,     0,   111,   112,   113,   114,
     115,     0,     0,     0,     0,   116,   117,     0,     0,   119,
     120,   121,   122,   123,    98,     0,    99,   100,   101,     0,
       0,     0,   127,    40,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,   102,     0,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   111,   112,   113,
     114,   115,   102,     0,   103,   104,   116,   117,     0,     0,
     119,   120,   121,   122,   123,   111,   112,   113,   114,   115,
       0,     0,     0,   127,   116,   117,     0,     0,   119,   120,
     121,   122,   123,    98,     0,    99,   100,   101,     0,     0,
       0,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    98,     0,    99,   100,   101,     0,     0,     0,     0,
       0,     0,     0,   102,     0,   103,   104,     0,     0,    98,
       0,    99,   100,   101,     0,     0,   111,   112,   113,   114,
     115,   102,     0,   103,   104,   116,   117,     0,     0,   119,
       0,   121,   122,   123,   111,   112,   113,   114,   115,   102,
       0,   103,   104,   116,   117,     0,     0,     0,     0,   121,
     122,   123,   111,   112,   113,   114,   115,    98,     0,    99,
     100,   101,    98,     0,    99,   100,   101,   121,   122,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,     0,   103,
     104,     0,   102,     0,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   115,     0,     0,     0,     0,   115,
       0,     0,     0,     0,     0,   121,   122,   123,     0,     0,
     121
};

static const yytype_int16 yycheck[] =
{
       0,     4,    82,    10,    12,    10,    13,     8,    10,     8,
      12,   155,    13,     8,    13,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       5,    13,    38,    15,    16,    17,    44,    40,   182,    45,
       8,    18,    19,    18,    19,    13,    79,     9,    54,    55,
      13,     8,    15,    16,    17,     9,     0,    63,   232,   233,
      43,    43,    68,    45,    46,    10,     2,    12,     4,     5,
       6,     9,   246,    13,    80,   155,    81,    83,    60,    85,
      43,     9,    45,    46,    84,     9,   260,   261,    24,    25,
      26,    27,    42,    68,     9,    31,    32,    60,    47,    74,
      75,    12,   182,    39,    43,    80,    45,    46,    71,    42,
      73,    10,    43,    12,    19,     8,    53,    19,    53,    80,
      47,    13,    19,    15,    53,    19,    10,     4,    19,    19,
      53,    10,   135,    69,     4,    10,   136,    10,   253,   215,
     264,   144,    -1,    -1,    -1,   145,    82,   144,    -1,    -1,
     150,    43,   152,    45,    46,    91,    92,    -1,    -1,    95,
      -1,    97,    98,    99,   100,   101,   102,    -1,    60,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,    -1,    -1,
     126,   127,    -1,    -1,     8,     9,    10,   133,    -1,    13,
      -1,   151,    16,    -1,    -1,   141,   142,    -1,   214,    -1,
     213,    -1,    -1,   216,   220,    -1,    -1,    -1,   151,   155,
     223,    -1,   225,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,   239,    -1,   241,    -1,    -1,    -1,    -1,
      -1,   244,   242,   193,    -1,    -1,   182,    61,    62,   185,
     200,    -1,   202,   189,   204,   255,    -1,    71,    -1,   195,
     193,   267,    -1,   266,    -1,   201,    -1,   200,    -1,   202,
      -1,   204,   208,   273,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   219,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   230,    -1,   232,   233,    -1,   235,
      -1,   251,    -1,    -1,    -1,    -1,   256,    -1,    -1,    -1,
     246,    -1,    -1,    -1,   264,    -1,    -1,    -1,   251,    -1,
      -1,    -1,    -1,   256,   260,   261,   276,    -1,    -1,    -1,
      -1,   264,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    13,   276,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      71,    -1,    -1,    74,    75,    76,    77,    78,    79,    80,
      81,     3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
       3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,
      13,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    81,     3,     4,
       5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    71,    -1,    -1,    74,
      75,    76,    77,    78,    79,    80,    81,     3,     4,     5,
      -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,     3,     4,     5,    -1,
      -1,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    81,     3,    -1,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,     5,    45,    46,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,     8,     9,    -1,
      -1,    80,    13,    82,    -1,    16,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    10,    -1,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      81,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,    69,    70,    71,    72,    73,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    81,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    66,    64,    -1,    69,    70,    71,    72,    73,
      13,    -1,    15,    16,    17,    18,    19,    -1,    82,    83,
      81,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    43,    44,
      45,    46,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    13,    -1,    15,    16,    17,    61,    62,    -1,    82,
      -1,    -1,    -1,    -1,     8,     9,    71,    -1,    -1,    13,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    56,    57,    58,    59,    60,    43,
      -1,    45,    46,    65,    66,    -1,    -1,    69,    70,    71,
      72,    73,    13,    -1,    15,    16,    17,    61,    62,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    13,    -1,    15,    16,    17,    -1,    -1,
      -1,    82,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    13,    -1,    15,    16,    17,    -1,
      -1,    -1,    82,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    43,    -1,    45,    46,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    82,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    13,    -1,    15,    16,    17,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    56,    57,    58,    59,
      60,    43,    -1,    45,    46,    65,    66,    -1,    -1,    69,
      -1,    71,    72,    73,    56,    57,    58,    59,    60,    43,
      -1,    45,    46,    65,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    56,    57,    58,    59,    60,    13,    -1,    15,
      16,    17,    13,    -1,    15,    16,    17,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,
      71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,     9,    13,    16,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    43,    45,    46,    61,    62,
      63,    68,    71,    74,    75,    76,    77,    78,    79,    80,
      81,    87,    88,    90,    91,    93,    94,    96,    97,    99,
     100,   101,   102,   103,   108,   109,   110,   111,   112,   113,
     114,   115,   117,   118,   120,   121,   123,     8,   109,     9,
     109,   121,   109,   109,   109,   109,   116,   109,   109,     8,
     109,   109,     9,    79,   120,   109,   121,     0,    90,    91,
     120,     5,    68,    74,    75,    80,   120,     5,    13,    15,
      16,    17,    43,    45,    46,    47,    48,    49,    50,    51,
      52,    56,    57,    58,    59,    60,    65,    66,    68,    69,
      70,    71,    72,    73,    74,    75,    80,    82,   120,   120,
       8,    13,   119,    43,   122,     9,   120,    10,   107,   109,
      10,    10,    12,    44,     9,   120,    92,   104,   109,   118,
     120,    88,   120,   109,   109,     9,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,     9,   109,   109,    47,    12,    44,   109,    43,
      10,   106,   121,    88,    10,    12,   109,   109,    10,   106,
      88,    19,    88,     4,    88,   104,    44,   104,    83,   109,
       8,    44,   109,    53,    95,    10,    12,     8,     4,     6,
       7,    98,   109,    53,    10,    12,     4,   105,   109,     4,
      80,     4,    19,    19,   109,    47,    44,   121,   120,    95,
     121,   109,   120,   121,    53,    64,    19,   109,   105,   105,
     109,    88,    89,   120,     8,   120,    88,   121,    10,   105,
      19,    19,     4,    89,    88,     4,    53,    10,   105,   105,
       4,    98,   121,   120,    10,    10,    88,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (module, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex (module)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, module); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Module* module)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, module)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Module* module;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (module);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Module* module)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, module)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Module* module;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, module);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Module* module)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, module)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    Module* module;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , module);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, module); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Module* module)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, module)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    Module* module;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (module);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (Module* module);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (Module* module)
#else
int
yyparse (module)
    Module* module;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 140 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		for (auto stmt : *(yyvsp[(1) - (1)].nodes))
		{
			module->getMain()->addStatement(stmt);
		}
	;}
    break;

  case 3:
#line 150 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);

		if ((yyvsp[(2) - (2)].node) != nullptr)
		{
    		(yyval.nodes)->push_back((yyvsp[(2) - (2)].node));
		}
	;}
    break;

  case 4:
#line 159 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);

		for (auto stmt : *(yyvsp[(2) - (2)].nodes))
		{
			if (stmt == nullptr) continue;
			(yyval.nodes)->push_back(stmt);
		}
	;}
    break;

  case 5:
#line 169 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();

		if ((yyvsp[(1) - (1)].node) != nullptr)
		{
			(yyval.nodes)->push_back((yyvsp[(1) - (1)].node));
		}
	;}
    break;

  case 6:
#line 178 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();

		for (auto stmt : *(yyvsp[(1) - (1)].nodes))
		{
			if (stmt == nullptr) continue;
			(yyval.nodes)->push_back(stmt);
		}
	;}
    break;

  case 7:
#line 190 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 8:
#line 191 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode *>(); ;}
    break;

  case 9:
#line 195 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].stmt); ;}
    break;

  case 10:
#line 196 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 11:
#line 197 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].expr); ;}
    break;

  case 12:
#line 198 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 13:
#line 203 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);
	;}
    break;

  case 14:
#line 210 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 15:
#line 214 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();
		(yyval.nodes)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 16:
#line 220 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 17:
#line 221 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 18:
#line 222 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 19:
#line 223 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 20:
#line 224 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 21:
#line 225 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 22:
#line 226 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 23:
#line 227 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 24:
#line 232 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto func = new Function(*(yyvsp[(2) - (8)].str), std::vector<Parameter *>());
		func->setReturnType((yyvsp[(5) - (8)].ty));

		for (auto stmt : *(yyvsp[(7) - (8)].nodes))
		{
			func->addStatement(stmt);
		}

		(yyval.stmt) = func;
	;}
    break;

  case 25:
#line 244 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto func = new Function(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params));
		func->setReturnType((yyvsp[(6) - (9)].ty));

		for (auto stmt : *(yyvsp[(8) - (9)].nodes))
		{
			func->addStatement(stmt);
		}

		(yyval.stmt) = func;
	;}
    break;

  case 26:
#line 258 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = (yyvsp[(2) - (2)].ty); ;}
    break;

  case 27:
#line 259 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 28:
#line 264 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		std::vector<Parameter *> params;
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (6)].str), params, (yyvsp[(6) - (6)].ty));
	;}
    break;

  case 29:
#line 269 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params), (yyvsp[(7) - (7)].ty));
	;}
    break;

  case 30:
#line 273 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params), (yyvsp[(9) - (9)].ty), true);
	;}
    break;

  case 31:
#line 280 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto blocks = (yyvsp[(5) - (5)].blocks);

		auto block = new CondBlock((yyvsp[(2) - (5)].expr));
		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			block->addStatement(stmt);
		}

		blocks->insert(blocks->begin(), block);

		auto if_stmt = new IfStmt();
		for (auto block : *blocks)
		{
			if_stmt->addBlock(block);
		}

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 32:
#line 303 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = (yyvsp[(5) - (5)].blocks);

		auto block = new CondBlock((yyvsp[(2) - (5)].expr));
		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			block->addStatement(stmt);
		}

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

	;}
    break;

  case 33:
#line 316 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();

		auto block = new Block();
		for (auto stmt : *(yyvsp[(3) - (4)].nodes))
		{
			block->addStatement(stmt);
		}

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);
	;}
    break;

  case 34:
#line 328 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();
	;}
    break;

  case 35:
#line 335 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (5)].expr), true);
		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			block->addStatement(stmt);
		}

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 36:
#line 350 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 37:
#line 360 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 38:
#line 373 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 39:
#line 383 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
	;}
    break;

  case 40:
#line 397 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(3) - (11)].nodes), (yyvsp[(5) - (11)].expr), (yyvsp[(7) - (11)].expr), false);

	  	for (auto stmt : *(yyvsp[(10) - (11)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
	;}
    break;

  case 41:
#line 408 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(2) - (5)].expr), nullptr, false);

		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
	;}
    break;

  case 42:
#line 419 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);

		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
	;}
    break;

  case 43:
#line 430 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(6) - (6)].expr), nullptr, true);

		for (auto stmt : *(yyvsp[(3) - (6)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
	;}
    break;

  case 44:
#line 445 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].node));
		(yyval.stmt) = loop;
	;}
    break;

  case 45:
#line 452 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].expr));
		(yyval.stmt) = loop;
	;}
    break;

  case 46:
#line 458 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].node));
		(yyval.stmt) = loop;
	;}
    break;

  case 47:
#line 464 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].expr));
		(yyval.stmt) = loop;
	;}
    break;

  case 48:
#line 470 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].node));
		(yyval.stmt) = loop;
	;}
    break;

  case 49:
#line 476 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].expr));
		(yyval.stmt) = loop;
	;}
    break;

  case 50:
#line 487 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 51:
#line 488 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); ;}
    break;

  case 52:
#line 492 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 53:
#line 493 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = nullptr; ;}
    break;

  case 54:
#line 498 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = (yyvsp[(1) - (4)].params);
		(yyval.params)->push_back(new Parameter((yyvsp[(3) - (4)].ty), *(yyvsp[(4) - (4)].str)));
	;}
    break;

  case 55:
#line 503 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = new std::vector<Parameter *>();
		(yyval.params)->push_back(new Parameter((yyvsp[(1) - (2)].ty), *(yyvsp[(2) - (2)].str)));
	;}
    break;

  case 56:
#line 510 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = (yyvsp[(1) - (3)].args);
		(yyval.args)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 57:
#line 515 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = new std::vector<Expression *>();
		(yyval.args)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 58:
#line 521 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 59:
#line 522 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 60:
#line 523 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 61:
#line 524 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 62:
#line 528 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 63:
#line 529 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 64:
#line 530 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 65:
#line 531 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 66:
#line 532 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 67:
#line 533 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 68:
#line 537 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 69:
#line 538 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 70:
#line 539 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 71:
#line 540 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 72:
#line 541 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 73:
#line 542 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 74:
#line 544 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 75:
#line 545 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 76:
#line 549 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 77:
#line 550 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 78:
#line 551 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 79:
#line 552 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 80:
#line 553 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 81:
#line 555 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 82:
#line 556 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 83:
#line 557 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 84:
#line 559 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 85:
#line 560 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 86:
#line 561 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 87:
#line 562 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 88:
#line 563 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 89:
#line 564 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 90:
#line 568 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr),  1, false); ;}
    break;

  case 91:
#line 569 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr), -1, false); ;}
    break;

  case 92:
#line 570 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr),  1, true); ;}
    break;

  case 93:
#line 571 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr), -1, true); ;}
    break;

  case 94:
#line 576 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new TernaryExpr((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));
	;}
    break;

  case 95:
#line 583 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		std::vector<Expression *> params;
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (3)].str), params);
	;}
    break;

  case 96:
#line 588 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
	;}
    break;

  case 97:
#line 594 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 98:
#line 595 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].val); ;}
    break;

  case 99:
#line 596 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new NegativeExpr((yyvsp[(2) - (2)].expr)); ;}
    break;

  case 100:
#line 597 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new StrValue(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 101:
#line 598 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IDReference(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 102:
#line 599 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new DerefExpr((yyvsp[(2) - (2)].expr)); ;}
    break;

  case 103:
#line 600 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ReferenceExpr((yyvsp[(2) - (2)].expr)); ;}
    break;

  case 104:
#line 601 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new CastExpr((yyvsp[(2) - (4)].ty), (yyvsp[(4) - (4)].expr)); ;}
    break;

  case 105:
#line 602 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayValue(*(yyvsp[(2) - (3)].exprs)); ;}
    break;

  case 106:
#line 603 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayAccessExpr((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 107:
#line 608 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (3)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 108:
#line 613 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 109:
#line 622 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt(nullptr);
	;}
    break;

  case 110:
#line 626 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt((yyvsp[(2) - (2)].expr));
	;}
    break;

  case 111:
#line 633 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode*>();

		for (auto tupl : *(yyvsp[(2) - (2)].pairs))
		{
			auto decl = new VarDecl((yyvsp[(1) - (2)].ty), std::get<0>(tupl), std::get<1>(tupl));
			(yyval.nodes)->push_back(decl);
		}
	;}
    break;

  case 112:
#line 646 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (3)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (3)].str), nullptr));
	;}
    break;

  case 113:
#line 651 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (5)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)));
	;}
    break;

  case 114:
#line 656 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<std::string, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (1)].str), nullptr));
	;}
    break;

  case 115:
#line 661 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<std::string, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].expr)));
	;}
    break;

  case 118:
#line 673 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = PointerType::get((yyvsp[(1) - (2)].ty));
	;}
    break;

  case 119:
#line 677 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 120:
#line 681 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(2) - (2)].ty)->getConst();
	;}
    break;

  case 121:
#line 685 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (2)].ty);

		bool is_const = true;
		for (int i = 0; i < (yyvsp[(2) - (2)].exprs)->size(); i++)
		{
			auto def = (yyvsp[(2) - (2)].exprs)->at(i);

			if (Type::exprValidForArrSize(def) == false)
			{
				is_const = false;
				break;
			}
		}

		int sz = (int)(yyvsp[(2) - (2)].exprs)->size();
		for (int i = sz - 1; i >= 0; i--)
		{
			auto def = (yyvsp[(2) - (2)].exprs)->at(i);

			if (is_const)
			{
				auto arr_sz = Type::exprAsArrSize(def);
				(yyval.ty) = ArrayType::get((yyval.ty), arr_sz, false);
			}
			else
			{
				(yyval.ty) = VariadicArrayType::get((yyval.ty), def, false);
			}
		}
	;}
    break;

  case 122:
#line 717 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = PointerType::get((yyvsp[(1) - (3)].ty));
	;}
    break;

  case 123:
#line 724 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (4)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (4)].expr));
	;}
    break;

  case 124:
#line 729 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(2) - (3)].expr));
	;}
    break;

  case 125:
#line 736 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(64); ;}
    break;

  case 126:
#line 737 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(64); ;}
    break;

  case 127:
#line 738 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = FloatType::get(); ;}
    break;

  case 128:
#line 739 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = DoubleType::get(); ;}
    break;

  case 129:
#line 740 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(8); ;}
    break;

  case 130:
#line 741 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(16); ;}
    break;

  case 131:
#line 742 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(32); ;}
    break;

  case 132:
#line 743 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(64); ;}
    break;

  case 133:
#line 744 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(8); ;}
    break;

  case 134:
#line 745 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(16); ;}
    break;

  case 135:
#line 746 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(32); ;}
    break;

  case 136:
#line 747 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(64); ;}
    break;

  case 137:
#line 748 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(8); ;}
    break;

  case 138:
#line 749 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = VoidType::get(); ;}
    break;

  case 139:
#line 750 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = VarType::get(); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3108 "/Users/robert/dev/orange/lib/grove/parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (module, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (module, yymsg);
	  }
	else
	  {
	    yyerror (module, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, module);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, module);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (module, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, module);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, module);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 753 "/Users/robert/dev/orange/lib/grove/parser.y"



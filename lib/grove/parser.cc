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
     IDENTIFIER = 263,
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
     CONST_FLAG = 336,
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
#define IDENTIFIER 263
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
#define CONST_FLAG 336
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
	#include <grove/AccessExpr.h>
	#include <grove/EnumStmt.h>
	#include <grove/SizeofExpr.h>
	#include <grove/OString.h>
	#include <grove/ClassDecl.h>
	#include <grove/ClassMethod.h>
	#include <grove/MemberVarDecl.h>

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

	#define SET_LOCATION(node, start, end)\
		node->setLocation(CodeLocation(module->getFile(), start.first_line,\
		end.last_line, start.first_column, end.last_column));

	extern struct YYLTYPE yylloc;
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
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 75 "/Users/robert/dev/orange/lib/grove/parser.y"
{
	std::vector<ASTNode*>* nodes;
	std::vector<Parameter*>* params;
	std::vector<Expression*>* args;
	std::vector<Block*>* blocks;
	std::vector<Expression*>* exprs;
	std::vector<std::tuple<OString, Expression*>>* pairs;
	std::vector<std::tuple<OString, Value*>>* vpairs;
	ASTNode* node;
	Block* block;
	Expression* expr;
	Statement* stmt;
	Value* val;
	OString* str;
	Type* ty;
}
/* Line 193 of yacc.c.  */
#line 344 "/Users/robert/dev/orange/lib/grove/parser.cc"
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
#line 369 "/Users/robert/dev/orange/lib/grove/parser.cc"

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
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1836

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNRULES -- Number of states.  */
#define YYNSTATES  314

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
      44,    46,    48,    50,    52,    54,    56,    65,    75,    78,
      79,    86,    94,   104,   105,   112,   118,   124,   129,   131,
     137,   141,   145,   149,   153,   165,   171,   177,   184,   194,
     204,   208,   212,   215,   218,   220,   221,   223,   224,   229,
     232,   236,   238,   240,   242,   244,   246,   248,   250,   252,
     254,   256,   258,   262,   266,   270,   274,   278,   282,   286,
     290,   294,   298,   302,   306,   310,   314,   318,   322,   326,
     330,   334,   338,   342,   346,   349,   352,   355,   358,   364,
     368,   373,   377,   379,   382,   384,   386,   389,   392,   397,
     401,   406,   410,   415,   420,   424,   426,   428,   431,   434,
     438,   444,   446,   450,   456,   460,   466,   469,   474,   476,
     479,   481,   483,   487,   490,   492,   495,   497,   499,   502,
     507,   511,   513,   515,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   535,   537,   539
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      87,     0,    -1,    88,    -1,    88,    90,    -1,    88,    91,
      -1,    90,    -1,    91,    -1,    88,    -1,    -1,    93,   125,
      -1,   110,   125,    -1,   111,   125,    -1,   125,    -1,   120,
     125,    -1,   120,    -1,   111,    -1,    94,    -1,    96,    -1,
      97,    -1,    99,    -1,   101,    -1,   102,    -1,   103,    -1,
     104,    -1,   105,    -1,   122,    -1,     3,     8,     9,    10,
      95,   125,    89,     4,    -1,     3,     8,     9,   108,    10,
      95,   125,    89,     4,    -1,    53,   127,    -1,    -1,    63,
       8,     9,    10,    53,   127,    -1,    63,     8,     9,   108,
      10,    53,   127,    -1,    63,     8,     9,   108,    12,    64,
      10,    53,   127,    -1,    -1,    36,     8,   125,    98,    89,
       4,    -1,     5,   111,   125,    88,   100,    -1,     6,   111,
     125,    88,   100,    -1,     7,   125,    88,     4,    -1,     4,
      -1,    68,   111,   125,    88,     4,    -1,   110,     5,   111,
      -1,   111,     5,   111,    -1,   110,    68,   111,    -1,   111,
      68,   111,    -1,    74,     9,   106,    19,   107,    19,   107,
      10,   125,    88,     4,    -1,    80,   111,   125,    88,     4,
      -1,    75,    79,   125,    88,     4,    -1,    79,   125,    88,
       4,    80,   111,    -1,   110,    74,     9,   106,    19,   107,
      19,   107,    10,    -1,   111,    74,     9,   106,    19,   107,
      19,   107,    10,    -1,   110,    80,   111,    -1,   111,    80,
     111,    -1,   110,    75,    -1,   111,    75,    -1,    92,    -1,
      -1,   111,    -1,    -1,   108,    12,   127,     8,    -1,   127,
       8,    -1,   109,    12,   111,    -1,   111,    -1,   119,    -1,
      77,    -1,    78,    -1,    76,    -1,   117,    -1,   112,    -1,
     113,    -1,   116,    -1,   114,    -1,   115,    -1,   111,    58,
     111,    -1,   111,    59,   111,    -1,   111,    56,   111,    -1,
     111,    57,   111,    -1,   111,    65,   111,    -1,   111,    66,
     111,    -1,   111,    69,   111,    -1,   111,    70,   111,    -1,
     111,    17,   111,    -1,   111,    16,   111,    -1,   111,    13,
     111,    -1,   111,    15,   111,    -1,   111,    60,   111,    -1,
     111,    71,   111,    -1,   111,    72,   111,    -1,   111,    73,
     111,    -1,   111,    47,   111,    -1,   111,    48,   111,    -1,
     111,    49,   111,    -1,   111,    50,   111,    -1,   111,    51,
     111,    -1,   111,    52,   111,    -1,   111,    45,    -1,   111,
      46,    -1,    45,   111,    -1,    46,   111,    -1,   111,    82,
     111,    83,   111,    -1,     8,     9,    10,    -1,     8,     9,
     109,    10,    -1,     9,   111,    10,    -1,    61,    -1,    16,
     111,    -1,    62,    -1,     8,    -1,    13,   111,    -1,    71,
     111,    -1,     9,   127,    10,   111,    -1,    43,   118,    44,
      -1,   111,    43,   111,    44,    -1,   111,    55,     8,    -1,
      85,     9,   111,    10,    -1,    85,     9,   127,    10,    -1,
     118,    12,   111,    -1,   111,    -1,    35,    -1,    35,   111,
      -1,   127,   121,    -1,   121,    12,     8,    -1,   121,    12,
       8,    47,   111,    -1,     8,    -1,     8,    47,   111,    -1,
      84,     8,   125,   123,     4,    -1,   123,     8,   125,    -1,
     123,     8,    47,   124,   125,    -1,     8,   125,    -1,     8,
      47,   124,   125,    -1,    61,    -1,    16,    61,    -1,    18,
      -1,    19,    -1,   126,    43,    44,    -1,   127,    13,    -1,
     130,    -1,    81,   127,    -1,   128,    -1,   126,    -1,   126,
     129,    -1,   129,    43,   111,    44,    -1,    43,   111,    44,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    26,    -1,    28,    -1,    30,    -1,    25,    -1,    27,
      -1,    29,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   153,   153,   165,   174,   186,   195,   210,   211,   215,
     216,   217,   218,   222,   229,   233,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   253,   279,   309,   310,
     314,   322,   330,   342,   341,   363,   390,   406,   422,   429,
     447,   458,   472,   483,   497,   513,   527,   541,   558,   568,
     578,   585,   592,   599,   609,   610,   614,   615,   619,   628,
     639,   644,   651,   652,   653,   654,   658,   659,   660,   661,
     662,   663,   667,   668,   669,   670,   671,   672,   674,   675,
     679,   680,   681,   682,   683,   685,   686,   687,   689,   690,
     691,   692,   693,   694,   698,   699,   700,   701,   705,   713,
     721,   732,   733,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   748,   753,   762,   767,   775,   801,
     808,   815,   822,   831,   847,   852,   857,   863,   871,   876,
     885,   886,   890,   894,   898,   905,   909,   913,   920,   955,
     960,   968,   969,   970,   971,   972,   973,   974,   975,   976,
     977,   978,   979,   980,   981,   982
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEF", "END", "IF", "ELIF", "ELSE",
  "IDENTIFIER", "OPEN_PAREN", "CLOSE_PAREN", "TYPE", "COMMA", "TIMES",
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
  "BREAK", "DO", "WHILE", "CONST_FLAG", "QUESTION", "COLON", "ENUM",
  "SIZEOF", "$accept", "start", "statements", "opt_statements",
  "statement", "compound_statement", "valued", "structures", "function",
  "type_hint", "extern_function", "class_stmt", "@1", "ifs",
  "else_if_or_end", "unless", "inline_if", "inline_unless", "for_loop",
  "inline_for_loop", "opt_valued", "opt_expression", "param_list",
  "arg_list", "controls", "expression", "comparison", "arithmetic",
  "increment", "ternary", "call", "primary", "expr_list", "return",
  "var_decl", "var_decl_list", "enum_stmt", "enum_members",
  "pos_or_neg_value", "term", "non_agg_type", "type", "array_type",
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
      93,    93,    93,    93,    93,    93,    94,    94,    95,    95,
      96,    96,    96,    98,    97,    99,   100,   100,   100,   101,
     102,   102,   103,   103,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   119,   119,   120,   121,
     121,   121,   121,   122,   123,   123,   123,   123,   124,   124,
     125,   125,   126,   126,   126,   127,   127,   127,   128,   129,
     129,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     0,     2,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     9,     2,     0,
       6,     7,     9,     0,     6,     5,     5,     4,     1,     5,
       3,     3,     3,     3,    11,     5,     5,     6,     9,     9,
       3,     3,     2,     2,     1,     0,     1,     0,     4,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     5,     3,
       4,     3,     1,     2,     1,     1,     2,     2,     4,     3,
       4,     3,     4,     4,     3,     1,     1,     2,     2,     3,
       5,     1,     3,     5,     3,     5,     2,     4,     1,     2,
       1,     1,     3,     2,     1,     2,     1,     1,     2,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   105,     0,     0,     0,   130,   131,   141,
     142,   143,   144,   145,   149,   146,   150,   147,   151,   148,
     152,   153,   154,   155,   116,     0,     0,     0,     0,   102,
     104,     0,     0,     0,     0,     0,    65,    63,    64,     0,
       0,     0,     0,     0,     0,     2,     5,     6,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
      67,    68,    70,    71,    69,    66,    62,     0,    25,    12,
     137,     0,   136,   134,     0,     0,     0,     0,     0,   106,
     103,   117,     0,   115,     0,    96,    97,     0,     0,   107,
      55,     0,     0,     0,   135,     0,     0,     1,     3,     4,
       9,     0,     0,     0,    52,     0,    10,     0,     0,     0,
       0,     0,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,    11,
      13,     0,   138,   121,   133,   118,     0,     0,    99,     0,
      61,   101,     0,    33,     0,   109,     0,     0,    54,     0,
      15,    14,     0,     0,     0,     0,     0,     0,    40,    42,
      55,    50,    41,    82,    83,    81,    80,     0,    88,    89,
      90,    91,    92,    93,   111,    74,    75,    72,    73,    84,
      76,    77,    43,    78,    79,    85,    86,    87,    55,    51,
       0,   132,     0,     0,     0,     0,    29,     0,     0,     0,
     100,     0,   108,     8,   114,     0,     0,     0,    57,     0,
       0,     0,     0,     0,   112,   113,     0,   110,     0,     0,
     140,     0,   122,   119,     0,     0,    29,     0,    59,    38,
       0,     0,    35,    60,     7,     0,     0,     0,     0,    39,
       0,    56,    46,     0,    45,     0,   126,   123,     0,    57,
      57,    98,   139,     0,    28,     8,     0,     0,     0,     0,
      34,    30,     0,     0,    57,    47,     0,   128,     0,     0,
     124,     0,     0,   120,     0,     8,    58,     0,     0,    31,
       0,     0,   129,   127,     0,    57,    57,    26,     0,     0,
      37,     0,     0,   125,     0,     0,    27,    36,    32,     0,
      48,    49,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    44,   244,   245,    46,    47,   158,    48,    49,   235,
      50,    51,   213,    52,   242,    53,    54,    55,    56,    57,
     159,   250,   207,   149,    58,    59,    60,    61,    62,    63,
      64,    65,    84,    66,    67,   145,    68,   223,   278,    69,
      70,    71,    72,   142,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -250
static const yytype_int16 yypact[] =
{
     878,     9,  1054,    15,  1023,  1054,  1054,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  1054,    23,  1054,  1054,  1054,  -250,
    -250,    41,  1054,  1054,    47,   -78,  -250,  -250,  -250,    96,
    1054,  1287,    56,    63,    79,   878,  -250,  -250,    96,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,    25,   955,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,    96,  -250,  -250,
      52,    34,  -250,  -250,    92,  1283,     5,  1097,    74,    28,
     822,  1527,    96,  1527,     8,  -250,  -250,    95,  1283,  1074,
    1023,    96,   878,  1283,    75,    96,  1023,  -250,  -250,  -250,
    -250,  1054,  1054,    98,  -250,  1054,  -250,  1054,  1054,  1054,
    1054,  1054,  1054,  -250,  -250,  1054,  1054,  1054,  1054,  1054,
    1054,   128,  1054,  1054,  1054,  1054,  1054,  1054,  1054,  1054,
    1054,  1054,  1054,  1054,  1054,   131,  -250,  1054,  1054,  -250,
    -250,   181,   103,   101,  -250,   137,   957,   878,  -250,    45,
    1527,  -250,  1054,  -250,  1054,  -250,  1163,   878,  -250,   132,
    1527,  -250,   878,   380,   878,   142,  1161,    76,  1527,  1527,
    1023,  1527,  1527,    28,    28,   822,   822,  1344,  1527,  1527,
    1527,  1527,  1527,  1527,  -250,  1724,  1724,  1724,  1724,    28,
    1690,  1690,  1527,  1656,  1622,  1074,  1743,  1765,  1023,  1527,
    1222,  -250,  1405,  1054,  1054,   144,   105,    86,    55,   297,
    -250,  1054,    28,   878,  1527,   106,   133,   463,  1054,   546,
      80,   629,    -9,    77,  -250,  -250,   146,  -250,   147,  1054,
    -250,  1466,  1527,   109,  1287,    96,   105,  1287,  -250,  -250,
    1054,    96,  -250,  1527,   878,   157,  1287,   110,  1225,  -250,
     148,  1527,  -250,  1054,  -250,    -8,  -250,  -250,    -7,  1054,
    1054,  1588,  -250,  1054,    75,   878,    96,    57,  1283,   878,
    -250,    75,  1287,   160,  1054,  1527,   111,  -250,    96,    -8,
    -250,   154,   155,  1527,   171,   878,  -250,   878,   712,    75,
     124,   169,  -250,  -250,    96,  1054,  1054,  -250,   177,   297,
    -250,  1287,    96,  -250,   172,   174,  -250,  -250,    75,   878,
    -250,  -250,   795,  -250
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,     0,  -249,   -41,   -26,  -250,  -250,  -250,   -51,
    -250,  -250,  -250,  -250,  -113,  -250,  -250,  -250,  -250,  -250,
    -138,  -237,    31,  -250,  -250,     1,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,   -29,  -250,  -250,  -250,   -91,   -13,
    -250,    -2,  -250,  -250,  -250
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      45,    91,    78,    75,    98,    77,    79,    80,   276,     7,
       8,     7,     8,     3,     4,   148,   284,    74,     5,    99,
     154,     6,   281,   282,    76,    81,    92,    83,    85,    86,
     101,    82,   226,    88,    89,   100,   298,   291,   255,    94,
     279,    93,   143,     7,     8,   106,   139,   144,    26,    87,
      27,    28,   155,   277,   140,   210,    90,   211,   304,   305,
     228,   161,   147,   238,    95,   286,    29,    30,   144,   153,
     144,   112,    96,   113,   114,   157,    33,   150,   162,    97,
     164,   257,   165,   121,   152,   258,   225,   144,   144,   144,
      43,   160,   163,   102,   167,   141,   236,   166,   237,   103,
     104,   146,   168,   169,   156,   105,   171,   170,   172,   173,
     174,   175,   176,   177,     7,     8,   178,   179,   180,   181,
     182,   183,    98,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   184,    99,   199,   200,
     198,   161,   202,   247,   208,   248,   203,   209,   204,   205,
     222,   218,   233,   212,   208,   214,   263,   217,   234,   246,
     253,   270,   219,   272,   221,   259,   260,   274,    98,   161,
     290,   160,   292,   295,   296,   297,    98,   301,    98,   302,
      98,   306,   310,    99,   311,   266,   307,   216,   294,     3,
       4,    99,     0,    99,     5,    99,     0,     6,     0,   160,
       0,     0,     0,    98,   231,   232,     0,     0,     0,   256,
       0,     0,   243,     0,     0,     0,     0,     0,    99,   251,
       0,     0,   265,     0,    26,   201,    27,    28,   269,     0,
     261,     0,   264,     0,     0,   267,     0,     0,     0,     0,
       0,   268,    29,    30,   271,   280,   267,    98,     0,     0,
       0,     0,    33,   285,   275,   287,     0,     0,    98,     0,
     251,   251,    99,     0,   283,   293,    43,     0,     0,   288,
     289,    98,     0,    99,     0,   251,     0,     0,     0,     0,
       0,   303,     0,     0,     0,     0,    99,   299,     0,   309,
       0,     0,     0,     0,     0,     0,   251,   251,     0,   308,
       1,   239,     2,   240,   241,     3,     4,     0,     0,   312,
       5,     0,     0,     6,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
      26,     0,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    30,
      31,     0,     0,     0,     0,    32,     0,     0,    33,     0,
       0,    34,    35,    36,    37,    38,    39,    40,    41,     0,
       0,    42,    43,     1,   220,     2,     0,     0,     3,     4,
       0,     0,     0,     5,     0,     0,     6,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,    26,     0,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,     0,    32,     0,
       0,    33,     0,     0,    34,    35,    36,    37,    38,    39,
      40,    41,     0,     0,    42,    43,     1,   249,     2,     0,
       0,     3,     4,     0,     0,     0,     5,     0,     0,     6,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,    26,     0,    27,    28,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    30,    31,     0,     0,     0,
       0,    32,     0,     0,    33,     0,     0,    34,    35,    36,
      37,    38,    39,    40,    41,     0,     0,    42,    43,     1,
     252,     2,     0,     0,     3,     4,     0,     0,     0,     5,
       0,     0,     6,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,    26,
       0,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,    31,
       0,     0,     0,     0,    32,     0,     0,    33,     0,     0,
      34,    35,    36,    37,    38,    39,    40,    41,     0,     0,
      42,    43,     1,   254,     2,     0,     0,     3,     4,     0,
       0,     0,     5,     0,     0,     6,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,    26,     0,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,    31,     0,     0,     0,     0,    32,     0,     0,
      33,     0,     0,    34,    35,    36,    37,    38,    39,    40,
      41,     0,     0,    42,    43,     1,   300,     2,     0,     0,
       3,     4,     0,     0,     0,     5,     0,     0,     6,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,     0,     0,     0,     0,    26,     0,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,     0,
      32,     0,     0,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    40,    41,     0,     0,    42,    43,     1,   313,
       2,     0,     0,     3,     4,     0,     0,     0,     5,     0,
       0,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     0,     0,     0,   108,     0,   109,    26,     0,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    30,    31,     0,
       0,     0,     0,    32,     0,   112,    33,   113,   114,    34,
      35,    36,    37,    38,    39,    40,    41,   121,     0,    42,
      43,     1,   126,     2,     0,     0,     3,     4,     0,     0,
       0,     5,     0,     0,     6,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,    26,     0,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      30,    31,     0,     0,     0,     0,    32,     0,     0,    33,
       0,     0,    34,    35,    36,    37,    38,    39,    40,    41,
     107,     0,    42,    43,     0,     0,     0,   206,   108,     0,
     109,   110,   111,     7,     8,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,     0,     0,     0,     0,     0,   112,     0,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
     121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
     127,   128,     0,   129,   130,   131,   132,   133,   134,   135,
     136,     3,     4,     0,     0,   137,     5,   138,    41,     6,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
       0,     0,     3,     4,     0,     0,    26,     5,    27,    28,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    30,     0,   108,     0,   109,
     110,   111,     0,     0,    33,     0,     0,    26,     0,    27,
      28,     0,     0,     0,    41,     0,     0,   151,    43,     0,
     108,     0,   109,   110,   111,    29,    30,   112,     0,   113,
     114,     0,     0,     0,     0,    33,     0,     0,     0,   121,
       0,     0,     0,     0,   126,     0,     0,     0,     0,    43,
     112,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,     0,   121,   122,   123,   124,   125,   126,     0,     0,
       0,     0,   127,   128,     0,     0,   130,   131,   132,   133,
     134,   224,     0,   215,   108,     0,   109,   110,   111,   138,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
       0,     0,     0,     0,   112,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,     0,   121,   122,   123,   124,
     125,   126,     0,     0,     0,     0,   127,   128,     0,     0,
     130,   131,   132,   133,   134,   108,     0,   109,   110,   111,
       0,     0,     0,   138,    41,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,   112,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,     0,   121,   122,   123,
     124,   125,   126,     0,     0,     0,     0,   127,   128,   273,
       0,   130,   131,   132,   133,   134,   108,     0,   109,   110,
     111,     7,     8,     0,   138,   229,    41,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,     0,     0,     0,   112,     0,   113,   114,
     115,   116,   117,   118,   119,   120,     0,     0,   121,   122,
     123,   124,   125,   126,     0,     0,     0,     0,   127,   128,
       0,     0,   130,   131,   132,   133,   134,   108,     0,   109,
     110,   111,     0,     0,     0,   138,     0,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   227,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,   121,
     122,   123,   124,   125,   126,     0,     0,     0,     0,   127,
     128,     0,     0,   130,   131,   132,   133,   134,   108,     0,
     109,   110,   111,     0,     0,     0,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   230,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
     121,   122,   123,   124,   125,   126,     0,     0,     0,     0,
     127,   128,     0,     0,   130,   131,   132,   133,   134,   108,
       0,   109,   110,   111,     0,     0,     0,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     262,   113,   114,   115,   116,   117,   118,   119,   120,     0,
       0,   121,   122,   123,   124,   125,   126,     0,     0,     0,
       0,   127,   128,     0,     0,   130,   131,   132,   133,   134,
     108,     0,   109,   110,   111,     0,     0,     0,   138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,     0,   121,   122,   123,   124,   125,   126,     0,     0,
       0,     0,   127,   128,     0,     0,   130,   131,   132,   133,
     134,   108,     0,   109,   110,   111,     0,     0,     0,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,     0,   113,   114,   108,     0,   109,   110,   111,
       0,     0,     0,   121,   122,   123,   124,   125,   126,     0,
       0,     0,     0,   127,   128,     0,     0,   130,   131,   132,
     133,   134,     0,     0,     0,   112,     0,   113,   114,   108,
     138,   109,   110,   111,     0,     0,     0,   121,   122,   123,
     124,   125,   126,     0,     0,     0,     0,   127,   128,     0,
       0,   130,     0,   132,   133,   134,     0,     0,     0,   112,
       0,   113,   114,   108,     0,   109,   110,   111,     0,     0,
       0,   121,   122,   123,   124,   125,   126,     0,     0,     0,
       0,   127,   128,     0,     0,     0,     0,   132,   133,   134,
       0,     0,     0,   112,     0,   113,   114,   108,     0,   109,
     110,   111,     0,     0,     0,   121,   122,   123,   124,   125,
     126,     0,     0,     0,     0,     0,   108,     0,   109,   110,
     111,   132,   133,   134,     0,     0,     0,   112,     0,   113,
     114,     0,     0,     0,     0,     0,     0,     0,   108,   121,
     109,   110,   111,     0,   126,     0,   112,     0,   113,   114,
       0,     0,     0,     0,     0,   132,   133,   134,   121,     0,
       0,     0,     0,   126,     0,     0,     0,     0,   112,     0,
     113,   114,     0,     0,   132,     0,   134,     0,     0,     0,
     121,     0,     0,     0,     0,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132
};

static const yytype_int16 yycheck[] =
{
       0,    79,     4,     2,    45,     4,     5,     6,    16,    18,
      19,    18,    19,     8,     9,    10,   265,     8,    13,    45,
      12,    16,   259,   260,     9,    24,    39,    26,    27,    28,
       5,     8,   170,    32,    33,    48,   285,   274,    47,    41,
      47,    40,     8,    18,    19,    58,    59,    13,    43,     8,
      45,    46,    44,    61,    67,    10,     9,    12,   295,   296,
     198,    90,    75,     8,     8,     8,    61,    62,    13,    82,
      13,    43,     9,    45,    46,    88,    71,    76,    91,     0,
      93,     4,    95,    55,    10,     8,    10,    13,    13,    13,
      85,    90,    92,    68,    96,    43,    10,    96,    12,    74,
      75,     9,   101,   102,     9,    80,   105,     9,   107,   108,
     109,   110,   111,   112,    18,    19,   115,   116,   117,   118,
     119,   120,   163,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,     8,   163,   137,   138,
       9,   170,   141,    10,   146,    12,    43,   147,    47,    12,
       8,    19,     8,   152,   156,   154,    47,   157,    53,    53,
      80,     4,   162,    53,   164,    19,    19,    19,   209,   198,
      10,   170,    61,    19,    19,     4,   217,    53,   219,    10,
     221,     4,    10,   209,    10,   236,   299,   156,   279,     8,
       9,   217,    -1,   219,    13,   221,    -1,    16,    -1,   198,
      -1,    -1,    -1,   244,   203,   204,    -1,    -1,    -1,   222,
      -1,    -1,   211,    -1,    -1,    -1,    -1,    -1,   244,   218,
      -1,    -1,   235,    -1,    43,    44,    45,    46,   241,    -1,
     229,    -1,   234,    -1,    -1,   237,    -1,    -1,    -1,    -1,
      -1,   240,    61,    62,   246,   258,   248,   288,    -1,    -1,
      -1,    -1,    71,   266,   253,   268,    -1,    -1,   299,    -1,
     259,   260,   288,    -1,   263,   278,    85,    -1,    -1,   269,
     272,   312,    -1,   299,    -1,   274,    -1,    -1,    -1,    -1,
      -1,   294,    -1,    -1,    -1,    -1,   312,   287,    -1,   302,
      -1,    -1,    -1,    -1,    -1,    -1,   295,   296,    -1,   301,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,   309,
      13,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    84,    85,     3,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    84,    85,     3,     4,     5,    -1,
      -1,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    85,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      84,    85,     3,     4,     5,    -1,    -1,     8,     9,    -1,
      -1,    -1,    13,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      71,    -1,    -1,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    84,    85,     3,     4,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    84,    85,     3,     4,
       5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    13,    -1,    15,    43,    -1,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    43,    71,    45,    46,    74,
      75,    76,    77,    78,    79,    80,    81,    55,    -1,    84,
      85,     3,    60,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
       5,    -1,    84,    85,    -1,    -1,    -1,    10,    13,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    66,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,     8,     9,    -1,    -1,    80,    13,    82,    81,    16,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,     8,     9,    -1,    -1,    43,    13,    45,    46,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    13,    -1,    15,
      16,    17,    -1,    -1,    71,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    81,    -1,    -1,    10,    85,    -1,
      13,    -1,    15,    16,    17,    61,    62,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    85,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    10,    -1,    10,    13,    -1,    15,    16,    17,    82,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    82,    81,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    64,
      -1,    69,    70,    71,    72,    73,    13,    -1,    15,    16,
      17,    18,    19,    -1,    82,    83,    81,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    13,    -1,    15,
      16,    17,    -1,    -1,    -1,    82,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,    69,    70,    71,    72,    73,    13,    -1,
      15,    16,    17,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    13,
      -1,    15,    16,    17,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,    69,    70,    71,    72,    73,
      13,    -1,    15,    16,    17,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    13,    -1,    15,    16,    17,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    43,    -1,    45,    46,    13,
      82,    15,    16,    17,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    43,
      -1,    45,    46,    13,    -1,    15,    16,    17,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,    -1,    -1,    71,    72,    73,
      -1,    -1,    -1,    43,    -1,    45,    46,    13,    -1,    15,
      16,    17,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    13,    -1,    15,    16,
      17,    71,    72,    73,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    55,
      15,    16,    17,    -1,    60,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    55,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    43,    -1,
      45,    46,    -1,    -1,    71,    -1,    73,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,     9,    13,    16,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    43,    45,    46,    61,
      62,    63,    68,    71,    74,    75,    76,    77,    78,    79,
      80,    81,    84,    85,    87,    88,    90,    91,    93,    94,
      96,    97,    99,   101,   102,   103,   104,   105,   110,   111,
     112,   113,   114,   115,   116,   117,   119,   120,   122,   125,
     126,   127,   128,   130,     8,   111,     9,   111,   127,   111,
     111,   111,     8,   111,   118,   111,   111,     8,   111,   111,
       9,    79,   125,   111,   127,     8,     9,     0,    90,    91,
     125,     5,    68,    74,    75,    80,   125,     5,    13,    15,
      16,    17,    43,    45,    46,    47,    48,    49,    50,    51,
      52,    55,    56,    57,    58,    59,    60,    65,    66,    68,
      69,    70,    71,    72,    73,    74,    75,    80,    82,   125,
     125,    43,   129,     8,    13,   121,     9,   125,    10,   109,
     111,    10,    10,   125,    12,    44,     9,   125,    92,   106,
     111,   120,   125,    88,   125,   125,   111,   127,   111,   111,
       9,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,     8,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,     9,   111,
     111,    44,   111,    43,    47,    12,    10,   108,   127,    88,
      10,    12,   111,    98,   111,    10,   108,    88,    19,    88,
       4,    88,     8,   123,    10,    10,   106,    44,   106,    83,
      44,   111,   111,     8,    53,    95,    10,    12,     8,     4,
       6,     7,   100,   111,    88,    89,    53,    10,    12,     4,
     107,   111,     4,    80,     4,    47,   125,     4,     8,    19,
      19,   111,    44,    47,   127,   125,    95,   127,   111,   125,
       4,   127,    53,    64,    19,   111,    16,    61,   124,    47,
     125,   107,   107,   111,    89,   125,     8,   125,    88,   127,
      10,   107,    61,   125,   124,    19,    19,     4,    89,    88,
       4,    53,    10,   125,   107,   107,     4,   100,   127,   125,
      10,    10,    88,     4
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
#line 154 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		for (auto stmt : *(yyvsp[(1) - (1)].nodes))
		{
			module->getMain()->addStatement(stmt);
		}

		delete (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 3:
#line 166 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);

		if ((yyvsp[(2) - (2)].node) != nullptr)
		{
    		(yyval.nodes)->push_back((yyvsp[(2) - (2)].node));
		}
	;}
    break;

  case 4:
#line 175 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);

		for (auto stmt : *(yyvsp[(2) - (2)].nodes))
		{
			if (stmt == nullptr) continue;
			(yyval.nodes)->push_back(stmt);
		}

		delete (yyvsp[(2) - (2)].nodes);
	;}
    break;

  case 5:
#line 187 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();

		if ((yyvsp[(1) - (1)].node) != nullptr)
		{
			(yyval.nodes)->push_back((yyvsp[(1) - (1)].node));
		}
	;}
    break;

  case 6:
#line 196 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();

		for (auto stmt : *(yyvsp[(1) - (1)].nodes))
		{
			if (stmt == nullptr) continue;
			(yyval.nodes)->push_back(stmt);
		}

		delete (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 7:
#line 210 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 8:
#line 211 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode *>(); ;}
    break;

  case 9:
#line 215 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].stmt); ;}
    break;

  case 10:
#line 216 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 11:
#line 217 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].expr); ;}
    break;

  case 12:
#line 218 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 13:
#line 223 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);
	;}
    break;

  case 14:
#line 230 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 15:
#line 234 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();
		(yyval.nodes)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 16:
#line 240 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 17:
#line 241 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 18:
#line 242 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 19:
#line 243 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 20:
#line 244 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 21:
#line 245 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 22:
#line 246 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 23:
#line 247 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 24:
#line 248 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 25:
#line 249 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 26:
#line 254 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		Function* func = nullptr;

		if (module->getBlock()->is<ClassDecl *>())
		{
			func = new ClassMethod(*(yyvsp[(2) - (8)].str), std::vector<Parameter *>());
		}
		else
		{
			func = new Function(*(yyvsp[(2) - (8)].str), std::vector<Parameter *>());
		}

		func->setReturnType((yyvsp[(5) - (8)].ty));

		for (auto stmt : *(yyvsp[(7) - (8)].nodes))
		{
			func->addStatement(stmt);
		}

		(yyval.stmt) = func;
        SET_LOCATION((yyval.stmt), (yylsp[(1) - (8)]), (yylsp[(8) - (8)]));

		delete (yyvsp[(2) - (8)].str);
		delete (yyvsp[(7) - (8)].nodes);
	;}
    break;

  case 27:
#line 280 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		Function* func = nullptr;

		if (module->getBlock()->is<ClassDecl *>())
		{
			func = new ClassMethod(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params));
		}
		else
		{
			func = new Function(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params));
		}

		func->setReturnType((yyvsp[(6) - (9)].ty));

		for (auto stmt : *(yyvsp[(8) - (9)].nodes))
		{
			func->addStatement(stmt);
		}

		(yyval.stmt) = func;
        SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(2) - (9)].str);
		delete (yyvsp[(4) - (9)].params);
		delete (yyvsp[(8) - (9)].nodes);
	;}
    break;

  case 28:
#line 309 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = (yyvsp[(2) - (2)].ty); ;}
    break;

  case 29:
#line 310 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 30:
#line 315 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		std::vector<Parameter *> params;
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (6)].str), params, (yyvsp[(6) - (6)].ty));
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));

		delete (yyvsp[(2) - (6)].str);
	;}
    break;

  case 31:
#line 323 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params), (yyvsp[(7) - (7)].ty));
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));

		delete (yyvsp[(2) - (7)].str);
		delete (yyvsp[(4) - (7)].params);
	;}
    break;

  case 32:
#line 331 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params), (yyvsp[(9) - (9)].ty), true);
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(2) - (9)].str);
		delete (yyvsp[(4) - (9)].params);
	;}
    break;

  case 33:
#line 342 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ClassDecl(*(yyvsp[(2) - (3)].str));
		module->pushBlock((Block *)(yyval.stmt));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 34:
#line 347 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		ClassDecl* inst = (ClassDecl *)(yyvsp[(4) - (6)].stmt);

		for (auto stmt : *(yyvsp[(5) - (6)].nodes))
		{
			inst->addStatement(stmt);
		}

		(yyval.stmt) = inst;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));

		delete (yyvsp[(5) - (6)].nodes);
		module->popBlock();
	;}
    break;

  case 35:
#line 364 "/Users/robert/dev/orange/lib/grove/parser.y"
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
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(4) - (5)].nodes);
		delete blocks;
	;}
    break;

  case 36:
#line 391 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = (yyvsp[(5) - (5)].blocks);

		auto block = new CondBlock((yyvsp[(2) - (5)].expr));
		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			block->addStatement(stmt);
		}

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(4) - (5)].nodes);
	;}
    break;

  case 37:
#line 407 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();

		auto block = new Block();
		for (auto stmt : *(yyvsp[(3) - (4)].nodes))
		{
			block->addStatement(stmt);
		}

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(3) - (4)].nodes);
	;}
    break;

  case 38:
#line 423 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();
	;}
    break;

  case 39:
#line 430 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (5)].expr), true);
		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			block->addStatement(stmt);
		}

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(4) - (5)].nodes);
	;}
    break;

  case 40:
#line 448 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 41:
#line 459 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 42:
#line 473 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 43:
#line 484 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 44:
#line 499 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(3) - (11)].nodes), (yyvsp[(5) - (11)].expr), (yyvsp[(7) - (11)].expr), false);

	  	for (auto stmt : *(yyvsp[(10) - (11)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (11)]), (yylsp[(11) - (11)]));

		delete (yyvsp[(3) - (11)].nodes);
		delete (yyvsp[(10) - (11)].nodes);
	;}
    break;

  case 45:
#line 514 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(2) - (5)].expr), nullptr, false);

		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(4) - (5)].nodes);
	;}
    break;

  case 46:
#line 528 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);

		for (auto stmt : *(yyvsp[(4) - (5)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(4) - (5)].nodes);
	;}
    break;

  case 47:
#line 542 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(6) - (6)].expr), nullptr, true);

		for (auto stmt : *(yyvsp[(3) - (6)].nodes))
		{
			loop->addStatement(stmt);
		}

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));

		delete (yyvsp[(3) - (6)].nodes);
	;}
    break;

  case 48:
#line 560 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 49:
#line 570 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 50:
#line 579 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 51:
#line 586 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 52:
#line 593 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 53:
#line 600 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 54:
#line 609 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 55:
#line 610 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); ;}
    break;

  case 56:
#line 614 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 57:
#line 615 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = nullptr; ;}
    break;

  case 58:
#line 620 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = (yyvsp[(1) - (4)].params);
		auto param = new Parameter((yyvsp[(3) - (4)].ty), *(yyvsp[(4) - (4)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(4) - (4)].str);
	;}
    break;

  case 59:
#line 629 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = new std::vector<Parameter *>();
		auto param = new Parameter((yyvsp[(1) - (2)].ty), *(yyvsp[(2) - (2)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));

		delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 60:
#line 640 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = (yyvsp[(1) - (3)].args);
		(yyval.args)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 61:
#line 645 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = new std::vector<Expression *>();
		(yyval.args)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 62:
#line 651 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 63:
#line 652 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 64:
#line 653 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 65:
#line 654 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 66:
#line 658 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 67:
#line 659 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 68:
#line 660 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 69:
#line 661 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 70:
#line 662 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 71:
#line 663 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 72:
#line 667 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 73:
#line 668 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 74:
#line 669 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 75:
#line 670 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 76:
#line 671 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 77:
#line 672 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 78:
#line 674 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 79:
#line 675 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 80:
#line 679 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 81:
#line 680 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 82:
#line 681 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 83:
#line 682 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 84:
#line 683 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 85:
#line 685 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 86:
#line 686 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 87:
#line 687 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 88:
#line 689 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 89:
#line 690 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 90:
#line 691 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 91:
#line 692 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 92:
#line 693 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 93:
#line 694 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 94:
#line 698 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr),  1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 95:
#line 699 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr), -1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 96:
#line 700 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr),  1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 97:
#line 701 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr), -1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 98:
#line 706 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new TernaryExpr((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
	;}
    break;

  case 99:
#line 714 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		std::vector<Expression *> params;
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (3)].str), params);
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str);
	;}
    break;

  case 100:
#line 722 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(1) - (4)].str);
		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 101:
#line 732 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 102:
#line 733 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].val); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); ;}
    break;

  case 103:
#line 734 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new NegativeExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 104:
#line 735 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new StrValue(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 105:
#line 736 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IDReference(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 106:
#line 737 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new DerefExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 107:
#line 738 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ReferenceExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 108:
#line 739 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new CastExpr((yyvsp[(2) - (4)].ty), (yyvsp[(4) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 109:
#line 740 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayValue(*(yyvsp[(2) - (3)].exprs)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].exprs); ;}
    break;

  case 110:
#line 741 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayAccessExpr((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 111:
#line 742 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new AccessExpr((yyvsp[(1) - (3)].expr), *(yyvsp[(3) - (3)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 112:
#line 743 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 113:
#line 744 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].ty)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 114:
#line 749 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (3)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 115:
#line 754 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 116:
#line 763 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt(nullptr);
		SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 117:
#line 768 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt((yyvsp[(2) - (2)].expr));
		SET_LOCATION((yyval.node), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 118:
#line 776 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode*>();

		for (auto tupl : *(yyvsp[(2) - (2)].pairs))
		{
			VarDecl* decl = nullptr;

			if (module->getBlock()->is<ClassDecl*>())
			{
				decl = new MemberVarDecl((yyvsp[(1) - (2)].ty), std::get<0>(tupl), std::get<1>(tupl));
			}
			else
			{
				decl = new VarDecl((yyvsp[(1) - (2)].ty), std::get<0>(tupl), std::get<1>(tupl));
			}

			(yyval.nodes)->push_back(decl);
    		SET_LOCATION(decl, (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
		}

		delete (yyvsp[(2) - (2)].pairs);
	;}
    break;

  case 119:
#line 802 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (3)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (3)].str), nullptr));

		delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 120:
#line 809 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (5)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)));

		delete (yyvsp[(3) - (5)].str);
	;}
    break;

  case 121:
#line 816 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (1)].str), nullptr));

		delete (yyvsp[(1) - (1)].str);
	;}
    break;

  case 122:
#line 823 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].expr)));

		delete (yyvsp[(1) - (3)].str);
	;}
    break;

  case 123:
#line 832 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto estmt = new EnumStmt(*(yyvsp[(2) - (5)].str), IntType::get(64));
		for (auto pair : *(yyvsp[(4) - (5)].vpairs))
		{
			estmt->addMember(std::get<0>(pair), std::get<1>(pair));
		}

		(yyval.stmt) = estmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));

		delete (yyvsp[(2) - (5)].str);
		delete (yyvsp[(4) - (5)].vpairs);
	;}
    break;

  case 124:
#line 848 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (3)].str), (Value *)nullptr));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 125:
#line 853 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].val)));
		delete (yyvsp[(2) - (5)].str);
	;}
    break;

  case 126:
#line 858 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (2)].str), (Value *)nullptr));
		delete (yyvsp[(1) - (2)].str);
	;}
    break;

  case 127:
#line 864 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].val)));
		delete (yyvsp[(1) - (4)].str);
	;}
    break;

  case 128:
#line 872 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(1) - (1)].val);
		SET_LOCATION((yyval.val), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 129:
#line 877 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(2) - (2)].val);
		(yyvsp[(2) - (2)].val)->negate();
		SET_LOCATION((yyval.val), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 132:
#line 891 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = PointerType::get((yyvsp[(1) - (3)].ty));
	;}
    break;

  case 133:
#line 895 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = PointerType::get((yyvsp[(1) - (2)].ty));
	;}
    break;

  case 134:
#line 899 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 135:
#line 906 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(2) - (2)].ty)->getConst();
	;}
    break;

  case 136:
#line 910 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 137:
#line 914 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 138:
#line 921 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (2)].ty);

		bool is_const = true;
		for (unsigned int i = 0; i < (yyvsp[(2) - (2)].exprs)->size(); i++)
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

  case 139:
#line 956 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (4)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (4)].expr));
	;}
    break;

  case 140:
#line 961 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(2) - (3)].expr));
	;}
    break;

  case 141:
#line 968 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(64); ;}
    break;

  case 142:
#line 969 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(64); ;}
    break;

  case 143:
#line 970 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = FloatType::get(); ;}
    break;

  case 144:
#line 971 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = DoubleType::get(); ;}
    break;

  case 145:
#line 972 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(8); ;}
    break;

  case 146:
#line 973 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(16); ;}
    break;

  case 147:
#line 974 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(32); ;}
    break;

  case 148:
#line 975 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(64); ;}
    break;

  case 149:
#line 976 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(8); ;}
    break;

  case 150:
#line 977 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(16); ;}
    break;

  case 151:
#line 978 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(32); ;}
    break;

  case 152:
#line 979 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = UIntType::get(64); ;}
    break;

  case 153:
#line 980 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = IntType::get(8); ;}
    break;

  case 154:
#line 981 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = VoidType::get(); ;}
    break;

  case 155:
#line 982 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = VarType::get(); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3444 "/Users/robert/dev/orange/lib/grove/parser.cc"
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


#line 985 "/Users/robert/dev/orange/lib/grove/parser.y"



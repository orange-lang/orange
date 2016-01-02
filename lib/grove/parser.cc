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
     PROTECTED = 294,
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
     SIZEOF = 340,
     TYPE_ID = 341,
     THIS = 342,
     AT = 343,
     STATIC = 344,
     FROM = 345
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
#define PROTECTED 294
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
#define TYPE_ID 341
#define THIS 342
#define AT 343
#define STATIC 344
#define FROM 345




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
	#include <grove/MemberAccess.h>
	#include <grove/CtorCall.h>
	#include <grove/Protectable.h>

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
	#include <grove/types/ReferenceType.h>

	#include <grove/exceptions/code_error.h>

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
#line 81 "/Users/robert/dev/orange/lib/grove/parser.y"
{
	std::vector<ASTNode*>* nodes;
	std::vector<Parameter*>* params;
	std::vector<Expression*>* args;
	std::vector<Block*>* blocks;
	std::vector<Expression*>* exprs;
	std::vector<std::tuple<OString, Expression*>>* pairs;
	std::vector<std::tuple<OString, Value*>>* vpairs;
	std::tuple<OString, ProtectionLevel>* ppair;
	ASTNode* node;
	Block* block;
	Expression* expr;
	Statement* stmt;
	Value* val;
	OString* str;
	const Orange::Type* ty;
}
/* Line 193 of yacc.c.  */
#line 361 "/Users/robert/dev/orange/lib/grove/parser.cc"
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
#line 386 "/Users/robert/dev/orange/lib/grove/parser.cc"

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1552

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  190
/* YYNRULES -- Number of states.  */
#define YYNSTATES  354

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

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
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    19,    23,
      25,    26,    28,    30,    32,    34,    37,    40,    43,    45,
      48,    50,    52,    54,    56,    58,    60,    62,    64,    66,
      68,    70,    72,    73,    84,    85,    95,    98,    99,   107,
     117,   118,   126,   129,   130,   131,   138,   139,   146,   147,
     153,   155,   156,   163,   167,   171,   175,   179,   180,   193,
     194,   201,   202,   209,   210,   218,   228,   238,   242,   246,
     249,   252,   254,   255,   257,   258,   263,   266,   268,   269,
     271,   272,   276,   278,   280,   282,   284,   286,   288,   290,
     292,   294,   296,   298,   302,   306,   310,   314,   318,   322,
     326,   330,   334,   338,   342,   346,   350,   354,   358,   362,
     366,   370,   374,   378,   382,   386,   389,   392,   395,   398,
     404,   409,   414,   419,   421,   423,   427,   429,   432,   434,
     436,   439,   442,   447,   451,   456,   460,   464,   468,   471,
     476,   481,   485,   487,   489,   492,   495,   499,   505,   507,
     511,   517,   521,   527,   530,   535,   537,   540,   542,   544,
     548,   551,   553,   556,   558,   560,   563,   568,   572,   574,
     575,   577,   579,   581,   583,   584,   586,   588,   590,   592,
     594,   596,   598,   600,   602,   604,   606,   608,   610,   612,
     614
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      92,     0,    -1,    93,    -1,    93,    94,    -1,    93,    95,
      -1,    94,    -1,    95,    -1,   152,   154,    98,    -1,   152,
     154,    99,    -1,    93,    -1,    -1,   101,    -1,   131,    -1,
     132,    -1,   142,    -1,   101,   147,    -1,   131,   147,    -1,
     132,   147,    -1,   147,    -1,   142,   147,    -1,   142,    -1,
     132,    -1,   102,    -1,   106,    -1,   107,    -1,   110,    -1,
     115,    -1,   117,    -1,   118,    -1,   119,    -1,   124,    -1,
     144,    -1,    -1,     3,   138,     9,   128,    10,   105,   147,
     103,    96,     4,    -1,    -1,     3,   138,     9,   128,    10,
     105,    83,   104,    97,    -1,    53,   149,    -1,    -1,    63,
       8,     9,   128,    10,    53,   149,    -1,    63,     8,     9,
     127,    12,    64,    10,    53,   149,    -1,    -1,    36,     8,
     109,   147,   108,    96,     4,    -1,    90,    86,    -1,    -1,
      -1,     5,   132,   111,   147,    93,   112,    -1,    -1,     6,
     132,   113,   147,    93,   112,    -1,    -1,     7,   114,   147,
      93,     4,    -1,     4,    -1,    -1,    68,   132,   116,   147,
      93,     4,    -1,   131,     5,   132,    -1,   132,     5,   132,
      -1,   131,    68,   132,    -1,   132,    68,   132,    -1,    -1,
      74,     9,   125,    19,   126,    19,   126,    10,   147,   120,
      93,     4,    -1,    -1,    80,   132,   147,   121,    93,     4,
      -1,    -1,    75,    79,   147,   122,    93,     4,    -1,    -1,
      79,   147,   123,    93,     4,    80,   132,    -1,   131,    74,
       9,   125,    19,   126,    19,   126,    10,    -1,   132,    74,
       9,   125,    19,   126,    19,   126,    10,    -1,   131,    80,
     132,    -1,   132,    80,   132,    -1,   131,    75,    -1,   132,
      75,    -1,   100,    -1,    -1,   132,    -1,    -1,   127,    12,
     149,     8,    -1,   149,     8,    -1,   127,    -1,    -1,   130,
      -1,    -1,   130,    12,   132,    -1,   132,    -1,   141,    -1,
      77,    -1,    78,    -1,    76,    -1,   139,    -1,   133,    -1,
     134,    -1,   137,    -1,   135,    -1,   136,    -1,   132,    58,
     132,    -1,   132,    59,   132,    -1,   132,    56,   132,    -1,
     132,    57,   132,    -1,   132,    65,   132,    -1,   132,    66,
     132,    -1,   132,    69,   132,    -1,   132,    70,   132,    -1,
     132,    17,   132,    -1,   132,    16,   132,    -1,   132,    13,
     132,    -1,   132,    15,   132,    -1,   132,    60,   132,    -1,
     132,    71,   132,    -1,   132,    72,   132,    -1,   132,    73,
     132,    -1,   132,    47,   132,    -1,   132,    48,   132,    -1,
     132,    49,   132,    -1,   132,    50,   132,    -1,   132,    51,
     132,    -1,   132,    52,   132,    -1,   132,    45,    -1,   132,
      46,    -1,    45,   132,    -1,    46,   132,    -1,   132,    82,
     132,    83,   132,    -1,     8,     9,   129,    10,    -1,    86,
       9,   129,    10,    -1,   132,     9,   129,    10,    -1,     8,
      -1,    86,    -1,     9,   132,    10,    -1,    61,    -1,    16,
     132,    -1,    62,    -1,     8,    -1,    13,   132,    -1,    71,
     132,    -1,     9,   149,    10,   132,    -1,    43,   140,    44,
      -1,   132,    43,   132,    44,    -1,   132,    55,     8,    -1,
      86,    55,     8,    -1,    87,    55,     8,    -1,    88,     8,
      -1,    85,     9,   132,    10,    -1,    85,     9,   149,    10,
      -1,   140,    12,   132,    -1,   132,    -1,    35,    -1,    35,
     132,    -1,   149,   143,    -1,   143,    12,     8,    -1,   143,
      12,     8,    47,   132,    -1,     8,    -1,     8,    47,   132,
      -1,    84,     8,   147,   145,     4,    -1,   145,     8,   147,
      -1,   145,     8,    47,   146,   147,    -1,     8,   147,    -1,
       8,    47,   146,   147,    -1,    61,    -1,    16,    61,    -1,
      18,    -1,    19,    -1,   148,    43,    44,    -1,   149,    13,
      -1,   155,    -1,    81,   149,    -1,   150,    -1,   148,    -1,
     148,   151,    -1,   151,    43,   132,    44,    -1,    43,   132,
      44,    -1,   153,    -1,    -1,    40,    -1,    39,    -1,    38,
      -1,    89,    -1,    -1,    20,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    26,    -1,    28,    -1,    30,    -1,
      25,    -1,    27,    -1,    29,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   165,   165,   169,   176,   186,   193,   206,   248,   297,
     298,   302,   303,   304,   305,   309,   310,   311,   312,   316,
     323,   327,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   348,   347,   379,   378,   418,   419,   423,   431,
     443,   442,   459,   465,   469,   468,   499,   498,   516,   515,
     532,   540,   539,   558,   569,   583,   594,   610,   608,   626,
     625,   640,   639,   654,   653,   671,   681,   691,   698,   705,
     712,   722,   723,   727,   728,   732,   741,   753,   754,   758,
     759,   763,   768,   775,   776,   777,   778,   782,   783,   784,
     785,   786,   787,   791,   792,   793,   794,   795,   796,   798,
     799,   803,   804,   805,   806,   807,   809,   810,   811,   813,
     814,   815,   816,   817,   818,   822,   823,   824,   825,   829,
     837,   845,   853,   863,   864,   868,   869,   870,   871,   872,
     873,   874,   875,   876,   877,   878,   879,   889,   898,   907,
     908,   912,   917,   926,   931,   939,   965,   972,   979,   986,
     995,  1011,  1016,  1021,  1027,  1035,  1040,  1049,  1050,  1054,
    1058,  1062,  1069,  1073,  1077,  1084,  1119,  1124,  1132,  1133,
    1137,  1138,  1139,  1143,  1144,  1148,  1149,  1150,  1151,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,
    1163
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
  "USING", "PUBLIC", "PROTECTED", "PRIVATE", "OPEN_BRACE", "CLOSE_BRACE",
  "OPEN_BRACKET", "CLOSE_BRACKET", "INCREMENT", "DECREMENT", "ASSIGN",
  "PLUS_ASSIGN", "MINUS_ASSIGN", "TIMES_ASSIGN", "DIVIDE_ASSIGN",
  "MOD_ASSIGN", "ARROW", "ARROW_LEFT", "DOT", "LEQ", "GEQ", "COMP_LT",
  "COMP_GT", "MOD", "VALUE", "STRING", "EXTERN", "VARARG", "EQUALS",
  "NEQUALS", "WHEN", "UNLESS", "LOGICAL_AND", "LOGICAL_OR", "BITWISE_AND",
  "BITWISE_OR", "BITWISE_XOR", "FOR", "FOREVER", "LOOP", "CONTINUE",
  "BREAK", "DO", "WHILE", "CONST_FLAG", "QUESTION", "COLON", "ENUM",
  "SIZEOF", "TYPE_ID", "THIS", "AT", "STATIC", "FROM", "$accept", "start",
  "statements", "flagged_statement", "flagged_compound_statement",
  "opt_statements", "statement_no_term", "statement", "compound_statement",
  "valued", "structures", "function", "@1", "@2", "type_hint",
  "extern_function", "class_stmt", "@3", "opt_inheritance", "ifs", "@4",
  "else_if_or_end", "@5", "@6", "unless", "@7", "inline_if",
  "inline_unless", "for_loop", "@8", "@9", "@10", "@11", "inline_for_loop",
  "opt_valued", "opt_expression", "param_list", "opt_param_list",
  "opt_arg_list", "arg_list", "controls", "expression", "comparison",
  "arithmetic", "increment", "ternary", "call", "typename_or_identifier",
  "primary", "expr_list", "return", "var_decl", "var_decl_list",
  "enum_stmt", "enum_members", "pos_or_neg_value", "term", "non_agg_type",
  "type", "array_type", "array_def_list", "opt_protection_level",
  "protection_level", "opt_static", "basic_type", 0
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    93,    93,    93,    94,    95,    96,
      96,    97,    97,    97,    97,    98,    98,    98,    98,    99,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   103,   102,   104,   102,   105,   105,   106,   106,
     108,   107,   109,   109,   111,   110,   113,   112,   114,   112,
     112,   116,   115,   117,   117,   118,   118,   120,   119,   121,
     119,   122,   119,   123,   119,   124,   124,   124,   124,   124,
     124,   125,   125,   126,   126,   127,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   131,   131,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     133,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   135,   135,   135,   136,
     137,   137,   137,   138,   138,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   141,   141,   142,   143,   143,   143,   143,
     144,   145,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   148,   149,   149,   149,   150,   151,   151,   152,   152,
     153,   153,   153,   154,   154,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     3,     3,     1,
       0,     1,     1,     1,     1,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,    10,     0,     9,     2,     0,     7,     9,
       0,     7,     2,     0,     0,     6,     0,     6,     0,     5,
       1,     0,     6,     3,     3,     3,     3,     0,    12,     0,
       6,     0,     6,     0,     7,     9,     9,     3,     3,     2,
       2,     1,     0,     1,     0,     4,     2,     1,     0,     1,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     5,
       4,     4,     4,     1,     1,     3,     1,     2,     1,     1,
       2,     2,     4,     3,     4,     3,     3,     3,     2,     4,
       4,     3,     1,     1,     2,     2,     3,     5,     1,     3,
       5,     3,     5,     2,     4,     1,     2,     1,     1,     3,
       2,     1,     2,     1,     1,     2,     4,     3,     1,     0,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     169,   172,   171,   170,     0,   169,     5,     6,   174,   168,
       1,     3,     4,   173,     0,     0,     0,   129,     0,     0,
       0,   157,   158,   175,   176,   177,   178,   179,   183,   180,
     184,   181,   185,   182,   186,   187,   188,   189,   143,     0,
       0,     0,     0,   126,   128,     0,     0,     0,     0,     0,
      86,    84,    85,     0,     0,     0,     0,     0,   190,     0,
       0,     7,     8,     0,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,    88,    89,    91,    92,    90,
      87,    83,     0,    31,    18,   164,     0,   163,   161,   123,
     124,     0,     0,    44,    80,     0,     0,   130,   127,   144,
      43,   142,     0,   117,   118,     0,    51,   131,    72,     0,
      63,     0,   190,   162,     0,     0,    80,     0,     0,   138,
      15,     0,     0,     0,    69,     0,    16,     0,    80,     0,
       0,     0,     0,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
      17,    19,     0,   165,   148,   160,   145,    78,     0,     0,
      79,    82,   125,     0,     0,     0,     0,   133,    78,     0,
      71,     0,    21,    20,    61,   169,    59,     0,     0,     0,
       0,   136,   137,    53,    55,    72,    67,    54,     0,   103,
     104,   102,   101,     0,   109,   110,   111,   112,   113,   114,
     135,    95,    96,    93,    94,   105,    97,    98,    56,    99,
     100,   106,   107,   108,    72,    68,     0,   159,     0,     0,
       0,     0,    77,     0,     0,   169,   120,     0,   132,    42,
      40,   141,    77,     0,   169,    74,   169,   169,   169,     0,
       0,   139,   140,   121,     0,   122,   134,     0,     0,   167,
       0,   149,   146,     0,    37,    76,   169,    81,   169,     0,
       0,   169,     0,    73,   169,     0,   169,     0,   153,   150,
       0,    74,    74,   119,   166,     0,     0,     0,     0,    50,
       0,    48,    45,   169,     0,     0,     0,    52,    74,    62,
       0,    60,     0,   155,     0,     0,   151,     0,     0,   147,
      75,    36,    34,    32,    46,     0,    41,     0,    38,     0,
      64,   156,   154,     0,    74,    74,     0,   169,     0,   169,
       0,     0,   152,     0,     0,    35,    11,    12,    13,    14,
       0,   169,   169,    39,    57,    65,    66,    33,   169,    49,
     169,    47,   169,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   293,     6,     7,   294,   335,    61,    62,   180,
      63,    64,   327,   326,   288,    65,    66,   268,   175,    67,
     168,   292,   328,   315,    68,   179,    69,    70,    71,   350,
     248,   246,   185,    72,   181,   272,   232,   233,   169,   170,
      73,   273,    75,    76,    77,    78,    79,    91,    80,   102,
      81,   183,   166,    83,   250,   304,    84,    85,    86,    87,
     163,     8,     9,    14,    88
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -171
static const yytype_int16 yypact[] =
{
     170,  -171,  -171,  -171,    20,   154,  -171,  -171,   -63,  -171,
    -171,  -171,  -171,  -171,   344,    -6,   542,    19,   511,   542,
     542,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,   542,    33,
     542,   542,   542,  -171,  -171,    42,   542,   542,    53,   -19,
    -171,  -171,  -171,   107,   542,   150,    76,    77,    21,    47,
      96,  -171,  -171,   107,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,    -1,   601,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,   107,  -171,  -171,    66,    34,  -171,  -171,  -171,
    -171,   124,    21,  1220,   542,   880,    98,    50,   277,  1220,
      57,  1220,     4,  -171,  -171,   139,  1220,    55,   511,   107,
    -171,   812,  -171,   143,   107,   511,   542,   144,   149,  -171,
    -171,   542,   542,   180,  -171,   542,  -171,   542,   542,   542,
     542,   542,   542,   542,  -171,  -171,   542,   542,   542,   542,
     542,   542,   151,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   191,  -171,   542,   542,
    -171,  -171,   152,   120,   159,  -171,   200,   150,   107,   207,
     210,  1220,  -171,   542,   133,   107,   542,  -171,   150,   107,
    -171,   206,  1220,  -171,  -171,   170,  -171,   221,   948,   104,
     231,  -171,  -171,  1220,  1220,   511,  1220,  1220,   232,    50,
      50,   277,   277,  1016,  1220,  1220,  1220,  1220,  1220,  1220,
    -171,  1460,  1460,  1460,  1460,    50,  1408,  1408,  1220,  1384,
    1323,    55,  1479,     6,   511,  1220,   741,  -171,  1084,   542,
     542,   237,   235,   245,    45,   170,  -171,   542,   156,  -171,
    -171,  1220,   244,   251,   170,   542,   170,    51,   170,    16,
      36,  -171,  -171,  -171,   259,  -171,  -171,   261,   542,  -171,
    1152,  1220,   236,   150,   229,  -171,   220,  1220,   165,  1286,
     240,   214,   266,  1220,   226,   208,   264,     8,  -171,  -171,
     169,   542,   542,  1288,  -171,   542,    75,   150,    -5,  -171,
     542,  -171,  -171,   269,   290,   285,   150,  -171,   542,  -171,
     542,  -171,   239,  -171,   107,     8,  -171,   278,   282,  1220,
    -171,   143,  -171,  -171,  1220,   107,  -171,   252,   143,   300,
    1220,  -171,  -171,   107,   542,   542,   430,   165,   107,   170,
     150,   107,  -171,   302,   303,  -171,  -171,     7,   673,  -171,
     312,   170,   295,   143,  -171,  -171,  -171,  -171,   220,  -171,
     170,  -171,   354,  -171
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,  -171,     0,    -4,     3,    -8,  -171,  -171,  -171,  -171,
      -2,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,   -27,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -170,   -91,   147,   148,   -89,  -171,
       1,    -9,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,   -11,  -171,  -171,  -171,    23,   -17,  -171,   -12,  -171,
    -171,  -171,  -171,  -171,  -171
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -11
static const yytype_int16 yytable[] =
{
       5,    11,    89,    82,   121,    74,    96,    93,    12,    95,
      97,    98,   121,    21,    22,   128,   176,    21,    22,   129,
      10,   130,   131,   132,   302,   254,    13,   190,    94,    99,
     116,   101,   103,   104,    21,    22,   110,   106,   107,   198,
     279,   100,   164,   113,   280,   111,   120,   165,   177,   133,
     105,   134,   135,   265,   257,   275,   126,   160,   165,   128,
     109,   142,   108,   277,   128,   161,   147,   122,   129,   303,
     130,   131,   132,   123,   124,   122,   117,   153,   312,   125,
      90,   123,   124,   310,   114,   171,   115,   125,   165,     1,
       2,     3,   184,   133,   186,   134,   135,   187,   133,   182,
     134,   135,   118,   189,   119,   142,   188,   171,   173,   162,
     142,   165,   193,   194,   252,   147,   196,   165,   197,   171,
     199,   200,   201,   202,   203,    21,    22,   204,   205,   206,
     207,   208,   209,   167,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   174,   178,   225,
     226,   235,   191,   228,    -2,   234,   165,   192,   240,   210,
      17,    18,   244,   229,   238,    19,   234,   241,    20,   -10,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   247,   182,    21,    22,   195,
     307,   308,     1,     2,     3,    40,   227,    41,    42,   133,
     224,   134,   135,     1,     2,     3,   230,   319,     1,     2,
       3,   142,   231,    43,    44,   182,   305,   236,   297,   239,
     260,   261,   237,    47,   289,   245,   290,   291,   267,   249,
     299,    55,   278,   333,   334,   266,   112,    57,    92,    59,
      60,   253,   255,    11,   271,   262,   274,   263,   276,   283,
      12,   286,     1,     2,     3,   264,   269,   286,     1,     2,
       3,   270,    11,   306,     1,     2,     3,    11,   301,    12,
      11,   313,    11,    -9,    12,   311,   309,    12,   281,    12,
     282,   314,   287,   285,   318,   298,   128,   322,   300,    11,
     129,   320,   130,   296,   316,   317,    12,   324,   329,   349,
     321,   325,     1,     2,     3,   330,   332,     1,     2,     3,
     331,   341,   345,   346,   344,   339,   347,   338,   343,   340,
     133,   351,   134,   135,   336,   242,   243,   337,   323,   342,
       0,     0,   142,     1,     2,     3,     0,   147,    11,     0,
       0,   348,     0,     0,    11,    12,     0,    15,    11,    16,
     352,    12,    17,    18,     0,    12,     0,    19,   353,     0,
      20,     0,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,     0,     0,     0,     0,     0,    40,     0,    41,
      42,     0,     1,     2,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,     0,     0,
       0,     0,    46,     0,     0,    47,     0,     0,    48,    49,
      50,    51,    52,    53,    54,    55,     0,     0,    56,    57,
      58,    59,    60,    15,     0,    16,     0,     0,    17,    18,
       0,     0,     0,    19,     0,     0,    20,     0,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,     0,     0,
       0,     0,     0,    40,     0,    41,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,     0,     0,     0,     0,    46,     0,
       0,    47,     0,     0,    48,    49,    50,    51,    52,    53,
      54,    55,     0,     0,    56,    57,    58,    59,    60,    17,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     0,     0,     0,     0,
      17,    18,     0,     0,    40,    19,    41,    42,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    47,     0,     0,    40,     0,    41,    42,     0,
       0,     0,    55,     0,     0,     0,    57,    58,    59,    60,
       0,     0,     0,    43,    44,     0,   127,     0,     0,     0,
     128,     0,     0,    47,   129,     0,   130,   131,   132,    21,
      22,     0,     0,     0,     0,     0,     0,    57,    92,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   137,
     138,   139,   140,   141,     0,     0,   142,   143,   144,   145,
     146,   147,     0,     0,     0,     0,   148,   149,     0,   150,
     151,   152,   153,   154,   155,   156,   157,     0,   127,     0,
       0,   158,   128,   159,     0,     0,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,   142,   143,
     144,   145,   146,   147,     0,     0,     0,     0,   148,   149,
       0,   150,   151,   152,   153,   154,   155,   156,   157,     0,
     128,     0,     0,   158,   129,   159,   130,   131,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   137,
     138,   139,   140,   141,     0,     0,   142,   143,   144,   145,
     146,   147,     0,     0,     0,     0,   148,   149,     0,     0,
     151,   152,   153,   154,   155,     0,     0,     0,     0,     0,
       0,   128,     0,   159,   258,   129,     0,   130,   131,   132,
      21,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     137,   138,   139,   140,   141,     0,     0,   142,   143,   144,
     145,   146,   147,     0,     0,     0,     0,   148,   149,     0,
       0,   151,   152,   153,   154,   155,     0,     0,     0,   128,
     172,     0,     0,   129,   159,   130,   131,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   137,   138,
     139,   140,   141,     0,     0,   142,   143,   144,   145,   146,
     147,     0,     0,     0,     0,   148,   149,     0,     0,   151,
     152,   153,   154,   155,     0,     0,     0,   128,   251,     0,
       0,   129,   159,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   137,   138,   139,   140,
     141,     0,     0,   142,   143,   144,   145,   146,   147,     0,
       0,     0,     0,   148,   149,     0,     0,   151,   152,   153,
     154,   155,     0,     0,     0,   128,     0,     0,     0,   129,
     159,   130,   131,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     256,   134,   135,   136,   137,   138,   139,   140,   141,     0,
       0,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,   148,   149,     0,     0,   151,   152,   153,   154,   155,
       0,     0,     0,   128,     0,     0,     0,   129,   159,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   133,   259,   134,
     135,   136,   137,   138,   139,   140,   141,     0,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,     0,   148,
     149,     0,     0,   151,   152,   153,   154,   155,     0,     0,
       0,   128,     0,     0,     0,   129,   159,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   284,   134,   135,   136,
     137,   138,   139,   140,   141,     0,     0,   142,   143,   144,
     145,   146,   147,     0,     0,     0,     0,   148,   149,     0,
       0,   151,   152,   153,   154,   155,     0,     0,     0,   128,
       0,     0,     0,   129,   159,   130,   131,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   137,   138,
     139,   140,   141,     0,     0,   142,   143,   144,   145,   146,
     147,     0,     0,     0,     0,   148,   149,     0,     0,   151,
     152,   153,   154,   155,     0,     0,     0,   128,     0,     0,
       0,   129,   159,   130,   131,   132,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,   128,   134,   135,     0,   129,     0,   130,   131,
     132,     0,     0,   142,   143,   144,   145,   146,   147,     0,
     295,     0,     0,   148,   149,     0,     0,   151,   152,   153,
     154,   155,     0,     0,     0,     0,   133,    55,   134,   135,
     159,     0,   112,     0,     0,     0,     0,     0,   142,   143,
     144,   145,   146,   147,     0,     0,     0,     0,   148,   149,
       0,     0,   151,   128,   153,   154,   155,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,     0,     0,
       0,   129,     0,   130,   131,   132,     0,   133,     0,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,     0,   148,
     149,   133,     0,   134,   135,   153,   154,   155,     0,     0,
       0,     0,     0,   142,   143,   144,   145,   146,   147,   128,
       0,     0,     0,   129,     0,   130,   131,   132,     0,   153,
     154,   155,     0,     0,     0,     0,     0,     0,   128,     0,
       0,     0,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,   134,   135,     0,     0,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,     0,
     147,     0,   133,     0,   134,   135,     0,     0,     0,     0,
       0,   153,   154,   155,   142,     0,     0,     0,     0,   147,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     153,     0,   155
};

static const yytype_int16 yycheck[] =
{
       0,     5,     8,    14,     5,    14,    18,    16,     5,    18,
      19,    20,     5,    18,    19,     9,    12,    18,    19,    13,
       0,    15,    16,    17,    16,   195,    89,   116,     9,    38,
       9,    40,    41,    42,    18,    19,    53,    46,    47,   128,
       4,     8,     8,    55,     8,    54,    63,    13,    44,    43,
       8,    45,    46,     8,   224,     4,    73,    74,    13,     9,
      79,    55,     9,    47,     9,    82,    60,    68,    13,    61,
      15,    16,    17,    74,    75,    68,    55,    71,    83,    80,
      86,    74,    75,     8,     8,    94,     9,    80,    13,    38,
      39,    40,   109,    43,   111,    45,    46,   114,    43,   108,
      45,    46,    55,   115,     8,    55,   115,   116,    10,    43,
      55,    13,   121,   122,    10,    60,   125,    13,   127,   128,
     129,   130,   131,   132,   133,    18,    19,   136,   137,   138,
     139,   140,   141,     9,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,    90,     9,   158,
     159,   168,     8,   162,     0,   167,    13,     8,   175,     8,
       8,     9,   179,    43,   173,    13,   178,   176,    16,     4,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   185,   195,    18,    19,     9,
     281,   282,    38,    39,    40,    43,    44,    45,    46,    43,
       9,    45,    46,    38,    39,    40,    47,   298,    38,    39,
      40,    55,    12,    61,    62,   224,    47,    10,     4,    86,
     229,   230,    12,    71,     4,    19,     6,     7,   237,     8,
       4,    81,   249,   324,   325,   235,    86,    85,    86,    87,
      88,    10,    10,   247,   244,     8,   246,    12,   248,   258,
     247,   263,    38,    39,    40,    10,    12,   269,    38,    39,
      40,    10,   266,   280,    38,    39,    40,   271,     4,   266,
     274,   288,   276,     4,   271,   287,   285,   274,    19,   276,
      19,   290,    53,    47,   296,    19,     9,   304,    80,   293,
      13,   300,    15,    53,     4,    10,   293,    19,   315,     4,
      61,    19,    38,    39,    40,    53,   323,    38,    39,    40,
      10,   328,    10,    10,   331,   326,     4,   326,   330,   327,
      43,   348,    45,    46,   326,   178,   178,   326,   305,   329,
      -1,    -1,    55,    38,    39,    40,    -1,    60,   342,    -1,
      -1,   341,    -1,    -1,   348,   342,    -1,     3,   352,     5,
     350,   348,     8,     9,    -1,   352,    -1,    13,     4,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,    85,
      86,    87,    88,     3,    -1,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    84,    85,    86,    87,    88,     8,
       9,    -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
       8,     9,    -1,    -1,    43,    13,    45,    46,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    -1,    61,    62,    -1,     5,    -1,    -1,    -1,
       9,    -1,    -1,    71,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,     5,    -1,
      -1,    80,     9,    82,    -1,    -1,    13,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
       9,    -1,    -1,    80,    13,    82,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    -1,    82,    83,    13,    -1,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,     9,
      10,    -1,    -1,    13,    82,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    -1,    -1,    -1,     9,    10,    -1,
      -1,    13,    82,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,
      72,    73,    -1,    -1,    -1,     9,    -1,    -1,    -1,    13,
      82,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,    69,    70,    71,    72,    73,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    13,    82,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    13,    82,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    13,    82,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    82,    15,    16,    17,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,     9,    45,    46,    -1,    13,    -1,    15,    16,
      17,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      64,    -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    43,    81,    45,    46,
      82,    -1,    86,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    69,     9,    71,    72,    73,    13,    -1,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    15,    16,    17,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    43,    -1,    45,    46,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,     9,
      -1,    -1,    -1,    13,    -1,    15,    16,    17,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    55,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,    40,    92,    93,    94,    95,   152,   153,
       0,    94,    95,    89,   154,     3,     5,     8,     9,    13,
      16,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      43,    45,    46,    61,    62,    63,    68,    71,    74,    75,
      76,    77,    78,    79,    80,    81,    84,    85,    86,    87,
      88,    98,    99,   101,   102,   106,   107,   110,   115,   117,
     118,   119,   124,   131,   132,   133,   134,   135,   136,   137,
     139,   141,   142,   144,   147,   148,   149,   150,   155,     8,
      86,   138,    86,   132,     9,   132,   149,   132,   132,   132,
       8,   132,   140,   132,   132,     8,   132,   132,     9,    79,
     147,   132,    86,   149,     8,     9,     9,    55,    55,     8,
     147,     5,    68,    74,    75,    80,   147,     5,     9,    13,
      15,    16,    17,    43,    45,    46,    47,    48,    49,    50,
      51,    52,    55,    56,    57,    58,    59,    60,    65,    66,
      68,    69,    70,    71,    72,    73,    74,    75,    80,    82,
     147,   147,    43,   151,     8,    13,   143,     9,   111,   129,
     130,   132,    10,    10,    90,   109,    12,    44,     9,   116,
     100,   125,   132,   142,   147,   123,   147,   147,   132,   149,
     129,     8,     8,   132,   132,     9,   132,   132,   129,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
       8,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,     9,   132,   132,    44,   132,    43,
      47,    12,   127,   128,   149,   147,    10,    12,   132,    86,
     147,   132,   127,   128,   147,    19,   122,    93,   121,     8,
     145,    10,    10,    10,   125,    10,    44,   125,    83,    44,
     132,   132,     8,    12,    10,     8,    93,   132,   108,    12,
      10,    93,   126,   132,    93,     4,    93,    47,   147,     4,
       8,    19,    19,   132,    44,    47,   149,    53,   105,     4,
       6,     7,   112,    93,    96,    64,    53,     4,    19,     4,
      80,     4,    16,    61,   146,    47,   147,   126,   126,   132,
       8,   149,    83,   147,   132,   114,     4,    10,   149,   126,
     132,    61,   147,   146,    19,    19,   104,   103,   113,   147,
      53,    10,   147,   126,   126,    97,   101,   131,   132,   142,
      96,   147,    93,   149,   147,    10,    10,     4,    93,     4,
     120,   112,    93,     4
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
        case 3:
#line 170 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		if ((yyvsp[(2) - (2)].node) != nullptr)
		{
			module->getBlock()->addStatement((yyvsp[(2) - (2)].node));
		}
	;}
    break;

  case 4:
#line 177 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		for (auto stmt : *(yyvsp[(2) - (2)].nodes))
		{
			if (stmt == nullptr) continue;
			module->getBlock()->addStatement(stmt);
		}

		delete (yyvsp[(2) - (2)].nodes);
	;}
    break;

  case 5:
#line 187 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		if ((yyvsp[(1) - (1)].node) != nullptr)
		{
			module->getBlock()->addStatement((yyvsp[(1) - (1)].node));
		}
	;}
    break;

  case 6:
#line 194 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		for (auto stmt : *(yyvsp[(1) - (1)].nodes))
		{
			if (stmt == nullptr) continue;
			module->getBlock()->addStatement(stmt);
		}

		delete (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 7:
#line 206 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = (yyvsp[(3) - (3)].node);

		if ((yyvsp[(1) - (3)].ppair) != nullptr)
		{
			if ((yyval.node)->is<Protectable*>() == false)
			{
				auto pair = *(yyvsp[(1) - (3)].ppair);
				throw code_error((yyval.node), [pair]() -> std::string
				{
					std::stringstream ss;
					ss << "Keyword " << std::get<0>(pair).str()
					   << " can't be used here";
					return ss.str();
				});
			}

			(yyval.node)->as<Protectable*>()->setProtectionLevel(std::get<1>(*(yyvsp[(1) - (3)].ppair)));
			delete (yyvsp[(1) - (3)].ppair);
		}

		if ((yyvsp[(2) - (3)].str) != nullptr)
		{
			if ((yyval.node)->is<Staticable*>() == false)
			{
				auto str = *(yyvsp[(2) - (3)].str);
				throw code_error((yyval.node), [str]() -> std::string
				{
					std::stringstream ss;
					ss << "Keyword " << str.str()
					   << " can't be used here";
					return ss.str();
				});
			}

			(yyval.node)->as<Staticable*>()->setStatic(true);
			delete (yyvsp[(2) - (3)].str);
		}
	;}
    break;

  case 8:
#line 248 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(3) - (3)].nodes);

		if ((yyvsp[(1) - (3)].ppair) != nullptr)
		{
			for (auto stmt : *(yyval.nodes))
			{
				if (stmt->is<Protectable*>() == false)
				{
					auto pair = *(yyvsp[(1) - (3)].ppair);
					throw code_error(stmt, [pair]() -> std::string
					{
						std::stringstream ss;
						ss << "Keyword " << std::get<0>(pair).str()
						   << " can't be used here";
						return ss.str();
					});
				}

				stmt->as<Protectable*>()->setProtectionLevel(std::get<1>(*(yyvsp[(1) - (3)].ppair)));
			}
			delete (yyvsp[(1) - (3)].ppair);
		}

		if ((yyvsp[(2) - (3)].str) != nullptr)
		{
			for (auto stmt : *(yyval.nodes))
			{
				if (stmt->is<Staticable*>() == false)
				{
					auto str = *(yyvsp[(2) - (3)].str);
					throw code_error(stmt, [str]() -> std::string
					{
						std::stringstream ss;
						ss << "Keyword " << str.str()
						   << " can't be used here";
						return ss.str();
					});
				}

				stmt->as<Staticable*>()->setStatic(true);
			}

			delete (yyvsp[(2) - (3)].str);
		}
	;}
    break;

  case 11:
#line 302 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].stmt)); ;}
    break;

  case 12:
#line 303 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].node)); ;}
    break;

  case 13:
#line 304 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].expr)); ;}
    break;

  case 14:
#line 305 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 15:
#line 309 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].stmt); ;}
    break;

  case 16:
#line 310 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 17:
#line 311 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].expr); ;}
    break;

  case 18:
#line 312 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 19:
#line 317 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);
	;}
    break;

  case 20:
#line 324 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 21:
#line 328 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();
		(yyval.nodes)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 22:
#line 334 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 23:
#line 335 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 24:
#line 336 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 25:
#line 337 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 26:
#line 338 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 27:
#line 339 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 28:
#line 340 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 29:
#line 341 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 30:
#line 342 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 31:
#line 343 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 32:
#line 348 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		Function* func = nullptr;

		if (module->getBlock()->is<ClassDecl *>())
		{
			func = new ClassMethod(*(yyvsp[(2) - (7)].str), module->getBlock()->as<ClassDecl *>(),
								   *(yyvsp[(4) - (7)].params));
		}
		else
		{
			func = new Function(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params));
		}

		func->setReturnType((yyvsp[(6) - (7)].ty));

		module->pushBlock(func);
		(yyval.stmt) = func;
	;}
    break;

  case 33:
#line 367 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto func = (Function *)(yyvsp[(8) - (10)].stmt);

		(yyval.stmt) = func;
        SET_LOCATION((yyval.stmt), (yylsp[(1) - (10)]), (yylsp[(10) - (10)]));

		module->popBlock();

		delete (yyvsp[(2) - (10)].str);
		delete (yyvsp[(4) - (10)].params);
	;}
    break;

  case 34:
#line 379 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		Function* func = nullptr;

		if (module->getBlock()->is<ClassDecl *>())
		{
			func = new ClassMethod(*(yyvsp[(2) - (7)].str), module->getBlock()->as<ClassDecl *>(),
								   *(yyvsp[(4) - (7)].params));
		}
		else
		{
			func = new Function(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params));
		}

		func->setReturnType((yyvsp[(6) - (7)].ty));

		module->pushBlock(func);
		(yyval.stmt) = func;
	;}
    break;

  case 35:
#line 398 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto func = (Function *)(yyvsp[(8) - (9)].stmt);

		for (auto statement : *(yyvsp[(9) - (9)].nodes))
		{
			func->addStatement(statement);
		}

		(yyval.stmt) = func;
        SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		module->popBlock();

		delete (yyvsp[(2) - (9)].str);
		delete (yyvsp[(4) - (9)].params);
		delete (yyvsp[(9) - (9)].nodes);
	;}
    break;

  case 36:
#line 418 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = (yyvsp[(2) - (2)].ty); ;}
    break;

  case 37:
#line 419 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 38:
#line 424 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params), (yyvsp[(7) - (7)].ty));
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));

		delete (yyvsp[(2) - (7)].str);
		delete (yyvsp[(4) - (7)].params);
	;}
    break;

  case 39:
#line 432 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params), (yyvsp[(9) - (9)].ty), true);
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(2) - (9)].str);
		delete (yyvsp[(4) - (9)].params);
	;}
    break;

  case 40:
#line 443 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ClassDecl(*(yyvsp[(2) - (4)].str));
		(yyval.stmt)->setModule(module);
		module->pushBlock((Block *)(yyval.stmt));
		delete (yyvsp[(2) - (4)].str);
	;}
    break;

  case 41:
#line 449 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		ClassDecl* inst = (ClassDecl *)(yyvsp[(5) - (7)].stmt);

		(yyval.stmt) = inst;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));

		module->popBlock();
	;}
    break;

  case 42:
#line 460 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = new ReferenceType(*(yyvsp[(2) - (2)].str));
		SET_LOCATION((yyval.ty)->as<ASTNode *>(), (yylsp[(2) - (2)]), (yylsp[(2) - (2)]))
		delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 43:
#line 465 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 44:
#line 469 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr));
		(yyval.stmt) = block;
		module->pushBlock(block);
	;}
    break;

  case 45:
#line 475 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto blocks = (yyvsp[(6) - (6)].blocks);

		auto block = (CondBlock *)(yyvsp[(3) - (6)].stmt);

		blocks->insert(blocks->begin(), block);

		auto if_stmt = new IfStmt();
		for (auto block : *blocks)
		{
			if_stmt->addBlock(block);
		}

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));

		module->popBlock();

		delete blocks;
	;}
    break;

  case 46:
#line 499 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr));
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 47:
#line 505 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = (yyvsp[(6) - (6)].blocks);

		auto block = (CondBlock *)(yyvsp[(3) - (6)].stmt);

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 48:
#line 516 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new Block();
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 49:
#line 522 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();

		auto block = (Block *)(yyvsp[(2) - (5)].stmt);

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
		module->popBlock();
	;}
    break;

  case 50:
#line 533 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();
	;}
    break;

  case 51:
#line 540 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr), true);
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 52:
#line 546 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = (CondBlock *)(yyvsp[(3) - (6)].stmt);

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 53:
#line 559 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 54:
#line 570 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr));
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 55:
#line 584 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].node));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 56:
#line 595 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(3) - (3)].expr), true);
		block->addStatement((yyvsp[(1) - (3)].expr));

		auto if_stmt = new IfStmt();
		if_stmt->addBlock(block);

		(yyval.stmt) = if_stmt;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 57:
#line 610 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(3) - (9)].nodes), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 58:
#line 616 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(10) - (12)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (12)]), (yylsp[(12) - (12)]));
		module->popBlock();

		delete (yyvsp[(3) - (12)].nodes);
	;}
    break;

  case 59:
#line 626 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(2) - (3)].expr), nullptr, false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 60:
#line 632 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(4) - (6)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 61:
#line 640 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 62:
#line 646 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(4) - (6)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 63:
#line 654 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, true);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 64:
#line 660 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(3) - (7)].stmt);
		loop->setCondition((yyvsp[(7) - (7)].expr));

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));
		module->popBlock();
	;}
    break;

  case 65:
#line 673 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 66:
#line 683 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 67:
#line 692 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 68:
#line 699 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 69:
#line 706 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 70:
#line 713 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 71:
#line 722 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 72:
#line 723 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); ;}
    break;

  case 73:
#line 727 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 74:
#line 728 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = nullptr; ;}
    break;

  case 75:
#line 733 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = (yyvsp[(1) - (4)].params);
		auto param = new Parameter((yyvsp[(3) - (4)].ty), *(yyvsp[(4) - (4)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(4) - (4)].str);
	;}
    break;

  case 76:
#line 742 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = new std::vector<Parameter *>();
		auto param = new Parameter((yyvsp[(1) - (2)].ty), *(yyvsp[(2) - (2)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));

		delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 77:
#line 753 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.params) = (yyvsp[(1) - (1)].params); ;}
    break;

  case 78:
#line 754 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.params) = new std::vector<Parameter *>(); ;}
    break;

  case 79:
#line 758 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.args) = (yyvsp[(1) - (1)].args); ;}
    break;

  case 80:
#line 759 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.args) = new std::vector<Expression *>(); ;}
    break;

  case 81:
#line 764 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = (yyvsp[(1) - (3)].args);
		(yyval.args)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 82:
#line 769 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = new std::vector<Expression *>();
		(yyval.args)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 83:
#line 775 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 84:
#line 776 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 85:
#line 777 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 86:
#line 778 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 87:
#line 782 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 88:
#line 783 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 89:
#line 784 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 90:
#line 785 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 91:
#line 786 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 92:
#line 787 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 93:
#line 791 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 94:
#line 792 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 95:
#line 793 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 96:
#line 794 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 97:
#line 795 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 98:
#line 796 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 99:
#line 798 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 100:
#line 799 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 101:
#line 803 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 102:
#line 804 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 103:
#line 805 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 104:
#line 806 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 105:
#line 807 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 106:
#line 809 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 107:
#line 810 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 108:
#line 811 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 109:
#line 813 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 110:
#line 814 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 111:
#line 815 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 112:
#line 816 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 113:
#line 817 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 114:
#line 818 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 115:
#line 822 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr),  1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 116:
#line 823 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr), -1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 117:
#line 824 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr),  1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 118:
#line 825 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr), -1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 119:
#line 830 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new TernaryExpr((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
	;}
    break;

  case 120:
#line 838 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(1) - (4)].str);
		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 121:
#line 846 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new CtorCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(1) - (4)].str);
		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 122:
#line 854 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new ExpressionCall((yyvsp[(1) - (4)].expr), *(yyvsp[(3) - (4)].args), true);
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 123:
#line 863 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 124:
#line 864 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 125:
#line 868 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 126:
#line 869 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].val); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); ;}
    break;

  case 127:
#line 870 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new NegativeExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 128:
#line 871 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new StrValue(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 129:
#line 872 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IDReference(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 130:
#line 873 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new DerefExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 131:
#line 874 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ReferenceExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 132:
#line 875 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new CastExpr((yyvsp[(2) - (4)].ty), (yyvsp[(4) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 133:
#line 876 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayValue(*(yyvsp[(2) - (3)].exprs)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].exprs); ;}
    break;

  case 134:
#line 877 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayAccessExpr((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 135:
#line 878 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new AccessExpr((yyvsp[(1) - (3)].expr), *(yyvsp[(3) - (3)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 136:
#line 879 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto ref = new ReferenceType(*(yyvsp[(1) - (3)].str));
		SET_LOCATION(ref, (yylsp[(1) - (3)]), (yylsp[(1) - (3)]));

		(yyval.expr) = new AccessExpr(ref, *(yyvsp[(3) - (3)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str);
		delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 137:
#line 889 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto lhs = new IDReference("this");
		SET_LOCATION(lhs, (yylsp[(1) - (3)]), (yylsp[(1) - (3)]));

		(yyval.expr) = new AccessExpr(lhs, *(yyvsp[(3) - (3)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str); delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 138:
#line 898 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto lhs = new IDReference("this");
		SET_LOCATION(lhs, (yylsp[(1) - (2)]), (yylsp[(1) - (2)]));

		(yyval.expr) = new AccessExpr(lhs, *(yyvsp[(2) - (2)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));

		delete (yyvsp[(1) - (2)].str); delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 139:
#line 907 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 140:
#line 908 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].ty)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 141:
#line 913 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (3)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 142:
#line 918 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 143:
#line 927 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt(nullptr);
		SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 144:
#line 932 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt((yyvsp[(2) - (2)].expr));
		SET_LOCATION((yyval.node), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 145:
#line 940 "/Users/robert/dev/orange/lib/grove/parser.y"
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

  case 146:
#line 966 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (3)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (3)].str), nullptr));

		delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 147:
#line 973 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (5)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)));

		delete (yyvsp[(3) - (5)].str);
	;}
    break;

  case 148:
#line 980 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (1)].str), nullptr));

		delete (yyvsp[(1) - (1)].str);
	;}
    break;

  case 149:
#line 987 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].expr)));

		delete (yyvsp[(1) - (3)].str);
	;}
    break;

  case 150:
#line 996 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto estmt = new EnumStmt(*(yyvsp[(2) - (5)].str), module, Orange::IntType::get(module, 64));
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

  case 151:
#line 1012 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (3)].str), (Value *)nullptr));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 152:
#line 1017 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].val)));
		delete (yyvsp[(2) - (5)].str);
	;}
    break;

  case 153:
#line 1022 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (2)].str), (Value *)nullptr));
		delete (yyvsp[(1) - (2)].str);
	;}
    break;

  case 154:
#line 1028 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].val)));
		delete (yyvsp[(1) - (4)].str);
	;}
    break;

  case 155:
#line 1036 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(1) - (1)].val);
		SET_LOCATION((yyval.val), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 156:
#line 1041 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(2) - (2)].val);
		(yyvsp[(2) - (2)].val)->negate();
		SET_LOCATION((yyval.val), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 159:
#line 1055 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = Orange::PointerType::get(module, (yyvsp[(1) - (3)].ty));
	;}
    break;

  case 160:
#line 1059 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = Orange::PointerType::get(module, (yyvsp[(1) - (2)].ty));
	;}
    break;

  case 161:
#line 1063 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 162:
#line 1070 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(2) - (2)].ty)->getConst();
	;}
    break;

  case 163:
#line 1074 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 164:
#line 1078 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 165:
#line 1085 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (2)].ty);

		bool is_const = true;
		for (unsigned int i = 0; i < (yyvsp[(2) - (2)].exprs)->size(); i++)
		{
			auto def = (yyvsp[(2) - (2)].exprs)->at(i);

			if (Orange::Type::exprValidForArrSize(def) == false)
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
				auto arr_sz = Orange::Type::exprAsArrSize(def);
				(yyval.ty) = Orange::ArrayType::get(module, (yyval.ty), arr_sz, false);
			}
			else
			{
				(yyval.ty) = Orange::VariadicArrayType::get(module, (yyval.ty), def, false);
			}
		}
	;}
    break;

  case 166:
#line 1120 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (4)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (4)].expr));
	;}
    break;

  case 167:
#line 1125 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(2) - (3)].expr));
	;}
    break;

  case 168:
#line 1132 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = (yyvsp[(1) - (1)].ppair); ;}
    break;

  case 169:
#line 1133 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = nullptr; ;}
    break;

  case 170:
#line 1137 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PRIVATE)); delete (yyvsp[(1) - (1)].str);;}
    break;

  case 171:
#line 1138 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PROTECTED)); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 172:
#line 1139 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PUBLIC)); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 173:
#line 1143 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 174:
#line 1144 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = nullptr; ;}
    break;

  case 175:
#line 1148 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 64); ;}
    break;

  case 176:
#line 1149 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 64); ;}
    break;

  case 177:
#line 1150 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::FloatType::get(module); ;}
    break;

  case 178:
#line 1151 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::DoubleType::get(module); ;}
    break;

  case 179:
#line 1152 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 8); ;}
    break;

  case 180:
#line 1153 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 16); ;}
    break;

  case 181:
#line 1154 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 32); ;}
    break;

  case 182:
#line 1155 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 64); ;}
    break;

  case 183:
#line 1156 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 8); ;}
    break;

  case 184:
#line 1157 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 16); ;}
    break;

  case 185:
#line 1158 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 32); ;}
    break;

  case 186:
#line 1159 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 64); ;}
    break;

  case 187:
#line 1160 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 8); ;}
    break;

  case 188:
#line 1161 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::VoidType::get(module); ;}
    break;

  case 189:
#line 1162 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::VarType::get(module); ;}
    break;

  case 190:
#line 1163 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto ty = new ReferenceType(*(yyvsp[(1) - (1)].str));
		delete (yyvsp[(1) - (1)].str);

		(yyval.ty) = ty;
		SET_LOCATION(ty, (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3709 "/Users/robert/dev/orange/lib/grove/parser.cc"
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


#line 1172 "/Users/robert/dev/orange/lib/grove/parser.y"



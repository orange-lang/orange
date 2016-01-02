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
     FROM = 345,
     SUPER = 346
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
#define SUPER 346




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
	#include <grove/SuperReference.h>
	#include <grove/SuperCall.h>

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
#line 83 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 365 "/Users/robert/dev/orange/lib/grove/parser.cc"
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
#line 390 "/Users/robert/dev/orange/lib/grove/parser.cc"

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
#define YYLAST   1531

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  192
/* YYNRULES -- Number of states.  */
#define YYNSTATES  360

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

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
      85,    86,    87,    88,    89,    90,    91
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
     404,   409,   414,   419,   424,   426,   428,   432,   434,   437,
     439,   441,   444,   447,   452,   456,   461,   465,   469,   473,
     477,   480,   485,   490,   494,   496,   498,   501,   504,   508,
     514,   516,   520,   526,   530,   536,   539,   544,   546,   549,
     551,   553,   557,   560,   562,   565,   567,   569,   572,   577,
     581,   583,   584,   586,   588,   590,   592,   593,   595,   597,
     599,   601,   603,   605,   607,   609,   611,   613,   615,   617,
     619,   621,   623
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    -1,    94,    95,    -1,    94,    96,
      -1,    95,    -1,    96,    -1,   153,   155,    99,    -1,   153,
     155,   100,    -1,    94,    -1,    -1,   102,    -1,   132,    -1,
     133,    -1,   143,    -1,   102,   148,    -1,   132,   148,    -1,
     133,   148,    -1,   148,    -1,   143,   148,    -1,   143,    -1,
     133,    -1,   103,    -1,   107,    -1,   108,    -1,   111,    -1,
     116,    -1,   118,    -1,   119,    -1,   120,    -1,   125,    -1,
     145,    -1,    -1,     3,   139,     9,   129,    10,   106,   148,
     104,    97,     4,    -1,    -1,     3,   139,     9,   129,    10,
     106,    83,   105,    98,    -1,    53,   150,    -1,    -1,    63,
       8,     9,   129,    10,    53,   150,    -1,    63,     8,     9,
     128,    12,    64,    10,    53,   150,    -1,    -1,    36,     8,
     110,   148,   109,    97,     4,    -1,    90,    86,    -1,    -1,
      -1,     5,   133,   112,   148,    94,   113,    -1,    -1,     6,
     133,   114,   148,    94,   113,    -1,    -1,     7,   115,   148,
      94,     4,    -1,     4,    -1,    -1,    68,   133,   117,   148,
      94,     4,    -1,   132,     5,   133,    -1,   133,     5,   133,
      -1,   132,    68,   133,    -1,   133,    68,   133,    -1,    -1,
      74,     9,   126,    19,   127,    19,   127,    10,   148,   121,
      94,     4,    -1,    -1,    80,   133,   148,   122,    94,     4,
      -1,    -1,    75,    79,   148,   123,    94,     4,    -1,    -1,
      79,   148,   124,    94,     4,    80,   133,    -1,   132,    74,
       9,   126,    19,   127,    19,   127,    10,    -1,   133,    74,
       9,   126,    19,   127,    19,   127,    10,    -1,   132,    80,
     133,    -1,   133,    80,   133,    -1,   132,    75,    -1,   133,
      75,    -1,   101,    -1,    -1,   133,    -1,    -1,   128,    12,
     150,     8,    -1,   150,     8,    -1,   128,    -1,    -1,   131,
      -1,    -1,   131,    12,   133,    -1,   133,    -1,   142,    -1,
      77,    -1,    78,    -1,    76,    -1,   140,    -1,   134,    -1,
     135,    -1,   138,    -1,   136,    -1,   137,    -1,   133,    58,
     133,    -1,   133,    59,   133,    -1,   133,    56,   133,    -1,
     133,    57,   133,    -1,   133,    65,   133,    -1,   133,    66,
     133,    -1,   133,    69,   133,    -1,   133,    70,   133,    -1,
     133,    17,   133,    -1,   133,    16,   133,    -1,   133,    13,
     133,    -1,   133,    15,   133,    -1,   133,    60,   133,    -1,
     133,    71,   133,    -1,   133,    72,   133,    -1,   133,    73,
     133,    -1,   133,    47,   133,    -1,   133,    48,   133,    -1,
     133,    49,   133,    -1,   133,    50,   133,    -1,   133,    51,
     133,    -1,   133,    52,   133,    -1,   133,    45,    -1,   133,
      46,    -1,    45,   133,    -1,    46,   133,    -1,   133,    82,
     133,    83,   133,    -1,     8,     9,   130,    10,    -1,    86,
       9,   130,    10,    -1,   133,     9,   130,    10,    -1,    91,
       9,   130,    10,    -1,     8,    -1,    86,    -1,     9,   133,
      10,    -1,    61,    -1,    16,   133,    -1,    62,    -1,     8,
      -1,    13,   133,    -1,    71,   133,    -1,     9,   150,    10,
     133,    -1,    43,   141,    44,    -1,   133,    43,   133,    44,
      -1,   133,    55,     8,    -1,    86,    55,     8,    -1,    87,
      55,     8,    -1,    91,    55,     8,    -1,    88,     8,    -1,
      85,     9,   133,    10,    -1,    85,     9,   150,    10,    -1,
     141,    12,   133,    -1,   133,    -1,    35,    -1,    35,   133,
      -1,   150,   144,    -1,   144,    12,     8,    -1,   144,    12,
       8,    47,   133,    -1,     8,    -1,     8,    47,   133,    -1,
      84,     8,   148,   146,     4,    -1,   146,     8,   148,    -1,
     146,     8,    47,   147,   148,    -1,     8,   148,    -1,     8,
      47,   147,   148,    -1,    61,    -1,    16,    61,    -1,    18,
      -1,    19,    -1,   149,    43,    44,    -1,   150,    13,    -1,
     156,    -1,    81,   150,    -1,   151,    -1,   149,    -1,   149,
     152,    -1,   152,    43,   133,    44,    -1,    43,   133,    44,
      -1,   154,    -1,    -1,    40,    -1,    39,    -1,    38,    -1,
      89,    -1,    -1,    20,    -1,    21,    -1,    22,    -1,    23,
      -1,    24,    -1,    26,    -1,    28,    -1,    30,    -1,    25,
      -1,    27,    -1,    29,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   171,   178,   188,   195,   208,   250,   299,
     300,   304,   305,   306,   307,   311,   312,   313,   314,   318,
     325,   329,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   350,   349,   381,   380,   420,   421,   425,   433,
     445,   444,   461,   467,   471,   470,   501,   500,   518,   517,
     534,   542,   541,   560,   571,   585,   596,   612,   610,   628,
     627,   642,   641,   656,   655,   673,   683,   693,   700,   707,
     714,   724,   725,   729,   730,   734,   743,   755,   756,   760,
     761,   765,   770,   777,   778,   779,   780,   784,   785,   786,
     787,   788,   789,   793,   794,   795,   796,   797,   798,   800,
     801,   805,   806,   807,   808,   809,   811,   812,   813,   815,
     816,   817,   818,   819,   820,   824,   825,   826,   827,   831,
     839,   847,   855,   862,   872,   873,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   898,   907,
     916,   925,   926,   930,   935,   944,   949,   957,   983,   990,
     997,  1004,  1013,  1029,  1034,  1039,  1045,  1053,  1058,  1067,
    1068,  1072,  1076,  1080,  1087,  1091,  1095,  1102,  1137,  1142,
    1150,  1151,  1155,  1156,  1157,  1161,  1162,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
    1179,  1180,  1181
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
  "SIZEOF", "TYPE_ID", "THIS", "AT", "STATIC", "FROM", "SUPER", "$accept",
  "start", "statements", "flagged_statement", "flagged_compound_statement",
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
     345,   346
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    94,    94,    94,    95,    96,    97,
      97,    98,    98,    98,    98,    99,    99,    99,    99,   100,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   104,   103,   105,   103,   106,   106,   107,   107,
     109,   108,   110,   110,   112,   111,   114,   113,   115,   113,
     113,   117,   116,   118,   118,   119,   119,   121,   120,   122,
     120,   123,   120,   124,   120,   125,   125,   125,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   132,   132,   133,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   137,
     138,   138,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   141,   141,   142,   142,   143,   144,   144,
     144,   144,   145,   146,   146,   146,   146,   147,   147,   148,
     148,   149,   149,   149,   150,   150,   150,   151,   152,   152,
     153,   153,   154,   154,   154,   155,   155,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156
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
       4,     4,     4,     4,     1,     1,     3,     1,     2,     1,
       1,     2,     2,     4,     3,     4,     3,     3,     3,     3,
       2,     4,     4,     3,     1,     1,     2,     2,     3,     5,
       1,     3,     5,     3,     5,     2,     4,     1,     2,     1,
       1,     3,     2,     1,     2,     1,     1,     2,     4,     3,
       1,     0,     1,     1,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     171,   174,   173,   172,     0,   171,     5,     6,   176,   170,
       1,     3,     4,   175,     0,     0,     0,   130,     0,     0,
       0,   159,   160,   177,   178,   179,   180,   181,   185,   182,
     186,   183,   187,   184,   188,   189,   190,   191,   145,     0,
       0,     0,     0,   127,   129,     0,     0,     0,     0,     0,
      86,    84,    85,     0,     0,     0,     0,     0,   192,     0,
       0,     0,     7,     8,     0,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,    88,    89,    91,    92,
      90,    87,    83,     0,    31,    18,   166,     0,   165,   163,
     124,   125,     0,     0,    44,    80,     0,     0,   131,   128,
     146,    43,   144,     0,   117,   118,     0,    51,   132,    72,
       0,    63,     0,   192,   164,     0,     0,    80,     0,     0,
     140,    80,     0,    15,     0,     0,     0,    69,     0,    16,
       0,    80,     0,     0,     0,     0,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,    17,    19,     0,   167,   150,   162,   147,
      78,     0,     0,    79,    82,   126,     0,     0,     0,     0,
     134,    78,     0,    71,     0,    21,    20,    61,   171,    59,
       0,     0,     0,     0,   137,   138,     0,   139,    53,    55,
      72,    67,    54,     0,   103,   104,   102,   101,     0,   109,
     110,   111,   112,   113,   114,   136,    95,    96,    93,    94,
     105,    97,    98,    56,    99,   100,   106,   107,   108,    72,
      68,     0,   161,     0,     0,     0,     0,    77,     0,     0,
     171,   120,     0,   133,    42,    40,   143,    77,     0,   171,
      74,   171,   171,   171,     0,     0,   141,   142,   121,   123,
       0,   122,   135,     0,     0,   169,     0,   151,   148,     0,
      37,    76,   171,    81,   171,     0,     0,   171,     0,    73,
     171,     0,   171,     0,   155,   152,     0,    74,    74,   119,
     168,     0,     0,     0,     0,    50,     0,    48,    45,   171,
       0,     0,     0,    52,    74,    62,     0,    60,     0,   157,
       0,     0,   153,     0,     0,   149,    75,    36,    34,    32,
      46,     0,    41,     0,    38,     0,    64,   158,   156,     0,
      74,    74,     0,   171,     0,   171,     0,     0,   154,     0,
       0,    35,    11,    12,    13,    14,     0,   171,   171,    39,
      57,    65,    66,    33,   171,    49,   171,    47,   171,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   299,     6,     7,   300,   341,    62,    63,   183,
      64,    65,   333,   332,   294,    66,    67,   274,   178,    68,
     171,   298,   334,   321,    69,   182,    70,    71,    72,   356,
     253,   251,   188,    73,   184,   278,   237,   238,   172,   173,
      74,   279,    76,    77,    78,    79,    80,    92,    81,   103,
      82,   186,   169,    84,   255,   310,    85,    86,    87,    88,
     166,     8,     9,    14,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -245
static const yytype_int16 yypact[] =
{
      73,  -245,  -245,  -245,    22,   162,  -245,  -245,   -65,  -245,
    -245,  -245,  -245,  -245,   444,    -5,   278,    20,   612,   278,
     278,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,   278,    47,
     278,   278,   278,  -245,  -245,    55,   278,   278,    81,   -41,
    -245,  -245,  -245,    30,   278,   369,    56,    90,     1,    27,
      95,    10,  -245,  -245,    30,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,    -1,   662,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,    30,  -245,  -245,    62,    29,  -245,  -245,
    -245,  -245,   106,     1,  1281,   278,   941,    17,    16,   164,
    1281,    26,  1281,    14,  -245,  -245,   110,  1281,   144,   612,
      30,  -245,   873,  -245,   107,    30,   612,   278,   114,   123,
    -245,   278,   130,  -245,   278,   278,   147,  -245,   278,  -245,
     278,   278,   278,   278,   278,   278,   278,  -245,  -245,   278,
     278,   278,   278,   278,   278,   155,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   158,
    -245,   278,   278,  -245,  -245,     7,   131,   129,  -245,   169,
     369,    30,   168,   170,  1281,  -245,   278,    97,    30,   278,
    -245,   369,    30,  -245,   172,  1281,  -245,  -245,    73,  -245,
     184,  1009,    87,   188,  -245,  -245,   193,  -245,  1281,  1281,
     612,  1281,  1281,   201,    16,    16,   164,   164,  1077,  1281,
    1281,  1281,  1281,  1281,  1281,  -245,   199,   199,   199,   199,
      16,  1423,  1423,  1281,  1388,  1353,   144,  1458,   300,   612,
    1281,   802,  -245,  1145,   278,   278,   186,   206,   210,    72,
      73,  -245,   278,   125,  -245,  -245,  1281,   209,   213,    73,
     278,    73,    68,    73,    57,    37,  -245,  -245,  -245,  -245,
     207,  -245,  -245,   214,   278,  -245,  1213,  1281,   178,   369,
     183,  -245,   258,  1281,   126,  1279,   185,   191,   220,  1281,
     288,   161,   344,     5,  -245,  -245,   166,   278,   278,   364,
    -245,   278,    88,   369,   -13,  -245,   278,  -245,  -245,   348,
     239,   236,   369,  -245,   278,  -245,   278,  -245,   189,  -245,
      30,     5,  -245,   228,   233,  1281,  -245,   107,  -245,  -245,
    1281,    30,  -245,   203,   107,   248,  1281,  -245,  -245,    30,
     278,   278,   531,   126,    30,    73,   369,    30,  -245,   250,
     251,  -245,  -245,     9,   734,  -245,   259,    73,   366,   107,
    -245,  -245,  -245,  -245,   258,  -245,    73,  -245,   374,  -245
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -245,  -245,     0,    -4,     3,   -67,  -245,  -245,  -245,  -245,
     -63,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,   -87,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -172,  -244,    93,    96,   -85,  -245,
     -53,    -7,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,   -12,  -245,  -245,  -245,   -30,   122,  -245,    36,  -245,
    -245,  -245,  -245,  -245,  -245
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -11
static const yytype_int16 yytable[] =
{
       5,    11,    83,    90,   124,    21,    22,    75,    12,    94,
     117,    96,    98,    99,   124,    17,    18,    21,    22,   121,
      19,   308,    10,    20,    13,   131,   179,   176,   260,    95,
     168,   100,   193,   102,   104,   105,   196,   167,   110,   107,
     108,   285,   168,   313,   314,   286,   203,   112,    21,    22,
      40,   232,    41,    42,    97,   101,   118,   263,   180,   136,
     325,   137,   138,   106,   115,   122,   309,   125,    43,    44,
     318,   145,   281,   126,   127,    21,    22,   125,    47,   128,
     271,    91,   119,   126,   127,   168,   339,   340,   174,   128,
     109,   114,    57,    93,    59,    60,   316,   257,    61,   116,
     168,   168,   185,   120,   283,   165,     1,     2,     3,   191,
     174,     1,     2,     3,   174,   170,   177,   198,   199,   181,
     168,   201,   194,   202,   174,   204,   205,   206,   207,   208,
     -10,   195,   209,   210,   211,   212,   213,   214,   197,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   192,   131,   230,   231,   200,   132,   233,   133,
     134,   135,    -2,   215,     1,     2,     3,   229,   136,   243,
     137,   138,   246,   131,   234,   111,   235,   132,   241,   133,
     145,   236,   242,   244,    21,    22,   123,   136,   252,   137,
     138,   250,   254,   185,   268,   303,   129,   163,   258,   145,
       1,     2,     3,   259,   150,   164,   239,   136,   131,   137,
     138,   261,   132,   311,   133,   134,   135,   239,   269,   145,
     270,   275,   185,   276,   150,   291,   287,   266,   267,     1,
       2,     3,   187,   288,   189,   273,   293,   190,   302,   304,
     272,   306,   136,   322,   137,   138,   323,   330,    11,   277,
     327,   280,   331,   282,   145,    12,   336,   289,   337,   150,
     351,   352,   295,   353,   296,   297,   346,   357,    11,   342,
     156,   157,   158,    11,   247,    12,    11,   248,    11,   343,
      12,   329,     0,    12,   315,    12,    17,    18,     0,   320,
       0,    19,   305,   240,    20,    11,     1,     2,     3,   326,
     245,     0,    12,     0,   249,   292,     0,     0,     0,   131,
       0,   292,     0,   132,     0,   133,   134,   135,     0,     0,
     345,    40,     0,    41,    42,   344,     1,     2,     3,   317,
       0,     0,     0,     0,     0,   348,     0,     0,   324,    43,
      44,     0,     0,   136,    11,   137,   138,   354,   307,    47,
      11,    12,    -9,     0,    11,   145,   358,    12,     0,     0,
     150,    12,     0,    57,    93,    59,    60,     0,     0,    61,
     355,   156,   349,   131,     0,     0,   284,   132,   359,   133,
     134,   135,     1,     2,     3,     0,     1,     2,     3,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     1,     2,     3,   136,   312,   137,
     138,     0,     1,     2,     3,     0,   319,     0,     0,   145,
     146,   147,   148,   149,   150,     0,     0,     0,     0,   151,
     152,     0,   328,   154,   155,   156,   157,   158,     0,     0,
       0,     0,     0,   335,     0,     0,   162,    15,     0,    16,
      55,   338,    17,    18,     0,   113,   347,    19,     0,   350,
      20,     0,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,     0,     0,     0,     0,     0,    40,     0,    41,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,     0,     0,
       0,     0,    46,     0,     0,    47,     0,     0,    48,    49,
      50,    51,    52,    53,    54,    55,     0,     0,    56,    57,
      58,    59,    60,     0,    15,    61,    16,     0,     0,    17,
      18,     0,     0,     0,    19,     0,     0,    20,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,     0,
       0,     0,     0,     0,    40,     0,    41,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,     0,     0,     0,     0,    46,
       0,     0,    47,     0,     0,    48,    49,    50,    51,    52,
      53,    54,    55,     0,     0,    56,    57,    58,    59,    60,
      17,    18,    61,     0,     0,    19,     0,     0,    20,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    40,     0,    41,    42,     0,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,   131,     0,    43,    44,   132,     0,   133,   134,   135,
      21,    22,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,     0,     0,     0,    57,    58,    59,
      60,     0,     0,    61,     0,   136,     0,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,   145,   146,   147,
     148,   149,   150,     0,     0,     0,     0,   151,   152,     0,
     153,   154,   155,   156,   157,   158,   159,   160,     0,   130,
       0,     0,   161,   131,   162,     0,     0,   132,     0,   133,
     134,   135,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   136,     0,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,   145,
     146,   147,   148,   149,   150,     0,     0,     0,     0,   151,
     152,     0,   153,   154,   155,   156,   157,   158,   159,   160,
       0,   131,     0,     0,   161,   132,   162,   133,   134,   135,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,     0,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,   145,   146,   147,
     148,   149,   150,     0,     0,     0,     0,   151,   152,     0,
       0,   154,   155,   156,   157,   158,     0,     0,     0,     0,
       0,     0,   131,     0,   162,   264,   132,     0,   133,   134,
     135,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,     0,   137,   138,
     139,   140,   141,   142,   143,   144,     0,     0,   145,   146,
     147,   148,   149,   150,     0,     0,     0,     0,   151,   152,
       0,     0,   154,   155,   156,   157,   158,     0,     0,     0,
     131,   175,     0,     0,   132,   162,   133,   134,   135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,     0,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   145,   146,   147,   148,
     149,   150,     0,     0,     0,     0,   151,   152,     0,     0,
     154,   155,   156,   157,   158,     0,     0,     0,   131,   256,
       0,     0,   132,   162,   133,   134,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,     0,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,   145,   146,   147,   148,   149,   150,
       0,     0,     0,     0,   151,   152,     0,     0,   154,   155,
     156,   157,   158,     0,     0,     0,   131,     0,     0,     0,
     132,   162,   133,   134,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   262,   137,   138,   139,   140,   141,   142,   143,   144,
       0,     0,   145,   146,   147,   148,   149,   150,     0,     0,
       0,     0,   151,   152,     0,     0,   154,   155,   156,   157,
     158,     0,     0,     0,   131,     0,     0,     0,   132,   162,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   136,   265,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
     145,   146,   147,   148,   149,   150,     0,     0,     0,     0,
     151,   152,     0,     0,   154,   155,   156,   157,   158,     0,
       0,     0,   131,     0,     0,     0,   132,   162,   133,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   290,   137,   138,
     139,   140,   141,   142,   143,   144,     0,     0,   145,   146,
     147,   148,   149,   150,     0,     0,     0,     0,   151,   152,
       0,     0,   154,   155,   156,   157,   158,     0,     0,     0,
     131,     0,     0,     0,   132,   162,   133,   134,   135,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,     0,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   145,   146,   147,   148,
     149,   150,     0,   301,     0,     0,   151,   152,     0,     0,
     154,   155,   156,   157,   158,     0,     0,     0,     0,     0,
      55,     0,   131,   162,     0,   113,   132,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   131,   137,   138,
       0,   132,     0,   133,   134,   135,     0,     0,   145,   146,
     147,   148,   149,   150,     0,     0,     0,     0,   151,   152,
       0,     0,   154,     0,   156,   157,   158,     0,     0,     0,
       0,   136,   131,   137,   138,     0,   132,     0,   133,   134,
     135,     0,     0,   145,   146,   147,   148,   149,   150,     0,
       0,     0,     0,   151,   152,     0,     0,     0,     0,   156,
     157,   158,     0,     0,     0,     0,   136,   131,   137,   138,
       0,   132,     0,   133,   134,   135,     0,     0,   145,   146,
     147,   148,   149,   150,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,   157,   158,     0,     0,     0,
       0,   136,     0,   137,   138,     0,     0,     0,     0,     0,
       0,     0,     0,   145,     0,     0,     0,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   156,
       0,   158
};

static const yytype_int16 yycheck[] =
{
       0,     5,    14,     8,     5,    18,    19,    14,     5,    16,
       9,    18,    19,    20,     5,     8,     9,    18,    19,     9,
      13,    16,     0,    16,    89,     9,    12,    10,   200,     9,
      13,    38,   117,    40,    41,    42,   121,     8,    79,    46,
      47,     4,    13,   287,   288,     8,   131,    54,    18,    19,
      43,    44,    45,    46,    18,     8,    55,   229,    44,    43,
     304,    45,    46,     8,     8,    55,    61,    68,    61,    62,
      83,    55,     4,    74,    75,    18,    19,    68,    71,    80,
       8,    86,    55,    74,    75,    13,   330,   331,    95,    80,
       9,    55,    85,    86,    87,    88,     8,    10,    91,     9,
      13,    13,   109,     8,    47,    43,    38,    39,    40,   116,
     117,    38,    39,    40,   121,     9,    90,   124,   125,     9,
      13,   128,     8,   130,   131,   132,   133,   134,   135,   136,
       4,     8,   139,   140,   141,   142,   143,   144,     8,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   116,     9,   161,   162,     9,    13,   165,    15,
      16,    17,     0,     8,    38,    39,    40,     9,    43,   176,
      45,    46,   179,     9,    43,    53,    47,    13,    10,    15,
      55,    12,    12,    86,    18,    19,    64,    43,   188,    45,
      46,    19,     8,   200,     8,     4,    74,    75,    10,    55,
      38,    39,    40,    10,    60,    83,   170,    43,     9,    45,
      46,    10,    13,    47,    15,    16,    17,   181,    12,    55,
      10,    12,   229,    10,    60,    47,    19,   234,   235,    38,
      39,    40,   110,    19,   112,   242,    53,   115,    53,    19,
     240,    80,    43,     4,    45,    46,    10,    19,   252,   249,
      61,   251,    19,   253,    55,   252,    53,   264,    10,    60,
      10,    10,     4,     4,     6,     7,   333,   354,   272,   332,
      71,    72,    73,   277,   181,   272,   280,   181,   282,   332,
     277,   311,    -1,   280,   291,   282,     8,     9,    -1,   296,
      -1,    13,     4,   171,    16,   299,    38,    39,    40,   306,
     178,    -1,   299,    -1,   182,   269,    -1,    -1,    -1,     9,
      -1,   275,    -1,    13,    -1,    15,    16,    17,    -1,    -1,
     332,    43,    -1,    45,    46,   332,    38,    39,    40,   293,
      -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,   302,    61,
      62,    -1,    -1,    43,   348,    45,    46,   347,     4,    71,
     354,   348,     4,    -1,   358,    55,   356,   354,    -1,    -1,
      60,   358,    -1,    85,    86,    87,    88,    -1,    -1,    91,
       4,    71,   336,     9,    -1,    -1,   254,    13,     4,    15,
      16,    17,    38,    39,    40,    -1,    38,    39,    40,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    38,    39,    40,    43,   286,    45,
      46,    -1,    38,    39,    40,    -1,   294,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,   310,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,   321,    -1,    -1,    82,     3,    -1,     5,
      81,   329,     8,     9,    -1,    86,   334,    13,    -1,   337,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,    85,
      86,    87,    88,    -1,     3,    91,     5,    -1,    -1,     8,
       9,    -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    71,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    84,    85,    86,    87,    88,
       8,     9,    91,    -1,    -1,    13,    -1,    -1,    16,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
      -1,     9,    -1,    61,    62,    13,    -1,    15,    16,    17,
      18,    19,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    86,    87,
      88,    -1,    -1,    91,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,     5,
      -1,    -1,    80,     9,    82,    -1,    -1,    13,    -1,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,     9,    -1,    -1,    80,    13,    82,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    -1,    82,    83,    13,    -1,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
       9,    10,    -1,    -1,    13,    82,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,     9,    10,
      -1,    -1,    13,    82,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    -1,    -1,    -1,     9,    -1,    -1,    -1,
      13,    82,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    -1,    -1,    -1,     9,    -1,    -1,    -1,    13,    82,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    13,    82,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    -1,    -1,    -1,
       9,    -1,    -1,    -1,    13,    82,    15,    16,    17,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    64,    -1,    -1,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      81,    -1,     9,    82,    -1,    86,    13,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,     9,    45,    46,
      -1,    13,    -1,    15,    16,    17,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    43,     9,    45,    46,    -1,    13,    -1,    15,    16,
      17,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    43,     9,    45,    46,
      -1,    13,    -1,    15,    16,    17,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,    40,    93,    94,    95,    96,   153,   154,
       0,    95,    96,    89,   155,     3,     5,     8,     9,    13,
      16,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      43,    45,    46,    61,    62,    63,    68,    71,    74,    75,
      76,    77,    78,    79,    80,    81,    84,    85,    86,    87,
      88,    91,    99,   100,   102,   103,   107,   108,   111,   116,
     118,   119,   120,   125,   132,   133,   134,   135,   136,   137,
     138,   140,   142,   143,   145,   148,   149,   150,   151,   156,
       8,    86,   139,    86,   133,     9,   133,   150,   133,   133,
     133,     8,   133,   141,   133,   133,     8,   133,   133,     9,
      79,   148,   133,    86,   150,     8,     9,     9,    55,    55,
       8,     9,    55,   148,     5,    68,    74,    75,    80,   148,
       5,     9,    13,    15,    16,    17,    43,    45,    46,    47,
      48,    49,    50,    51,    52,    55,    56,    57,    58,    59,
      60,    65,    66,    68,    69,    70,    71,    72,    73,    74,
      75,    80,    82,   148,   148,    43,   152,     8,    13,   144,
       9,   112,   130,   131,   133,    10,    10,    90,   110,    12,
      44,     9,   117,   101,   126,   133,   143,   148,   124,   148,
     148,   133,   150,   130,     8,     8,   130,     8,   133,   133,
       9,   133,   133,   130,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,     8,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,     9,
     133,   133,    44,   133,    43,    47,    12,   128,   129,   150,
     148,    10,    12,   133,    86,   148,   133,   128,   129,   148,
      19,   123,    94,   122,     8,   146,    10,    10,    10,    10,
     126,    10,    44,   126,    83,    44,   133,   133,     8,    12,
      10,     8,    94,   133,   109,    12,    10,    94,   127,   133,
      94,     4,    94,    47,   148,     4,     8,    19,    19,   133,
      44,    47,   150,    53,   106,     4,     6,     7,   113,    94,
      97,    64,    53,     4,    19,     4,    80,     4,    16,    61,
     147,    47,   148,   127,   127,   133,     8,   150,    83,   148,
     133,   115,     4,    10,   150,   127,   133,    61,   148,   147,
      19,    19,   105,   104,   114,   148,    53,    10,   148,   127,
     127,    98,   102,   132,   133,   143,    97,   148,    94,   150,
     148,    10,    10,     4,    94,     4,   121,   113,    94,     4
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
#line 172 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		if ((yyvsp[(2) - (2)].node) != nullptr)
		{
			module->getBlock()->addStatement((yyvsp[(2) - (2)].node));
		}
	;}
    break;

  case 4:
#line 179 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 189 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		if ((yyvsp[(1) - (1)].node) != nullptr)
		{
			module->getBlock()->addStatement((yyvsp[(1) - (1)].node));
		}
	;}
    break;

  case 6:
#line 196 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 208 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 250 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 304 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].stmt)); ;}
    break;

  case 12:
#line 305 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].node)); ;}
    break;

  case 13:
#line 306 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); (yyval.nodes)->push_back((yyvsp[(1) - (1)].expr)); ;}
    break;

  case 14:
#line 307 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 15:
#line 311 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].stmt); ;}
    break;

  case 16:
#line 312 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 17:
#line 313 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].expr); ;}
    break;

  case 18:
#line 314 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 19:
#line 319 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (2)].nodes);
	;}
    break;

  case 20:
#line 326 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = (yyvsp[(1) - (1)].nodes);
	;}
    break;

  case 21:
#line 330 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.nodes) = new std::vector<ASTNode *>();
		(yyval.nodes)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 22:
#line 336 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 23:
#line 337 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 24:
#line 338 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 25:
#line 339 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 26:
#line 340 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 27:
#line 341 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 28:
#line 342 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 29:
#line 343 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 30:
#line 344 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 31:
#line 345 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); ;}
    break;

  case 32:
#line 350 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 369 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 381 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 400 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 420 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = (yyvsp[(2) - (2)].ty); ;}
    break;

  case 37:
#line 421 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 38:
#line 426 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (7)].str), *(yyvsp[(4) - (7)].params), (yyvsp[(7) - (7)].ty));
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));

		delete (yyvsp[(2) - (7)].str);
		delete (yyvsp[(4) - (7)].params);
	;}
    break;

  case 39:
#line 434 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ExternFunction(*(yyvsp[(2) - (9)].str), *(yyvsp[(4) - (9)].params), (yyvsp[(9) - (9)].ty), true);
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(2) - (9)].str);
		delete (yyvsp[(4) - (9)].params);
	;}
    break;

  case 40:
#line 445 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.stmt) = new ClassDecl(*(yyvsp[(2) - (4)].str), (ReferenceType*)(yyvsp[(3) - (4)].ty));
		(yyval.stmt)->setModule(module);
		module->pushBlock((Block *)(yyval.stmt));
		delete (yyvsp[(2) - (4)].str);
	;}
    break;

  case 41:
#line 451 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		ClassDecl* inst = (ClassDecl *)(yyvsp[(5) - (7)].stmt);

		(yyval.stmt) = inst;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));

		module->popBlock();
	;}
    break;

  case 42:
#line 462 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = new ReferenceType(*(yyvsp[(2) - (2)].str));
		SET_LOCATION((yyval.ty)->as<ASTNode *>(), (yylsp[(2) - (2)]), (yylsp[(2) - (2)]))
		delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 43:
#line 467 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = nullptr; ;}
    break;

  case 44:
#line 471 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr));
		(yyval.stmt) = block;
		module->pushBlock(block);
	;}
    break;

  case 45:
#line 477 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 501 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr));
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 47:
#line 507 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = (yyvsp[(6) - (6)].blocks);

		auto block = (CondBlock *)(yyvsp[(3) - (6)].stmt);

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 48:
#line 518 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new Block();
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 49:
#line 524 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();

		auto block = (Block *)(yyvsp[(2) - (5)].stmt);

		(yyval.blocks)->insert((yyval.blocks)->begin(), block);

		SET_LOCATION(block, (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
		module->popBlock();
	;}
    break;

  case 50:
#line 535 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.blocks) = new std::vector<Block *>();
	;}
    break;

  case 51:
#line 542 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto block = new CondBlock((yyvsp[(2) - (2)].expr), true);
		module->pushBlock(block);
		(yyval.stmt) = block;
	;}
    break;

  case 52:
#line 548 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 561 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 572 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 586 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 597 "/Users/robert/dev/orange/lib/grove/parser.y"
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
#line 612 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(3) - (9)].nodes), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 58:
#line 618 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(10) - (12)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (12)]), (yylsp[(12) - (12)]));
		module->popBlock();

		delete (yyvsp[(3) - (12)].nodes);
	;}
    break;

  case 59:
#line 628 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(2) - (3)].expr), nullptr, false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 60:
#line 634 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(4) - (6)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 61:
#line 642 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 62:
#line 648 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(4) - (6)].stmt);

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
		module->popBlock();
	;}
    break;

  case 63:
#line 656 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, true);
		module->pushBlock(loop);
		(yyval.stmt) = loop;
	;}
    break;

  case 64:
#line 662 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = (Loop *)(yyvsp[(3) - (7)].stmt);
		loop->setCondition((yyvsp[(7) - (7)].expr));

		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (7)]), (yylsp[(7) - (7)]));
		module->popBlock();
	;}
    break;

  case 65:
#line 675 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 66:
#line 685 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(*(yyvsp[(4) - (9)].nodes), (yyvsp[(6) - (9)].expr), (yyvsp[(8) - (9)].expr), false);
		loop->addStatement((yyvsp[(1) - (9)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (9)]), (yylsp[(9) - (9)]));

		delete (yyvsp[(4) - (9)].nodes);
	;}
    break;

  case 67:
#line 694 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 68:
#line 701 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), (yyvsp[(3) - (3)].expr), nullptr, false);
		loop->addStatement((yyvsp[(1) - (3)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
	;}
    break;

  case 69:
#line 708 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].node));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 70:
#line 715 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto loop = new Loop(std::vector<ASTNode*>(), nullptr, nullptr, false);
		loop->addStatement((yyvsp[(1) - (2)].expr));
		(yyval.stmt) = loop;
		SET_LOCATION((yyval.stmt), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 71:
#line 724 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = (yyvsp[(1) - (1)].nodes); ;}
    break;

  case 72:
#line 725 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.nodes) = new std::vector<ASTNode*>(); ;}
    break;

  case 73:
#line 729 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 74:
#line 730 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = nullptr; ;}
    break;

  case 75:
#line 735 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = (yyvsp[(1) - (4)].params);
		auto param = new Parameter((yyvsp[(3) - (4)].ty), *(yyvsp[(4) - (4)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(4) - (4)].str);
	;}
    break;

  case 76:
#line 744 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.params) = new std::vector<Parameter *>();
		auto param = new Parameter((yyvsp[(1) - (2)].ty), *(yyvsp[(2) - (2)].str));
		(yyval.params)->push_back(param);
		SET_LOCATION(param, (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));

		delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 77:
#line 755 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.params) = (yyvsp[(1) - (1)].params); ;}
    break;

  case 78:
#line 756 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.params) = new std::vector<Parameter *>(); ;}
    break;

  case 79:
#line 760 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.args) = (yyvsp[(1) - (1)].args); ;}
    break;

  case 80:
#line 761 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.args) = new std::vector<Expression *>(); ;}
    break;

  case 81:
#line 766 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = (yyvsp[(1) - (3)].args);
		(yyval.args)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 82:
#line 771 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.args) = new std::vector<Expression *>();
		(yyval.args)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 83:
#line 777 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 84:
#line 778 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 85:
#line 779 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 86:
#line 780 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.node) = new LoopTerminator(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 87:
#line 784 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 88:
#line 785 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 89:
#line 786 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 90:
#line 787 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 91:
#line 788 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 92:
#line 789 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 93:
#line 793 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 94:
#line 794 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 95:
#line 795 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 96:
#line 796 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 97:
#line 797 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 98:
#line 798 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpCompare((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 99:
#line 800 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 100:
#line 801 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAndOr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 101:
#line 805 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 102:
#line 806 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 103:
#line 807 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 104:
#line 808 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 105:
#line 809 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 106:
#line 811 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 107:
#line 812 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 108:
#line 813 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpArith((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 109:
#line 815 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 110:
#line 816 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 111:
#line 817 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 112:
#line 818 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 113:
#line 819 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 114:
#line 820 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new BinOpAssign((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].str); ;}
    break;

  case 115:
#line 824 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr),  1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 116:
#line 825 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(1) - (2)].expr), -1, false); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 117:
#line 826 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr),  1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 118:
#line 827 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IncrementExpr((yyvsp[(2) - (2)].expr), -1, true); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 119:
#line 832 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new TernaryExpr((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
	;}
    break;

  case 120:
#line 840 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new FunctionCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(1) - (4)].str);
		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 121:
#line 848 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new CtorCall(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(1) - (4)].str);
		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 122:
#line 856 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new ExpressionCall((yyvsp[(1) - (4)].expr), *(yyvsp[(3) - (4)].args), true);
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 123:
#line 863 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.expr) = new SuperCall(*(yyvsp[(3) - (4)].args));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)]));

		delete (yyvsp[(3) - (4)].args);
	;}
    break;

  case 124:
#line 872 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 125:
#line 873 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 126:
#line 877 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 127:
#line 878 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].val); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); ;}
    break;

  case 128:
#line 879 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new NegativeExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 129:
#line 880 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new StrValue(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 130:
#line 881 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new IDReference(*(yyvsp[(1) - (1)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (1)]), (yylsp[(1) - (1)])); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 131:
#line 882 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new DerefExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 132:
#line 883 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ReferenceExpr((yyvsp[(2) - (2)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)])); ;}
    break;

  case 133:
#line 884 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new CastExpr((yyvsp[(2) - (4)].ty), (yyvsp[(4) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 134:
#line 885 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayValue(*(yyvsp[(2) - (3)].exprs)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(2) - (3)].exprs); ;}
    break;

  case 135:
#line 886 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new ArrayAccessExpr((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 136:
#line 887 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new AccessExpr((yyvsp[(1) - (3)].expr), *(yyvsp[(3) - (3)].str)); SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)])); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 137:
#line 888 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto ref = new ReferenceType(*(yyvsp[(1) - (3)].str));
		SET_LOCATION(ref, (yylsp[(1) - (3)]), (yylsp[(1) - (3)]));

		(yyval.expr) = new AccessExpr(ref, *(yyvsp[(3) - (3)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str);
		delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 138:
#line 898 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto lhs = new IDReference("this");
		SET_LOCATION(lhs, (yylsp[(1) - (3)]), (yylsp[(1) - (3)]));

		(yyval.expr) = new AccessExpr(lhs, *(yyvsp[(3) - (3)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str); delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 139:
#line 907 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto lhs = new SuperReference();
		SET_LOCATION(lhs, (yylsp[(1) - (3)]), (yylsp[(1) - (3)]));

		(yyval.expr) = new AccessExpr(lhs, *(yyvsp[(3) - (3)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (3)]), (yylsp[(3) - (3)]));

		delete (yyvsp[(1) - (3)].str); delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 140:
#line 916 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto lhs = new IDReference("this");
		SET_LOCATION(lhs, (yylsp[(1) - (2)]), (yylsp[(1) - (2)]));

		(yyval.expr) = new AccessExpr(lhs, *(yyvsp[(2) - (2)].str));
		SET_LOCATION((yyval.expr), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));

		delete (yyvsp[(1) - (2)].str); delete (yyvsp[(2) - (2)].str);
	;}
    break;

  case 141:
#line 925 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].expr)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 142:
#line 926 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.expr) = new SizeofExpr((yyvsp[(3) - (4)].ty)); SET_LOCATION((yyval.expr), (yylsp[(1) - (4)]), (yylsp[(4) - (4)])); ;}
    break;

  case 143:
#line 931 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (3)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (3)].expr));
	;}
    break;

  case 144:
#line 936 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(1) - (1)].expr));
	;}
    break;

  case 145:
#line 945 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt(nullptr);
		SET_LOCATION((yyval.node), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 146:
#line 950 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.node) = new ReturnStmt((yyvsp[(2) - (2)].expr));
		SET_LOCATION((yyval.node), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 147:
#line 958 "/Users/robert/dev/orange/lib/grove/parser.y"
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

  case 148:
#line 984 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (3)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (3)].str), nullptr));

		delete (yyvsp[(3) - (3)].str);
	;}
    break;

  case 149:
#line 991 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = (yyvsp[(1) - (5)].pairs);
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(3) - (5)].str), (yyvsp[(5) - (5)].expr)));

		delete (yyvsp[(3) - (5)].str);
	;}
    break;

  case 150:
#line 998 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (1)].str), nullptr));

		delete (yyvsp[(1) - (1)].str);
	;}
    break;

  case 151:
#line 1005 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.pairs) = new std::vector<std::tuple<OString, Expression*>>();
		(yyval.pairs)->push_back(std::make_tuple(*(yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].expr)));

		delete (yyvsp[(1) - (3)].str);
	;}
    break;

  case 152:
#line 1014 "/Users/robert/dev/orange/lib/grove/parser.y"
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

  case 153:
#line 1030 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (3)].str), (Value *)nullptr));
		delete (yyvsp[(2) - (3)].str);
	;}
    break;

  case 154:
#line 1035 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].val)));
		delete (yyvsp[(2) - (5)].str);
	;}
    break;

  case 155:
#line 1040 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (2)].str), (Value *)nullptr));
		delete (yyvsp[(1) - (2)].str);
	;}
    break;

  case 156:
#line 1046 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.vpairs) = new std::vector<std::tuple<OString, Value*>>();
		(yyval.vpairs)->push_back(std::make_tuple(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].val)));
		delete (yyvsp[(1) - (4)].str);
	;}
    break;

  case 157:
#line 1054 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(1) - (1)].val);
		SET_LOCATION((yyval.val), (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;

  case 158:
#line 1059 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.val) = (yyvsp[(2) - (2)].val);
		(yyvsp[(2) - (2)].val)->negate();
		SET_LOCATION((yyval.val), (yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
	;}
    break;

  case 161:
#line 1073 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = Orange::PointerType::get(module, (yyvsp[(1) - (3)].ty));
	;}
    break;

  case 162:
#line 1077 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = Orange::PointerType::get(module, (yyvsp[(1) - (2)].ty));
	;}
    break;

  case 163:
#line 1081 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 164:
#line 1088 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(2) - (2)].ty)->getConst();
	;}
    break;

  case 165:
#line 1092 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 166:
#line 1096 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.ty) = (yyvsp[(1) - (1)].ty);
	;}
    break;

  case 167:
#line 1103 "/Users/robert/dev/orange/lib/grove/parser.y"
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

  case 168:
#line 1138 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = (yyvsp[(1) - (4)].exprs);
		(yyval.exprs)->push_back((yyvsp[(3) - (4)].expr));
	;}
    break;

  case 169:
#line 1143 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		(yyval.exprs) = new std::vector<Expression *>();
		(yyval.exprs)->push_back((yyvsp[(2) - (3)].expr));
	;}
    break;

  case 170:
#line 1150 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = (yyvsp[(1) - (1)].ppair); ;}
    break;

  case 171:
#line 1151 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = nullptr; ;}
    break;

  case 172:
#line 1155 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PRIVATE)); delete (yyvsp[(1) - (1)].str);;}
    break;

  case 173:
#line 1156 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PROTECTED)); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 174:
#line 1157 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ppair) = new std::tuple<OString,ProtectionLevel>(std::make_tuple(*(yyvsp[(1) - (1)].str), ProtectionLevel::PROTECTION_PUBLIC)); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 175:
#line 1161 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 176:
#line 1162 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.str) = nullptr; ;}
    break;

  case 177:
#line 1166 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 64); ;}
    break;

  case 178:
#line 1167 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 64); ;}
    break;

  case 179:
#line 1168 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::FloatType::get(module); ;}
    break;

  case 180:
#line 1169 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::DoubleType::get(module); ;}
    break;

  case 181:
#line 1170 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 8); ;}
    break;

  case 182:
#line 1171 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 16); ;}
    break;

  case 183:
#line 1172 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 32); ;}
    break;

  case 184:
#line 1173 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 64); ;}
    break;

  case 185:
#line 1174 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 8); ;}
    break;

  case 186:
#line 1175 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 16); ;}
    break;

  case 187:
#line 1176 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 32); ;}
    break;

  case 188:
#line 1177 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::UIntType::get(module, 64); ;}
    break;

  case 189:
#line 1178 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::IntType::get(module, 8); ;}
    break;

  case 190:
#line 1179 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::VoidType::get(module); ;}
    break;

  case 191:
#line 1180 "/Users/robert/dev/orange/lib/grove/parser.y"
    { (yyval.ty) = Orange::VarType::get(module); ;}
    break;

  case 192:
#line 1181 "/Users/robert/dev/orange/lib/grove/parser.y"
    {
		auto ty = new ReferenceType(*(yyvsp[(1) - (1)].str));
		delete (yyvsp[(1) - (1)].str);

		(yyval.ty) = ty;
		SET_LOCATION(ty, (yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3733 "/Users/robert/dev/orange/lib/grove/parser.cc"
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


#line 1190 "/Users/robert/dev/orange/lib/grove/parser.y"



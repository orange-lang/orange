/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 9 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:339  */

	#include <iostream>
	#include <orange/orange.h>
	#include <orange/generator.h>
	#include <orange/Block.h>

	extern int yylex();
	extern struct YYLTYPE yyloc;
	extern void yyerror(const char *s);

	#define SET_LOCATION(x) CodeLocation loc = { yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column }; x->setLocation(loc);

#line 79 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hh".  */
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
    ENUM = 339
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:355  */

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

#line 222 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 253 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  90
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1625

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   104,   105,   109,   110,   114,   115,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   139,   140,   144,   145,   146,   147,   148,   150,
     151,   152,   153,   154,   155,   157,   158,   160,   161,   162,
     164,   165,   167,   168,   169,   171,   173,   175,   176,   177,
     181,   185,   186,   187,   188,   189,   190,   192,   193,   195,
     196,   198,   199,   201,   206,   207,   211,   211,   216,   216,
     223,   224,   228,   229,   230,   231,   232,   236,   243,   244,
     248,   249,   253,   257,   253,   270,   274,   270,   278,   278,
     287,   293,   307,   307,   318,   328,   328,   336,   336,   344,
     344,   352,   352,   364,   369,   374,   381,   382,   383,   387,
     401,   402,   403,   404,   408,   409,   413,   414,   417,   418,
     422,   423,   427,   428,   429,   430,   433,   434,   438,   439,
     440,   444,   445,   449,   450,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     472,   492,   503,   504,   505,   509,   510,   513,   514,   517,
     518,   519
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "BREAK", "DO", "WHILE", "CONST", "QUESTION", "COLON", "ENUM", "$accept",
  "start", "statements", "opt_statements", "statement", "more_exprs",
  "expression", "primary_high", "primary", "opt_array", "function", "@1",
  "@2", "opt_func_params", "func_params", "extern_function",
  "opt_arg_list", "arg_list", "if_statement", "@3", "$@4",
  "else_ifs_or_end", "@5", "$@6", "@7", "inline_if", "unless_statement",
  "@8", "inline_unless", "for_loop", "@9", "@10", "@11", "@12",
  "inline_loop", "loop_breaks", "enum_stmt", "enum_members", "initializer",
  "opt_expr", "variable_decl", "opt_variable_decls",
  "opt_variable_decls_impl", "const_var", "return_or_expr", "return",
  "term", "basic_type", "any_type", "any_type_no_array",
  "var_arrays_and_ptrs", "opt_primary", "var_arrays", "var_ptrs", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     335,   336,   337,   338,   339
};
# endif

#define YYPACT_NINF -235

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-235)))

#define YYTABLE_NINF -156

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     880,    14,   283,    10,   203,   283,   283,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,   283,   283,   283,   283,  -235,  -235,
      22,   283,   283,    26,   -39,  -235,  -235,  -235,    50,   283,
    1054,    29,    44,   880,  -235,   982,  -235,  -235,    19,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,     4,    50,  -235,  -235,    39,    62,  1290,   283,    65,
     920,    67,    35,    -3,  1473,  1473,    38,    75,  -235,  -235,
      79,  1290,   126,   203,    50,  -235,  1290,    42,    82,    50,
    -235,  -235,   283,   283,   283,   283,   283,  -235,  -235,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,    50,   283,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,   283,   283,    83,  -235,   283,  -235,    56,    11,  1177,
    -235,    81,  -235,  -235,   283,  -235,   283,  1177,  -235,  1473,
      74,  -235,  -235,   880,  -235,   283,    53,   113,  1044,    35,
      35,    -3,    -3,  1473,  1473,  1473,  1473,  1473,   998,   998,
     998,   998,    35,  1552,  1552,  1491,   393,   126,  1121,   271,
    1105,  -235,  1351,  1473,  1473,   203,  1473,     5,   110,   119,
     283,  -235,  -235,   118,   117,  -235,   122,   880,  -235,  -235,
    1473,   121,   880,   283,   880,   352,   880,  1473,   283,    13,
      48,  -235,   283,    89,   116,  -235,  1412,  -235,    27,  -235,
    1167,     6,  1550,     3,  -235,   880,    85,   472,  1473,   125,
     554,    60,   636,  1473,    84,  -235,  -235,    36,   109,   283,
    -235,   124,   283,  -235,  1230,  -235,  -235,  -235,   139,  -235,
     283,    57,  1230,  -235,   283,  -235,   283,  -235,    50,    88,
    -235,   131,  -235,  1229,    50,   880,  -235,  1473,   107,   108,
    -235,   283,    50,  -235,  -235,   146,  1473,  -235,    50,   283,
     124,  -235,   880,   154,  -235,  1290,  -235,    50,  -235,   149,
    -235,   880,  -235,  -235,   880,  -235,  -235,   156,   880,   718,
     880,  -235,   880,  -235,   800,    57,  -235,  -235
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    54,     0,     0,     0,   133,   134,   135,
     136,   137,   138,   139,   143,   140,   144,   141,   145,   142,
     146,   147,   148,   149,   131,    79,     0,     0,    52,    53,
       0,     0,     0,     0,     0,   106,   107,   108,     0,     0,
       0,     0,     0,     2,     4,   129,    47,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,   128,     7,   158,     0,     0,     0,    79,     0,
       0,     0,    63,    56,   132,    81,     0,    78,    58,    60,
       0,     0,    49,     0,     0,   101,     0,     0,     0,     0,
       1,     3,     0,     0,     0,     0,     0,    57,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    12,    14,    13,    15,    18,    19,    20,    21,    16,
      17,     0,     0,     0,   105,     0,    11,   160,   121,    71,
      82,     0,    46,    51,     0,    61,     0,    71,    92,   115,
       0,   114,    99,     0,    97,     0,     0,     0,    23,    37,
      38,    36,    35,    24,    25,    26,    27,    28,    31,    32,
      29,    30,    39,    33,    34,    40,    41,    42,    43,    44,
       0,     8,     0,    91,    94,     0,   104,     0,   150,     0,
       0,   118,    76,     0,    70,   154,     0,     0,    55,    48,
      80,     0,     0,   117,     0,     0,     0,   127,     0,     0,
       0,    22,     0,    62,     0,   161,     0,   159,   124,   120,
     121,     0,     0,   151,    75,    83,     0,     0,   116,     0,
       0,     0,     0,   126,     0,   112,   109,     0,    45,   117,
     157,   121,     0,   119,     0,    66,    73,    74,     0,   152,
     156,     0,     0,    93,   117,   100,     0,    98,     0,     0,
     110,     0,   122,   125,     0,     6,    72,     0,    50,     0,
      90,     0,     0,    84,    77,     0,   102,   113,     0,   117,
     121,    68,     5,     0,   153,     0,    88,     0,   111,     0,
     123,     6,    67,    85,     0,    95,   103,     0,     0,     0,
       0,    69,    86,    89,     0,     0,    96,    87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,     0,  -130,   -42,    12,     2,  -235,   -88,  -235,
    -235,  -235,  -235,    17,  -235,  -235,   105,  -235,  -235,  -235,
    -235,  -129,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,    -8,  -234,
     -66,  -205,  -235,  -235,  -235,  -235,   252,  -136,    -2,   -38,
    -235,  -235,  -235,  -235
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    42,   282,   283,    44,   117,    45,    46,    47,    48,
      49,   265,   291,   193,   194,    50,    76,    77,    51,   197,
     251,   273,   298,   305,   294,    52,    53,   202,    54,    55,
     300,   206,   204,   153,    56,    57,    58,   210,   150,   229,
      59,   191,   219,    60,    61,    62,    63,    64,    65,   196,
     223,   269,   137,   188
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    91,    71,   195,    67,   261,    70,    72,    73,   131,
      93,   195,    94,     3,     4,   243,   249,   151,     5,    68,
     275,     6,    66,   189,     7,     8,    74,    75,    78,    79,
      80,     7,     8,    81,    82,    83,   262,    89,    88,   241,
      84,    86,    97,    98,    90,   289,   250,   138,    25,   215,
      26,    27,   236,   -64,     7,     8,   237,   108,   190,   244,
     234,   270,   118,   271,   272,    69,    28,    29,     7,     8,
      75,   139,   132,   142,   242,   290,    32,   144,   133,   134,
      97,    98,   145,   259,   135,   149,   195,   146,   147,   155,
     156,   198,   185,   203,   158,   159,   160,   161,   162,   187,
     208,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   151,
     182,   209,    93,   217,    94,    95,    96,   218,   221,   222,
     224,   226,   -65,   183,   184,   239,   189,   186,   252,    93,
     256,    94,    95,    96,   254,   258,   199,   266,   200,   278,
     279,  -155,   284,   205,    97,    98,   287,   207,   292,   296,
     301,   297,   268,    91,   201,   104,   105,   106,   107,   108,
     211,    97,    98,   141,   109,   110,   307,   214,   111,   112,
     113,   114,   115,    91,   248,    91,   108,   149,    91,   216,
      91,   116,   220,     0,     0,     0,     0,   225,     0,     0,
       0,     0,   227,     0,   230,   228,   232,     0,     0,     0,
     233,     3,     4,     0,   238,     0,     5,     0,     0,     6,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
      91,   228,   264,     0,   263,     0,    25,     0,    26,    27,
     274,     0,   267,     0,     0,     0,   228,    91,   276,     0,
      91,     0,    91,     0,    28,    29,     0,     0,     0,     0,
       0,     0,     0,   285,    32,     0,     0,     0,     0,     0,
       0,   228,     0,     0,    93,     0,    94,    95,    96,     0,
      85,     3,     4,     0,   299,     0,     5,     0,   302,     6,
     304,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     0,   136,     0,    97,    98,     0,   140,
       0,     0,     0,     0,     0,     0,    25,     0,    26,    27,
       0,   108,     0,   148,     0,     0,   152,     0,   154,     0,
       0,   157,   113,     0,    28,    29,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     1,   231,     2,     0,     0,
       3,     4,     0,     0,     0,     5,     0,     0,     6,   181,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    26,    27,     0,
       0,     0,     0,     0,     0,     0,    93,     0,    94,    95,
      96,     0,     0,    28,    29,    30,     0,     0,     0,     0,
      31,     0,     0,    32,     0,     0,    33,    34,    35,    36,
      37,    38,    39,    40,     0,     0,    41,     0,    97,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,   106,   107,   108,     0,     0,     0,     0,   109,   110,
       0,   235,   111,     0,   113,   114,   115,     0,     0,     0,
       0,     0,     0,   245,     0,     1,   253,     2,     0,     0,
       3,     4,     0,     0,     0,     5,     0,     0,     6,   260,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
     277,     0,     0,     0,     0,    25,   281,    26,    27,     0,
       0,     0,     0,     0,   286,     0,     0,     0,     0,     0,
     288,     0,     0,    28,    29,    30,     0,   293,     0,   295,
      31,     0,     0,    32,     0,     0,    33,    34,    35,    36,
      37,    38,    39,    40,     0,     0,    41,     1,   255,     2,
       0,     0,     3,     4,     0,     0,     0,     5,     0,     0,
       6,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,     0,     0,    25,     0,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,     0,     0,
       0,     0,    31,     0,     0,    32,     0,     0,    33,    34,
      35,    36,    37,    38,    39,    40,     0,     0,    41,     1,
     257,     2,     0,     0,     3,     4,     0,     0,     0,     5,
       0,     0,     6,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,     0,    31,     0,     0,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,    40,     0,     0,
      41,     1,   303,     2,     0,     0,     3,     4,     0,     0,
       0,     5,     0,     0,     6,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,    25,     0,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    30,     0,     0,     0,     0,    31,     0,     0,    32,
       0,     0,    33,    34,    35,    36,    37,    38,    39,    40,
       0,     0,    41,     1,   306,     2,     0,     0,     3,     4,
       0,     0,     0,     5,     0,     0,     6,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,    25,     0,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,     0,     0,     0,     0,    31,     0,
       0,    32,     0,     0,    33,    34,    35,    36,    37,    38,
      39,    40,     0,     1,    41,     2,     0,     0,     3,     4,
       0,     0,     0,     5,     0,     0,     6,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,    25,     0,    26,    27,     0,     0,     0,
     143,     0,     0,    93,     0,    94,    95,    96,     0,     0,
       0,    28,    29,    30,     0,     0,     0,     0,    31,     0,
       0,    32,     0,     0,    33,    34,    35,    36,    37,    38,
      39,    40,     0,     0,    41,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,   104,   105,   106,   107,
     108,     0,     0,     0,     0,   109,   110,     0,     0,   111,
     112,   113,   114,   115,    92,    93,     0,    94,    95,    96,
     -23,   -23,   116,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   104,   105,
     106,   107,   108,    97,    98,     0,     0,   109,   110,     0,
       0,   111,   112,   113,   114,   115,    92,    93,   108,    94,
      95,    96,    87,     0,   116,     0,     0,     0,     0,   113,
     114,   115,     0,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
     104,   105,   106,   107,   108,     0,     0,     0,     0,   109,
     110,     0,     0,   111,   112,   113,   114,   115,    93,     0,
      94,    95,    96,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,    93,     0,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,   104,   105,   106,   107,   108,    97,    98,     0,     0,
     109,   110,     0,     0,   111,   112,   113,   114,   115,   189,
      93,   108,    94,    95,    96,   192,     0,   116,   212,     0,
       0,     0,   113,     0,   115,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,   104,   105,   106,   107,   108,     0,     0,
       0,     0,   109,   110,     0,     0,   111,   112,   113,   114,
     115,   280,    93,     0,    94,    95,    96,     0,     0,   116,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,   104,   105,   106,   107,   108,
       0,     0,     0,     0,   109,   110,     0,     0,   111,   112,
     113,   114,   115,    93,     0,    94,    95,    96,     7,     8,
       0,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,   104,   105,   106,   107,
     108,     0,     0,     0,     0,   109,   110,     0,     0,   111,
     112,   113,   114,   115,    93,     0,    94,    95,    96,     0,
       0,     0,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   213,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,   104,   105,   106,
     107,   108,     0,     0,     0,     0,   109,   110,     0,     0,
     111,   112,   113,   114,   115,    93,     0,    94,    95,    96,
       0,     0,     0,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   240,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   104,   105,
     106,   107,   108,     0,     0,     0,     0,   109,   110,     0,
       0,   111,   112,   113,   114,   115,    93,     0,    94,    95,
      96,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,   104,
     105,   106,   107,   108,     0,     0,    97,    98,   109,   110,
       0,     0,   111,   112,   113,   114,   115,   104,   105,   106,
     107,   108,     0,     0,     0,   116,   109,   110,   246,     0,
       0,     0,   113,   114,   115,    93,     0,    94,    95,    96,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   105,
     106,   107,   108,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
       0,    43,     4,   139,     2,   239,     4,     5,     6,     5,
      13,   147,    15,     8,     9,   220,    13,    83,    13,     9,
     254,    16,     8,    12,    18,    19,    24,    25,    26,    27,
       8,    18,    19,    31,    32,     9,   241,     8,    40,    12,
      79,    39,    45,    46,     0,   279,    43,     8,    43,    44,
      45,    46,     4,    43,    18,    19,     8,    60,    47,    53,
      47,     4,    43,     6,     7,    55,    61,    62,    18,    19,
      68,     9,    68,     8,    47,   280,    71,    10,    74,    75,
      45,    46,    44,    47,    80,    83,   222,    12,     9,    47,
       8,    10,     9,    19,    92,    93,    94,    95,    96,    43,
      47,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   185,
     118,     8,    13,    13,    15,    16,    17,     8,    10,    12,
       8,    10,    43,   131,   132,    19,    12,   135,    53,    13,
      80,    15,    16,    17,    19,    61,   144,     8,   146,    61,
      19,    44,    44,   153,    45,    46,    10,   155,     4,    10,
       4,   291,   250,   205,   147,    56,    57,    58,    59,    60,
     158,    45,    46,    68,    65,    66,   305,   185,    69,    70,
      71,    72,    73,   225,   222,   227,    60,   185,   230,   187,
     232,    82,   190,    -1,    -1,    -1,    -1,   197,    -1,    -1,
      -1,    -1,   202,    -1,   204,   203,   206,    -1,    -1,    -1,
     208,     8,     9,    -1,   212,    -1,    13,    -1,    -1,    16,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
     282,   239,   244,    -1,   242,    -1,    43,    -1,    45,    46,
     252,    -1,   250,    -1,    -1,    -1,   254,   299,   256,    -1,
     302,    -1,   304,    -1,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    71,    -1,    -1,    -1,    -1,    -1,
      -1,   279,    -1,    -1,    13,    -1,    15,    16,    17,    -1,
      38,     8,     9,    -1,   294,    -1,    13,    -1,   298,    16,
     300,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    45,    46,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,
      -1,    60,    -1,    81,    -1,    -1,    84,    -1,    86,    -1,
      -1,    89,    71,    -1,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,     3,     4,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,   117,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    15,    16,
      17,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    84,    -1,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,   209,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,   221,    -1,     3,     4,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    16,   237,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
     258,    -1,    -1,    -1,    -1,    43,   264,    45,    46,    -1,
      -1,    -1,    -1,    -1,   272,    -1,    -1,    -1,    -1,    -1,
     278,    -1,    -1,    61,    62,    63,    -1,   285,    -1,   287,
      68,    -1,    -1,    71,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    84,     3,     4,     5,
      -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    71,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      84,     3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,     3,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,     3,    84,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,
      10,    -1,    -1,    13,    -1,    15,    16,    17,    -1,    -1,
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    84,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    12,    13,    -1,    15,    16,    17,
      18,    19,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    45,    46,    -1,    -1,    65,    66,    -1,
      -1,    69,    70,    71,    72,    73,    12,    13,    60,    15,
      16,    17,     8,    -1,    82,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    45,
      46,    47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,    69,    70,    71,    72,    73,    13,    -1,
      15,    16,    17,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    45,    46,    -1,    -1,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    12,
      13,    60,    15,    16,    17,     8,    -1,    82,    83,    -1,
      -1,    -1,    71,    -1,    73,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    12,    13,    -1,    15,    16,    17,    -1,    -1,    82,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    13,    -1,    15,    16,    17,    18,    19,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    13,    -1,    15,    16,    17,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    69,    70,    71,    72,    73,    13,    -1,    15,    16,
      17,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    -1,    -1,    45,    46,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    82,    65,    66,     8,    -1,
      -1,    -1,    71,    72,    73,    13,    -1,    15,    16,    17,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,     9,    13,    16,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    43,    45,    46,    61,    62,
      63,    68,    71,    74,    75,    76,    77,    78,    79,    80,
      81,    84,    86,    87,    89,    91,    92,    93,    94,    95,
     100,   103,   110,   111,   113,   114,   119,   120,   121,   125,
     128,   129,   130,   131,   132,   133,     8,    91,     9,    55,
      91,   133,    91,    91,    91,    91,   101,   102,    91,    91,
       8,    91,    91,     9,    79,   131,    91,     8,   133,     8,
       0,    89,    12,    13,    15,    16,    17,    45,    46,    47,
      48,    49,    50,    51,    56,    57,    58,    59,    60,    65,
      66,    69,    70,    71,    72,    73,    82,    90,    43,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,     5,    68,    74,    75,    80,   131,   137,     8,     9,
     131,   101,     8,    10,    10,    44,    12,     9,   131,    91,
     123,   125,   131,   118,   131,    47,     8,   131,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,   131,    91,    91,    91,     9,    91,    43,   138,    12,
      47,   126,     8,    98,    99,   132,   134,   104,    10,    91,
      91,    98,   112,    19,   117,    87,   116,    91,    47,     8,
     122,    90,    83,    44,   123,    44,    91,    13,     8,   127,
      91,    10,    12,   135,     8,    87,    10,    87,    91,   124,
      87,     4,    87,    91,    47,   131,     4,     8,    91,    19,
      44,    12,    47,   126,    53,   131,     8,    64,   134,    13,
      43,   105,    53,     4,    19,     4,    80,     4,    61,    47,
     131,   124,   126,    91,   133,    96,     8,    91,    93,   136,
       4,     6,     7,   106,   133,   124,    91,   131,    61,    19,
      12,   131,    87,    88,    44,    91,   131,    10,   131,   124,
     126,    97,     4,   131,   109,   131,    10,    88,   107,    87,
     115,     4,    87,     4,    87,   108,     4,   106
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    96,    95,    97,    95,
      98,    98,    99,    99,    99,    99,    99,   100,   101,   101,
     102,   102,   104,   105,   103,   107,   108,   106,   109,   106,
     106,   110,   112,   111,   113,   115,   114,   116,   114,   117,
     114,   118,   114,   119,   119,   119,   120,   120,   120,   121,
     122,   122,   122,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   127,   128,   128,   129,   129,
     129,   130,   130,   131,   131,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     133,   134,   135,   135,   135,   136,   136,   137,   137,   138,
     138,   138
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     0,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     3,     1,     4,     2,
       1,     3,     1,     1,     1,     4,     2,     2,     2,     2,
       2,     3,     4,     2,     1,     4,     0,     9,     0,    11,
       1,     0,     4,     3,     3,     2,     1,     7,     1,     0,
       3,     1,     0,     0,     7,     0,     0,     7,     0,     5,
       1,     3,     0,     6,     3,     0,    12,     0,     6,     0,
       6,     0,     7,     9,     3,     2,     1,     1,     1,     5,
       3,     5,     2,     4,     1,     1,     1,     0,     3,     5,
       2,     0,     3,     5,     1,     3,     5,     4,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     4,     0,     1,     0,     4,     0,     2,
       0,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
     '$$ = $1'.

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
#line 104 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-1].block)->addStatement((yyvsp[0].node)); }
#line 1924 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 4:
#line 105 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.block) = GE::runner()->topBlock(); (yyval.block)->addStatement((yyvsp[0].node)); }
#line 1930 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 5:
#line 109 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.block) = (yyvsp[0].block); }
#line 1936 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 6:
#line 110 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.block) = GE::runner()->topBlock(); }
#line 1942 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 7:
#line 114 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = nullptr; }
#line 1948 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 8:
#line 115 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		if ((yyvsp[-1].arglist)->size() > 0) {
			(yyvsp[-1].arglist)->push_back((yyvsp[-2].expr));
			(yyval.node) = new CommaStmt(*(yyvsp[-1].arglist));
		} else {
			(yyval.node) = (yyvsp[-2].expr); 			
		}
	}
#line 1961 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 9:
#line 123 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1967 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 10:
#line 124 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1973 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 11:
#line 125 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1979 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 12:
#line 126 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1985 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 13:
#line 127 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1991 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 14:
#line 128 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 1997 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 15:
#line 129 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2003 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 16:
#line 130 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2009 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 17:
#line 131 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2015 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 18:
#line 132 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2021 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 19:
#line 133 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2027 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 20:
#line 134 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2033 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 21:
#line 135 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[-1].stmt); }
#line 2039 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 22:
#line 139 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[0].arglist)->push_back((yyvsp[-1].expr)); (yyval.arglist) = (yyvsp[0].arglist); }
#line 2045 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 23:
#line 140 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.arglist) = new ArgList(); }
#line 2051 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 24:
#line 144 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2057 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 25:
#line 145 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2063 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 26:
#line 146 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2069 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 27:
#line 147 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2075 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 28:
#line 148 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2081 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 29:
#line 150 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2087 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 30:
#line 151 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2093 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 31:
#line 152 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2099 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 32:
#line 153 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2105 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 33:
#line 154 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2111 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 34:
#line 155 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2117 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 35:
#line 157 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2123 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 36:
#line 158 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2129 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 37:
#line 160 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2135 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 38:
#line 161 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2141 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 39:
#line 162 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2147 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 40:
#line 164 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2153 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 41:
#line 165 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2159 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 42:
#line 167 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2165 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 43:
#line 168 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2171 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 44:
#line 169 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].strele), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2177 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 45:
#line 171 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new TernaryExpr((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); SET_LOCATION((yyval.expr)); }
#line 2183 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 46:
#line 173 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new DotExpr(new AnyID(*(yyvsp[-2].str)), *(yyvsp[0].str)); }
#line 2189 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 47:
#line 175 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2195 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 48:
#line 176 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new CastExpr((yyvsp[-2].orangety), (yyvsp[0].expr)); }
#line 2201 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 49:
#line 177 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new AddressOfExpr((yyvsp[0].expr)); }
#line 2207 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 50:
#line 181 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2213 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 51:
#line 185 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = (yyvsp[-1].expr); SET_LOCATION((yyval.expr)); }
#line 2219 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 52:
#line 186 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = (yyvsp[0].expr); SET_LOCATION((yyval.expr)); }
#line 2225 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 53:
#line 187 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new StrVal(*(yyvsp[0].str)); }
#line 2231 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 54:
#line 188 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new AnyID(*(yyvsp[0].str)); SET_LOCATION((yyval.expr)); }
#line 2237 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 55:
#line 189 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new FuncCall(*(yyvsp[-3].str), *(yyvsp[-1].arglist)); SET_LOCATION((yyval.expr)); }
#line 2243 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 56:
#line 190 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new NegativeExpr((yyvsp[0].expr)); }
#line 2249 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 57:
#line 192 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new IncrementExpr((yyvsp[-1].expr), *(yyvsp[0].strele), false); }
#line 2255 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 58:
#line 193 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new IncrementExpr((yyvsp[0].expr), *(yyvsp[-1].strele), true); }
#line 2261 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 59:
#line 195 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new IncrementExpr((yyvsp[-1].expr), *(yyvsp[0].strele), false); }
#line 2267 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 60:
#line 196 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new IncrementExpr((yyvsp[0].expr), *(yyvsp[-1].strele), true); }
#line 2273 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 61:
#line 198 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new ArrayExpr(*(yyvsp[-1].arglist)); }
#line 2279 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 62:
#line 199 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new ArrayAccess((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2285 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 63:
#line 201 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new DerefExpr((yyvsp[0].expr)); }
#line 2291 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 64:
#line 206 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new VarExpr(*(yyvsp[0].str)); }
#line 2297 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 65:
#line 207 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = new ArrayAccess((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2303 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 66:
#line 211 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { 
			SymTable *tab = new SymTable(nullptr, GE::runner()->symtab());
			(yyval.stmt) = new FunctionStmt(*(yyvsp[-4].str), *(yyvsp[-2].paramlist), tab);
			GE::runner()->pushBlock((FunctionStmt *)(yyval.stmt));
		}
#line 2313 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 67:
#line 215 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = (yyvsp[-2].stmt); GE::runner()->popBlock(); SET_LOCATION((yyval.stmt)); }
#line 2319 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 68:
#line 216 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
			SymTable *tab = new SymTable(nullptr, GE::runner()->symtab());
			(yyval.stmt) = new FunctionStmt(*(yyvsp[-6].str), (yyvsp[-1].orangety), *(yyvsp[-4].paramlist), tab);
			GE::runner()->pushBlock((FunctionStmt *)(yyval.stmt));			
		}
#line 2329 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 69:
#line 220 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = (yyvsp[-2].stmt); GE::runner()->popBlock(); SET_LOCATION((yyval.stmt)); }
#line 2335 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 70:
#line 223 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 2341 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 71:
#line 224 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.paramlist) = new ParamList(); }
#line 2347 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 72:
#line 228 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-3].paramlist)->push_back(new VarExpr(*(yyvsp[0].str), (yyvsp[-1].orangety))); }
#line 2353 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 73:
#line 229 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-2].paramlist)->push_back(new VarExpr(*(yyvsp[0].str))); }
#line 2359 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 74:
#line 230 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-2].paramlist)->setVarArg(true); }
#line 2365 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 75:
#line 231 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.paramlist) = new ParamList(); (yyval.paramlist)->push_back(new VarExpr(*(yyvsp[0].str), (yyvsp[-1].orangety))); }
#line 2371 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 76:
#line 232 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.paramlist) = new ParamList(); (yyval.paramlist)->push_back(new VarExpr(*(yyvsp[0].str))); }
#line 2377 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 77:
#line 237 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
	 		(yyval.stmt) = new ExternFunction((yyvsp[0].orangety), *(yyvsp[-5].str), *(yyvsp[-3].paramlist));
	 	}
#line 2385 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 78:
#line 243 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.arglist) = (yyvsp[0].arglist); }
#line 2391 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 79:
#line 244 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.arglist) = new ArgList(); }
#line 2397 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 80:
#line 248 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-2].arglist)->push_back((yyvsp[0].expr)); }
#line 2403 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 81:
#line 249 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.arglist) = new ArgList(); (yyval.arglist)->push_back((yyvsp[0].expr)); }
#line 2409 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 82:
#line 253 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new CondBlock((yyvsp[-1].expr), tab);
		GE::runner()->pushBlock((CondBlock *)(yyval.stmt));
	}
#line 2419 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 83:
#line 257 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { GE::runner()->popBlock(); }
#line 2425 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 84:
#line 257 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { 		
		(yyval.stmt) = new IfStmts;

		(yyvsp[0].blocklist)->insert((yyvsp[0].blocklist)->begin(), (CondBlock*)(yyvsp[-3].stmt));
		for (unsigned int i = 0; i < (yyvsp[0].blocklist)->size(); i++) { 
			((IfStmts *)(yyval.stmt))->addBlock((yyvsp[0].blocklist)->at(i)); 
		} 

		SET_LOCATION((yyval.stmt));
	}
#line 2440 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 85:
#line 270 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new CondBlock((yyvsp[-1].expr), tab);
		GE::runner()->pushBlock((CondBlock *)(yyval.stmt));
	}
#line 2450 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 86:
#line 274 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { GE::runner()->popBlock(); }
#line 2456 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 87:
#line 274 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { 		
		(yyvsp[0].blocklist)->insert((yyvsp[0].blocklist)->begin(), (CondBlock*)(yyvsp[-3].stmt));
		(yyval.blocklist) = (yyvsp[0].blocklist);
	}
#line 2465 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 88:
#line 278 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Block(tab);
		GE::runner()->pushBlock((Block *)(yyval.stmt));
	}
#line 2475 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 89:
#line 282 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.blocklist) = new std::vector<Block*>;
		(yyval.blocklist)->insert((yyval.blocklist)->begin(), (Block*)(yyvsp[-2].stmt));
		GE::runner()->popBlock();
	}
#line 2485 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 90:
#line 287 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.blocklist) = new std::vector<Block*>;
	}
#line 2493 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 91:
#line 293 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable* tab = new SymTable(GE::runner()->symtab());
		CondBlock* block = new CondBlock((yyvsp[0].expr), tab);
		GE::runner()->pushBlock(block);

		block->addStatement((yyvsp[-2].node));
		(yyval.stmt) = new IfStmts;
		((IfStmts *)(yyval.stmt))->addBlock(block); 

		GE::runner()->popBlock();
	}
#line 2509 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 92:
#line 307 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new CondBlock((yyvsp[-1].expr), tab, true);
		GE::runner()->pushBlock((CondBlock *)(yyval.stmt));
	}
#line 2519 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 93:
#line 311 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.stmt) = new IfStmts;
		((IfStmts *)(yyval.stmt))->addBlock((CondBlock*)(yyvsp[-2].stmt)); 
		SET_LOCATION((yyval.stmt));
	}
#line 2529 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 94:
#line 318 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable* tab = new SymTable(GE::runner()->symtab());
		CondBlock* block = new CondBlock((yyvsp[0].expr), tab, true);
		block->addStatement((yyvsp[-2].node));
		(yyval.stmt) = new IfStmts;
		((IfStmts *)(yyval.stmt))->addBlock(block); 
	}
#line 2541 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 95:
#line 328 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop((yyvsp[-6].node), (yyvsp[-4].expr), (yyvsp[-2].expr), tab);
		GE::runner()->pushBlock((Loop *)(yyval.stmt));
	}
#line 2551 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 96:
#line 332 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.stmt) = (Loop *)(yyvsp[-2].stmt);
		GE::runner()->popBlock();
	}
#line 2560 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 97:
#line 336 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop((yyvsp[-1].expr), false, tab);
		GE::runner()->pushBlock((Loop *)(yyval.stmt));		
	}
#line 2570 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 98:
#line 340 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.stmt) = (Loop *)(yyvsp[-2].stmt);
		GE::runner()->popBlock();
	}
#line 2579 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 99:
#line 344 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop(tab);
		GE::runner()->pushBlock((Loop *)(yyval.stmt));				
	}
#line 2589 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 100:
#line 348 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.stmt) = (Loop *)(yyvsp[-2].stmt);
		GE::runner()->popBlock();
	}
#line 2598 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 101:
#line 352 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop(nullptr, true, tab);
		GE::runner()->pushBlock((Loop *)(yyval.stmt));				
	}
#line 2608 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 102:
#line 356 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		(yyval.stmt) = (Loop *)(yyvsp[-4].stmt);
		((Loop *)(yyval.stmt))->setCondition((yyvsp[0].expr));
		GE::runner()->popBlock();
	}
#line 2618 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 103:
#line 364 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop((yyvsp[-5].node), (yyvsp[-3].expr), (yyvsp[-1].expr), tab);
		((Loop *)(yyval.stmt))->addStatement((yyvsp[-8].node));		
	}
#line 2628 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 104:
#line 369 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop((yyvsp[0].expr), false, tab);
		((Loop *)(yyval.stmt))->addStatement((yyvsp[-2].node));				
	}
#line 2638 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 105:
#line 374 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		SymTable *tab = new SymTable(GE::runner()->symtab());
		(yyval.stmt) = new Loop(tab);
		((Loop *)(yyval.stmt))->addStatement((yyvsp[-1].node));
	}
#line 2648 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 106:
#line 381 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new LoopSkip(true); }
#line 2654 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 107:
#line 382 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new LoopSkip(true); }
#line 2660 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 108:
#line 383 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new LoopSkip(false); }
#line 2666 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 109:
#line 387 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    {
		EnumStmt* enumStmt = new EnumStmt(*(yyvsp[-3].str));
		for (auto pair : *(yyvsp[-1].enumlist)) {
			if (pair.value == nullptr) {
				enumStmt->addEnum(pair.name);
			} else {
				enumStmt->addEnum(pair.name, pair.value);
			}
		}

		(yyval.stmt) = (Statement *)enumStmt;
	}
#line 2683 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 110:
#line 401 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-2].enumlist)->push_back(EnumPair(*(yyvsp[-1].str))); }
#line 2689 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 111:
#line 402 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-4].enumlist)->push_back(EnumPair(*(yyvsp[-3].str), (BaseVal*)(yyvsp[-1].expr))); }
#line 2695 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 112:
#line 403 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.enumlist) = new std::vector<EnumPair>; (yyval.enumlist)->push_back(EnumPair(*(yyvsp[-1].str))); }
#line 2701 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 113:
#line 404 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.enumlist) = new std::vector<EnumPair>; (yyval.enumlist)->push_back(EnumPair(*(yyvsp[-3].str), (BaseVal*)(yyvsp[-1].expr))); }
#line 2707 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 114:
#line 408 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[0].stmt); }
#line 2713 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 115:
#line 409 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[0].expr); }
#line 2719 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 116:
#line 413 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2725 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 117:
#line 414 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.expr) = nullptr; }
#line 2731 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 118:
#line 417 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new ExplicitDeclStmt(new VarExpr(*(yyvsp[-1].str), (yyvsp[-2].orangety)), *(yyvsp[0].declpairlist)); }
#line 2737 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 119:
#line 418 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new ExplicitDeclStmt(new VarExpr(*(yyvsp[-3].str), (yyvsp[-4].orangety)), (yyvsp[-1].expr), *(yyvsp[0].declpairlist)); }
#line 2743 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 120:
#line 422 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.declpairlist) = (yyvsp[0].declpairlist); }
#line 2749 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 121:
#line 423 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.declpairlist) = new std::vector<DeclPair>(); }
#line 2755 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 122:
#line 427 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[0].declpairlist)->push_back(DeclPair(*(yyvsp[-2].str), nullptr)); }
#line 2761 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 123:
#line 428 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[0].declpairlist)->push_back(DeclPair(*(yyvsp[-4].str), (yyvsp[-2].expr))); }
#line 2767 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 124:
#line 429 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.declpairlist) = new std::vector<DeclPair>(); (yyval.declpairlist)->push_back(DeclPair(*(yyvsp[0].str), nullptr)); }
#line 2773 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 125:
#line 430 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.declpairlist) = new std::vector<DeclPair>(); (yyval.declpairlist)->push_back(DeclPair(*(yyvsp[-2].str), (yyvsp[0].expr))); }
#line 2779 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 126:
#line 433 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = new ExplicitDeclStmt(new VarExpr(*(yyvsp[-2].str), (yyvsp[-3].orangety), true), (yyvsp[0].expr)); }
#line 2785 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 127:
#line 434 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = new BinOpExpr(new VarExpr(*(yyvsp[-2].str), true), "=", (yyvsp[0].expr)); }
#line 2791 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 128:
#line 438 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[0].stmt); }
#line 2797 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 129:
#line 439 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[0].expr); }
#line 2803 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 130:
#line 440 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.node) = (yyvsp[0].stmt); }
#line 2809 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 131:
#line 444 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new ReturnStmt(); SET_LOCATION((yyval.stmt)); }
#line 2815 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 132:
#line 445 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.stmt) = new ReturnStmt((yyvsp[0].expr)); SET_LOCATION((yyval.stmt)); }
#line 2821 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 150:
#line 472 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { 
		(yyval.orangety) = OrangeTy::get(*(yyvsp[-2].str));

		// finally, get our pointers to the array. 
		for (int i =0; i < (yyvsp[0].number); i++) {
			(yyval.orangety) = (yyval.orangety)->getPointerTo();
		}
		
		// now, get our arrays.
		for (auto i = (yyvsp[-1].exprlist)->rbegin(); i != (yyvsp[-1].exprlist)->rend(); i++) {
			if (OrangeTy::isExpressionValidForConstArray(*i)) {
				(yyval.orangety) = ArrayTy::get((yyval.orangety), OrangeTy::valueFromExpression(*i));
			} else {
				(yyval.orangety) = VariadicArrayTy::get((yyval.orangety), *i);				
			}
		}
	}
#line 2843 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 151:
#line 492 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { 
		(yyval.orangety) = OrangeTy::get(*(yyvsp[-1].str));
		
		// get all of our pointers 
		for (int i = 0; i < (yyvsp[0].number); i++) {
			(yyval.orangety) = (yyval.orangety)->getPointerTo();
		}
	}
#line 2856 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 152:
#line 503 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number)++; }
#line 2862 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 153:
#line 504 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number)++; }
#line 2868 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 154:
#line 505 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number) = 0; }
#line 2874 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 157:
#line 513 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyvsp[-3].exprlist)->push_back((yyvsp[-1].expr)); }
#line 2880 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 158:
#line 514 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.exprlist) = new std::vector<Expression *>(); }
#line 2886 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 159:
#line 517 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number)++; }
#line 2892 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 160:
#line 518 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number) = 0; }
#line 2898 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;

  case 161:
#line 519 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1661  */
    { (yyval.number) = 1; }
#line 2904 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
    break;


#line 2908 "/Users/robert/dev/orange/tools/orange/parser.cc" /* yacc.c:1661  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 522 "/Users/robert/dev/orange/tools/orange/parser.y" /* yacc.c:1906  */


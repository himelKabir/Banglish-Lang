
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 5 "test.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

// Forward declarations
struct Expression;
struct Statement;
int evaluateExpression(struct Expression* e);


/* --- NEW: Expression Tree Structure --- */
// Represents a calculation that can be evaluated later.
typedef struct Expression {
    enum { EXPR_CONST, EXPR_VAR, EXPR_ARRAY_ACCESS, EXPR_BINOP, EXPR_UNOP, EXPR_STRLEN_VAR, EXPR_STRLEN_LIT } kind;
    int op; // The operator for BINOP/UNOP (e.g., PLUS, MINUS)
    struct Expression *left;
    struct Expression *right;
    int value;
    char name[50];
    char* str_literal;
} Expression;


/* Symbol table */
#define MAX_SYMBOLS 100
typedef struct {
    char name[50];
    int intValue;
    char* strValue;
    int type;      // 0=int, 1=char, 2=string, 3=array
    int array_values[100];
    int array_size;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

/* --- MODIFIED: Statement structure --- */
typedef struct Statement {
    enum { STMT_SHOW, STMT_ASSIGN, STMT_EXPR, STMT_ASSIGN_STR, STMT_ASSIGN_CHAR, STMT_ARRAY_ASSIGN, STMT_IF, STMT_WHILE, STMT_SWAP } kind;
    char varName[50];
    struct Expression* value_expr; // For conditions, assignments, array indices etc.
    char* strValue;                // For string literal assignments
    struct Statement* body;        // For if/while
    struct Statement* else_body;   // For if-else
    struct Statement* next;
    char swapVar2[50]; // For SWAP statement: second variable name
} Statement;

/* Function table */
#define MAX_FUNCTIONS 50
typedef struct {
    char name[50];
    Statement* body;
} Function;

Function funcTable[MAX_FUNCTIONS];
int funcCount = 0;

/* Function prototypes */
int findSymbolIndex(char* name);
void addSymbol(char* name,int intVal,char* strVal,int type);
void addFunction(char* name, Statement* body);
void executeFunction(char* name);
void executeStatement(Statement* s);
char* value_to_unquoted_string_from_identifier(const char* name);
char* strip_quotes(const char* s);
char* concat_and_quote(const char* a, const char* b);
Expression* new_const_node(int val);
Expression* new_var_node(char* name);
Expression* new_array_access_node(char* name, Expression* index_expr);
Expression* new_op_node(int op, Expression* left, Expression* right);
Expression* new_strlen_var_node(char* name);
Expression* new_strlen_lit_node(char* literal);



/* Line 189 of yacc.c  */
#line 155 "test.tab.c"

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

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 2 "test.y"

typedef struct { int *vals; int count; } IntList;



/* Line 209 of yacc.c  */
#line 185 "test.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MYTYPE = 258,
     SHOW = 259,
     SWAP = 260,
     FUNCTION = 261,
     RETURN = 262,
     STRLEN = 263,
     CONCAT = 264,
     INTTYPE = 265,
     FLOATTYPE = 266,
     CHARTYPE = 267,
     STRINGTYPE = 268,
     IF = 269,
     ELSE = 270,
     WHILE = 271,
     ARRAYTYPE = 272,
     IDENTIFIER = 273,
     STRING_LITERAL = 274,
     CHAR_LITERAL = 275,
     NUMBER = 276,
     PLUS = 277,
     MINUS = 278,
     TIMES = 279,
     DIVIDE = 280,
     AND = 281,
     OR = 282,
     NOT = 283,
     BAND = 284,
     BOR = 285,
     BXOR = 286,
     BNOT = 287,
     LSHIFT = 288,
     RSHIFT = 289,
     EQ = 290,
     NE = 291,
     GE = 292,
     LE = 293,
     UMINUS = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 87 "test.y"

    int num;
    char* str;
    struct Statement* stmt;
    struct Expression* expr; // Added to hold expression trees
    IntList* ilist;



/* Line 214 of yacc.c  */
#line 251 "test.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 263 "test.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   588

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  182

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    45,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
      40,    43,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35,    36,    37,    38,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    14,    19,    25,    31,
      39,    47,    52,    59,    64,    70,    76,    84,    90,    95,
      98,   102,   104,   107,   109,   114,   120,   126,   134,   139,
     146,   151,   157,   163,   166,   174,   176,   180,   185,   191,
     195,   199,   203,   209,   216,   224,   230,   236,   238,   240,
     242,   244,   246,   250,   252,   257,   262,   266,   270,   274,
     278,   282,   286,   290,   294,   297,   301,   305,   309,   313,
     315,   317,   322
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    53,    54,    -1,    54,    -1,
      59,    58,    42,    -1,    18,    43,    61,    42,    -1,    16,
      44,    61,    45,    55,    -1,    14,    44,    61,    45,    55,
      -1,    14,    44,    61,    45,    55,    15,    55,    -1,    18,
      46,    61,    47,    43,    61,    42,    -1,    18,    43,    19,
      42,    -1,    18,    43,    18,     9,    18,    42,    -1,    18,
      43,    20,    42,    -1,     4,    44,    18,    45,    42,    -1,
       4,    44,    61,    45,    42,    -1,     5,    44,    18,    48,
      18,    45,    42,    -1,     6,    18,    44,    45,    55,    -1,
      18,    44,    45,    42,    -1,    61,    42,    -1,    49,    56,
      50,    -1,    57,    -1,    56,    57,    -1,    57,    -1,    18,
      43,    61,    42,    -1,    16,    44,    61,    45,    55,    -1,
      14,    44,    61,    45,    55,    -1,    14,    44,    61,    45,
      55,    15,    55,    -1,    18,    43,    19,    42,    -1,    18,
      43,    18,     9,    18,    42,    -1,    18,    43,    20,    42,
      -1,     4,    44,    18,    45,    42,    -1,     4,    44,    61,
      45,    42,    -1,    61,    42,    -1,     5,    44,    18,    48,
      18,    45,    42,    -1,    18,    -1,    18,    43,    61,    -1,
      18,    46,    21,    47,    -1,    18,    43,    49,    60,    50,
      -1,    18,    43,    19,    -1,    18,    43,    20,    -1,    58,
      48,    18,    -1,    58,    48,    18,    43,    61,    -1,    58,
      48,    18,    46,    21,    47,    -1,    58,    48,    18,    43,
      49,    60,    50,    -1,    58,    48,    18,    43,    19,    -1,
      58,    48,    18,    43,    20,    -1,     3,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    60,    48,    61,    -1,
      61,    -1,     8,    44,    18,    45,    -1,     8,    44,    19,
      45,    -1,    61,    39,    61,    -1,    61,    40,    61,    -1,
      61,    35,    61,    -1,    61,    36,    61,    -1,    61,    37,
      61,    -1,    61,    38,    61,    -1,    61,    26,    61,    -1,
      61,    27,    61,    -1,    28,    61,    -1,    61,    22,    61,
      -1,    61,    23,    61,    -1,    61,    24,    61,    -1,    61,
      25,    61,    -1,    21,    -1,    18,    -1,    18,    46,    61,
      47,    -1,    44,    61,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   133,   134,   138,   139,   148,   157,   166,
     175,   183,   191,   204,   212,   219,   226,   234,   239,   243,
     254,   255,   259,   267,   271,   280,   289,   298,   307,   315,
     327,   335,   342,   349,   356,   368,   369,   370,   371,   381,
     382,   383,   384,   385,   386,   396,   397,   401,   402,   403,
     404,   405,   409,   413,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MYTYPE", "SHOW", "SWAP", "FUNCTION",
  "RETURN", "STRLEN", "CONCAT", "INTTYPE", "FLOATTYPE", "CHARTYPE",
  "STRINGTYPE", "IF", "ELSE", "WHILE", "ARRAYTYPE", "IDENTIFIER",
  "STRING_LITERAL", "CHAR_LITERAL", "NUMBER", "PLUS", "MINUS", "TIMES",
  "DIVIDE", "AND", "OR", "NOT", "BAND", "BOR", "BXOR", "BNOT", "LSHIFT",
  "RSHIFT", "EQ", "NE", "GE", "LE", "'>'", "'<'", "UMINUS", "';'", "'='",
  "'('", "')'", "'['", "']'", "','", "'{'", "'}'", "$accept", "program",
  "statements", "statement", "block", "statements_in_func",
  "statement_in_func", "declaration_list", "type_spec", "expr_list",
  "expression", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    62,
      60,   294,    59,    61,    40,    41,    91,    93,    44,   123,
     125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     4,     5,     5,     7,
       7,     4,     6,     4,     5,     5,     7,     5,     4,     2,
       3,     1,     2,     1,     4,     5,     5,     7,     4,     6,
       4,     5,     5,     2,     7,     1,     3,     4,     5,     3,
       3,     3,     5,     6,     7,     5,     5,     1,     1,     1,
       1,     1,     3,     1,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     1,
       1,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    47,     0,     0,     0,     0,    48,    49,    50,    51,
       0,     0,    70,    69,     0,     0,     0,     2,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    64,     0,     1,     3,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      70,     0,     0,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,    72,     0,     0,     5,     0,
      65,    66,    67,    68,    62,    63,    58,    59,    60,    61,
      56,    57,     0,     0,     0,     0,    54,    55,     0,     0,
       0,    11,    13,     6,    18,    71,     0,    39,    40,     0,
      36,     0,    41,    14,    15,     0,     0,     0,     0,     0,
      70,     0,    17,    21,     0,     8,     7,     0,     0,    71,
       0,    53,    37,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,    33,     0,    12,     0,     0,    38,    45,
      46,     0,    42,     0,    16,    70,     0,     0,     0,     0,
      70,     0,     0,     0,    20,    22,     9,    10,    52,     0,
      43,     0,     0,     0,     0,     0,     0,    28,    30,    24,
      44,    31,    32,     0,    26,    25,     0,     0,     0,    29,
      34,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,   112,   131,   113,    36,    19,   120,
     114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yytype_int16 yypact[] =
{
     139,  -110,   -32,   -26,    18,   -16,  -110,  -110,  -110,  -110,
      25,    33,    13,  -110,   183,   183,    54,   139,  -110,    44,
     418,   201,    65,    46,   -13,   183,   183,   169,    43,   183,
      48,   548,   250,  -110,  -110,    24,   -41,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,  -110,
     -22,   274,    50,    57,    58,    59,   298,   322,     4,    67,
      69,   439,    71,   212,   183,  -110,    87,    89,  -110,    74,
      -5,    -5,   225,   225,   548,   529,  -110,  -110,  -110,  -110,
     -27,   -27,    72,    77,    98,    68,  -110,  -110,    68,    68,
     102,  -110,  -110,  -110,  -110,    78,   231,  -110,  -110,   183,
     523,    75,    28,  -110,  -110,    79,    81,    83,    88,    90,
      35,   158,  -110,  -110,   460,   118,  -110,    93,   183,  -110,
      10,   523,  -110,   150,   117,    97,   202,   122,   183,   183,
     187,    47,  -110,  -110,    68,  -110,   481,   183,  -110,  -110,
    -110,   183,   523,    99,  -110,    55,   346,   100,   370,   394,
       7,   112,   114,   502,  -110,  -110,  -110,  -110,   523,    37,
    -110,   119,   123,   141,    68,    68,   146,  -110,  -110,  -110,
    -110,  -110,  -110,   128,   160,  -110,   138,   140,    68,  -110,
    -110,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,   164,   -85,  -110,  -109,  -110,  -110,    51,
       0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      20,    68,   132,   115,   116,    54,    55,    69,    43,    44,
      45,    46,    21,    90,    31,    32,   166,    20,    22,    39,
      40,    51,   155,    82,    64,    56,    57,    61,    24,    63,
      43,    44,    45,    46,    47,    48,    23,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,   156,
      64,   106,   107,    64,    33,     5,    27,    28,   137,    29,
     138,   108,    35,   109,    96,   110,   100,    66,    13,    25,
      67,   123,   106,   107,   124,    14,     5,    26,   130,   174,
     175,    64,   108,    52,   109,   137,   110,   170,    62,    13,
      53,    15,   102,   181,    64,     5,    14,   154,    84,   121,
     161,    64,    85,    86,    87,    30,    97,    98,    13,    91,
     101,    92,    15,    94,   103,    14,   105,   111,   136,   104,
     117,   118,   122,   142,   125,   126,   146,   127,   148,   149,
     153,    15,   128,   134,   129,   135,    99,   158,   143,   144,
     147,   121,     1,     2,     3,     4,   160,     5,   163,     6,
       7,     8,     9,    10,   167,    11,   168,    12,     5,   173,
      13,   171,   106,   107,   176,   172,     5,    14,    30,   139,
     140,    13,   108,   177,   109,   178,   110,     5,    14,    13,
     179,    34,   180,    15,     0,     0,    14,    58,    59,    60,
      13,     5,   159,     0,    15,     5,     0,    14,     0,   141,
       0,    30,    15,     0,    13,   150,   151,   152,    13,     5,
       5,    14,     0,    15,     0,    14,     0,     0,     0,    50,
     145,     0,    13,    13,     0,     0,     0,    15,     0,    14,
      14,    15,     0,     0,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,     0,    15,    15,    43,    44,    45,
      46,    47,    48,    37,    38,    39,    40,    41,    42,    95,
      43,    44,    45,    46,    47,    48,    43,    44,    45,    46,
      47,    48,    37,    38,    39,    40,    41,    42,   119,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     0,     0,     0,     0,    65,    37,    38,    39,    40,
      41,    42,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     0,     0,     0,     0,    83,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,     0,
       0,     0,     0,    88,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     0,     0,     0,     0,    89,    37,    38,
      39,    40,    41,    42,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,     0,     0,     0,
       0,   162,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     0,     0,     0,     0,   164,    37,    38,    39,    40,
      41,    42,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     0,     0,     0,     0,   165,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,     0,
      49,    37,    38,    39,    40,    41,    42,     0,     0,     0,
       0,     0,     0,     0,    43,    44,    45,    46,    47,    48,
       0,    93,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     0,   133,    37,    38,    39,    40,    41,    42,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     0,   157,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     0,   169,    37,    38,    39,    40,    41,
      42,    37,    38,    39,    40,    41,     0,     0,    43,    44,
      45,    46,    47,    48,    43,    44,    45,    46,    47,    48,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48
};

static const yytype_int16 yycheck[] =
{
       0,    42,   111,    88,    89,    18,    19,    48,    35,    36,
      37,    38,    44,     9,    14,    15,     9,    17,    44,    24,
      25,    21,   131,    45,    46,    25,    26,    27,    44,    29,
      35,    36,    37,    38,    39,    40,    18,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,   134,
      46,     4,     5,    46,     0,     8,    43,    44,    48,    46,
      50,    14,    18,    16,    64,    18,    66,    43,    21,    44,
      46,    43,     4,     5,    46,    28,     8,    44,    43,   164,
     165,    46,    14,    18,    16,    48,    18,    50,    45,    21,
      44,    44,    18,   178,    46,     8,    28,    50,    48,    99,
      45,    46,    45,    45,    45,    18,    19,    20,    21,    42,
      21,    42,    44,    42,    42,    28,    18,    49,   118,    42,
      18,    43,    47,   123,    45,    44,   126,    44,   128,   129,
     130,    44,    44,    15,    44,    42,    49,   137,    21,    42,
      18,   141,     3,     4,     5,     6,    47,     8,    48,    10,
      11,    12,    13,    14,    42,    16,    42,    18,     8,    18,
      21,    42,     4,     5,    18,    42,     8,    28,    18,    19,
      20,    21,    14,    45,    16,    15,    18,     8,    28,    21,
      42,    17,    42,    44,    -1,    -1,    28,    18,    19,    20,
      21,     8,   141,    -1,    44,     8,    -1,    28,    -1,    49,
      -1,    18,    44,    -1,    21,    18,    19,    20,    21,     8,
       8,    28,    -1,    44,    -1,    28,    -1,    -1,    -1,    18,
      18,    -1,    21,    21,    -1,    -1,    -1,    44,    -1,    28,
      28,    44,    -1,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    44,    44,    35,    36,    37,
      38,    39,    40,    22,    23,    24,    25,    26,    27,    47,
      35,    36,    37,    38,    39,    40,    35,    36,    37,    38,
      39,    40,    22,    23,    24,    25,    26,    27,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    45,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,
      22,    23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    45,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    45,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    45,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    45,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,
      22,    23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      42,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      -1,    42,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    40,    -1,    42,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    42,    22,    23,    24,    25,    26,
      27,    22,    23,    24,    25,    26,    -1,    -1,    35,    36,
      37,    38,    39,    40,    35,    36,    37,    38,    39,    40,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    10,    11,    12,    13,
      14,    16,    18,    21,    28,    44,    52,    53,    54,    59,
      61,    44,    44,    18,    44,    44,    44,    43,    44,    46,
      18,    61,    61,     0,    54,    18,    58,    22,    23,    24,
      25,    26,    27,    35,    36,    37,    38,    39,    40,    42,
      18,    61,    18,    44,    18,    19,    61,    61,    18,    19,
      20,    61,    45,    61,    46,    45,    43,    46,    42,    48,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    45,    45,    48,    45,    45,    45,    45,    45,
       9,    42,    42,    42,    42,    47,    61,    19,    20,    49,
      61,    21,    18,    42,    42,    18,     4,     5,    14,    16,
      18,    49,    55,    57,    61,    55,    55,    18,    43,    47,
      60,    61,    47,    43,    46,    45,    44,    44,    44,    44,
      43,    56,    57,    42,    15,    42,    61,    48,    50,    19,
      20,    49,    61,    21,    42,    18,    61,    18,    61,    61,
      18,    19,    20,    61,    50,    57,    55,    42,    61,    60,
      47,    45,    45,    48,    45,    45,     9,    42,    42,    42,
      50,    42,    42,    18,    55,    55,    18,    45,    15,    42,
      42,    55
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# if YYLTYPE_IS_TRIVIAL
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
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 133 "test.y"
    { if((yyvsp[(2) - (2)].stmt)) executeStatement((yyvsp[(2) - (2)].stmt)); free((yyvsp[(2) - (2)].stmt)); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 134 "test.y"
    { if((yyvsp[(1) - (1)].stmt)) executeStatement((yyvsp[(1) - (1)].stmt)); free((yyvsp[(1) - (1)].stmt)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 138 "test.y"
    { (yyval.stmt)=NULL; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 139 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->value_expr=(yyvsp[(3) - (4)].expr);
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 148 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_WHILE;
          s->value_expr = (yyvsp[(3) - (5)].expr); // Store the condition expression tree
          s->body = (yyvsp[(5) - (5)].stmt);
          s->else_body = NULL;
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 157 "test.y"
    { 
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = (yyvsp[(3) - (5)].expr); // Store the condition expression tree
          s->body = (yyvsp[(5) - (5)].stmt);
          s->else_body = NULL;
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 166 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = (yyvsp[(3) - (7)].expr); // Store the condition expression tree
          s->body = (yyvsp[(5) - (7)].stmt);
          s->else_body = (yyvsp[(7) - (7)].stmt);
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 175 "test.y"
    {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_ARRAY_ASSIGN;
        strcpy(s->varName,(yyvsp[(1) - (7)].str));
        s->value_expr = new_op_node(0, (yyvsp[(3) - (7)].expr), (yyvsp[(6) - (7)].expr)); // Use op node to hold index and value
        s->next = NULL;
        (yyval.stmt) = s;
      ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 183 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->strValue=strdup((yyvsp[(3) - (4)].str));
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 191 "test.y"
    {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_ASSIGN_STR;
        strcpy(s->varName,(yyvsp[(1) - (6)].str));
        char* left = value_to_unquoted_string_from_identifier((yyvsp[(3) - (6)].str));
        char* right = value_to_unquoted_string_from_identifier((yyvsp[(5) - (6)].str));
        char* res = concat_and_quote(left,right);
        s->strValue = res;
        s->next = NULL;
        if(left) free(left);
        if(right) free(right);
        (yyval.stmt) = s;
      ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 204 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_CHAR;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->strValue = strdup((yyvsp[(3) - (4)].str)); // Store full literal e.g. 'c'
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 212 "test.y"
    {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_SHOW;
        strcpy(s->varName,(yyvsp[(3) - (5)].str));
        s->next=NULL;
        (yyval.stmt)=s;
      ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 219 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = (yyvsp[(3) - (5)].expr);
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 226 "test.y"
    {
                Statement* s = malloc(sizeof(Statement));
                s->kind = STMT_SWAP;
                strcpy(s->varName, (yyvsp[(3) - (7)].str));
                strcpy(s->swapVar2, (yyvsp[(5) - (7)].str));
                s->next = NULL;
                (yyval.stmt) = s;
            ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 234 "test.y"
    { 
        addFunction((yyvsp[(2) - (5)].str),(yyvsp[(5) - (5)].stmt)); 
        printf("Function %s defined.\n",(yyvsp[(2) - (5)].str)); 
        (yyval.stmt)=NULL;
      ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 239 "test.y"
    { 
        executeFunction((yyvsp[(1) - (4)].str)); 
        (yyval.stmt)=NULL;
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 243 "test.y"
    { 
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_EXPR;
        s->value_expr = (yyvsp[(1) - (2)].expr);
        s->next=NULL;
        (yyval.stmt)=s;
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 254 "test.y"
    { (yyval.stmt)=(yyvsp[(2) - (3)].stmt); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 255 "test.y"
    { (yyval.stmt)=(yyvsp[(1) - (1)].stmt); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 259 "test.y"
    { 
          if((yyvsp[(1) - (2)].stmt)) {
              Statement* t = (yyvsp[(1) - (2)].stmt);
              while(t->next) t=t->next;
              t->next = (yyvsp[(2) - (2)].stmt);
              (yyval.stmt) = (yyvsp[(1) - (2)].stmt);
          } else (yyval.stmt)=(yyvsp[(2) - (2)].stmt);
      ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 267 "test.y"
    { (yyval.stmt)=(yyvsp[(1) - (1)].stmt); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 271 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->value_expr=(yyvsp[(3) - (4)].expr);
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 280 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_WHILE;
          s->value_expr = (yyvsp[(3) - (5)].expr);
          s->body = (yyvsp[(5) - (5)].stmt);
          s->else_body = NULL;
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 289 "test.y"
    { 
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = (yyvsp[(3) - (5)].expr);
          s->body = (yyvsp[(5) - (5)].stmt);
          s->else_body = NULL;
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 298 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = (yyvsp[(3) - (7)].expr);
          s->body = (yyvsp[(5) - (7)].stmt);
          s->else_body = (yyvsp[(7) - (7)].stmt);
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 307 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->strValue=strdup((yyvsp[(3) - (4)].str));
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 315 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,(yyvsp[(1) - (6)].str));
          char* left = value_to_unquoted_string_from_identifier((yyvsp[(3) - (6)].str));
          char* right = value_to_unquoted_string_from_identifier((yyvsp[(5) - (6)].str));
          s->strValue = concat_and_quote(left,right);
          s->next=NULL;
          if(left) free(left);
          if(right) free(right);
          (yyval.stmt)=s;
      ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 327 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_CHAR;
          strcpy(s->varName,(yyvsp[(1) - (4)].str));
          s->strValue = strdup((yyvsp[(3) - (4)].str));
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 335 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_SHOW;
          strcpy(s->varName,(yyvsp[(3) - (5)].str));
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 342 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = (yyvsp[(3) - (5)].expr);
          s->next = NULL;
          (yyval.stmt) = s;
      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 349 "test.y"
    {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = (yyvsp[(1) - (2)].expr);
          s->next=NULL;
          (yyval.stmt)=s;
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 356 "test.y"
    {
                Statement* s = malloc(sizeof(Statement));
                s->kind = STMT_SWAP;
                strcpy(s->varName, (yyvsp[(3) - (7)].str));
                strcpy(s->swapVar2, (yyvsp[(5) - (7)].str));
                s->next = NULL;
                (yyval.stmt) = s;
            ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 368 "test.y"
    { addSymbol((yyvsp[(1) - (1)].str),0,NULL,0); printf("Declared %s as int with default 0\n",(yyvsp[(1) - (1)].str)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 369 "test.y"
    { int val=evaluateExpression((yyvsp[(3) - (3)].expr)); addSymbol((yyvsp[(1) - (3)].str),val,NULL,0); printf("Declared %s with value %d\n",(yyvsp[(1) - (3)].str),val); free((yyvsp[(3) - (3)].expr)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 370 "test.y"
    { addSymbol((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].num),NULL,3); printf("Declared %s as array of size %d\n",(yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].num)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 371 "test.y"
    { 
                    IntList* il = (yyvsp[(4) - (5)].ilist);
                    addSymbol((yyvsp[(1) - (5)].str), il->count, NULL, 3);
                    int idx = findSymbolIndex((yyvsp[(1) - (5)].str));
                    if(idx != -1){
                            for(int i=0;i<il->count;i++) symbolTable[idx].array_values[i]=il->vals[i];
                    }
                    printf("Declared %s as array with initializer (size %d)\n",(yyvsp[(1) - (5)].str), il->count);
                    free(il->vals); free(il);
            ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 381 "test.y"
    { addSymbol((yyvsp[(1) - (3)].str),0,(yyvsp[(3) - (3)].str),2); printf("Declared %s as string with value '%s'\n",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 382 "test.y"
    { addSymbol((yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str)[1],NULL,1); printf("Declared %s as char with value '%c'\n",(yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str)[1]); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 383 "test.y"
    { addSymbol((yyvsp[(3) - (3)].str),0,NULL,0); printf("Declared %s as int with default 0\n",(yyvsp[(3) - (3)].str)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 384 "test.y"
    { int val=evaluateExpression((yyvsp[(5) - (5)].expr)); addSymbol((yyvsp[(3) - (5)].str),val,NULL,0); printf("Declared %s with value %d\n",(yyvsp[(3) - (5)].str),val); free((yyvsp[(5) - (5)].expr)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 385 "test.y"
    { addSymbol((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].num),NULL,3); printf("Declared %s as array of size %d\n",(yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].num)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 386 "test.y"
    { 
            IntList* il = (yyvsp[(6) - (7)].ilist);
            addSymbol((yyvsp[(3) - (7)].str), il->count, NULL, 3);
            int idx = findSymbolIndex((yyvsp[(3) - (7)].str));
            if(idx != -1){
                for(int i=0;i<il->count;i++) symbolTable[idx].array_values[i]=il->vals[i];
            }
            printf("Declared %s as array with initializer (size %d)\n",(yyvsp[(3) - (7)].str), il->count);
            free(il->vals); free(il);
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 396 "test.y"
    { addSymbol((yyvsp[(3) - (5)].str),0,(yyvsp[(5) - (5)].str),2); printf("Declared %s as string with value '%s'\n",(yyvsp[(3) - (5)].str),(yyvsp[(5) - (5)].str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 397 "test.y"
    { addSymbol((yyvsp[(3) - (5)].str),(yyvsp[(5) - (5)].str)[1],NULL,1); printf("Declared %s as char with value '%c'\n",(yyvsp[(3) - (5)].str),(yyvsp[(5) - (5)].str)[1]); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 401 "test.y"
    { (yyval.num) = 0; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 402 "test.y"
    { (yyval.num) = 0; ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 403 "test.y"
    { (yyval.num) = 4; ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 404 "test.y"
    { (yyval.num) = 1; ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 405 "test.y"
    { (yyval.num) = 2; ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 409 "test.y"
    {
          IntList* t = (yyvsp[(1) - (3)].ilist);
          t->vals = realloc(t->vals, (t->count+1)*sizeof(int));
          t->vals[t->count] = evaluateExpression((yyvsp[(3) - (3)].expr)); t->count++; (yyval.ilist) = t; free((yyvsp[(3) - (3)].expr)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 413 "test.y"
    { IntList* t = malloc(sizeof(IntList)); t->vals = malloc(sizeof(int)); t->vals[0] = evaluateExpression((yyvsp[(1) - (1)].expr)); t->count = 1; (yyval.ilist) = t; free((yyvsp[(1) - (1)].expr)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 418 "test.y"
    { (yyval.expr) = new_strlen_var_node((yyvsp[(3) - (4)].str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 419 "test.y"
    { (yyval.expr) = new_strlen_lit_node((yyvsp[(3) - (4)].str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 420 "test.y"
    { (yyval.expr) = new_op_node('>', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 421 "test.y"
    { (yyval.expr) = new_op_node('<', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 422 "test.y"
    { (yyval.expr) = new_op_node(EQ, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 423 "test.y"
    { (yyval.expr) = new_op_node(NE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 424 "test.y"
    { (yyval.expr) = new_op_node(GE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 425 "test.y"
    { (yyval.expr) = new_op_node(LE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 426 "test.y"
    { (yyval.expr) = new_op_node(AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 427 "test.y"
    { (yyval.expr) = new_op_node(OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 428 "test.y"
    { (yyval.expr) = new_op_node(NOT, (yyvsp[(2) - (2)].expr), NULL); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 429 "test.y"
    { (yyval.expr) = new_op_node(PLUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 430 "test.y"
    { (yyval.expr) = new_op_node(MINUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 431 "test.y"
    { (yyval.expr) = new_op_node(TIMES, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 432 "test.y"
    { (yyval.expr) = new_op_node(DIVIDE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 433 "test.y"
    { (yyval.expr) = new_const_node((yyvsp[(1) - (1)].num)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 434 "test.y"
    { (yyval.expr) = new_var_node((yyvsp[(1) - (1)].str)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 435 "test.y"
    { (yyval.expr) = new_array_access_node((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 436 "test.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2384 "test.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 1675 of yacc.c  */
#line 439 "test.y"


void yyerror(const char *s){ fprintf(stderr,"Error: %s\n",s); }
int main(){ return yyparse(); }

/* --- NEW: Expression Tree Node Constructors --- */
Expression* new_const_node(int val) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_CONST; e->value = val;
    return e;
}
Expression* new_var_node(char* name) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_VAR; strcpy(e->name, name);
    return e;
}
Expression* new_array_access_node(char* name, Expression* index_expr) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_ARRAY_ACCESS;
    strcpy(e->name, name);
    e->left = index_expr;
    e->right = NULL;
    return e;
}
Expression* new_op_node(int op, Expression* left, Expression* right) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = right ? EXPR_BINOP : EXPR_UNOP;
    e->op = op; e->left = left; e->right = right;
    return e;
}
Expression* new_strlen_var_node(char* name) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_STRLEN_VAR; strcpy(e->name, name);
    return e;
}
Expression* new_strlen_lit_node(char* literal) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_STRLEN_LIT; e->str_literal = strdup(literal);
    return e;
}

/* --- NEW: Expression Tree Evaluator --- */
int evaluateExpression(Expression* e) {
    if (!e) return 0;
    switch (e->kind) {
        case EXPR_CONST: return e->value;
        case EXPR_VAR: {
            int idx = findSymbolIndex(e->name);
            if (idx == -1) { printf("Error: %s not declared\n", e->name); return 0; }
            return symbolTable[idx].intValue;
        }
        case EXPR_ARRAY_ACCESS: {
            int idx = findSymbolIndex(e->name);
            if(idx==-1){printf("Error: %s not declared\n",e->name);return 0;}
            int i = evaluateExpression(e->left);
            if(i<0 || i>=symbolTable[idx].array_size){printf("Index out of bounds for %s\n",e->name); return 0;}
            return symbolTable[idx].array_values[i];
        }
        case EXPR_STRLEN_VAR: {
            int idx = findSymbolIndex(e->name);
            if (idx == -1) { printf("Error: %s not declared\n", e->name); return 0; }
            if(symbolTable[idx].type == 2 && symbolTable[idx].strValue) {
                char* str = symbolTable[idx].strValue;
                size_t len = strlen(str);
                if(len >= 2 && str[0] == '"' && str[len-1] == '"') return (int)(len-2);
                return (int)len;
            } else if (symbolTable[idx].type == 1) { return 1; }
            return 0;
        }
        case EXPR_STRLEN_LIT: {
            char* s = e->str_literal;
            size_t len = strlen(s);
            if(len >= 2 && s[0] == '"' && s[len-1] == '"') return (int)(len-2);
            return (int)len;
        }
        case EXPR_UNOP:
            if (e->op == NOT) return !evaluateExpression(e->left);
            return 0; // Other unary ops can be added here
        case EXPR_BINOP: {
            int left_val = evaluateExpression(e->left);
            int right_val = evaluateExpression(e->right);
            switch (e->op) {
                case PLUS: return left_val + right_val;
                case MINUS: return left_val - right_val;
                case TIMES: return left_val * right_val;
                case DIVIDE: if(right_val==0){yyerror("Division by zero");return 0;} return left_val/right_val;
                case '>': return left_val > right_val;
                case '<': return left_val < right_val;
                case EQ: return left_val == right_val;
                case NE: return left_val != right_val;
                case GE: return left_val >= right_val;
                case LE: return left_val <= right_val;
                case AND: return left_val && right_val;
                case OR: return left_val || right_val;
                default: return 0;
            }
        }
    }
    return 0;
}

/* ---------- SYMBOL FUNCTIONS ---------- */
int findSymbolIndex(char* name){ 
    for(int i=0;i<symbolCount;i++) 
        if(strcmp(symbolTable[i].name,name)==0) return i; 
    return -1; 
}
void addSymbol(char* name,int intVal,char* strVal,int type){
    int idx=findSymbolIndex(name);
    if(idx==-1){ 
        strcpy(symbolTable[symbolCount].name,name); 
        symbolTable[symbolCount].intValue=intVal; 
        symbolTable[symbolCount].strValue=strVal?strdup(strVal):NULL; 
        symbolTable[symbolCount].type=type; 
        symbolTable[symbolCount].array_size = (type==3)?intVal:0;
        symbolCount++; 
    }
    else{ 
        symbolTable[idx].intValue=intVal; 
        if(symbolTable[idx].strValue) free(symbolTable[idx].strValue); 
        symbolTable[idx].strValue=strVal?strdup(strVal):NULL; 
        symbolTable[idx].type=type; 
        if(type==3) symbolTable[idx].array_size = intVal;
    }
}

/* --- MODIFIED: Statement Executor --- */
void executeStatement(Statement* s) {
    if(!s) return;
    switch(s->kind) {
        case STMT_ASSIGN: {
            int val = evaluateExpression(s->value_expr);
            addSymbol(s->varName, val, NULL, 0);
            printf("Assigned %d to %s\n", val, s->varName);
            break;
        }
        case STMT_ASSIGN_STR: {
            addSymbol(s->varName, 0, s->strValue, 2);
            printf("Assigned string %s to %s\n", s->strValue, s->varName);
            break;
        }
        case STMT_ASSIGN_CHAR: {
            addSymbol(s->varName, s->strValue[1], NULL, 1);
            printf("Assigned char '%c' to %s\n", s->strValue[1], s->varName);
            break;
        }
        case STMT_ARRAY_ASSIGN: {
            int idx_val = evaluateExpression(s->value_expr->left);
            int val = evaluateExpression(s->value_expr->right);
            int sym_idx = findSymbolIndex(s->varName);
            if(sym_idx == -1) { printf("Error: %s not declared\n", s->varName); }
            else if(symbolTable[sym_idx].type != 3) { printf("Error: %s is not an array\n", s->varName); }
            else if(idx_val < 0 || idx_val >= symbolTable[sym_idx].array_size) { printf("Index out of bounds for %s\n", s->varName); }
            else { symbolTable[sym_idx].array_values[idx_val] = val; printf("Assigned %d to %s[%d]\n", val, s->varName, idx_val); }
            break;
        }
        case STMT_SHOW: {
            int idx=findSymbolIndex(s->varName);
            if(idx!=-1){
                if(symbolTable[idx].type==0) printf("%s=%d\n",s->varName,symbolTable[idx].intValue);
                else if(symbolTable[idx].type==1) printf("%s='%c'\n",s->varName,(char)symbolTable[idx].intValue);
                else if(symbolTable[idx].type==2 && symbolTable[idx].strValue) printf("%s=%s\n",s->varName, symbolTable[idx].strValue);
                else printf("%s=<unknown type>\n",s->varName);
            } else printf("Variable %s not declared\n",s->varName);
            break;
        }
        case STMT_EXPR: {
            printf("Expression result: %d\n", evaluateExpression(s->value_expr));
            break;
        }
        case STMT_SWAP: {
            int idx1 = findSymbolIndex(s->varName);
            int idx2 = findSymbolIndex(s->swapVar2);
            if(idx1 == -1 || idx2 == -1) {
                printf("Error: variable(s) not declared\n");
                break;
            }
            if(symbolTable[idx1].type != symbolTable[idx2].type) {
                printf("Error: type mismatch for swap\n");
                break;
            }
            switch(symbolTable[idx1].type) {
                case 0: // int
                case 4: // float (if supported)
                    {
                        int tmp = symbolTable[idx1].intValue;
                        symbolTable[idx1].intValue = symbolTable[idx2].intValue;
                        symbolTable[idx2].intValue = tmp;
                        printf("Swapped %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 1: // char
                    {
                        int tmp = symbolTable[idx1].intValue;
                        symbolTable[idx1].intValue = symbolTable[idx2].intValue;
                        symbolTable[idx2].intValue = tmp;
                        printf("Swapped chars %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 2: // string
                    {
                        char* tmp = symbolTable[idx1].strValue;
                        symbolTable[idx1].strValue = symbolTable[idx2].strValue;
                        symbolTable[idx2].strValue = tmp;
                        printf("Swapped strings %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 3: // array
                    {
                        int* tmp = malloc(sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(tmp, symbolTable[idx1].array_values, sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(symbolTable[idx1].array_values, symbolTable[idx2].array_values, sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(symbolTable[idx2].array_values, tmp, sizeof(int)*symbolTable[idx1].array_size);
                        free(tmp);
                        printf("Swapped arrays %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                default:
                    printf("Swap not supported for this type\n");
            }
            break;
        }
        case STMT_IF: {
            if (evaluateExpression(s->value_expr)) {
                Statement* t = s->body;
                while(t) { executeStatement(t); t = t->next; }
            } else if (s->else_body) {
                Statement* t = s->else_body;
                while(t) { executeStatement(t); t = t->next; }
            }
            break;
        }
        /* --- NEW: WHILE loop execution logic --- */
        case STMT_WHILE: {
            while (evaluateExpression(s->value_expr)) {
                Statement* t = s->body;
                while (t) {
                    executeStatement(t);
                    t = t->next;
                }
            }
            break;
        }
    }
}

/* ---------- FUNCTION SUPPORT ---------- */
int findFunctionIndex(char* name){ 
    for(int i=0;i<funcCount;i++) 
        if(strcmp(funcTable[i].name,name)==0) return i; 
    return -1; 
}
void addFunction(char* name, Statement* body){ 
    strcpy(funcTable[funcCount].name,name); 
    funcTable[funcCount].body=body; 
    funcCount++; 
}
void executeFunction(char* name){
    int idx=findFunctionIndex(name);
    if(idx==-1){ printf("Error: function %s not found\n",name); return; }
    Statement* s=funcTable[idx].body;
    printf("Executing function %s\n",name);
    while(s){
        executeStatement(s);
        s=s->next;
    }
}

/* ---------- STRING HELPERS ---------- */
char* strip_quotes(const char* s){
    if(!s) return NULL;
    size_t len = strlen(s);
    if(len >= 2 && s[0] == '"' && s[len-1] == '"'){
        char* out = malloc(len-1);
        strncpy(out, s+1, len-2);
        out[len-2] = '\0';
        return out;
    }
    return strdup(s);
}

char* concat_and_quote(const char* a, const char* b){
    const char* aa = a?a:"";
    const char* bb = b?b:"";
    size_t la = strlen(aa);
    size_t lb = strlen(bb);
    char* out = malloc(la+lb+3);
    out[0] = '"';
    memcpy(out+1, aa, la);
    memcpy(out+1+la, bb, lb);
    out[1+la+lb] = '"';
    out[1+la+lb+1] = '\0';
    return out;
}

char* value_to_unquoted_string_from_identifier(const char* name){
    int idx = findSymbolIndex((char*)name);
    if(idx == -1) return strdup("");
    if(symbolTable[idx].type == 2 && symbolTable[idx].strValue){
        return strip_quotes(symbolTable[idx].strValue);
    }
    if(symbolTable[idx].type == 1){
        char buf[2] = {(char)symbolTable[idx].intValue, '\0'};
        return strdup(buf);
    }
    if(symbolTable[idx].type == 0){
        char tmp[64];
        sprintf(tmp, "%d", symbolTable[idx].intValue);
        return strdup(tmp);
    }
    return strdup("");
}


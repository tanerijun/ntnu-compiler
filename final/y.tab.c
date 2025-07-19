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
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BEGIN_TOKEN = 258,
     END_TOKEN = 259,
     DECLARE_TOKEN = 260,
     AS_TOKEN = 261,
     INTEGER_TOKEN = 262,
     REAL_TOKEN = 263,
     PROGRAM_TOKEN = 264,
     IF_TOKEN = 265,
     THEN_TOKEN = 266,
     ELSE_TOKEN = 267,
     ENDIF_TOKEN = 268,
     FOR_TOKEN = 269,
     TO_TOKEN = 270,
     DOWNTO_TOKEN = 271,
     ENDFOR_TOKEN = 272,
     STEP_TOKEN = 273,
     WHILE_TOKEN = 274,
     ENDWHILE_TOKEN = 275,
     PRINT_TOKEN = 276,
     WRITE_TOKEN = 277,
     ASSIGN_OP = 278,
     GE_OP = 279,
     LE_OP = 280,
     EQ_OP = 281,
     NE_OP = 282,
     INT_LITERAL = 283,
     FLOAT_LITERAL = 284,
     ID = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define BEGIN_TOKEN 258
#define END_TOKEN 259
#define DECLARE_TOKEN 260
#define AS_TOKEN 261
#define INTEGER_TOKEN 262
#define REAL_TOKEN 263
#define PROGRAM_TOKEN 264
#define IF_TOKEN 265
#define THEN_TOKEN 266
#define ELSE_TOKEN 267
#define ENDIF_TOKEN 268
#define FOR_TOKEN 269
#define TO_TOKEN 270
#define DOWNTO_TOKEN 271
#define ENDFOR_TOKEN 272
#define STEP_TOKEN 273
#define WHILE_TOKEN 274
#define ENDWHILE_TOKEN 275
#define PRINT_TOKEN 276
#define WRITE_TOKEN 277
#define ASSIGN_OP 278
#define GE_OP 279
#define LE_OP 280
#define EQ_OP 281
#define NE_OP 282
#define INT_LITERAL 283
#define FLOAT_LITERAL 284
#define ID 285
#define UMINUS 286




/* Copy the first part of user declarations.  */
#line 1 "microex.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microex.h"

void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

struct symtab symtab[NSYMS];
int symtab_count = 0;
char program_name[256];

int temp_counter = 0;
int label_counter = 0;
struct label_stack if_stack[20];
int if_stack_ptr = 0;
struct label_stack for_stack[20];
int for_stack_ptr = 0;

int in_while_loop = 0;

struct {
    struct symtab *ids[100];
    int count;
    int type;
} current_decl;

struct {
    struct symtab *array;
    struct symtab *index;
} current_array_access;


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
#line 36 "microex.y"
{
    int ival;
    float fval;
    struct symtab *symp;
    struct {
        struct symtab *place;
        int type;
    } expr;
}
/* Line 193 of yacc.c.  */
#line 203 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 216 "y.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,    33,    31,    37,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      43,     2,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    11,    13,    16,    18,    20,    22,
      24,    26,    28,    34,    36,    40,    42,    47,    49,    51,
      56,    58,    63,    67,    71,    73,    77,    81,    83,    87,
      90,    92,    94,    96,   101,   105,   110,   111,   118,   119,
     123,   127,   128,   131,   141,   151,   155,   156,   162,   166,
     170,   174,   178,   182,   186,   190,   196,   202,   204
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,     3,    47,     4,    -1,     9,    30,
      -1,    48,    -1,    47,    48,    -1,    49,    -1,    53,    -1,
      58,    -1,    63,    -1,    66,    -1,    70,    -1,     5,    50,
       6,    52,    36,    -1,    51,    -1,    50,    37,    51,    -1,
      30,    -1,    30,    38,    28,    39,    -1,     7,    -1,     8,
      -1,    54,    23,    55,    36,    -1,    30,    -1,    30,    38,
      55,    39,    -1,    55,    31,    56,    -1,    55,    32,    56,
      -1,    56,    -1,    56,    33,    57,    -1,    56,    34,    57,
      -1,    57,    -1,    40,    55,    41,    -1,    32,    57,    -1,
      28,    -1,    29,    -1,    30,    -1,    30,    38,    55,    39,
      -1,    59,    47,    13,    -1,    59,    47,    61,    13,    -1,
      -1,    10,    40,    60,    69,    41,    11,    -1,    -1,    12,
      62,    47,    -1,    65,    47,    17,    -1,    -1,    18,    55,
      -1,    14,    40,    30,    23,    55,    15,    55,    64,    41,
      -1,    14,    40,    30,    23,    55,    16,    55,    64,    41,
      -1,    67,    47,    20,    -1,    -1,    19,    40,    68,    69,
      41,    -1,    55,    42,    55,    -1,    55,    43,    55,    -1,
      55,    24,    55,    -1,    55,    25,    55,    -1,    55,    26,
      55,    -1,    55,    27,    55,    -1,    40,    69,    41,    -1,
      21,    40,    71,    41,    36,    -1,    22,    40,    71,    41,
      36,    -1,    55,    -1,    71,    37,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    74,    82,    83,    87,    88,    89,    90,
      91,    92,    96,   118,   119,   123,   129,   138,   139,   143,
     190,   200,   222,   249,   276,   283,   310,   337,   344,   348,
     360,   370,   380,   395,   422,   427,   436,   435,   449,   448,
     457,   497,   501,   511,   538,   568,   578,   577,   592,   605,
     618,   631,   644,   657,   670,   674,   675,   679,   683
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEGIN_TOKEN", "END_TOKEN",
  "DECLARE_TOKEN", "AS_TOKEN", "INTEGER_TOKEN", "REAL_TOKEN",
  "PROGRAM_TOKEN", "IF_TOKEN", "THEN_TOKEN", "ELSE_TOKEN", "ENDIF_TOKEN",
  "FOR_TOKEN", "TO_TOKEN", "DOWNTO_TOKEN", "ENDFOR_TOKEN", "STEP_TOKEN",
  "WHILE_TOKEN", "ENDWHILE_TOKEN", "PRINT_TOKEN", "WRITE_TOKEN",
  "ASSIGN_OP", "GE_OP", "LE_OP", "EQ_OP", "NE_OP", "INT_LITERAL",
  "FLOAT_LITERAL", "ID", "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'",
  "','", "'['", "']'", "'('", "')'", "'>'", "'<'", "$accept", "program",
  "program_header", "stmt_list", "stmt", "declaration_stmt", "id_list",
  "id_decl", "type", "assignment_stmt", "lvalue", "expression", "term",
  "factor", "if_stmt", "if_header", "@1", "else_part", "@2", "for_stmt",
  "optional_step", "for_header", "while_stmt", "while_header", "@3",
  "condition", "print_stmt", "print_list", 0
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
     285,    43,    45,    42,    47,   286,    59,    44,    91,    93,
      40,    41,    62,    60
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    48,    48,    48,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      54,    54,    55,    55,    55,    56,    56,    56,    57,    57,
      57,    57,    57,    57,    58,    58,    60,    59,    62,    61,
      63,    64,    64,    65,    65,    66,    68,    67,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     1,     4,     1,     1,     4,
       1,     4,     3,     3,     1,     3,     3,     1,     3,     2,
       1,     1,     1,     4,     3,     4,     0,     6,     0,     3,
       3,     0,     2,     9,     9,     3,     0,     5,     3,     3,
       3,     3,     3,     3,     3,     5,     5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     0,    20,     0,     4,     6,     7,     0,     8,
       0,     9,     0,    10,     0,    11,    15,     0,    13,    36,
       0,    46,     0,     0,     0,     2,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
       0,     0,    57,    24,    27,     0,     0,     0,     0,    38,
      34,     0,    40,    45,     0,    17,    18,     0,    14,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    19,     0,    35,    16,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,    28,    22,    23,    25,    26,    58,    55,    56,
      39,    54,    50,    51,    52,    53,    48,    49,    37,     0,
       0,    33,    41,    41,     0,     0,     0,    42,    43,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    14,    15,    16,    27,    28,    67,    17,
      18,    52,    53,    54,    19,    20,    44,    61,    86,    21,
     125,    22,    23,    24,    46,    71,    25,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -43
static const yytype_int8 yypact[] =
{
       1,   -18,    28,    29,   -43,   -43,   111,    23,     6,    15,
      18,    60,    61,    30,    62,   -43,   -43,   -43,    79,   -43,
     111,   -43,   111,   -43,   111,   -43,    67,    -4,   -43,   -43,
      80,   -43,    45,    45,    45,   -43,   -43,    45,    85,    35,
      98,    81,    63,    23,    94,    88,    94,   -43,   -43,    75,
      45,    45,    48,    55,   -43,    10,    41,   -12,   -15,   -43,
     -43,   101,   -43,   -43,    90,   -43,   -43,    91,   -43,    94,
     125,    99,    45,   104,    45,   -43,     3,    45,    45,    45,
      45,    45,    95,   106,   -43,   -43,   111,   -43,   -43,   -43,
     112,   105,    45,    45,    45,    45,    45,    45,   124,    -1,
     -43,    11,   -43,    55,    55,   -43,   -43,    48,   -43,   -43,
     111,   -43,    48,    48,    48,    48,    48,    48,   -43,    45,
      45,   -43,    -9,    -9,    45,   107,   117,    48,   -43,   -43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,   -17,   -14,   -43,   -43,   116,   -43,   -43,
     -43,   -33,    16,   -42,   -43,   -43,   -43,   -43,   -43,   -43,
      24,   -43,   -43,   -43,   -43,   -40,   -43,   127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      36,    57,    42,    38,    58,    39,    73,    40,    75,   124,
       1,    70,     4,    70,   119,   120,    77,    78,    76,    77,
      78,    85,    77,    78,    36,    36,    36,    84,     5,    91,
      77,    78,     6,    43,    77,    78,    90,   105,   106,    99,
       7,   101,    77,    78,   102,     8,    29,    81,   107,     9,
     121,    82,    62,    26,    10,    30,    11,    12,    31,   112,
     113,   114,   115,   116,   117,    13,    35,     7,    34,   110,
      65,    66,     8,    47,    48,    49,     9,    50,    81,    77,
      78,    10,    83,    11,    12,    51,   122,   123,    79,    80,
       7,   127,    13,   103,   104,     8,    36,    59,    60,     9,
      32,    33,    37,     7,    10,    41,    11,    12,     8,    64,
      45,    72,     9,    74,    87,    13,     7,    10,    63,    11,
      12,     8,    47,    48,    49,     9,    50,    89,    13,    88,
      10,   108,    11,    12,    69,   118,    92,    93,    94,    95,
      98,    13,   109,    77,    78,   100,   111,   126,   128,    92,
      93,    94,    95,   102,    96,    97,    77,    78,   129,    68,
      56,     0,     0,     0,     0,     0,     0,    96,    97
};

static const yytype_int8 yycheck[] =
{
      14,    34,     6,    20,    37,    22,    46,    24,    50,    18,
       9,    44,    30,    46,    15,    16,    31,    32,    51,    31,
      32,    36,    31,    32,    38,    39,    40,    39,     0,    69,
      31,    32,     3,    37,    31,    32,    69,    79,    80,    72,
       5,    74,    31,    32,    41,    10,    40,    37,    81,    14,
      39,    41,    17,    30,    19,    40,    21,    22,    40,    92,
      93,    94,    95,    96,    97,    30,     4,     5,    38,    86,
       7,     8,    10,    28,    29,    30,    14,    32,    37,    31,
      32,    19,    41,    21,    22,    40,   119,   120,    33,    34,
       5,   124,    30,    77,    78,    10,   110,    12,    13,    14,
      40,    40,    23,     5,    19,    38,    21,    22,    10,    28,
      30,    23,    14,    38,    13,    30,     5,    19,    20,    21,
      22,    10,    28,    29,    30,    14,    32,    36,    30,    39,
      19,    36,    21,    22,    40,    11,    24,    25,    26,    27,
      41,    30,    36,    31,    32,    41,    41,   123,    41,    24,
      25,    26,    27,    41,    42,    43,    31,    32,    41,    43,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    45,    46,    30,     0,     3,     5,    10,    14,
      19,    21,    22,    30,    47,    48,    49,    53,    54,    58,
      59,    63,    65,    66,    67,    70,    30,    50,    51,    40,
      40,    40,    40,    40,    38,     4,    48,    23,    47,    47,
      47,    38,     6,    37,    60,    30,    68,    28,    29,    30,
      32,    40,    55,    56,    57,    71,    71,    55,    55,    12,
      13,    61,    17,    20,    28,     7,     8,    52,    51,    40,
      55,    69,    23,    69,    38,    57,    55,    31,    32,    33,
      34,    37,    41,    41,    39,    36,    62,    13,    39,    36,
      55,    69,    24,    25,    26,    27,    42,    43,    41,    55,
      41,    55,    41,    56,    56,    57,    57,    55,    36,    36,
      47,    41,    55,    55,    55,    55,    55,    55,    11,    15,
      16,    39,    55,    55,    18,    64,    64,    55,    41,    41
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
yyparse (void)
#else
int
yyparse ()

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



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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
#line 75 "microex.y"
    {
        strcpy(program_name, (yyvsp[(2) - (2)].symp)->name);
        printf("START %s\n", program_name);
    ;}
    break;

  case 12:
#line 97 "microex.y"
    {
        for(int i = 0; i < current_decl.count; i++) {
            current_decl.ids[i]->type = (yyvsp[(4) - (5)].ival);
            current_decl.ids[i]->is_declared = 1;

            if (current_decl.ids[i]->isArray) {
                printf("Declare %s, %s_array,%d\n",
                    current_decl.ids[i]->name,
                    (yyvsp[(4) - (5)].ival) == TYPE_INT ? "Integer" : "Float",
                    current_decl.ids[i]->size);
            } else {
                printf("Declare %s, %s\n",
                    current_decl.ids[i]->name,
                    (yyvsp[(4) - (5)].ival) == TYPE_INT ? "Integer" : "Float");
            }
        }
        current_decl.count = 0;
    ;}
    break;

  case 15:
#line 124 "microex.y"
    {
        (yyvsp[(1) - (1)].symp)->isArray = 0;
        (yyvsp[(1) - (1)].symp)->size = 0;
        current_decl.ids[current_decl.count++] = (yyvsp[(1) - (1)].symp);
    ;}
    break;

  case 16:
#line 130 "microex.y"
    {
        (yyvsp[(1) - (4)].symp)->isArray = 1;
        (yyvsp[(1) - (4)].symp)->size = (yyvsp[(3) - (4)].ival);
        current_decl.ids[current_decl.count++] = (yyvsp[(1) - (4)].symp);
    ;}
    break;

  case 17:
#line 138 "microex.y"
    { (yyval.ival) = TYPE_INT; ;}
    break;

  case 18:
#line 139 "microex.y"
    { (yyval.ival) = TYPE_FLOAT; ;}
    break;

  case 19:
#line 144 "microex.y"
    {
        if (current_array_access.array != NULL) {
            char target_operand_name[100];
            sprintf(target_operand_name, "%s[%s]", current_array_access.array->name, current_array_access.index->name);

            if (current_array_access.array->type == TYPE_INT) {
                if ((yyvsp[(3) - (4)].expr).type == TYPE_INT) {
                    printf("I_Store %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, target_operand_name);
                } else {
                    char *temp_conv = new_temp(TYPE_INT);
                    printf("F_TO_I %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, temp_conv);
                    printf("I_Store %s,%s\n", temp_conv, target_operand_name);
                }
            } else {
                if ((yyvsp[(3) - (4)].expr).type == TYPE_INT) {
                    char *temp_conv = new_temp(TYPE_FLOAT);
                    printf("I_TO_F %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, temp_conv);
                    printf("F_Store %s,%s\n", temp_conv, target_operand_name);
                } else {
                    printf("F_Store %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, target_operand_name);
                }
            }
            current_array_access.array = NULL;
        } else {
            if ((yyvsp[(1) - (4)].symp)->type == TYPE_INT) {
                if ((yyvsp[(3) - (4)].expr).type == TYPE_INT) {
                    printf("I_Store %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, (yyvsp[(1) - (4)].symp)->name);
                } else {
                    char *temp = new_temp(TYPE_INT);
                    printf("F_TO_I %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, temp);
                    printf("I_Store %s,%s\n", temp, (yyvsp[(1) - (4)].symp)->name);
                }
            } else {
                if ((yyvsp[(3) - (4)].expr).type == TYPE_INT) {
                    char *temp = new_temp(TYPE_FLOAT);
                    printf("I_TO_F %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, temp);
                    printf("F_Store %s,%s\n", temp, (yyvsp[(1) - (4)].symp)->name);
                } else {
                    printf("F_Store %s,%s\n", (yyvsp[(3) - (4)].expr).place->name, (yyvsp[(1) - (4)].symp)->name);
                }
            }
        }
    ;}
    break;

  case 20:
#line 191 "microex.y"
    {
        if (!(yyvsp[(1) - (1)].symp)->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' not declared.", (yyvsp[(1) - (1)].symp)->name);
            yyerror(err_msg);
        }
        (yyval.symp) = (yyvsp[(1) - (1)].symp);
        current_array_access.array = NULL;
    ;}
    break;

  case 21:
#line 201 "microex.y"
    {
        if (!(yyvsp[(1) - (4)].symp)->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Array '%s' not declared.", (yyvsp[(1) - (4)].symp)->name);
            yyerror(err_msg);
        }
        if (!(yyvsp[(1) - (4)].symp)->isArray) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' is not an array.", (yyvsp[(1) - (4)].symp)->name);
            yyerror(err_msg);
        }
        if ((yyvsp[(3) - (4)].expr).type != TYPE_INT) {
            yyerror("Array index must be an integer.");
        }
        current_array_access.array = (yyvsp[(1) - (4)].symp);
        current_array_access.index = (yyvsp[(3) - (4)].expr).place;
        (yyval.symp) = (yyvsp[(1) - (4)].symp);
    ;}
    break;

  case 22:
#line 223 "microex.y"
    {
        (yyval.expr).type = ((yyvsp[(1) - (3)].expr).type == TYPE_FLOAT || (yyvsp[(3) - (3)].expr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        char *temp_res_name;

        if ((yyval.expr).type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        (yyval.expr).place = symlook(temp_res_name);
        (yyval.expr).place->type = (yyval.expr).type;
    ;}
    break;

  case 23:
#line 250 "microex.y"
    {
        (yyval.expr).type = ((yyvsp[(1) - (3)].expr).type == TYPE_FLOAT || (yyvsp[(3) - (3)].expr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        char *temp_res_name;

        if ((yyval.expr).type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_SUB %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_SUB %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        (yyval.expr).place = symlook(temp_res_name);
        (yyval.expr).place->type = (yyval.expr).type;
    ;}
    break;

  case 24:
#line 277 "microex.y"
    {
        (yyval.expr) = (yyvsp[(1) - (1)].expr);
    ;}
    break;

  case 25:
#line 284 "microex.y"
    {
        (yyval.expr).type = ((yyvsp[(1) - (3)].expr).type == TYPE_FLOAT || (yyvsp[(3) - (3)].expr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        char *temp_res_name;

        if ((yyval.expr).type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_MUL %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_MUL %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        (yyval.expr).place = symlook(temp_res_name);
        (yyval.expr).place->type = (yyval.expr).type;
    ;}
    break;

  case 26:
#line 311 "microex.y"
    {
        (yyval.expr).type = ((yyvsp[(1) - (3)].expr).type == TYPE_FLOAT || (yyvsp[(3) - (3)].expr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        char *temp_res_name;

        if ((yyval.expr).type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_DIV %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_DIV %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        (yyval.expr).place = symlook(temp_res_name);
        (yyval.expr).place->type = (yyval.expr).type;
    ;}
    break;

  case 27:
#line 338 "microex.y"
    {
        (yyval.expr) = (yyvsp[(1) - (1)].expr);
    ;}
    break;

  case 28:
#line 345 "microex.y"
    {
        (yyval.expr) = (yyvsp[(2) - (3)].expr);
    ;}
    break;

  case 29:
#line 349 "microex.y"
    {
        (yyval.expr).type = (yyvsp[(2) - (2)].expr).type;
        char *temp_res_name = new_temp((yyval.expr).type);
        if ((yyval.expr).type == TYPE_INT) {
            printf("I_UMINUS %s,%s\n", (yyvsp[(2) - (2)].expr).place->name, temp_res_name);
        } else {
            printf("F_UMINUS %s,%s\n", (yyvsp[(2) - (2)].expr).place->name, temp_res_name);
        }
        (yyval.expr).place = symlook(temp_res_name);
        (yyval.expr).place->type = (yyval.expr).type;
    ;}
    break;

  case 30:
#line 361 "microex.y"
    {
        char temp_val[20];
        sprintf(temp_val, "%d", (yyvsp[(1) - (1)].ival));
        struct symtab *s = symlook(temp_val);
        s->type = TYPE_INT;
        s->is_declared = 1;
        (yyval.expr).place = s;
        (yyval.expr).type = TYPE_INT;
    ;}
    break;

  case 31:
#line 371 "microex.y"
    {
        char temp_val[30];
        sprintf(temp_val, "%f", (yyvsp[(1) - (1)].fval));
        struct symtab *s = symlook(temp_val);
        s->type = TYPE_FLOAT;
        s->is_declared = 1;
        (yyval.expr).place = s;
        (yyval.expr).type = TYPE_FLOAT;
    ;}
    break;

  case 32:
#line 381 "microex.y"
    {
        if (!(yyvsp[(1) - (1)].symp)->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' not declared.", (yyvsp[(1) - (1)].symp)->name);
            yyerror(err_msg);
        }
        if ((yyvsp[(1) - (1)].symp)->isArray) {
             char err_msg[100];
             sprintf(err_msg, "Array '%s' used without index.", (yyvsp[(1) - (1)].symp)->name);
             yyerror(err_msg);
        }
        (yyval.expr).place = (yyvsp[(1) - (1)].symp);
        (yyval.expr).type = (yyvsp[(1) - (1)].symp)->type;
    ;}
    break;

  case 33:
#line 396 "microex.y"
    {
        if (!(yyvsp[(1) - (4)].symp)->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Array '%s' not declared.", (yyvsp[(1) - (4)].symp)->name);
            yyerror(err_msg);
        }
        if (!(yyvsp[(1) - (4)].symp)->isArray) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' is not an array, cannot be indexed.", (yyvsp[(1) - (4)].symp)->name);
            yyerror(err_msg);
        }
        if ((yyvsp[(3) - (4)].expr).type != TYPE_INT) {
            yyerror("Array index must be an integer expression.");
        }

        char temp_operand_name[100];
        sprintf(temp_operand_name, "%s[%s]", (yyvsp[(1) - (4)].symp)->name, (yyvsp[(3) - (4)].expr).place->name);
        struct symtab *s = symlook(temp_operand_name);
        s->type = (yyvsp[(1) - (4)].symp)->type;
        s->is_declared = 1;
        (yyval.expr).place = s;
        (yyval.expr).type = (yyvsp[(1) - (4)].symp)->type;
    ;}
    break;

  case 34:
#line 423 "microex.y"
    {
        if_stack_ptr--;
        printf("label_%d:\n", if_stack[if_stack_ptr].begin_label);
    ;}
    break;

  case 35:
#line 428 "microex.y"
    {
        if_stack_ptr--;
        printf("label_%d:\n", if_stack[if_stack_ptr].end_label);
    ;}
    break;

  case 36:
#line 436 "microex.y"
    {
        if_stack[if_stack_ptr].begin_label = new_label();
        if_stack[if_stack_ptr].end_label = new_label();
        if_stack_ptr++;
    ;}
    break;

  case 37:
#line 442 "microex.y"
    {
        /* condition rule has already generated the jump to begin_label (else/endif) if false */
    ;}
    break;

  case 38:
#line 449 "microex.y"
    {
        printf("J label_%d\n", if_stack[if_stack_ptr-1].end_label);
        printf("label_%d:\n", if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 40:
#line 458 "microex.y"
    {
        char* step_val_str = for_stack[for_stack_ptr-1].step_expr;
        if (step_val_str == NULL) {
            if (for_stack[for_stack_ptr-1].is_downto) {
                printf("DEC %s\n", for_stack[for_stack_ptr-1].var_name);
            } else {
                printf("INC %s\n", for_stack[for_stack_ptr-1].var_name);
            }
        } else {
            if (for_stack[for_stack_ptr-1].is_downto) {
                printf("I_SUB %s,%s,%s\n", for_stack[for_stack_ptr-1].var_name, step_val_str, for_stack[for_stack_ptr-1].var_name);
            } else {
                printf("I_ADD %s,%s,%s\n", for_stack[for_stack_ptr-1].var_name, step_val_str, for_stack[for_stack_ptr-1].var_name);
            }
        }

        printf("I_CMP %s,%s\n", for_stack[for_stack_ptr-1].var_name,
                                        for_stack[for_stack_ptr-1].end_expr);
        if (for_stack[for_stack_ptr-1].is_downto) {
            printf("JGE label_%d\n", for_stack[for_stack_ptr-1].begin_label);
        } else {
            printf("JLE label_%d\n", for_stack[for_stack_ptr-1].begin_label);
        }
        printf("label_%d:\n", for_stack[for_stack_ptr-1].end_label);

        free(for_stack[for_stack_ptr-1].var_name);
        for_stack[for_stack_ptr-1].var_name = NULL;
        free(for_stack[for_stack_ptr-1].end_expr);
        for_stack[for_stack_ptr-1].end_expr = NULL;
        if (for_stack[for_stack_ptr-1].step_expr != NULL) {
            free(for_stack[for_stack_ptr-1].step_expr);
            for_stack[for_stack_ptr-1].step_expr = NULL;
        }
        for_stack_ptr--;
    ;}
    break;

  case 41:
#line 497 "microex.y"
    {
        (yyval.expr).place = NULL;
        (yyval.expr).type = TYPE_INT;
    ;}
    break;

  case 42:
#line 502 "microex.y"
    {
        if ((yyvsp[(2) - (2)].expr).type != TYPE_INT) {
            yyerror("FOR loop STEP expression must be integer.");
        }
        (yyval.expr) = (yyvsp[(2) - (2)].expr);
    ;}
    break;

  case 43:
#line 512 "microex.y"
    {
        if (!(yyvsp[(3) - (9)].symp)->is_declared) { char err_msg[100]; sprintf(err_msg, "Loop variable '%s' not declared.", (yyvsp[(3) - (9)].symp)->name); yyerror(err_msg); }
        if ((yyvsp[(3) - (9)].symp)->type != TYPE_INT && (yyvsp[(3) - (9)].symp)->type != -1) { yyerror("Loop variable must be an integer."); }
        if ((yyvsp[(5) - (9)].expr).type != TYPE_INT) { yyerror("FOR loop start expression must be integer.");}
        if ((yyvsp[(7) - (9)].expr).type != TYPE_INT) { yyerror("FOR loop end expression must be integer.");}
        (yyvsp[(3) - (9)].symp)->type = TYPE_INT;

        printf("I_Store %s,%s\n", (yyvsp[(5) - (9)].expr).place->name, (yyvsp[(3) - (9)].symp)->name);

        for_stack[for_stack_ptr].begin_label = new_label();
        for_stack[for_stack_ptr].end_label = new_label();
        for_stack[for_stack_ptr].var_name = strdup((yyvsp[(3) - (9)].symp)->name);
        for_stack[for_stack_ptr].end_expr = strdup((yyvsp[(7) - (9)].expr).place->name);
        if ((yyvsp[(8) - (9)].expr).place != NULL) { // $8 is optional_step
            for_stack[for_stack_ptr].step_expr = strdup((yyvsp[(8) - (9)].expr).place->name);
        } else {
            for_stack[for_stack_ptr].step_expr = NULL; // Explicitly mark no custom step
        }
        for_stack[for_stack_ptr].is_downto = 0;

        printf("label_%d:\n", for_stack[for_stack_ptr].begin_label);
        printf("I_CMP %s,%s\n", (yyvsp[(3) - (9)].symp)->name, for_stack[for_stack_ptr].end_expr);
        printf("JG label_%d\n", for_stack[for_stack_ptr].end_label);

        for_stack_ptr++;
    ;}
    break;

  case 44:
#line 539 "microex.y"
    {
        if (!(yyvsp[(3) - (9)].symp)->is_declared) { char err_msg[100]; sprintf(err_msg, "Loop variable '%s' not declared.", (yyvsp[(3) - (9)].symp)->name); yyerror(err_msg); }
        if ((yyvsp[(3) - (9)].symp)->type != TYPE_INT && (yyvsp[(3) - (9)].symp)->type != -1) { yyerror("Loop variable must be an integer."); }
        if ((yyvsp[(5) - (9)].expr).type != TYPE_INT) { yyerror("FOR loop start expression must be integer.");}
        if ((yyvsp[(7) - (9)].expr).type != TYPE_INT) { yyerror("FOR loop end expression must be integer.");}
        (yyvsp[(3) - (9)].symp)->type = TYPE_INT;

        printf("I_Store %s,%s\n", (yyvsp[(5) - (9)].expr).place->name, (yyvsp[(3) - (9)].symp)->name);

        for_stack[for_stack_ptr].begin_label = new_label();
        for_stack[for_stack_ptr].end_label = new_label();
        for_stack[for_stack_ptr].var_name = strdup((yyvsp[(3) - (9)].symp)->name);
        for_stack[for_stack_ptr].end_expr = strdup((yyvsp[(7) - (9)].expr).place->name);
        if ((yyvsp[(8) - (9)].expr).place != NULL) { // $8 is optional_step
            for_stack[for_stack_ptr].step_expr = strdup((yyvsp[(8) - (9)].expr).place->name);
        } else {
            for_stack[for_stack_ptr].step_expr = NULL;
        }
        for_stack[for_stack_ptr].is_downto = 1;

        printf("label_%d:\n", for_stack[for_stack_ptr].begin_label);
        printf("I_CMP %s,%s\n", (yyvsp[(3) - (9)].symp)->name, for_stack[for_stack_ptr].end_expr);
        printf("JL label_%d\n", for_stack[for_stack_ptr].end_label);

        for_stack_ptr++;
    ;}
    break;

  case 45:
#line 569 "microex.y"
    {
        printf("J label_%d\n", if_stack[if_stack_ptr-1].begin_label);
        printf("label_%d:\n", if_stack[if_stack_ptr-1].end_label);
        if_stack_ptr--;
    ;}
    break;

  case 46:
#line 578 "microex.y"
    {
        if_stack[if_stack_ptr].begin_label = new_label();
        if_stack[if_stack_ptr].end_label = new_label();
        if_stack_ptr++;
        printf("label_%d:\n", if_stack[if_stack_ptr-1].begin_label);
        in_while_loop = 1;
    ;}
    break;

  case 47:
#line 586 "microex.y"
    {
        in_while_loop = 0;
    ;}
    break;

  case 48:
#line 593 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JLE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 49:
#line 606 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JGE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 50:
#line 619 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JL label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 51:
#line 632 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JG label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 52:
#line 645 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JNE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 53:
#line 658 "microex.y"
    {
        char *op1_name = (yyvsp[(1) - (3)].expr).place->name;
        char *op2_name = (yyvsp[(3) - (3)].expr).place->name;
        if ((yyvsp[(1) - (3)].expr).type == TYPE_INT && (yyvsp[(3) - (3)].expr).type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ((yyvsp[(1) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ((yyvsp[(3) - (3)].expr).type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    ;}
    break;

  case 57:
#line 680 "microex.y"
    {
        printf("CALL print, %s\n", (yyvsp[(1) - (1)].expr).place->name);
    ;}
    break;

  case 58:
#line 684 "microex.y"
    {
        printf("CALL print, %s\n", (yyvsp[(3) - (3)].expr).place->name);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2186 "y.tab.c"
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
		      yytoken, &yylval);
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 689 "microex.y"


struct symtab *symlook(char *s) {
    for(int i = 0; i < symtab_count; i++) {
        if(strcmp(symtab[i].name, s) == 0) {
            return &symtab[i];
        }
    }

    if(symtab_count >= NSYMS) {
        fprintf(stderr, "Symbol table full, too many symbols (max %d)\n", NSYMS);
        exit(1);
    }

    symtab[symtab_count].name = strdup(s);
    symtab[symtab_count].is_declared = 0;
    symtab[symtab_count].isArray = 0;
    symtab[symtab_count].size = 0;
    symtab[symtab_count].type = -1;
    return &symtab[symtab_count++];
}

char *new_temp(int type) {
    char name_buf[20];
    sprintf(name_buf, "T&%d", ++temp_counter);
    struct symtab *s = symlook(name_buf);
    s->type = type;
    s->is_declared = 1;
    s->isArray = 0;
    s->size = 0;
    return s->name;
}

int new_label() {
    return ++label_counter;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}

int main(int argc, char* argv[]) {
    memset(symtab, 0, sizeof(symtab));
    symtab_count = 0;
    current_decl.count = 0;
    temp_counter = 0;
    label_counter = 0;
    if_stack_ptr = 0;
    for_stack_ptr = 0;
    program_name[0] = '\0';


    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    int result = yyparse();

    if(result == 0) {
        printf("HALT %s\n", program_name[0] == '\0' ? "DefaultProgram" : program_name);

        for(int i = 0; i < symtab_count; i++) { /* iterate all symbols to find temporaries */
            if (symtab[i].name[0] == 'T' && symtab[i].name[1] == '&') {
                 if (symtab[i].type != -1) {
                    printf("Declare %s, %s\n", symtab[i].name,
                        symtab[i].type == TYPE_INT ? "Integer" : "Float");
                 }
            }
        }
    } else {
        fprintf(stderr, "\nParsing failed.\n");
    }

    if (yyin != stdin && yyin != NULL) {
        fclose(yyin);
    }

    return result;
}


/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     IDENTIFIER = 258,
     HEX_CONSTANT = 259,
     OCT_CONSTANT = 260,
     DEC_CONSTANT = 261,
     FLT_CONSTANT = 262,
     STRING_LITERAL = 263,
     PTR_OP = 264,
     INC_OP = 265,
     DEC_OP = 266,
     LEFT_OP = 267,
     RIGHT_OP = 268,
     LE_OP = 269,
     GE_OP = 270,
     EQ_OP = 271,
     NE_OP = 272,
     ASSIGN_OP = 273,
     AND_OP = 274,
     OR_OP = 275,
     MUL_ASSIGN = 276,
     DIV_ASSIGN = 277,
     MOD_ASSIGN = 278,
     ADD_ASSIGN = 279,
     SUB_ASSIGN = 280,
     LEFT_ASSIGN = 281,
     RIGHT_ASSIGN = 282,
     AND_ASSIGN = 283,
     XOR_ASSIGN = 284,
     OR_ASSIGN = 285,
     TYPE_NAME = 286,
     SIZEOF = 287,
     TYPEDEF = 288,
     EXTERN = 289,
     STATIC = 290,
     AUTO = 291,
     REGISTER = 292,
     CHAR = 293,
     SHORT = 294,
     INT = 295,
     LONG = 296,
     SIGNED = 297,
     UNSIGNED = 298,
     FLOAT = 299,
     DOUBLE = 300,
     CONST = 301,
     VOLATILE = 302,
     VOID = 303,
     STRUCT = 304,
     UNION = 305,
     ENUM = 306,
     ELLIPSIS = 307,
     CASE = 308,
     DEFAULT = 309,
     IF = 310,
     ELSE = 311,
     SWITCH = 312,
     WHILE = 313,
     DO = 314,
     FOR = 315,
     GOTO = 316,
     CONTINUE = 317,
     BREAK = 318,
     RETURN = 319
   };
#endif
#define IDENTIFIER 258
#define HEX_CONSTANT 259
#define OCT_CONSTANT 260
#define DEC_CONSTANT 261
#define FLT_CONSTANT 262
#define STRING_LITERAL 263
#define PTR_OP 264
#define INC_OP 265
#define DEC_OP 266
#define LEFT_OP 267
#define RIGHT_OP 268
#define LE_OP 269
#define GE_OP 270
#define EQ_OP 271
#define NE_OP 272
#define ASSIGN_OP 273
#define AND_OP 274
#define OR_OP 275
#define MUL_ASSIGN 276
#define DIV_ASSIGN 277
#define MOD_ASSIGN 278
#define ADD_ASSIGN 279
#define SUB_ASSIGN 280
#define LEFT_ASSIGN 281
#define RIGHT_ASSIGN 282
#define AND_ASSIGN 283
#define XOR_ASSIGN 284
#define OR_ASSIGN 285
#define TYPE_NAME 286
#define SIZEOF 287
#define TYPEDEF 288
#define EXTERN 289
#define STATIC 290
#define AUTO 291
#define REGISTER 292
#define CHAR 293
#define SHORT 294
#define INT 295
#define LONG 296
#define SIGNED 297
#define UNSIGNED 298
#define FLOAT 299
#define DOUBLE 300
#define CONST 301
#define VOLATILE 302
#define VOID 303
#define STRUCT 304
#define UNION 305
#define ENUM 306
#define ELLIPSIS 307
#define CASE 308
#define DEFAULT 309
#define IF 310
#define ELSE 311
#define SWITCH 312
#define WHILE 313
#define DO 314
#define FOR 315
#define GOTO 316
#define CONTINUE 317
#define BREAK 318
#define RETURN 319




/* Copy the first part of user declarations.  */
#line 1 "zyacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1

#include "zsymtab.h"
#include "zutils.h"
#include "zemit.h"
#include "zpreproc.h"

/* identifier scope */
extern int g_scope_level;
extern PIDENT_t g_current_function;
extern PCR_t g_cr_block;
extern int max_pseudo_num;
extern FILELIST_t g_filelist[MAX_INCLUDES];
extern int inc_level;
extern int file_flag;
extern int g_errcount;


extern char yytext[];
extern int g_column;
extern int g_line;

extern int yylex();
void yyerror(char* s);
extern void print_cr_block(PCR_t block);
extern void print_function();



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 36 "zyacc.y"
typedef union YYSTYPE {
	TOKEN_t		token;
	PTYPE_t		ptype;
	PDATA_t		pdata;
	PIDENT_t	pident;
	PLIST_t		plist;
	PCR_t		pcr;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 247 "zparser.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 259 "zparser.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   857

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  60
/* YYNRULES -- Number of rules. */
#define YYNRULES  184
/* YYNRULES -- Number of states. */
#define YYNSTATES  299

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,     2,     2,    77,    72,     2,
      65,    66,    73,    78,    70,    71,    69,    76,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    86,    83,
      79,     2,    80,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    67,     2,    68,    81,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    82,    85,    74,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    19,
      21,    26,    30,    35,    39,    43,    46,    49,    51,    55,
      57,    60,    63,    66,    69,    72,    75,    78,    81,    86,
      91,    96,   101,   106,   108,   110,   114,   118,   122,   124,
     128,   132,   134,   138,   142,   144,   148,   152,   156,   160,
     162,   166,   170,   172,   176,   178,   182,   184,   188,   190,
     194,   196,   200,   202,   204,   208,   210,   212,   214,   216,
     218,   220,   222,   224,   226,   228,   230,   232,   236,   238,
     242,   244,   247,   249,   252,   254,   257,   259,   263,   265,
     269,   271,   273,   275,   277,   279,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   299,   305,   308,   310,   312,
     314,   317,   321,   324,   326,   329,   331,   333,   335,   340,
     346,   349,   351,   355,   357,   361,   363,   365,   368,   370,
     372,   377,   381,   386,   391,   395,   397,   400,   403,   405,
     407,   411,   414,   417,   419,   421,   425,   427,   429,   433,
     438,   440,   444,   446,   448,   450,   452,   454,   456,   461,
     465,   468,   472,   477,   479,   482,   484,   487,   489,   492,
     498,   506,   512,   518,   526,   534,   537,   540,   543,   547,
     549,   552,   554,   556,   560
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     144,     0,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,    65,   106,    66,    -1,    88,
      -1,    89,    67,   106,    68,    -1,    89,    65,    66,    -1,
      89,    65,    90,    66,    -1,    89,    69,     3,    -1,    89,
       9,     3,    -1,    89,    10,    -1,    89,    11,    -1,   104,
      -1,    90,    70,   104,    -1,    89,    -1,    10,    91,    -1,
      11,    91,    -1,    71,    92,    -1,    72,    92,    -1,    73,
      92,    -1,    74,    92,    -1,    75,    92,    -1,    32,    91,
      -1,    32,    65,    38,    66,    -1,    32,    65,    39,    66,
      -1,    32,    65,    40,    66,    -1,    32,    65,    41,    66,
      -1,    32,    65,    44,    66,    -1,    91,    -1,    92,    -1,
      93,    73,    92,    -1,    93,    76,    92,    -1,    93,    77,
      92,    -1,    93,    -1,    94,    78,    93,    -1,    94,    71,
      93,    -1,    94,    -1,    95,    12,    94,    -1,    95,    13,
      94,    -1,    95,    -1,    96,    79,    95,    -1,    96,    80,
      95,    -1,    96,    14,    95,    -1,    96,    15,    95,    -1,
      96,    -1,    97,    16,    96,    -1,    97,    17,    96,    -1,
      97,    -1,    98,    72,    97,    -1,    98,    -1,    99,    81,
      98,    -1,    99,    -1,   100,    82,    99,    -1,   100,    -1,
     101,    19,   100,    -1,   101,    -1,   102,    20,   101,    -1,
     102,    -1,   103,    -1,    91,   105,   104,    -1,    18,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,
     104,    -1,   106,    70,   104,    -1,   103,    -1,   109,   110,
      83,    -1,   112,    -1,   112,   109,    -1,   113,    -1,   113,
     109,    -1,   124,    -1,   124,   109,    -1,   111,    -1,   110,
      70,   111,    -1,   125,    -1,   125,    18,   133,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    48,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,    44,    -1,    45,
      -1,    42,    -1,    43,    -1,   114,    -1,   121,    -1,   115,
       3,    84,   116,    85,    -1,   115,     3,    -1,    49,    -1,
      50,    -1,   117,    -1,   116,   117,    -1,   118,   119,    83,
      -1,   113,   118,    -1,   113,    -1,   124,   118,    -1,   124,
      -1,   120,    -1,   125,    -1,    51,    84,   122,    85,    -1,
      51,     3,    84,   122,    85,    -1,    51,     3,    -1,   123,
      -1,   122,    70,   123,    -1,     3,    -1,     3,    18,   107,
      -1,    46,    -1,    47,    -1,   127,   126,    -1,   126,    -1,
       3,    -1,   126,    67,   107,    68,    -1,   126,    67,    68,
      -1,   126,    65,   128,    66,    -1,   126,    65,   131,    66,
      -1,   126,    65,    66,    -1,    73,    -1,    73,   124,    -1,
      73,   127,    -1,   129,    -1,   130,    -1,   129,    70,   130,
      -1,   109,   125,    -1,   109,   132,    -1,   109,    -1,     3,
      -1,   131,    70,     3,    -1,   127,    -1,   104,    -1,    84,
     134,    85,    -1,    84,   134,    70,    85,    -1,   133,    -1,
     134,    70,   133,    -1,   136,    -1,   137,    -1,   140,    -1,
     141,    -1,   142,    -1,   143,    -1,    53,   107,    86,   135,
      -1,    54,    86,   135,    -1,    84,    85,    -1,    84,   139,
      85,    -1,    84,   138,   139,    85,    -1,   108,    -1,   138,
     108,    -1,   135,    -1,   139,   135,    -1,    83,    -1,   106,
      83,    -1,    55,    65,   106,    66,   135,    -1,    55,    65,
     106,    66,   135,    56,   135,    -1,    57,    65,   106,    66,
     135,    -1,    58,    65,   106,    66,   135,    -1,    59,   135,
      58,    65,   106,    66,    83,    -1,    60,    65,   140,   140,
     106,    66,   135,    -1,    62,    83,    -1,    63,    83,    -1,
      64,    83,    -1,    64,   106,    83,    -1,   145,    -1,   144,
     145,    -1,   146,    -1,   108,    -1,   109,   125,   137,    -1,
     125,   137,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    81,    81,    95,    99,   103,   107,   111,   115,   119,
     123,   128,   133,   138,   139,   140,   145,   153,   154,   162,
     166,   171,   176,   178,   179,   180,   181,   182,   188,   189,
     190,   191,   192,   205,   213,   214,   215,   216,   220,   221,
     222,   226,   227,   228,   232,   233,   234,   235,   236,   240,
     241,   242,   246,   247,   251,   252,   256,   257,   261,   262,
     266,   267,   271,   276,   277,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   299,   303,   311,   316,
     367,   371,   376,   380,   385,   389,   397,   401,   409,   413,
     423,   424,   425,   426,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   445,   450,   462,   475,   476,   480,
     484,   492,   507,   513,   517,   522,   529,   537,   552,   553,
     554,   558,   559,   563,   564,   568,   569,   573,   578,   585,
     591,   602,   613,   623,   624,   632,   637,   641,   656,   661,
     662,   670,   679,   692,   704,   705,   714,   733,   734,   735,
     739,   740,   748,   752,   756,   760,   764,   768,   781,   788,
     795,   796,   798,   802,   803,   811,   816,   823,   824,   834,
     839,   844,   855,   865,   876,   890,   894,   898,   902,   914,
     915,   919,   939,   947,   962
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "HEX_CONSTANT", 
  "OCT_CONSTANT", "DEC_CONSTANT", "FLT_CONSTANT", "STRING_LITERAL", 
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", 
  "EQ_OP", "NE_OP", "ASSIGN_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", 
  "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", 
  "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME", 
  "SIZEOF", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR", 
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", 
  "CONST", "VOLATILE", "VOID", "STRUCT", "UNION", "ENUM", "ELLIPSIS", 
  "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", 
  "CONTINUE", "BREAK", "RETURN", "'('", "')'", "'['", "']'", "'.'", "','", 
  "'-'", "'&'", "'*'", "'~'", "'!'", "'/'", "'%'", "'+'", "'<'", "'>'", 
  "'^'", "'|'", "';'", "'{'", "'}'", "':'", "$accept", 
  "primary_expression", "postfix_expression", "argument_expression_list", 
  "unary_expression", "cast_expression", "multiplicative_expression", 
  "additive_expression", "shift_expression", "relational_expression", 
  "equality_expression", "and_expression", "exclusive_or_expression", 
  "inclusive_or_expression", "logical_and_expression", 
  "logical_or_expression", "conditional_expression", 
  "assignment_expression", "assignment_operator", "expression", 
  "constant_expression", "declaration", "declaration_specifiers", 
  "init_declarator_list", "init_declarator", "storage_class_specifier", 
  "type_specifier", "struct_or_union_specifier", "struct_or_union", 
  "struct_declaration_list", "struct_declaration", 
  "specifier_qualifier_list", "struct_declarator_list", 
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator", 
  "type_qualifier", "declarator", "direct_declarator", "pointer", 
  "parameter_type_list", "parameter_list", "parameter_declaration", 
  "identifier_list", "abstract_declarator", "initializer", 
  "initializer_list", "statement", "labeled_statement", 
  "compound_statement", "declaration_list", "statement_list", 
  "expression_statement", "selection_statement", "iteration_statement", 
  "jump_statement", "translation_unit", "external_declaration", 
  "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,    40,    41,    91,    93,    46,
      44,    45,    38,    42,   126,    33,    47,    37,    43,    60,
      62,    94,   124,    59,   123,   125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    87,    88,    88,    88,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    93,    93,    93,    93,    94,    94,
      94,    95,    95,    95,    96,    96,    96,    96,    96,    97,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   107,   108,
     109,   109,   109,   109,   109,   109,   110,   110,   111,   111,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   118,   118,   118,   118,   119,   120,   121,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   128,   129,
     129,   130,   130,   130,   131,   131,   132,   133,   133,   133,
     134,   134,   135,   135,   135,   135,   135,   135,   136,   136,
     137,   137,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   141,   142,   142,   142,   143,   143,   143,   143,   144,
     144,   145,   145,   146,   146
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       4,     3,     4,     3,     3,     2,     2,     1,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     4,
       4,     4,     4,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     2,     1,     2,     1,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     1,     4,     5,
       2,     1,     3,     1,     3,     1,     1,     2,     1,     1,
       4,     3,     4,     4,     3,     1,     2,     2,     1,     1,
       3,     2,     2,     1,     1,     3,     1,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     4,     3,
       2,     3,     4,     1,     2,     1,     2,     1,     2,     5,
       7,     5,     5,     7,     7,     2,     2,     2,     3,     1,
       2,     1,     1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,   129,    90,    91,    92,    93,    95,    96,    97,    98,
     101,   102,    99,   100,   125,   126,    94,   107,   108,     0,
     135,   182,     0,    80,    82,   103,     0,   104,    84,     0,
     128,     0,     0,   179,   181,   120,     0,   136,   137,     0,
      86,    88,    81,    83,   106,    85,     0,   184,     0,     0,
     127,     1,   180,     0,   123,     0,   121,     0,    79,     0,
     183,     0,     2,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,   160,     9,
      19,    33,    34,    38,    41,    44,    49,    52,    54,    56,
      58,    60,    62,    63,    76,     0,   163,     0,   165,   152,
     153,     0,     0,   154,   155,   156,   157,   144,   134,   143,
       0,   138,   139,     0,   131,    33,    78,     0,     0,     0,
       0,   118,    87,    88,     0,   147,    89,   113,     0,   109,
       0,   115,    20,    21,     0,    27,     0,     0,     0,     0,
       0,     0,     0,   175,   176,   177,     0,     0,    22,    23,
      24,    25,    26,     0,    15,    16,     0,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   164,     0,   161,   166,   141,   146,   142,   132,     0,
     133,     0,   130,   119,   124,   122,   150,     0,   112,   105,
     110,     0,   116,   117,   114,     0,     0,     0,     0,     0,
       0,   159,     0,     0,     0,     0,     0,   178,     8,    14,
      11,     0,    17,     0,    13,    64,    35,    36,    37,    40,
      39,    42,    43,    47,    48,    45,    46,    50,    51,    53,
      55,    57,    59,    61,    77,   162,   140,   145,     0,   148,
     111,    28,    29,    30,    31,    32,   158,     0,     0,     0,
       0,     0,    12,     0,    10,   149,   151,   169,   171,   172,
       0,     0,    18,     0,     0,     0,   170,   173,   174
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    89,    90,   241,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   180,   105,
     127,    21,    22,    39,    40,    23,    24,    25,    26,   138,
     139,   140,   221,   222,    27,    55,    56,    28,    29,    30,
      31,   120,   121,   122,   123,   207,   136,   217,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    32,    33,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -141
static const short yypact[] =
{
     784,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,    15,
      21,  -141,    19,   401,   401,  -141,    27,  -141,   401,   -48,
       6,    67,   624,  -141,  -141,    -8,    92,  -141,  -141,   -44,
    -141,     3,  -141,  -141,    52,  -141,   222,  -141,   285,    78,
       6,  -141,  -141,    92,    83,   -47,  -141,    19,  -141,   518,
    -141,   590,  -141,  -141,  -141,  -141,  -141,  -141,   718,   718,
     741,   718,    25,    80,    89,   125,   504,   127,   133,   134,
     538,   718,   718,   718,   718,   718,   718,  -141,  -141,  -141,
     124,   818,  -141,   -42,    -9,   135,    51,   165,   103,   138,
     139,   203,   211,  -141,  -141,   -30,  -141,    19,  -141,  -141,
    -141,   422,   305,  -141,  -141,  -141,  -141,  -141,  -141,    19,
     157,   164,  -141,   -15,  -141,  -141,  -141,   167,   -38,   718,
      92,  -141,  -141,   232,   518,  -141,  -141,   590,   198,  -141,
      19,   590,  -141,  -141,   695,  -141,   166,   504,   718,   718,
     718,   193,   612,  -141,  -141,  -141,   -20,    32,  -141,  -141,
    -141,  -141,  -141,   250,  -141,  -141,   644,   718,   256,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
     718,   718,   718,   718,   718,   718,   718,   718,   718,   718,
     718,   718,   718,   718,   718,   718,   718,   718,   718,   718,
    -141,  -141,   339,  -141,  -141,  -141,    67,  -141,  -141,   401,
    -141,   271,  -141,  -141,  -141,  -141,  -141,   -37,  -141,  -141,
    -141,   195,  -141,  -141,  -141,   223,   224,   225,   226,   233,
     504,  -141,    62,    71,    72,   235,   612,  -141,  -141,  -141,
    -141,   108,  -141,   -14,  -141,  -141,  -141,  -141,  -141,   -42,
     -42,    -9,    -9,   135,   135,   135,   135,    51,    51,   165,
     103,   138,   139,   203,  -141,  -141,  -141,  -141,   112,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,   504,   504,   504,
     718,   718,  -141,   718,  -141,  -141,  -141,   242,  -141,  -141,
     110,   128,  -141,   504,   218,   504,  -141,  -141,  -141
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -141,  -141,  -141,  -141,   -25,   -69,    16,    26,    17,    22,
     109,   107,   118,   120,   106,  -141,   -29,   -59,  -141,   -70,
     -52,   -18,   -21,  -141,   265,  -141,   -32,  -141,  -141,  -141,
     200,    58,  -141,  -141,  -141,   286,   210,   -12,   -16,   -27,
     -11,  -141,  -141,   132,  -141,  -141,  -129,  -141,   -75,  -141,
      23,  -141,   237,  -140,  -141,  -141,  -141,  -141,   320,  -141
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
     135,   151,    42,    43,    50,   216,    41,    45,    37,    38,
     156,   157,   236,   158,   159,   160,   161,   162,    35,   146,
     126,    59,     1,   130,   125,   107,    57,   119,   106,   137,
      44,   181,   130,   268,   182,   183,    46,   204,   131,    58,
     199,   133,   126,   142,   143,   145,   125,   213,   269,   141,
     199,   210,    47,   200,   284,   211,   199,   125,   125,   125,
     125,   125,   184,   237,    60,   188,   189,    14,    15,   185,
       1,    48,   231,    49,   157,   135,    53,   214,   232,   233,
     234,    62,    63,    64,    65,    66,    67,    46,    68,    69,
     107,   133,    20,   201,    20,    54,   281,   243,   238,    36,
     126,   129,   199,   205,   125,   137,   137,   242,   206,   137,
      70,   147,   246,   247,   248,    62,    63,    64,    65,    66,
      67,   245,    68,    69,   223,   141,   141,   204,   277,   141,
     190,   191,   199,   163,   164,   165,    61,   278,   279,   286,
     264,   199,   199,    81,    70,   148,   124,   186,   187,    82,
      83,    84,    85,    86,   149,   276,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   282,   194,   294,    81,   283,    50,
     199,   192,   193,    82,    83,    84,    85,    86,   119,   166,
     150,   167,   152,   168,   295,   218,   134,   285,   199,   224,
     249,   250,   287,   288,   289,   253,   254,   255,   256,   135,
     290,   291,   251,   252,   257,   258,   153,   154,   296,   195,
     298,   196,   197,   208,   292,    62,    63,    64,    65,    66,
      67,   198,    68,    69,   209,   212,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      59,   235,   230,   239,    70,     2,     3,     4,     5,   244,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,   267,    71,    72,    73,   270,    74,
      75,    76,    77,   219,    78,    79,    80,    81,   117,   271,
     272,   273,   274,    82,    83,    84,    85,    86,   293,   275,
     280,   297,   260,   259,   263,    87,    46,    88,    62,    63,
      64,    65,    66,    67,   261,    68,    69,   262,     2,     3,
       4,     5,   132,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    70,   220,   128,
     215,   266,    62,    63,    64,    65,    66,    67,   202,    68,
      69,   118,    52,     0,     0,     0,     0,     0,    71,    72,
      73,     0,    74,    75,    76,    77,     0,    78,    79,    80,
      81,    70,     0,     0,     0,     0,    82,    83,    84,    85,
      86,     0,     0,     0,     0,     0,     0,     0,    87,    46,
     203,     0,    71,    72,    73,     0,    74,    75,    76,    77,
       0,    78,    79,    80,    81,     0,     0,     0,     0,     0,
      82,    83,    84,    85,    86,     0,     0,     0,     0,     0,
       0,     0,    87,    46,   265,    62,    63,    64,    65,    66,
      67,     0,    68,    69,     2,     3,     4,     5,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    70,     2,     3,     4,     5,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    71,    72,    73,     0,    74,
      75,    76,    77,     0,    78,    79,    80,    81,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    86,     0,     0,
       0,     0,     0,     0,     0,    87,    46,    62,    63,    64,
      65,    66,    67,     0,    68,    69,     0,     0,     0,     0,
       0,    62,    63,    64,    65,    66,    67,     0,    68,    69,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,     0,     0,     0,     0,     0,    71,    72,    73,
       0,    74,    75,    76,    77,     0,    78,    79,    80,    81,
      70,     0,     0,     0,     0,    82,    83,    84,    85,    86,
       0,     0,     0,    81,     0,     0,     0,    87,    46,    82,
      83,    84,    85,    86,     0,     0,     0,     0,     0,     0,
       0,     0,   134,    81,     0,     0,     0,     0,     0,    82,
      83,    84,    85,    86,     0,    62,    63,    64,    65,    66,
      67,   155,    68,    69,    51,     0,     0,     1,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,    70,     0,     0,    62,    63,    64,
      65,    66,    67,     0,    68,    69,     0,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    70,    81,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    86,     0,     0,
       0,     0,     0,     0,     0,    87,     0,    20,    62,    63,
      64,    65,    66,    67,     0,    68,    69,     0,     0,    81,
     240,     0,     0,     0,     0,    82,    83,    84,    85,    86,
       0,    62,    63,    64,    65,    66,    67,    70,    68,    69,
       0,     0,     0,   225,   226,   227,   228,     0,     0,   229,
       0,     0,     0,     0,    62,    63,    64,    65,    66,    67,
      70,    68,    69,     0,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,    82,    83,    84,    85,
      86,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,     0,     0,     0,     1,     0,    82,
      83,    84,    85,    86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   144,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   169,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,    20
};

static const short yycheck[] =
{
      59,    76,    23,    24,    31,   134,    22,    28,    20,    20,
      80,    81,   152,    82,    83,    84,    85,    86,     3,    71,
      49,    18,     3,    70,    49,    46,    70,    48,    46,    61,
       3,    73,    70,    70,    76,    77,    84,   112,    85,    83,
      70,    57,    71,    68,    69,    70,    71,    85,    85,    61,
      70,    66,    29,    83,    68,    70,    70,    82,    83,    84,
      85,    86,    71,    83,    41,    14,    15,    46,    47,    78,
       3,    65,   147,    67,   144,   134,    84,   129,   148,   149,
     150,     3,     4,     5,     6,     7,     8,    84,    10,    11,
     111,   107,    73,   111,    73,     3,   236,   167,    66,    84,
     129,    18,    70,   119,   129,   137,   138,   166,   119,   141,
      32,    86,   181,   182,   183,     3,     4,     5,     6,     7,
       8,   180,    10,    11,   140,   137,   138,   202,    66,   141,
      79,    80,    70,     9,    10,    11,    84,    66,    66,   268,
     199,    70,    70,    65,    32,    65,    68,    12,    13,    71,
      72,    73,    74,    75,    65,   230,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,    66,    72,    66,    65,    70,   206,
      70,    16,    17,    71,    72,    73,    74,    75,   209,    65,
      65,    67,    65,    69,    66,   137,    84,    85,    70,   141,
     184,   185,   277,   278,   279,   188,   189,   190,   191,   268,
     280,   281,   186,   187,   192,   193,    83,    83,   293,    81,
     295,    82,    19,    66,   283,     3,     4,     5,     6,     7,
       8,    20,    10,    11,    70,    68,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      18,    58,    86,     3,    32,    33,    34,    35,    36,     3,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,     3,    53,    54,    55,    83,    57,
      58,    59,    60,    85,    62,    63,    64,    65,     3,    66,
      66,    66,    66,    71,    72,    73,    74,    75,    56,    66,
      65,    83,   195,   194,   198,    83,    84,    85,     3,     4,
       5,     6,     7,     8,   196,    10,    11,   197,    33,    34,
      35,    36,    57,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    32,   138,    53,
     130,   209,     3,     4,     5,     6,     7,     8,   111,    10,
      11,    66,    32,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    32,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    -1,    53,    54,    55,    -1,    57,    58,    59,    60,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    85,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    33,    34,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    84,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    65,
      32,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    83,    84,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    65,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    -1,     3,     4,     5,     6,     7,
       8,    83,    10,    11,     0,    -1,    -1,     3,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    32,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    32,    65,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    -1,    73,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    65,
      66,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      -1,     3,     4,     5,     6,     7,     8,    32,    10,    11,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    -1,    44,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      32,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,     3,    -1,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,    33,    34,    35,    36,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      73,   108,   109,   112,   113,   114,   115,   121,   124,   125,
     126,   127,   144,   145,   146,     3,    84,   124,   127,   110,
     111,   125,   109,   109,     3,   109,    84,   137,    65,    67,
     126,     0,   145,    84,     3,   122,   123,    70,    83,    18,
     137,    84,     3,     4,     5,     6,     7,     8,    10,    11,
      32,    53,    54,    55,    57,    58,    59,    60,    62,    63,
      64,    65,    71,    72,    73,    74,    75,    83,    85,    88,
      89,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   106,   108,   109,   135,   136,
     137,   138,   139,   140,   141,   142,   143,     3,    66,   109,
     128,   129,   130,   131,    68,    91,   103,   107,   122,    18,
      70,    85,   111,   125,    84,   104,   133,   113,   116,   117,
     118,   124,    91,    91,    65,    91,   107,    86,    65,    65,
      65,   135,    65,    83,    83,    83,   106,   106,    92,    92,
      92,    92,    92,     9,    10,    11,    65,    67,    69,    18,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     105,    73,    76,    77,    71,    78,    12,    13,    14,    15,
      79,    80,    16,    17,    72,    81,    82,    19,    20,    70,
      83,   108,   139,    85,   135,   125,   127,   132,    66,    70,
      66,    70,    68,    85,   107,   123,   133,   134,   118,    85,
     117,   119,   120,   125,   118,    38,    39,    40,    41,    44,
      86,   135,   106,   106,   106,    58,   140,    83,    66,     3,
      66,    90,   104,   106,     3,   104,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    95,    96,    96,    97,
      98,    99,   100,   101,   104,    85,   130,     3,    70,    85,
      83,    66,    66,    66,    66,    66,   135,    66,    66,    66,
      65,   140,    66,    70,    68,    85,   133,   135,   135,   135,
     106,   106,   104,    56,    66,    66,   135,    83,   135
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 2:
#line 82 "zyacc.y"
    {
			PIDENT_t psym;

			psym = get_symbol(yyvsp[0].token.data);
			if(!psym)
			{
				psym = getparam(g_current_function, yyvsp[0].token.data);
				if(!psym)
					yyerror("undeclared identifier");
			}
			
			yyval.plist = new_node(IDENTIFIER_TYPE, psym);
		}
    break;

  case 3:
#line 96 "zyacc.y"
    {
			yyval.plist = new_node(CONSTANT_TYPE, yyvsp[0].pdata);
		}
    break;

  case 4:
#line 100 "zyacc.y"
    {
			yyval.plist = new_node(CONSTANT_TYPE, yyvsp[0].pdata);
		}
    break;

  case 5:
#line 104 "zyacc.y"
    {
			yyval.plist = new_node(CONSTANT_TYPE, yyvsp[0].pdata);
		}
    break;

  case 6:
#line 108 "zyacc.y"
    {
			yyval.plist = new_node(CONSTANT_TYPE, yyvsp[0].pdata);
		}
    break;

  case 7:
#line 112 "zyacc.y"
    {
			yyval.plist = new_node(STRING_TYPE, yyvsp[0].pdata);
		}
    break;

  case 8:
#line 115 "zyacc.y"
    { yyval.plist = yyvsp[-1].plist; }
    break;

  case 9:
#line 120 "zyacc.y"
    {
			yyval.plist = yyvsp[0].plist;
		}
    break;

  case 10:
#line 124 "zyacc.y"
    {
			yyval.plist = emit_arrayaccess(yyvsp[-3].plist,yyvsp[-1].plist);
			g_cr_block = 0;
		}
    break;

  case 11:
#line 129 "zyacc.y"
    {
			yyval.plist = emit_functioncall(yyvsp[-2].plist,0);
			g_cr_block = 0;
		}
    break;

  case 12:
#line 134 "zyacc.y"
    {
			yyval.plist = emit_functioncall(yyvsp[-3].plist,yyvsp[-1].plist);
			g_cr_block = 0;
		}
    break;

  case 15:
#line 141 "zyacc.y"
    {
			yyval.plist = emit_post(yyvsp[-1].plist,1);
			g_cr_block = 0;
		}
    break;

  case 16:
#line 146 "zyacc.y"
    {
			yyval.plist = emit_post(yyvsp[-1].plist,0);
			g_cr_block = 0;
		}
    break;

  case 17:
#line 153 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 18:
#line 155 "zyacc.y"
    {
			add_node(yyvsp[0].plist,yyvsp[-2].plist);
			yyval.plist = yyvsp[0].plist;
		}
    break;

  case 19:
#line 163 "zyacc.y"
    {
			yyval.plist = yyvsp[0].plist;
		}
    break;

  case 20:
#line 167 "zyacc.y"
    {
			yyval.plist = emit_pre(yyvsp[0].plist,1);
			g_cr_block = 0;
		}
    break;

  case 21:
#line 172 "zyacc.y"
    {
			yyval.plist = emit_pre(yyvsp[0].plist,0);
			g_cr_block = 0;
		}
    break;

  case 22:
#line 176 "zyacc.y"
    {yyval.plist = emit_negate(yyvsp[0].plist); g_cr_block = 0;}
    break;

  case 23:
#line 178 "zyacc.y"
    { yyval.plist = emit_addressaccess(yyvsp[0].plist); g_cr_block = 0; }
    break;

  case 24:
#line 179 "zyacc.y"
    { yyval.plist = emit_pointeraccess(yyvsp[0].plist); g_cr_block = 0; }
    break;

  case 25:
#line 180 "zyacc.y"
    { yyval.plist = emit_complement(yyvsp[0].plist); g_cr_block = 0; }
    break;

  case 26:
#line 181 "zyacc.y"
    { yyval.plist = emit_not(yyvsp[0].plist); g_cr_block =0; }
    break;

  case 27:
#line 183 "zyacc.y"
    {
			PDATA_t data;
			data = new_data(INT_t, typesize(yyvsp[0].plist) );
			yyval.plist = new_node(CONSTANT_TYPE, data);
		}
    break;

  case 28:
#line 188 "zyacc.y"
    { yyval.plist = new_node(CONSTANT_TYPE, new_data(INT_t, 1)); }
    break;

  case 29:
#line 189 "zyacc.y"
    { yyval.plist = new_node(CONSTANT_TYPE, new_data(INT_t, 2)); }
    break;

  case 30:
#line 190 "zyacc.y"
    { yyval.plist = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
    break;

  case 31:
#line 191 "zyacc.y"
    { yyval.plist = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
    break;

  case 32:
#line 192 "zyacc.y"
    { yyval.plist = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
    break;

  case 33:
#line 206 "zyacc.y"
    {
			yyval.plist = yyvsp[0].plist;
		}
    break;

  case 34:
#line 213 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 35:
#line 214 "zyacc.y"
    { yyval.plist = emit_multiply(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0;}
    break;

  case 36:
#line 215 "zyacc.y"
    { yyval.plist = emit_divide(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0;}
    break;

  case 37:
#line 216 "zyacc.y"
    { yyval.plist = emit_modulus(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0;}
    break;

  case 38:
#line 220 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 39:
#line 221 "zyacc.y"
    { yyval.plist = emit_add(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0;}
    break;

  case 40:
#line 222 "zyacc.y"
    { yyval.plist = emit_sub(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0;}
    break;

  case 41:
#line 226 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 42:
#line 227 "zyacc.y"
    { yyval.plist = emit_leftshift(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 43:
#line 228 "zyacc.y"
    { yyval.plist = emit_rightshift(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 44:
#line 232 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 45:
#line 233 "zyacc.y"
    { yyval.plist = emit_lessthan(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 46:
#line 234 "zyacc.y"
    { yyval.plist = emit_greaterthan(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 47:
#line 235 "zyacc.y"
    { yyval.plist = emit_lessthanequal(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 48:
#line 236 "zyacc.y"
    { yyval.plist = emit_greaterthanequal(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 49:
#line 240 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 50:
#line 241 "zyacc.y"
    { yyval.plist = emit_equal(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 51:
#line 242 "zyacc.y"
    { yyval.plist = emit_notequal(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 52:
#line 246 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 53:
#line 247 "zyacc.y"
    { yyval.plist = emit_logicaland(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 54:
#line 251 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 55:
#line 252 "zyacc.y"
    { yyval.plist = emit_logicalxor(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 56:
#line 256 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 57:
#line 257 "zyacc.y"
    { yyval.plist = emit_logicalor(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 58:
#line 261 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 59:
#line 262 "zyacc.y"
    { yyval.plist = emit_reland(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 60:
#line 266 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 61:
#line 267 "zyacc.y"
    { yyval.plist = emit_relor(yyvsp[-2].plist, yyvsp[0].plist); g_cr_block=0; }
    break;

  case 62:
#line 271 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 63:
#line 276 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 64:
#line 278 "zyacc.y"
    {
			yyval.plist = emit_assign(yyvsp[-2].plist, yyvsp[-1].token.token, yyvsp[0].plist);
			g_cr_block=0;
		}
    break;

  case 65:
#line 285 "zyacc.y"
    {yyval.token.token = ASSIGN_OP;}
    break;

  case 66:
#line 286 "zyacc.y"
    {yyval.token.token = MUL_ASSIGN;}
    break;

  case 67:
#line 287 "zyacc.y"
    {yyval.token.token = DIV_ASSIGN;}
    break;

  case 68:
#line 288 "zyacc.y"
    {yyval.token.token = MOD_ASSIGN;}
    break;

  case 69:
#line 289 "zyacc.y"
    {yyval.token.token = ADD_ASSIGN;}
    break;

  case 70:
#line 290 "zyacc.y"
    {yyval.token.token = SUB_ASSIGN;}
    break;

  case 71:
#line 291 "zyacc.y"
    {yyval.token.token = LEFT_ASSIGN;}
    break;

  case 72:
#line 292 "zyacc.y"
    {yyval.token.token = RIGHT_ASSIGN;}
    break;

  case 73:
#line 293 "zyacc.y"
    {yyval.token.token = AND_ASSIGN;}
    break;

  case 74:
#line 294 "zyacc.y"
    {yyval.token.token = XOR_ASSIGN;}
    break;

  case 75:
#line 295 "zyacc.y"
    {yyval.token.token = OR_ASSIGN;}
    break;

  case 76:
#line 300 "zyacc.y"
    {
			yyval.plist = emit_lineno(yyvsp[0].plist);  g_cr_block=0;
		}
    break;

  case 77:
#line 304 "zyacc.y"
    { 
			add_node(yyvsp[-2].plist,yyvsp[0].plist);
			yyval.plist = yyvsp[-2].plist; 
		}
    break;

  case 78:
#line 311 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 79:
#line 317 "zyacc.y"
    {
			PIDENT_t psym,ptemp;
			PLIST_t symlist=NULL;

			psym = yyvsp[-1].pident;
			if(IDENT_TYPE(yyvsp[-1].pident) == VARIABLE_t)
			{
				while(psym)
				{
					ptemp = psym->parg_list;
					psym->parg_list = NULL;
					/* pointers followed by base type */
					if(IDENT_VARTYPE(psym))
						add_subtype(IDENT_VARTYPE(psym), yyvsp[-2].ptype);
					else
						IDENT_VARTYPE(psym) = yyvsp[-2].ptype;
					add_symbol(psym);
					/* define_symbol(psym); */
					if(symlist==NULL)
						symlist = new_node(SYMBOL_TYPE, psym);
					else
						add_node(symlist, new_node(SYMBOL_TYPE,psym));
					psym = ptemp;
				}
			}
			else if(IDENT_TYPE(yyvsp[-1].pident) == ARRAY_t)
			{
				IDENT_VARTYPE(psym) = yyvsp[-2].ptype;
				/* base type followed by size */
				add_subtype(IDENT_VARTYPE(psym), IDENT_VARTYPE((psym->parg_list)));
				psym->parg_list = NULL;
				add_symbol(psym);
				symlist = new_node(SYMBOL_TYPE, psym);
			}
			else
			{
				/* pointers followed by base type */
				if(IDENT_VARTYPE(psym))
					add_subtype(IDENT_VARTYPE(psym), yyvsp[-2].ptype);
				else
					IDENT_VARTYPE(psym) = yyvsp[-2].ptype;
				add_symbol(psym);
				/* define_symbol(psym) */
				symlist = new_node(SYMBOL_TYPE, psym);
			}
			yyval.plist = symlist;
		}
    break;

  case 80:
#line 368 "zyacc.y"
    {
			yyval.ptype = new_type(0,0,0,0,yyvsp[0].token.token);
		}
    break;

  case 81:
#line 372 "zyacc.y"
    {
			yyvsp[0].ptype->specifier = yyvsp[-1].token.token;
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 82:
#line 377 "zyacc.y"
    {
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 83:
#line 381 "zyacc.y"
    {
			yyvsp[-1].ptype->type = yyvsp[0].ptype->type;
			yyval.ptype = yyvsp[-1].ptype;
		}
    break;

  case 84:
#line 386 "zyacc.y"
    {
			yyval.ptype = new_type(0,0,yyvsp[0].token.token,0,0);
		}
    break;

  case 85:
#line 390 "zyacc.y"
    {
			yyvsp[0].ptype->qualifier = yyvsp[-1].token.token;
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 86:
#line 398 "zyacc.y"
    {
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 87:
#line 402 "zyacc.y"
    {
			add_argument(yyvsp[-2].pident,yyvsp[0].pident);
			yyval.pident = yyvsp[-2].pident;
		}
    break;

  case 88:
#line 410 "zyacc.y"
    {
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 89:
#line 414 "zyacc.y"
    {
			/*typecheck($1, $3);*/
			yyvsp[-2].pident->pinitlist = yyvsp[0].plist;
			yyval.pident = yyvsp[-2].pident;
			/*printf("\n**%d", DATA_INT((PDATA_t)($3->node_ptr)));*/
		}
    break;

  case 90:
#line 423 "zyacc.y"
    { yyval.token.token = (TYPE_e)TYPEDEF_t; }
    break;

  case 91:
#line 424 "zyacc.y"
    { yyval.token.token = (TYPE_e)EXTERN_t; }
    break;

  case 92:
#line 425 "zyacc.y"
    { yyval.token.token = (TYPE_e)STATIC_t; }
    break;

  case 93:
#line 426 "zyacc.y"
    { yyval.token.token = (TYPE_e)AUTO_t; }
    break;

  case 94:
#line 431 "zyacc.y"
    { yyval.ptype = new_type(VOID_t,0,0,0,0); }
    break;

  case 95:
#line 432 "zyacc.y"
    { yyval.ptype = new_type(CHAR_t,SIGNED_t,0,0,0); }
    break;

  case 96:
#line 433 "zyacc.y"
    { yyval.ptype = new_type(SHORT_t,SIGNED_t,0,0,0);}
    break;

  case 97:
#line 434 "zyacc.y"
    { yyval.ptype = new_type(INT_t,SIGNED_t,0,0,0);}
    break;

  case 98:
#line 435 "zyacc.y"
    { yyval.ptype = new_type(LONG_t,SIGNED_t,0,0,0);}
    break;

  case 99:
#line 436 "zyacc.y"
    { yyval.ptype = new_type(FLOAT_t,SIGNED_t,0,0,0);}
    break;

  case 100:
#line 437 "zyacc.y"
    { yyval.ptype = new_type(DOUBLE_t,SIGNED_t,0,0,0);}
    break;

  case 101:
#line 438 "zyacc.y"
    { yyval.ptype = new_type(INT_t,SIGNED_t,0,0,0);}
    break;

  case 102:
#line 439 "zyacc.y"
    { yyval.ptype = new_type(INT_t,UNSIGNED_t,0,0,0);}
    break;

  case 103:
#line 441 "zyacc.y"
    { 
			yyval.ptype = new_type(STRUCT_t,0,0,0,0);
			yyval.ptype->u.ptag = yyvsp[0].pident;
		}
    break;

  case 104:
#line 445 "zyacc.y"
    { yyval.ptype = NULL; }
    break;

  case 105:
#line 451 "zyacc.y"
    {
			PIDENT_t psym;

			psym = new_ident(yyvsp[-3].token.data);
			IDENT_TYPE(psym) = STRUCT_t;
			IDENT_ARGLST(psym) = yyvsp[-1].pident;
			add_symbol(psym); /* new symbol */

			yyval.pident = psym;
		}
    break;

  case 106:
#line 463 "zyacc.y"
    {
			PIDENT_t psym;

			psym = get_symbol(yyvsp[0].token.data);
			if(!psym)
				yyerror("undeclared identifier");
			else
				yyval.pident = psym;
		}
    break;

  case 107:
#line 475 "zyacc.y"
    { yyval.token.token = (TYPE_e)STRUCT_t; }
    break;

  case 108:
#line 476 "zyacc.y"
    { yyval.token.token = (TYPE_e)UNION_t; }
    break;

  case 109:
#line 481 "zyacc.y"
    {
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 110:
#line 485 "zyacc.y"
    {
			add_argument(yyvsp[-1].pident,yyvsp[0].pident);
			yyval.pident = yyvsp[-1].pident;
		}
    break;

  case 111:
#line 493 "zyacc.y"
    {
			if(IDENT_VARTYPE(yyvsp[-1].pident))
			{
				add_subtype(IDENT_VARTYPE(yyvsp[-1].pident),yyvsp[-2].ptype);
				add_subtype(IDENT_VARTYPE(yyvsp[-1].pident), IDENT_VARTYPE((yyvsp[-1].pident->parg_list)));
				yyvsp[-1].pident->parg_list = NULL;
			}
			else
				IDENT_VARTYPE(yyvsp[-1].pident) = yyvsp[-2].ptype;
			yyval.pident = yyvsp[-1].pident;
		}
    break;

  case 112:
#line 508 "zyacc.y"
    {
			yyvsp[-1].ptype->type = yyvsp[0].ptype->type;
			yyvsp[-1].ptype->specifier = yyvsp[0].ptype->specifier;
			yyval.ptype = yyvsp[-1].ptype;
		}
    break;

  case 113:
#line 514 "zyacc.y"
    {
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 114:
#line 518 "zyacc.y"
    {
			yyvsp[0].ptype->qualifier = yyvsp[-1].token.token;
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 115:
#line 523 "zyacc.y"
    {
			yyval.ptype = new_type(0,0,yyvsp[0].token.token,0,0);
		}
    break;

  case 116:
#line 530 "zyacc.y"
    {
			yyval.pident = yyvsp[0].pident;			
		}
    break;

  case 117:
#line 538 "zyacc.y"
    {
			if(IDENT_TYPE(yyvsp[0].pident) == ARRAY_t)
			{
				/* base type followed by size */
				IDENT_VARTYPE(yyvsp[0].pident) = new_type(ARRAY_t,0,0,0,0);
			}
			IDENT_TYPE(yyvsp[0].pident) = MEMBER_t;
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 125:
#line 568 "zyacc.y"
    {yyval.token.token = (TYPE_e)CONST_t;}
    break;

  case 126:
#line 569 "zyacc.y"
    {yyval.token.token = (TYPE_e)VOLATILE_t;}
    break;

  case 127:
#line 574 "zyacc.y"
    {
			IDENT_VARTYPE(yyvsp[0].pident) = yyvsp[-1].ptype;
			yyval.pident = yyvsp[0].pident;			
		}
    break;

  case 128:
#line 579 "zyacc.y"
    {
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 129:
#line 586 "zyacc.y"
    {
			yyval.pident = new_ident(yyvsp[0].token.data);
			IDENT_TYPE(yyval.pident) = VARIABLE_t;
		}
    break;

  case 130:
#line 592 "zyacc.y"
    {
			PIDENT_t arrsize;
			
			IDENT_TYPE(yyvsp[-3].pident) = ARRAY_t;
			arrsize = new_ident("~arrsize");
			ident_addstuff(arrsize, INT_t, new_type(INT_t,0,0,0,0),NULL);
			arrsize->pvar_type->size = DATA_INT(NODE_DATA(yyvsp[-1].plist));
			add_argument(yyvsp[-3].pident,arrsize);
			yyval.pident = yyvsp[-3].pident;
		}
    break;

  case 131:
#line 603 "zyacc.y"
    {
			PIDENT_t arrsize;
			
			IDENT_TYPE(yyvsp[-2].pident) = ARRAY_t;
			arrsize = new_ident("~arrsize");
			ident_addstuff(arrsize, INT_t, new_type(INT_t,0,0,0,0),NULL);
			arrsize->pvar_type->size = 0;
			add_argument(yyvsp[-2].pident,arrsize);
			yyval.pident = yyvsp[-2].pident;
		}
    break;

  case 132:
#line 614 "zyacc.y"
    {
			IDENT_TYPE(yyvsp[-3].pident) = FUNCTION_t;
			IDENT_ARGLST(yyvsp[-3].pident) = yyvsp[-1].pident;
			yyval.pident = yyvsp[-3].pident;
			//print_symbol($1);
			g_current_function = yyvsp[-3].pident;
			/* update stack position for return val */
			g_current_function->stackpos = update_parameter_offsets(IDENT_ARGLST(g_current_function));
		}
    break;

  case 134:
#line 625 "zyacc.y"
    {
			IDENT_TYPE(yyvsp[-2].pident) = FUNCTION_t;
			yyval.pident = yyvsp[-2].pident;
		}
    break;

  case 135:
#line 633 "zyacc.y"
    {
			yyval.ptype = new_type(POINTER_t,0,0,0,0);
		}
    break;

  case 136:
#line 638 "zyacc.y"
    {
			yyval.ptype = new_type(POINTER_t,0,0,0,yyvsp[0].token.token);
		}
    break;

  case 137:
#line 642 "zyacc.y"
    {
			add_subtype(yyvsp[0].ptype,new_type(POINTER_t,0,0,0,0));
			yyval.ptype = yyvsp[0].ptype;
		}
    break;

  case 138:
#line 656 "zyacc.y"
    { yyval.pident = yyvsp[0].pident; }
    break;

  case 139:
#line 661 "zyacc.y"
    { yyval.pident = yyvsp[0].pident; }
    break;

  case 140:
#line 663 "zyacc.y"
    {
			add_argument(yyvsp[-2].pident,yyvsp[0].pident);
			yyval.pident = yyvsp[-2].pident;
		}
    break;

  case 141:
#line 671 "zyacc.y"
    {
			IDENT_TYPE(yyvsp[0].pident) = PARAMETER_t;
			if(IDENT_VARTYPE(yyvsp[0].pident))
				add_subtype(IDENT_VARTYPE(yyvsp[0].pident), yyvsp[-1].ptype);
			else
				IDENT_VARTYPE(yyvsp[0].pident) = yyvsp[-1].ptype;
			yyval.pident = yyvsp[0].pident;
		}
    break;

  case 142:
#line 680 "zyacc.y"
    {
			PIDENT_t param;
			
			param = new_ident("~dummy");
			IDENT_TYPE(param) = PARAMETER_t;
			if(yyvsp[0].ptype)
				add_subtype(yyvsp[0].ptype, yyvsp[-1].ptype);
			else
				yyvsp[0].ptype = yyvsp[-1].ptype;
			IDENT_VARTYPE(param) = yyvsp[0].ptype;
			yyval.pident = param;
		}
    break;

  case 143:
#line 693 "zyacc.y"
    {
			PIDENT_t param;
			
			param = new_ident("~dummy");
			IDENT_TYPE(param) = PARAMETER_t;
			IDENT_VARTYPE(param) = yyvsp[0].ptype;
			yyval.pident = param;
		}
    break;

  case 146:
#line 714 "zyacc.y"
    { yyval.ptype = yyvsp[0].ptype; }
    break;

  case 147:
#line 733 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 148:
#line 734 "zyacc.y"
    { yyval.plist = yyvsp[-1].plist; }
    break;

  case 149:
#line 735 "zyacc.y"
    { yyval.plist = yyvsp[-2].plist; }
    break;

  case 150:
#line 739 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 151:
#line 741 "zyacc.y"
    {
			add_node(yyvsp[-2].plist, yyvsp[0].plist);
			yyval.plist = yyvsp[-2].plist;
		}
    break;

  case 152:
#line 749 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 153:
#line 753 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 154:
#line 757 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 155:
#line 761 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 156:
#line 765 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 157:
#line 769 "zyacc.y"
    { 
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 158:
#line 782 "zyacc.y"
    {
			PCR_t pcrcase;
			pcrcase = new_cr(CRCASEVAL, 0);
			add_operand(pcrcase,0,yyvsp[-2].plist);
			yyval.pcr = add_cr(pcrcase,yyvsp[0].pcr);
		}
    break;

  case 159:
#line 789 "zyacc.y"
    {
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 160:
#line 795 "zyacc.y"
    { yyval.pcr=NULL; }
    break;

  case 161:
#line 796 "zyacc.y"
    { yyval.pcr=NULL; yyval.pcr = add_cr(yyval.pcr,yyvsp[-1].pcr); }
    break;

  case 162:
#line 798 "zyacc.y"
    { yyval.pcr=NULL; yyval.pcr = add_cr(yyval.pcr,yyvsp[-1].pcr); }
    break;

  case 163:
#line 802 "zyacc.y"
    { yyval.plist = yyvsp[0].plist; }
    break;

  case 164:
#line 804 "zyacc.y"
    {
			add_node(yyvsp[-1].plist, yyvsp[0].plist);
			yyval.plist = yyvsp[-1].plist;
		}
    break;

  case 165:
#line 812 "zyacc.y"
    {
			yyval.pcr = NULL;
			yyval.pcr = add_cr(yyval.pcr,yyvsp[0].pcr); 
		}
    break;

  case 166:
#line 817 "zyacc.y"
    {
			yyval.pcr = add_cr(yyvsp[-1].pcr, yyvsp[0].pcr);
		}
    break;

  case 167:
#line 823 "zyacc.y"
    { yyval.pcr=NULL; }
    break;

  case 168:
#line 825 "zyacc.y"
    {
			PCR_t pcrexp;
			pcrexp = new_cr(CREXPVAL, 0);
			add_operand(pcrexp,0/*operand number*/,yyvsp[-1].plist);
			yyval.pcr = pcrexp;
		}
    break;

  case 169:
#line 835 "zyacc.y"
    {
			yyval.pcr = emit_if(yyvsp[-2].plist/*exp*/, 0/*boolean exp*/, yyvsp[0].pcr/*true block*/,0/*false block*/);
			g_cr_block = 0;
		}
    break;

  case 170:
#line 840 "zyacc.y"
    {
			yyval.pcr = emit_if(yyvsp[-4].plist/*exp*/, 0/*boolean exp*/, yyvsp[-2].pcr/*true block*/,yyvsp[0].pcr/*false block*/);
			g_cr_block = 0;
		}
    break;

  case 171:
#line 845 "zyacc.y"
    {
			PCR_t label;
			label = new_label();
			yyval.pcr = emit_switch(yyvsp[-2].plist/*exp*/, yyvsp[0].pcr/*statement list*/);
			yyval.pcr = prefix_label(yyval.pcr,label);
			yyval.pcr = process_break_continue(yyval.pcr,label);
		}
    break;

  case 172:
#line 856 "zyacc.y"
    {
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			yyvsp[0].pcr = add_cr(yyvsp[0].pcr, emit_jp(label));
			pcr = emit_if(yyvsp[-2].plist, 0, yyvsp[0].pcr, 0);
			yyval.pcr = prefix_label(pcr, label);
			yyval.pcr = process_break_continue(yyval.pcr,label);
			g_cr_block=0;
		}
    break;

  case 173:
#line 866 "zyacc.y"
    {
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			pcr = emit_if(yyvsp[-2].plist,0, emit_jp(label),0);
			pcr = add_cr(yyvsp[-5].pcr,pcr);
			yyval.pcr = prefix_label(pcr, label);
			yyval.pcr = process_break_continue(yyval.pcr,label);
			g_cr_block=0;
		}
    break;

  case 174:
#line 877 "zyacc.y"
    {
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			yyvsp[0].pcr = add_cr(yyvsp[0].pcr, get_exp_cr(yyvsp[-2].plist));
			yyvsp[0].pcr = add_cr(yyvsp[0].pcr, emit_jp(label));
			pcr = emit_if((PLIST_t)(yyvsp[-3].pcr->operand[0]), 0, yyvsp[0].pcr, 0);
			yyval.pcr = add_cr(yyvsp[-4].pcr,prefix_label(pcr, label));
			yyval.pcr = process_break_continue(yyval.pcr,label);
		}
    break;

  case 175:
#line 891 "zyacc.y"
    {
			yyval.pcr = new_cr(CRCONTINUE, 0); /* this code record will be processed later */
		}
    break;

  case 176:
#line 895 "zyacc.y"
    {
			yyval.pcr = new_cr(CRBREAK, 0); /* this code record will be processed later */
		}
    break;

  case 177:
#line 899 "zyacc.y"
    {
			yyval.pcr = new_cr(CRBREAK, 0); /* this code record will be processed later */
		}
    break;

  case 178:
#line 903 "zyacc.y"
    {
			PCR_t pcr,pcrexp;
			pcrexp = new_cr(CREXPVAL, 0);
			add_operand(pcrexp,0/*operand number*/,yyvsp[-1].plist);
			pcr = return_val(yyvsp[-1].plist);
			pcr = add_cr(pcrexp,pcr);
			yyval.pcr = add_cr(pcr,new_cr(CRBREAK, 0)); /* this code record will be processed later */
		}
    break;

  case 181:
#line 920 "zyacc.y"
    {
			//print_cr_block($1);
			if( !emit_function(yyvsp[0].pcr) )
				yyerror("Internal Error");
			else
			{
				yyvsp[0].pcr = prefix_label(g_cr_block,new_func_label(g_current_function->pident_name));
				file_flag = 1;
				print_cr_block(yyvsp[0].pcr);
				print_function();
				delete_symhash(1);
				file_flag = 0;

				g_current_function = (PIDENT_t)NULL;
			}
			//print_cr_block($1);
			max_pseudo_num = 0; /* reset the pseudo registe counter */
			g_cr_block=0;
		}
    break;

  case 182:
#line 940 "zyacc.y"
    {
			emit_sym_decl(yyvsp[0].plist);
		}
    break;

  case 183:
#line 948 "zyacc.y"
    {
			PIDENT_t psym;
			
			psym = yyvsp[-1].pident;
			/* pointers followed by base type */
			if(IDENT_VARTYPE(psym))
				add_subtype(IDENT_VARTYPE(psym), yyvsp[-2].ptype);
			else
				IDENT_VARTYPE(psym) = yyvsp[-2].ptype;
			add_symbol(psym);
			g_current_function = psym;
			yyval.pcr = yyvsp[0].pcr;
		}
    break;

  case 184:
#line 963 "zyacc.y"
    {
			PIDENT_t psym;
			
			psym = yyvsp[-1].pident;
			/* pointers followed by base type */
			if(IDENT_VARTYPE(psym))
				add_subtype(IDENT_VARTYPE(psym), new_type(VOID_t,0,0,0,0));
			else
				IDENT_VARTYPE(psym) = new_type(VOID_t,0,0,0,0);
			add_symbol(psym);
			g_current_function = psym;
			yyval.pcr = yyvsp[0].pcr;
		}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2799 "zparser.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 978 "zyacc.y"


void yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%s (%d): ERROR :%s \n", g_filelist[inc_level].filename, g_line, s);
	g_errcount++;
}



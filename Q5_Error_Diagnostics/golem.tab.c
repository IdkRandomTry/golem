/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "golem.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

/* Error tracking */
int error_count = 0;
int warning_count = 0;

/* Input buffer for context display */
#define MAX_LINE_LENGTH 1024
char current_line[MAX_LINE_LENGTH];
int current_line_number = 0;

/* Enhanced error reporting */
void syntax_error(const char *msg, const char *token) {
    error_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "╔════════════════════════════════════════════════════════════════╗\n");
    fprintf(stderr, "║                      SYNTAX ERROR #%-3d                        ║\n", error_count);
    fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Location: Line %d\n", yylineno);
    fprintf(stderr, "Error:    %s\n", msg);
    if (token && strlen(token) > 0) {
        fprintf(stderr, "Token:    '%s'\n", token);
    }
    fprintf(stderr, "\n");
    
    /* Provide helpful suggestions */
    fprintf(stderr, "Possible causes:\n");
    if (strstr(msg, "syntax error") || strstr(msg, "unexpected")) {
        fprintf(stderr, "  • Missing semicolon (;) at the end of statement\n");
        fprintf(stderr, "  • Unmatched parentheses () or braces {}\n");
        fprintf(stderr, "  • Invalid token or keyword\n");
        fprintf(stderr, "  • Missing required keyword or operator\n");
    }
    fprintf(stderr, "\n");
}

void semantic_error(const char *msg) {
    error_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "╔════════════════════════════════════════════════════════════════╗\n");
    fprintf(stderr, "║                     SEMANTIC ERROR #%-3d                       ║\n", error_count);
    fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Location: Line %d\n", yylineno);
    fprintf(stderr, "Error:    %s\n", msg);
    fprintf(stderr, "\n");
}

void warning_message(const char *msg) {
    warning_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "⚠ Warning #%d (Line %d): %s\n", warning_count, yylineno, msg);
    fprintf(stderr, "\n");
}


#line 139 "golem.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "golem.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_GRID = 3,                       /* GRID  */
  YYSYMBOL_OBSTACLE = 4,                   /* OBSTACLE  */
  YYSYMBOL_BLUEPRINT = 5,                  /* BLUEPRINT  */
  YYSYMBOL_CONSTRUCT = 6,                  /* CONSTRUCT  */
  YYSYMBOL_SPAWN = 7,                      /* SPAWN  */
  YYSYMBOL_AT = 8,                         /* AT  */
  YYSYMBOL_AS = 9,                         /* AS  */
  YYSYMBOL_GO = 10,                        /* GO  */
  YYSYMBOL_TURN = 11,                      /* TURN  */
  YYSYMBOL_SCAN = 12,                      /* SCAN  */
  YYSYMBOL_PICK = 13,                      /* PICK  */
  YYSYMBOL_DROP = 14,                      /* DROP  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_REPEAT = 17,                    /* REPEAT  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_NORTH = 19,                     /* NORTH  */
  YYSYMBOL_SOUTH = 20,                     /* SOUTH  */
  YYSYMBOL_EAST = 21,                      /* EAST  */
  YYSYMBOL_WEST = 22,                      /* WEST  */
  YYSYMBOL_TRUE = 23,                      /* TRUE  */
  YYSYMBOL_FALSE = 24,                     /* FALSE  */
  YYSYMBOL_EMPTY = 25,                     /* EMPTY  */
  YYSYMBOL_EAST_SCAN = 26,                 /* EAST_SCAN  */
  YYSYMBOL_WEST_SCAN = 27,                 /* WEST_SCAN  */
  YYSYMBOL_NORTH_SCAN = 28,                /* NORTH_SCAN  */
  YYSYMBOL_SOUTH_SCAN = 29,                /* SOUTH_SCAN  */
  YYSYMBOL_EQ_OP = 30,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 31,                     /* NE_OP  */
  YYSYMBOL_PLUS = 32,                      /* PLUS  */
  YYSYMBOL_MINUS = 33,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 34,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 35,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 36,                    /* MODULO  */
  YYSYMBOL_INTEGER = 37,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 38,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 39,            /* STRING_LITERAL  */
  YYSYMBOL_UMINUS = 40,                    /* UMINUS  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* '?'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_grid_decl = 51,                 /* grid_decl  */
  YYSYMBOL_obstacle_list = 52,             /* obstacle_list  */
  YYSYMBOL_obstacle_stmt = 53,             /* obstacle_stmt  */
  YYSYMBOL_blueprint_decl = 54,            /* blueprint_decl  */
  YYSYMBOL_construct_decl = 55,            /* construct_decl  */
  YYSYMBOL_spawn_list = 56,                /* spawn_list  */
  YYSYMBOL_spawn_stmt = 57,                /* spawn_stmt  */
  YYSYMBOL_stmt_list = 58,                 /* stmt_list  */
  YYSYMBOL_stmt = 59,                      /* stmt  */
  YYSYMBOL_compound_stmt = 60,             /* compound_stmt  */
  YYSYMBOL_movement_stmt = 61,             /* movement_stmt  */
  YYSYMBOL_rotation_stmt = 62,             /* rotation_stmt  */
  YYSYMBOL_pick_stmt = 63,                 /* pick_stmt  */
  YYSYMBOL_drop_stmt = 64,                 /* drop_stmt  */
  YYSYMBOL_conditional_stmt = 65,          /* conditional_stmt  */
  YYSYMBOL_repetition_stmt = 66,           /* repetition_stmt  */
  YYSYMBOL_condition = 67,                 /* condition  */
  YYSYMBOL_directional_scan = 68,          /* directional_scan  */
  YYSYMBOL_scan_result = 69,               /* scan_result  */
  YYSYMBOL_direction = 70,                 /* direction  */
  YYSYMBOL_expr = 71                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    44,     2,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,     2,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   107,   111,   112,   113,   114,   115,   124,
     137,   145,   146,   147,   156,   169,   173,   182,   183,   191,
     192,   193,   201,   211,   221,   230,   231,   232,   240,   241,
     242,   243,   244,   245,   246,   250,   254,   262,   274,   283,
     287,   297,   301,   310,   314,   323,   327,   331,   341,   354,
     358,   368,   378,   379,   380,   381,   382,   392,   393,   394,
     395,   399,   400,   404,   405,   406,   407,   411,   415,   419,
     423,   427,   431,   441,   451,   455
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "GRID", "OBSTACLE",
  "BLUEPRINT", "CONSTRUCT", "SPAWN", "AT", "AS", "GO", "TURN", "SCAN",
  "PICK", "DROP", "IF", "ELSE", "REPEAT", "THEN", "NORTH", "SOUTH", "EAST",
  "WEST", "TRUE", "FALSE", "EMPTY", "EAST_SCAN", "WEST_SCAN", "NORTH_SCAN",
  "SOUTH_SCAN", "EQ_OP", "NE_OP", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "INTEGER", "IDENTIFIER", "STRING_LITERAL", "UMINUS", "';'",
  "'('", "','", "')'", "'{'", "'}'", "'?'", "$accept", "program",
  "statement", "grid_decl", "obstacle_list", "obstacle_stmt",
  "blueprint_decl", "construct_decl", "spawn_list", "spawn_stmt",
  "stmt_list", "stmt", "compound_stmt", "movement_stmt", "rotation_stmt",
  "pick_stmt", "drop_stmt", "conditional_stmt", "repetition_stmt",
  "condition", "directional_scan", "scan_result", "direction", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -82,    75,   -82,   -18,     4,     6,     2,   -82,   -82,   -82,
     -82,   -82,   -82,   -12,    46,   -11,   -19,     9,   -82,   -82,
      46,   -82,    49,   154,   -82,   -82,   -82,     3,   -82,   -16,
      87,    46,    46,    46,    46,    46,    46,     7,   -82,    29,
     -82,   -82,   -82,   -82,   108,   108,   -82,   -82,   -82,   118,
     -82,    64,    89,    31,    32,    24,    26,    28,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,    44,   138,    27,
      48,   188,    71,   -82,   -82,   -82,   -82,    76,   100,   124,
     125,   137,    85,   106,   -82,   -82,   104,    41,    47,   -82,
      63,   110,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   139,   -82,   -82,   -82,   -82,   135,   130,
     -82,   -82,   -82,   -82,    46,   174,     5,   107,    85,    15,
      15,   159,   142,   -82,   156,   -82,   -82,   149,   167,   -82,
     -82,   -82,   -82,    46,    46,    46,   155,    85,   123,   171,
     176,   133,   -82,   160,    46,    46,    15,    15,   -82,   136,
     141,   -82,   -82,   172,   175,   -82,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     7,     3,     4,
       5,     6,     8,     0,     0,     0,     0,     0,    19,    10,
       0,    67,     0,     0,    16,    25,    18,     0,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
      17,    20,    75,    74,    68,    69,    71,    72,    73,     0,
      27,     0,     0,     0,     0,     0,     0,     0,    15,    26,
      34,    28,    29,    30,    31,    32,    33,     0,     0,     0,
       0,     0,     0,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,     0,    51,    49,     0,     0,     0,    24,
       0,     0,    11,    38,    37,    40,    39,    42,    41,    44,
      43,    47,    56,     0,    57,    58,    59,    60,     0,     0,
      50,    48,    36,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     9,    12,     0,    45,    61,
      62,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,     0,     0,     0,     0,     0,    22,     0,
       0,    52,    53,     0,     0,    23,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     143,   -81,    -2,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -43,    98,   -20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     8,     9,   116,   126,    10,    11,    27,    41,
      37,    59,    60,    61,    62,    63,    64,    65,    66,   108,
     109,   131,    77,    23
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,   101,    30,    17,    38,    13,   123,    15,    50,   124,
      39,    44,    45,    46,    47,    48,    49,    51,    52,   129,
      53,    54,    55,    12,    56,    82,    25,    84,    42,    87,
      67,    71,    78,    80,    19,    24,    86,   128,   -25,   -25,
     130,   -25,   -25,   -25,    16,   -25,    14,    18,    50,    40,
      29,   125,    57,    58,    85,    26,   142,    51,    52,    20,
      53,    54,    55,    21,    56,    70,    83,    68,    22,    79,
      81,    57,    92,   -25,   -25,     2,     3,   132,     4,    20,
       5,     6,    20,    21,   111,    89,    21,   112,    22,    93,
      72,    22,    57,   113,   121,    51,    52,    20,    53,    54,
      55,    21,    56,   151,   152,   114,    22,   102,    73,    74,
      75,    76,    95,   138,   139,   140,     7,    96,   103,    31,
      32,    33,    34,    35,   149,   150,    73,    74,    75,    76,
      57,    43,   104,   105,   106,   107,    31,    32,    33,    34,
      35,    97,    33,    34,    35,   110,    90,    91,   115,    57,
      31,    32,    33,    34,    35,    31,    32,    33,    34,    35,
     119,   120,    69,   146,   147,    98,    99,   143,    31,    32,
      33,    34,    35,    31,    32,    33,    34,    35,   100,   118,
     153,   117,   122,   137,   134,   154,    31,    32,    33,    34,
      35,    31,    32,    33,    34,    35,   136,    36,   135,   141,
      88,   148,   133,    31,    32,    33,    34,    35,    31,    32,
      33,    34,    35,   155,   144,   127,   156,     0,     0,   145,
      31,    32,    33,    34,    35,     0,     0,     0,     0,    94
};

static const yytype_int16 yycheck[] =
{
      20,    82,    22,     1,     1,     1,     1,     1,     1,     4,
       7,    31,    32,    33,    34,    35,    36,    10,    11,     4,
      13,    14,    15,    41,    17,     1,    45,     1,    44,     1,
       1,    51,     1,     1,    46,    46,    56,   118,    10,    11,
      25,    13,    14,    15,    38,    17,    42,    45,     1,    46,
       1,    46,    45,    46,    56,    46,   137,    10,    11,    33,
      13,    14,    15,    37,    17,     1,    42,    38,    42,    38,
      38,    45,    45,    45,    46,     0,     1,   120,     3,    33,
       5,     6,    33,    37,    86,    41,    37,    46,    42,    41,
       1,    42,    45,    46,   114,    10,    11,    33,    13,    14,
      15,    37,    17,   146,   147,    42,    42,     1,    19,    20,
      21,    22,    41,   133,   134,   135,    41,    41,    12,    32,
      33,    34,    35,    36,   144,   145,    19,    20,    21,    22,
      45,    44,    26,    27,    28,    29,    32,    33,    34,    35,
      36,    41,    34,    35,    36,    41,     8,     9,    38,    45,
      32,    33,    34,    35,    36,    32,    33,    34,    35,    36,
      30,    31,    44,    30,    31,    41,    41,    44,    32,    33,
      34,    35,    36,    32,    33,    34,    35,    36,    41,    44,
      44,    42,     8,    16,    42,    44,    32,    33,    34,    35,
      36,    32,    33,    34,    35,    36,    47,    43,    42,    44,
      57,    41,    43,    32,    33,    34,    35,    36,    32,    33,
      34,    35,    36,    41,    43,   117,    41,    -1,    -1,    43,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,     0,     1,     3,     5,     6,    41,    50,    51,
      54,    55,    41,     1,    42,     1,    38,     1,    45,    46,
      33,    37,    42,    71,    46,    45,    46,    56,    71,     1,
      71,    32,    33,    34,    35,    36,    43,    58,     1,     7,
      46,    57,    44,    44,    71,    71,    71,    71,    71,    71,
       1,    10,    11,    13,    14,    15,    17,    45,    46,    59,
      60,    61,    62,    63,    64,    65,    66,     1,    38,    44,
       1,    71,     1,    19,    20,    21,    22,    70,     1,    38,
       1,    38,     1,    42,     1,    60,    71,     1,    58,    41,
       8,     9,    45,    41,    41,    41,    41,    41,    41,    41,
      41,    59,     1,    12,    26,    27,    28,    29,    67,    68,
      41,    60,    46,    46,    42,    38,    52,    42,    44,    30,
      31,    71,     8,     1,     4,    46,    53,    70,    59,     4,
      25,    69,    69,    43,    42,    42,    47,    16,    71,    71,
      71,    44,    59,    44,    43,    43,    30,    31,    41,    71,
      71,    69,    69,    44,    44,    41,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    50,    51,
      51,    52,    52,    52,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    57,    58,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    63,    64,    64,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    67,    67,    68,    68,    68,
      68,    69,    69,    70,    70,    70,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     2,     9,
       3,     0,     2,     2,     7,     5,     3,     4,     3,     0,
       2,     2,     9,    11,     3,     0,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     7,     3,     3,     2,
       3,     2,     7,     7,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* statement: error ';'  */
#line 116 "golem.y"
        {
		syntax_error("Invalid statement", yytext);
		fprintf(stderr, "Recovery: Skipping to next semicolon\n\n");
		yyerrok;
	}
#line 1702 "golem.tab.c"
    break;

  case 9: /* grid_decl: GRID '(' expr ',' expr ')' '{' obstacle_list '}'  */
#line 125 "golem.y"
        {
		if ((yyvsp[-6].ival) < 0 || (yyvsp[-4].ival) < 0) {
			semantic_error("Grid dimensions must be non-negative");
			fprintf(stderr, "Found: grid(%d, %d)\n", (yyvsp[-6].ival), (yyvsp[-4].ival));
			fprintf(stderr, "Expected: Both dimensions >= 0\n\n");
			YYERROR;
		}
		if ((yyvsp[-6].ival) == 0 || (yyvsp[-4].ival) == 0) {
			warning_message("Grid has zero dimension");
		}
		printf("  Grid: %d x %d\n", (yyvsp[-6].ival), (yyvsp[-4].ival));
	}
#line 1719 "golem.tab.c"
    break;

  case 10: /* grid_decl: GRID error '}'  */
#line 138 "golem.y"
        {
		syntax_error("Invalid grid declaration", NULL);
		fprintf(stderr, "Expected: grid(rows, cols) { ... }\n\n");
		yyerrok;
	}
#line 1729 "golem.tab.c"
    break;

  case 13: /* obstacle_list: obstacle_list error  */
#line 148 "golem.y"
        {
		syntax_error("Invalid obstacle statement", NULL);
		fprintf(stderr, "Expected: obstacle(x, y);\n\n");
		yyerrok;
	}
#line 1739 "golem.tab.c"
    break;

  case 14: /* obstacle_stmt: OBSTACLE '(' expr ',' expr ')' ';'  */
#line 157 "golem.y"
        {
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			semantic_error("Obstacle coordinates must be non-negative");
			fprintf(stderr, "Found: obstacle(%d, %d)\n", (yyvsp[-4].ival), (yyvsp[-2].ival));
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
			YYERROR;
		}
		printf("  Obstacle at (%d, %d)\n", (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1753 "golem.tab.c"
    break;

  case 15: /* blueprint_decl: BLUEPRINT IDENTIFIER '{' stmt_list '}'  */
#line 170 "golem.y"
        {
		printf("Blueprint '%s' defined\n", (yyvsp[-3].sval));
	}
#line 1761 "golem.tab.c"
    break;

  case 16: /* blueprint_decl: BLUEPRINT error '}'  */
#line 174 "golem.y"
        {
		syntax_error("Invalid blueprint declaration", NULL);
		fprintf(stderr, "Expected: blueprint name { ... }\n\n");
		yyerrok;
	}
#line 1771 "golem.tab.c"
    break;

  case 18: /* construct_decl: CONSTRUCT error '}'  */
#line 184 "golem.y"
        {
		syntax_error("Invalid construct declaration", NULL);
		fprintf(stderr, "Expected: construct { spawn statements }\n\n");
		yyerrok;
	}
#line 1781 "golem.tab.c"
    break;

  case 21: /* spawn_list: spawn_list error  */
#line 194 "golem.y"
        {
		syntax_error("Invalid spawn statement in construct block", NULL);
		yyerrok;
	}
#line 1790 "golem.tab.c"
    break;

  case 22: /* spawn_stmt: SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'  */
#line 202 "golem.y"
        {
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			semantic_error("Spawn coordinates must be non-negative");
			fprintf(stderr, "Found: spawn %s at (%d, %d)\n", (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1804 "golem.tab.c"
    break;

  case 23: /* spawn_stmt: SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'  */
#line 212 "golem.y"
        {
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			semantic_error("Spawn coordinates must be non-negative");
			fprintf(stderr, "Found: spawn %s as %s at (%d, %d)\n", (yyvsp[-9].sval), (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", (yyvsp[-9].sval), (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1818 "golem.tab.c"
    break;

  case 24: /* spawn_stmt: SPAWN error ';'  */
#line 222 "golem.y"
        {
		syntax_error("Invalid spawn statement", NULL);
		fprintf(stderr, "Expected: spawn name at (x, y);\n");
		fprintf(stderr, "      or: spawn name as alias at (x, y);\n\n");
		yyerrok;
	}
#line 1829 "golem.tab.c"
    break;

  case 27: /* stmt_list: stmt_list error  */
#line 233 "golem.y"
        {
		syntax_error("Invalid statement in statement list", NULL);
		yyerrok;
	}
#line 1838 "golem.tab.c"
    break;

  case 35: /* compound_stmt: '{' stmt_list '}'  */
#line 251 "golem.y"
        {
		printf("    { compound statements }\n");
	}
#line 1846 "golem.tab.c"
    break;

  case 36: /* compound_stmt: '{' error '}'  */
#line 255 "golem.y"
        {
		syntax_error("Invalid compound statement", NULL);
		yyerrok;
	}
#line 1855 "golem.tab.c"
    break;

  case 37: /* movement_stmt: GO expr ';'  */
#line 263 "golem.y"
        {
		if ((yyvsp[-1].ival) == 0) {
			warning_message("Movement with 0 steps has no effect");
			printf("    go 0;  (no movement)\n");
		} else if ((yyvsp[-1].ival) < 0) {
			int steps = -(yyvsp[-1].ival);
			printf("    go -%d;  (turn 180°, move %d steps forward, face reversed direction)\n", steps, steps);
		} else {
			printf("    go %d;  (move %d steps forward)\n", (yyvsp[-1].ival), (yyvsp[-1].ival));
		}
	}
#line 1871 "golem.tab.c"
    break;

  case 38: /* movement_stmt: GO error ';'  */
#line 275 "golem.y"
        {
		syntax_error("Invalid movement statement", NULL);
		fprintf(stderr, "Expected: go <number>;\n\n");
		yyerrok;
	}
#line 1881 "golem.tab.c"
    break;

  case 39: /* rotation_stmt: TURN direction ';'  */
#line 284 "golem.y"
        {
		printf("    turn direction;\n");
	}
#line 1889 "golem.tab.c"
    break;

  case 40: /* rotation_stmt: TURN error ';'  */
#line 288 "golem.y"
        {
		syntax_error("Invalid turn statement", NULL);
		fprintf(stderr, "Expected: turn <direction>;\n");
		fprintf(stderr, "Directions: north, south, east, west\n\n");
		yyerrok;
	}
#line 1900 "golem.tab.c"
    break;

  case 41: /* pick_stmt: PICK IDENTIFIER ';'  */
#line 298 "golem.y"
        {
		printf("    pick %s;\n", (yyvsp[-1].sval));
	}
#line 1908 "golem.tab.c"
    break;

  case 42: /* pick_stmt: PICK error ';'  */
#line 302 "golem.y"
        {
		syntax_error("Invalid pick statement", NULL);
		fprintf(stderr, "Expected: pick <identifier>;\n\n");
		yyerrok;
	}
#line 1918 "golem.tab.c"
    break;

  case 43: /* drop_stmt: DROP IDENTIFIER ';'  */
#line 311 "golem.y"
        {
		printf("    drop %s;\n", (yyvsp[-1].sval));
	}
#line 1926 "golem.tab.c"
    break;

  case 44: /* drop_stmt: DROP error ';'  */
#line 315 "golem.y"
        {
		syntax_error("Invalid drop statement", NULL);
		fprintf(stderr, "Expected: drop <identifier>;\n\n");
		yyerrok;
	}
#line 1936 "golem.tab.c"
    break;

  case 45: /* conditional_stmt: IF '(' condition ')' stmt  */
#line 324 "golem.y"
        {
		printf("    if (...) stmt\n");
	}
#line 1944 "golem.tab.c"
    break;

  case 46: /* conditional_stmt: IF '(' condition ')' stmt ELSE stmt  */
#line 328 "golem.y"
        {
		printf("    if (...) stmt else stmt\n");
	}
#line 1952 "golem.tab.c"
    break;

  case 47: /* conditional_stmt: IF error stmt  */
#line 332 "golem.y"
        {
		syntax_error("Invalid if statement", NULL);
		fprintf(stderr, "Expected: if (condition) statement\n");
		fprintf(stderr, "      or: if (condition) statement else statement\n\n");
		yyerrok;
	}
#line 1963 "golem.tab.c"
    break;

  case 48: /* repetition_stmt: REPEAT expr compound_stmt  */
#line 342 "golem.y"
        {
		if ((yyvsp[-1].ival) < 0) {
			semantic_error("Repeat count cannot be negative");
			fprintf(stderr, "Found: repeat %d { ... }\n", (yyvsp[-1].ival));
			fprintf(stderr, "Expected: count >= 0\n\n");
			YYERROR;
		}
		if ((yyvsp[-1].ival) == 0) {
			warning_message("Repeat with 0 iterations has no effect");
		}
		printf("    repeat %d { ... }\n", (yyvsp[-1].ival));
	}
#line 1980 "golem.tab.c"
    break;

  case 49: /* repetition_stmt: REPEAT compound_stmt  */
#line 355 "golem.y"
        {
		printf("    repeat (infinite) { ... }\n");
	}
#line 1988 "golem.tab.c"
    break;

  case 50: /* repetition_stmt: REPEAT expr ';'  */
#line 359 "golem.y"
        {
		if ((yyvsp[-1].ival) < 0) {
			semantic_error("Repeat count cannot be negative");
			fprintf(stderr, "Found: repeat %d;\n", (yyvsp[-1].ival));
			fprintf(stderr, "Expected: count >= 0\n\n");
			YYERROR;
		}
		printf("    repeat %d; (single iteration marker)\n", (yyvsp[-1].ival));
	}
#line 2002 "golem.tab.c"
    break;

  case 51: /* repetition_stmt: REPEAT error  */
#line 369 "golem.y"
        {
		syntax_error("Invalid repeat statement", NULL);
		fprintf(stderr, "Expected: repeat { ... }\n");
		fprintf(stderr, "      or: repeat <count> { ... }\n\n");
		yyerrok;
	}
#line 2013 "golem.tab.c"
    break;

  case 56: /* condition: error  */
#line 383 "golem.y"
        {
		syntax_error("Invalid condition", NULL);
		fprintf(stderr, "Expected: scan(direction?) == result\n");
		fprintf(stderr, "      or: directional_scan == result\n\n");
		yyerrok;
	}
#line 2024 "golem.tab.c"
    break;

  case 67: /* expr: INTEGER  */
#line 412 "golem.y"
        {
		(yyval.ival) = (yyvsp[0].ival);
	}
#line 2032 "golem.tab.c"
    break;

  case 68: /* expr: expr PLUS expr  */
#line 416 "golem.y"
        {
		(yyval.ival) = (yyvsp[-2].ival) + (yyvsp[0].ival);
	}
#line 2040 "golem.tab.c"
    break;

  case 69: /* expr: expr MINUS expr  */
#line 420 "golem.y"
        {
		(yyval.ival) = (yyvsp[-2].ival) - (yyvsp[0].ival);
	}
#line 2048 "golem.tab.c"
    break;

  case 70: /* expr: MINUS expr  */
#line 424 "golem.y"
        {
		(yyval.ival) = -(yyvsp[0].ival);
	}
#line 2056 "golem.tab.c"
    break;

  case 71: /* expr: expr MULTIPLY expr  */
#line 428 "golem.y"
        {
		(yyval.ival) = (yyvsp[-2].ival) * (yyvsp[0].ival);
	}
#line 2064 "golem.tab.c"
    break;

  case 72: /* expr: expr DIVIDE expr  */
#line 432 "golem.y"
        {
		if ((yyvsp[0].ival) == 0) {
			semantic_error("Division by zero");
			fprintf(stderr, "Expression: %d / %d\n", (yyvsp[-2].ival), (yyvsp[0].ival));
			fprintf(stderr, "Division by zero is undefined\n\n");
			YYERROR;
		}
		(yyval.ival) = (yyvsp[-2].ival) / (yyvsp[0].ival);
	}
#line 2078 "golem.tab.c"
    break;

  case 73: /* expr: expr MODULO expr  */
#line 442 "golem.y"
        {
		if ((yyvsp[0].ival) == 0) {
			semantic_error("Modulo by zero");
			fprintf(stderr, "Expression: %d %% %d\n", (yyvsp[-2].ival), (yyvsp[0].ival));
			fprintf(stderr, "Modulo by zero is undefined\n\n");
			YYERROR;
		}
		(yyval.ival) = (yyvsp[-2].ival) % (yyvsp[0].ival);
	}
#line 2092 "golem.tab.c"
    break;

  case 74: /* expr: '(' expr ')'  */
#line 452 "golem.y"
        {
		(yyval.ival) = (yyvsp[-1].ival);
	}
#line 2100 "golem.tab.c"
    break;

  case 75: /* expr: '(' error ')'  */
#line 456 "golem.y"
        {
		syntax_error("Invalid expression", NULL);
		fprintf(stderr, "Check for proper arithmetic expression syntax\n\n");
		(yyval.ival) = 0;
		yyerrok;
	}
#line 2111 "golem.tab.c"
    break;


#line 2115 "golem.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 464 "golem.y"


void yyerror(const char *s) {
	if (strstr(s, "syntax error") != NULL) {
		syntax_error(s, yytext);
	} else {
		fprintf(stderr, "\n╔════════════════════════════════════════════════════════════════╗\n");
		fprintf(stderr, "║                         PARSE ERROR                            ║\n");
		fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
		fprintf(stderr, "\nLine %d: %s\n", yylineno, s);
		if (yytext && strlen(yytext) > 0) {
			fprintf(stderr, "Near token: '%s'\n", yytext);
		}
		fprintf(stderr, "\n");
	}
}

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

/* Derivation tree structure */
typedef struct DerivationNode {
    char *production;
    int rule_num;
    struct DerivationNode *next;
} DerivationNode;

DerivationNode *derivation_head = NULL;
DerivationNode *derivation_tail = NULL;
int derivation_count = 0;

/* Function to add a derivation step */
void add_derivation(const char *rule_desc, int rule_num) {
    DerivationNode *node = (DerivationNode*)malloc(sizeof(DerivationNode));
    node->production = strdup(rule_desc);
    node->rule_num = rule_num;
    node->next = NULL;
    
    if (derivation_tail == NULL) {
        derivation_head = derivation_tail = node;
    } else {
        derivation_tail->next = node;
        derivation_tail = node;
    }
    derivation_count++;
}

/* Function to display derivation tree in reverse order */
void display_reverse_derivation() {
    if (derivation_head == NULL) {
        printf("No derivations recorded.\n");
        return;
    }
    
    /* Store in array for reverse display */
    DerivationNode **arr = (DerivationNode**)malloc(derivation_count * sizeof(DerivationNode*));
    DerivationNode *current = derivation_head;
    int i = 0;
    
    while (current != NULL) {
        arr[i++] = current;
        current = current->next;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║           REVERSE DERIVATION TREE (Bottom-Up)                 ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ Total Derivation Steps: %-38d ║\n", derivation_count);
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    /* Display in reverse order */
    for (i = derivation_count - 1; i >= 0; i--) {
        printf("[Step %3d/%d] Rule %2d: %s\n", 
               derivation_count - i, derivation_count, 
               arr[i]->rule_num, arr[i]->production);
    }
    
    printf("\n");
    free(arr);
}

/* Free derivation list */
void free_derivations() {
    DerivationNode *current = derivation_head;
    while (current != NULL) {
        DerivationNode *next = current->next;
        free(current->production);
        free(current);
        current = next;
    }
}


#line 153 "golem.tab.c"

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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   186

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

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
       0,   117,   117,   118,   123,   125,   127,   129,   134,   146,
     147,   152,   164,   172,   177,   178,   183,   192,   204,   205,
     210,   212,   214,   216,   218,   220,   222,   227,   235,   250,
     258,   266,   274,   279,   287,   296,   301,   313,   315,   317,
     319,   324,   326,   328,   330,   335,   337,   342,   344,   346,
     348,   353,   358,   363,   368,   373,   378,   387,   396
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
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

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -85,    14,   -85,   -35,   -22,   -27,   -85,   -85,   -85,   -85,
     -85,    98,   -24,   -85,    98,   -85,    98,   111,   -85,    -4,
     -85,    49,    98,    98,    98,    98,    98,    98,    18,   -15,
     -85,   -85,   -85,    41,    41,   -85,   -85,   -85,    62,    98,
     101,     8,    12,    -8,    97,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,    53,     7,   145,   -85,   -85,
     -85,   -85,    32,    48,    58,    10,   -85,    33,    34,    17,
      65,   -85,   -85,   -85,   -85,   -85,    63,   -85,   -85,   -85,
     -85,    60,    40,   -85,   -85,   -85,    98,    92,    -3,   101,
      43,     1,     1,   116,    76,    90,   -85,   -85,    70,   117,
     -85,   -85,   -85,   -85,    98,    98,    98,    94,    43,    75,
     128,   133,    56,   -85,    95,    98,    98,     1,     1,   -85,
      80,    93,   -85,   -85,   100,   112,   -85,   -85
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     7,     3,     4,     5,
       6,     0,     0,    14,     0,    51,     0,     0,    18,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    15,    58,    52,    53,    55,    56,    57,     0,     0,
       0,     0,     0,     0,     0,    18,    12,    19,    26,    20,
      21,    22,    23,    24,    25,     0,     0,     0,    47,    48,
      49,    50,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     9,    28,    29,    30,    31,     0,    41,    42,    43,
      44,     0,     0,    36,    34,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,    10,     0,    32,
      45,    46,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,    16,
       0,     0,    37,    38,     0,     0,    17,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     110,   -84,   -40,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -77,    67,   -14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     7,     8,    88,    97,     9,    10,    19,    31,
      28,    47,    48,    49,    50,    51,    52,    53,    54,    81,
      82,   102,    62,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      20,    95,    21,    29,    66,   100,    99,    11,    33,    34,
      35,    36,    37,    38,     2,   103,    12,     3,    13,     4,
       5,    18,    76,    55,   113,    57,   101,    84,    39,    40,
      67,    41,    42,    43,    65,    44,    77,    78,    79,    80,
     122,   123,    30,    96,    39,    40,    63,    41,    42,    43,
      64,    44,    71,    39,    40,     6,    41,    42,    43,    86,
      44,    69,    70,    45,    46,    22,    23,    24,    25,    26,
      91,    92,    93,    73,    83,    24,    25,    26,    45,    45,
      85,    22,    23,    24,    25,    26,   117,   118,    45,    74,
     109,   110,   111,    32,    22,    23,    24,    25,    26,    75,
      94,   120,   121,    87,    90,    89,    56,    22,    23,    24,
      25,    26,    22,    23,    24,    25,    26,   107,   105,   114,
      58,    59,    60,    61,   124,    22,    23,    24,    25,    26,
      14,    14,   106,   108,    15,    15,   119,   125,   112,    16,
      16,   126,    45,    22,    23,    24,    25,    26,    22,    23,
      24,    25,    26,   127,    27,    68,    98,     0,     0,   104,
      22,    23,    24,    25,    26,    22,    23,    24,    25,    26,
       0,   115,     0,     0,     0,     0,   116,    22,    23,    24,
      25,    26,     0,     0,     0,     0,    72
};

static const yytype_int8 yycheck[] =
{
      14,     4,    16,     7,    44,     4,    90,    42,    22,    23,
      24,    25,    26,    27,     0,    92,    38,     3,    45,     5,
       6,    45,    12,    38,   108,    39,    25,    67,    10,    11,
      44,    13,    14,    15,    42,    17,    26,    27,    28,    29,
     117,   118,    46,    46,    10,    11,    38,    13,    14,    15,
      38,    17,    45,    10,    11,    41,    13,    14,    15,    42,
      17,     8,     9,    45,    46,    32,    33,    34,    35,    36,
      30,    31,    86,    41,    41,    34,    35,    36,    45,    45,
      46,    32,    33,    34,    35,    36,    30,    31,    45,    41,
     104,   105,   106,    44,    32,    33,    34,    35,    36,    41,
       8,   115,   116,    38,    44,    42,    44,    32,    33,    34,
      35,    36,    32,    33,    34,    35,    36,    47,    42,    44,
      19,    20,    21,    22,    44,    32,    33,    34,    35,    36,
      33,    33,    42,    16,    37,    37,    41,    44,    44,    42,
      42,    41,    45,    32,    33,    34,    35,    36,    32,    33,
      34,    35,    36,    41,    43,    45,    89,    -1,    -1,    43,
      32,    33,    34,    35,    36,    32,    33,    34,    35,    36,
      -1,    43,    -1,    -1,    -1,    -1,    43,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,     0,     3,     5,     6,    41,    50,    51,    54,
      55,    42,    38,    45,    33,    37,    42,    71,    45,    56,
      71,    71,    32,    33,    34,    35,    36,    43,    58,     7,
      46,    57,    44,    71,    71,    71,    71,    71,    71,    10,
      11,    13,    14,    15,    17,    45,    46,    59,    60,    61,
      62,    63,    64,    65,    66,    38,    44,    71,    19,    20,
      21,    22,    70,    38,    38,    42,    60,    71,    58,     8,
       9,    45,    41,    41,    41,    41,    12,    26,    27,    28,
      29,    67,    68,    41,    60,    46,    42,    38,    52,    42,
      44,    30,    31,    71,     8,     4,    46,    53,    70,    59,
       4,    25,    69,    69,    43,    42,    42,    47,    16,    71,
      71,    71,    44,    59,    44,    43,    43,    30,    31,    41,
      71,    71,    69,    69,    44,    44,    41,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    51,    52,
      52,    53,    54,    55,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    60,    61,    62,
      63,    64,    65,    65,    66,    66,    66,    67,    67,    67,
      67,    68,    68,    68,    68,    69,    69,    70,    70,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     9,     0,
       2,     7,     5,     4,     0,     2,     9,    11,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     5,     7,     3,     2,     3,     7,     7,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     3,     3,     3,     3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 117 "golem.y"
        { add_derivation("program → ε", 1); }
#line 1302 "golem.tab.c"
    break;

  case 3: /* program: program statement  */
#line 119 "golem.y"
        { add_derivation("program → program statement", 2); }
#line 1308 "golem.tab.c"
    break;

  case 4: /* statement: grid_decl  */
#line 124 "golem.y"
        { add_derivation("statement → grid_decl", 3); }
#line 1314 "golem.tab.c"
    break;

  case 5: /* statement: blueprint_decl  */
#line 126 "golem.y"
        { add_derivation("statement → blueprint_decl", 4); }
#line 1320 "golem.tab.c"
    break;

  case 6: /* statement: construct_decl  */
#line 128 "golem.y"
        { add_derivation("statement → construct_decl", 5); }
#line 1326 "golem.tab.c"
    break;

  case 7: /* statement: ';'  */
#line 130 "golem.y"
        { add_derivation("statement → ';'", 6); }
#line 1332 "golem.tab.c"
    break;

  case 8: /* grid_decl: GRID '(' expr ',' expr ')' '{' obstacle_list '}'  */
#line 135 "golem.y"
        {
		add_derivation("grid_decl → GRID '(' expr ',' expr ')' '{' obstacle_list '}'", 7);
		if ((yyvsp[-6].ival) < 0 || (yyvsp[-4].ival) < 0) {
			yyerror("Grid dimensions must be non-negative");
			YYERROR;
		}
		printf("  Grid: %d x %d\n", (yyvsp[-6].ival), (yyvsp[-4].ival));
	}
#line 1345 "golem.tab.c"
    break;

  case 9: /* obstacle_list: %empty  */
#line 146 "golem.y"
        { add_derivation("obstacle_list → ε", 8); }
#line 1351 "golem.tab.c"
    break;

  case 10: /* obstacle_list: obstacle_list obstacle_stmt  */
#line 148 "golem.y"
        { add_derivation("obstacle_list → obstacle_list obstacle_stmt", 9); }
#line 1357 "golem.tab.c"
    break;

  case 11: /* obstacle_stmt: OBSTACLE '(' expr ',' expr ')' ';'  */
#line 153 "golem.y"
        {
		add_derivation("obstacle_stmt → OBSTACLE '(' expr ',' expr ')' ';'", 10);
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			yyerror("Obstacle coordinates must be non-negative");
			YYERROR;
		}
		printf("  Obstacle at (%d, %d)\n", (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1370 "golem.tab.c"
    break;

  case 12: /* blueprint_decl: BLUEPRINT IDENTIFIER '{' stmt_list '}'  */
#line 165 "golem.y"
        {
		add_derivation("blueprint_decl → BLUEPRINT IDENTIFIER '{' stmt_list '}'", 11);
		printf("Blueprint '%s' defined\n", (yyvsp[-3].sval));
	}
#line 1379 "golem.tab.c"
    break;

  case 13: /* construct_decl: CONSTRUCT '{' spawn_list '}'  */
#line 173 "golem.y"
        { add_derivation("construct_decl → CONSTRUCT '{' spawn_list '}'", 12); }
#line 1385 "golem.tab.c"
    break;

  case 14: /* spawn_list: %empty  */
#line 177 "golem.y"
        { add_derivation("spawn_list → ε", 13); }
#line 1391 "golem.tab.c"
    break;

  case 15: /* spawn_list: spawn_list spawn_stmt  */
#line 179 "golem.y"
        { add_derivation("spawn_list → spawn_list spawn_stmt", 14); }
#line 1397 "golem.tab.c"
    break;

  case 16: /* spawn_stmt: SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'  */
#line 184 "golem.y"
        {
		add_derivation("spawn_stmt → SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'", 15);
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1410 "golem.tab.c"
    break;

  case 17: /* spawn_stmt: SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'  */
#line 193 "golem.y"
        {
		add_derivation("spawn_stmt → SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'", 16);
		if ((yyvsp[-4].ival) < 0 || (yyvsp[-2].ival) < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", (yyvsp[-9].sval), (yyvsp[-7].sval), (yyvsp[-4].ival), (yyvsp[-2].ival));
	}
#line 1423 "golem.tab.c"
    break;

  case 18: /* stmt_list: %empty  */
#line 204 "golem.y"
        { add_derivation("stmt_list → ε", 17); }
#line 1429 "golem.tab.c"
    break;

  case 19: /* stmt_list: stmt_list stmt  */
#line 206 "golem.y"
        { add_derivation("stmt_list → stmt_list stmt", 18); }
#line 1435 "golem.tab.c"
    break;

  case 20: /* stmt: movement_stmt  */
#line 211 "golem.y"
        { add_derivation("stmt → movement_stmt", 19); }
#line 1441 "golem.tab.c"
    break;

  case 21: /* stmt: rotation_stmt  */
#line 213 "golem.y"
        { add_derivation("stmt → rotation_stmt", 20); }
#line 1447 "golem.tab.c"
    break;

  case 22: /* stmt: pick_stmt  */
#line 215 "golem.y"
        { add_derivation("stmt → pick_stmt", 21); }
#line 1453 "golem.tab.c"
    break;

  case 23: /* stmt: drop_stmt  */
#line 217 "golem.y"
        { add_derivation("stmt → drop_stmt", 22); }
#line 1459 "golem.tab.c"
    break;

  case 24: /* stmt: conditional_stmt  */
#line 219 "golem.y"
        { add_derivation("stmt → conditional_stmt", 23); }
#line 1465 "golem.tab.c"
    break;

  case 25: /* stmt: repetition_stmt  */
#line 221 "golem.y"
        { add_derivation("stmt → repetition_stmt", 24); }
#line 1471 "golem.tab.c"
    break;

  case 26: /* stmt: compound_stmt  */
#line 223 "golem.y"
        { add_derivation("stmt → compound_stmt", 25); }
#line 1477 "golem.tab.c"
    break;

  case 27: /* compound_stmt: '{' stmt_list '}'  */
#line 228 "golem.y"
        {
		add_derivation("compound_stmt → '{' stmt_list '}'", 26);
		printf("    { compound statements }\n");
	}
#line 1486 "golem.tab.c"
    break;

  case 28: /* movement_stmt: GO expr ';'  */
#line 236 "golem.y"
        {
		add_derivation("movement_stmt → GO expr ';'", 27);
		if ((yyvsp[-1].ival) == 0) {
			printf("    go 0;  (no movement)\n");
		} else if ((yyvsp[-1].ival) < 0) {
			int steps = -(yyvsp[-1].ival);
			printf("    go -%d;  (turn 180°, move %d steps forward, face reversed direction)\n", steps, steps);
		} else {
			printf("    go %d;  (move %d steps forward)\n", (yyvsp[-1].ival), (yyvsp[-1].ival));
		}
	}
#line 1502 "golem.tab.c"
    break;

  case 29: /* rotation_stmt: TURN direction ';'  */
#line 251 "golem.y"
        {
		add_derivation("rotation_stmt → TURN direction ';'", 28);
		printf("    turn direction;\n");
	}
#line 1511 "golem.tab.c"
    break;

  case 30: /* pick_stmt: PICK IDENTIFIER ';'  */
#line 259 "golem.y"
        {
		add_derivation("pick_stmt → PICK IDENTIFIER ';'", 29);
		printf("    pick %s;\n", (yyvsp[-1].sval));
	}
#line 1520 "golem.tab.c"
    break;

  case 31: /* drop_stmt: DROP IDENTIFIER ';'  */
#line 267 "golem.y"
        {
		add_derivation("drop_stmt → DROP IDENTIFIER ';'", 30);
		printf("    drop %s;\n", (yyvsp[-1].sval));
	}
#line 1529 "golem.tab.c"
    break;

  case 32: /* conditional_stmt: IF '(' condition ')' stmt  */
#line 275 "golem.y"
        {
		add_derivation("conditional_stmt → IF '(' condition ')' stmt", 31);
		printf("    if (...) stmt\n");
	}
#line 1538 "golem.tab.c"
    break;

  case 33: /* conditional_stmt: IF '(' condition ')' stmt ELSE stmt  */
#line 280 "golem.y"
        {
		add_derivation("conditional_stmt → IF '(' condition ')' stmt ELSE stmt", 32);
		printf("    if (...) stmt else stmt\n");
	}
#line 1547 "golem.tab.c"
    break;

  case 34: /* repetition_stmt: REPEAT expr compound_stmt  */
#line 288 "golem.y"
        {
		add_derivation("repetition_stmt → REPEAT expr compound_stmt", 33);
		if ((yyvsp[-1].ival) < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		printf("    repeat %d { ... }\n", (yyvsp[-1].ival));
	}
#line 1560 "golem.tab.c"
    break;

  case 35: /* repetition_stmt: REPEAT compound_stmt  */
#line 297 "golem.y"
        {
		add_derivation("repetition_stmt → REPEAT compound_stmt", 34);
		printf("    repeat (infinite) { ... }\n");
	}
#line 1569 "golem.tab.c"
    break;

  case 36: /* repetition_stmt: REPEAT expr ';'  */
#line 302 "golem.y"
        {
		add_derivation("repetition_stmt → REPEAT expr ';'", 35);
		if ((yyvsp[-1].ival) < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		printf("    repeat %d; (single iteration marker)\n", (yyvsp[-1].ival));
	}
#line 1582 "golem.tab.c"
    break;

  case 37: /* condition: SCAN '(' direction '?' ')' EQ_OP scan_result  */
#line 314 "golem.y"
        { add_derivation("condition → SCAN '(' direction '?' ')' EQ_OP scan_result", 36); }
#line 1588 "golem.tab.c"
    break;

  case 38: /* condition: SCAN '(' direction '?' ')' NE_OP scan_result  */
#line 316 "golem.y"
        { add_derivation("condition → SCAN '(' direction '?' ')' NE_OP scan_result", 37); }
#line 1594 "golem.tab.c"
    break;

  case 39: /* condition: directional_scan EQ_OP scan_result  */
#line 318 "golem.y"
        { add_derivation("condition → directional_scan EQ_OP scan_result", 38); }
#line 1600 "golem.tab.c"
    break;

  case 40: /* condition: directional_scan NE_OP scan_result  */
#line 320 "golem.y"
        { add_derivation("condition → directional_scan NE_OP scan_result", 39); }
#line 1606 "golem.tab.c"
    break;

  case 41: /* directional_scan: EAST_SCAN  */
#line 325 "golem.y"
        { add_derivation("directional_scan → EAST_SCAN", 40); }
#line 1612 "golem.tab.c"
    break;

  case 42: /* directional_scan: WEST_SCAN  */
#line 327 "golem.y"
        { add_derivation("directional_scan → WEST_SCAN", 41); }
#line 1618 "golem.tab.c"
    break;

  case 43: /* directional_scan: NORTH_SCAN  */
#line 329 "golem.y"
        { add_derivation("directional_scan → NORTH_SCAN", 42); }
#line 1624 "golem.tab.c"
    break;

  case 44: /* directional_scan: SOUTH_SCAN  */
#line 331 "golem.y"
        { add_derivation("directional_scan → SOUTH_SCAN", 43); }
#line 1630 "golem.tab.c"
    break;

  case 45: /* scan_result: OBSTACLE  */
#line 336 "golem.y"
        { add_derivation("scan_result → OBSTACLE", 44); }
#line 1636 "golem.tab.c"
    break;

  case 46: /* scan_result: EMPTY  */
#line 338 "golem.y"
        { add_derivation("scan_result → EMPTY", 45); }
#line 1642 "golem.tab.c"
    break;

  case 47: /* direction: NORTH  */
#line 343 "golem.y"
        { add_derivation("direction → NORTH", 46); }
#line 1648 "golem.tab.c"
    break;

  case 48: /* direction: SOUTH  */
#line 345 "golem.y"
        { add_derivation("direction → SOUTH", 47); }
#line 1654 "golem.tab.c"
    break;

  case 49: /* direction: EAST  */
#line 347 "golem.y"
        { add_derivation("direction → EAST", 48); }
#line 1660 "golem.tab.c"
    break;

  case 50: /* direction: WEST  */
#line 349 "golem.y"
        { add_derivation("direction → WEST", 49); }
#line 1666 "golem.tab.c"
    break;

  case 51: /* expr: INTEGER  */
#line 354 "golem.y"
        {
		add_derivation("expr → INTEGER", 50);
		(yyval.ival) = (yyvsp[0].ival);
	}
#line 1675 "golem.tab.c"
    break;

  case 52: /* expr: expr PLUS expr  */
#line 359 "golem.y"
        {
		add_derivation("expr → expr PLUS expr", 51);
		(yyval.ival) = (yyvsp[-2].ival) + (yyvsp[0].ival);
	}
#line 1684 "golem.tab.c"
    break;

  case 53: /* expr: expr MINUS expr  */
#line 364 "golem.y"
        {
		add_derivation("expr → expr MINUS expr", 52);
		(yyval.ival) = (yyvsp[-2].ival) - (yyvsp[0].ival);
	}
#line 1693 "golem.tab.c"
    break;

  case 54: /* expr: MINUS expr  */
#line 369 "golem.y"
        {
		add_derivation("expr → MINUS expr", 53);
		(yyval.ival) = -(yyvsp[0].ival);
	}
#line 1702 "golem.tab.c"
    break;

  case 55: /* expr: expr MULTIPLY expr  */
#line 374 "golem.y"
        {
		add_derivation("expr → expr MULTIPLY expr", 54);
		(yyval.ival) = (yyvsp[-2].ival) * (yyvsp[0].ival);
	}
#line 1711 "golem.tab.c"
    break;

  case 56: /* expr: expr DIVIDE expr  */
#line 379 "golem.y"
        {
		add_derivation("expr → expr DIVIDE expr", 55);
		if ((yyvsp[0].ival) == 0) {
			yyerror("Division by zero");
			YYERROR;
		}
		(yyval.ival) = (yyvsp[-2].ival) / (yyvsp[0].ival);
	}
#line 1724 "golem.tab.c"
    break;

  case 57: /* expr: expr MODULO expr  */
#line 388 "golem.y"
        {
		add_derivation("expr → expr MODULO expr", 56);
		if ((yyvsp[0].ival) == 0) {
			yyerror("Modulo by zero");
			YYERROR;
		}
		(yyval.ival) = (yyvsp[-2].ival) % (yyvsp[0].ival);
	}
#line 1737 "golem.tab.c"
    break;

  case 58: /* expr: '(' expr ')'  */
#line 397 "golem.y"
        {
		add_derivation("expr → '(' expr ')'", 57);
		(yyval.ival) = (yyvsp[-1].ival);
	}
#line 1746 "golem.tab.c"
    break;


#line 1750 "golem.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 403 "golem.y"


void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

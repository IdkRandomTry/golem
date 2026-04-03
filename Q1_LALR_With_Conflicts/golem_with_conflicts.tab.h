/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GOLEM_WITH_CONFLICTS_TAB_H_INCLUDED
# define YY_YY_GOLEM_WITH_CONFLICTS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    GRID = 258,                    /* GRID  */
    OBSTACLE = 259,                /* OBSTACLE  */
    BLUEPRINT = 260,               /* BLUEPRINT  */
    CONSTRUCT = 261,               /* CONSTRUCT  */
    SPAWN = 262,                   /* SPAWN  */
    AT = 263,                      /* AT  */
    AS = 264,                      /* AS  */
    GO = 265,                      /* GO  */
    TURN = 266,                    /* TURN  */
    SCAN = 267,                    /* SCAN  */
    PICK = 268,                    /* PICK  */
    DROP = 269,                    /* DROP  */
    IF = 270,                      /* IF  */
    ELSE = 271,                    /* ELSE  */
    REPEAT = 272,                  /* REPEAT  */
    THEN = 273,                    /* THEN  */
    NORTH = 274,                   /* NORTH  */
    SOUTH = 275,                   /* SOUTH  */
    EAST = 276,                    /* EAST  */
    WEST = 277,                    /* WEST  */
    TRUE = 278,                    /* TRUE  */
    FALSE = 279,                   /* FALSE  */
    EMPTY = 280,                   /* EMPTY  */
    EAST_SCAN = 281,               /* EAST_SCAN  */
    WEST_SCAN = 282,               /* WEST_SCAN  */
    NORTH_SCAN = 283,              /* NORTH_SCAN  */
    SOUTH_SCAN = 284,              /* SOUTH_SCAN  */
    EQ_OP = 285,                   /* EQ_OP  */
    NE_OP = 286,                   /* NE_OP  */
    PLUS = 287,                    /* PLUS  */
    MINUS = 288,                   /* MINUS  */
    MULTIPLY = 289,                /* MULTIPLY  */
    DIVIDE = 290,                  /* DIVIDE  */
    MODULO = 291,                  /* MODULO  */
    INTEGER = 292,                 /* INTEGER  */
    IDENTIFIER = 293,              /* IDENTIFIER  */
    STRING_LITERAL = 294,          /* STRING_LITERAL  */
    UMINUS = 295                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "golem_with_conflicts.y"

	int ival;
	char *sval;

#line 109 "golem_with_conflicts.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GOLEM_WITH_CONFLICTS_TAB_H_INCLUDED  */

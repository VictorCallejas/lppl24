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

#ifndef YY_YY_ASIN_H_INCLUDED
# define YY_YY_ASIN_H_INCLUDED
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
    INT_ = 258,                    /* INT_  */
    BOOL_ = 259,                   /* BOOL_  */
    IF_ = 260,                     /* IF_  */
    ELSE_ = 261,                   /* ELSE_  */
    FOR_ = 262,                    /* FOR_  */
    RETURN_ = 263,                 /* RETURN_  */
    READ_ = 264,                   /* READ_  */
    PRINT_ = 265,                  /* PRINT_  */
    TRUE_ = 266,                   /* TRUE_  */
    FALSE_ = 267,                  /* FALSE_  */
    IGUALDAD_ = 268,               /* IGUALDAD_  */
    DISTINTO_ = 269,               /* DISTINTO_  */
    MAYORIGUAL_ = 270,             /* MAYORIGUAL_  */
    MENORIGUAL_ = 271,             /* MENORIGUAL_  */
    AND_ = 272,                    /* AND_  */
    OR_ = 273,                     /* OR_  */
    MAS_ = 274,                    /* MAS_  */
    MENOS_ = 275,                  /* MENOS_  */
    POR_ = 276,                    /* POR_  */
    DIV_ = 277,                    /* DIV_  */
    NOT_ = 278,                    /* NOT_  */
    ASIG_ = 279,                   /* ASIG_  */
    MAYOR_ = 280,                  /* MAYOR_  */
    MENOR_ = 281,                  /* MENOR_  */
    AP_ = 282,                     /* AP_  */
    CP_ = 283,                     /* CP_  */
    ALLAVE_ = 284,                 /* ALLAVE_  */
    CLLAVE_ = 285,                 /* CLLAVE_  */
    ACOR_ = 286,                   /* ACOR_  */
    CCOR_ = 287,                   /* CCOR_  */
    PCOMA_ = 288,                  /* PCOMA_  */
    COMA_ = 289,                   /* COMA_  */
    ID_ = 290,                     /* ID_  */
    CTE_ = 291                     /* CTE_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "src/asin.y"

    char *ident;
    int cent;

#line 105 "asin.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ASIN_H_INCLUDED  */

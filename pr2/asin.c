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
#line 1 "src/asin.y"

    #include <stdio.h>
    #include <string.h>
    #include "header.h"
    #include "libtds.h"

    extern int dvar; /* desplazamiento variables */
    extern int niv;  /* nivel ("global"=0 o "local"=1) */

    int hayMain = FALSE;
    int refFunActual = -1;  
    int tipoFunActual = T_ERROR;
    char *nomFunActual = NULL;   
    int guardadvar; 
    int parActual; 

    int sonTiposCompatibles(int t1, int t2) {
        if (t1 == T_ERROR || t2 == T_ERROR) return FALSE;
        return (t1 == t2 && (t1 == T_ENTERO || t1 == T_LOGICO));
    }

    void checkEntero(int tipo, const char* msg) {
        if (tipo != T_ENTERO && tipo != T_ERROR) {
            yyerror(msg);
        }
    }

    void checkLogico(int tipo, const char* msg) {
        if (tipo != T_LOGICO && tipo != T_ERROR) {
            yyerror(msg);
        }
    }

    void checkTipoSimple(int tipo, const char* msg) {
        if (tipo!=T_ENTERO && tipo!=T_LOGICO && tipo!=T_ERROR) {
            yyerror(msg);
        }
    }

    void checkNoArray(int tipo, const char* msg) {
        if (tipo == T_ARRAY && tipo != T_ERROR) {
            yyerror(msg);
        }
    }

    void checkIndiceArray(int tipo) {
        if (tipo != T_ENTERO && tipo != T_ERROR) {
            yyerror("El indice del array debe ser entero");
        }
    }

#line 123 "asin.c"

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

#include "asin.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_ = 3,                       /* INT_  */
  YYSYMBOL_BOOL_ = 4,                      /* BOOL_  */
  YYSYMBOL_IF_ = 5,                        /* IF_  */
  YYSYMBOL_ELSE_ = 6,                      /* ELSE_  */
  YYSYMBOL_FOR_ = 7,                       /* FOR_  */
  YYSYMBOL_RETURN_ = 8,                    /* RETURN_  */
  YYSYMBOL_READ_ = 9,                      /* READ_  */
  YYSYMBOL_PRINT_ = 10,                    /* PRINT_  */
  YYSYMBOL_TRUE_ = 11,                     /* TRUE_  */
  YYSYMBOL_FALSE_ = 12,                    /* FALSE_  */
  YYSYMBOL_IGUALDAD_ = 13,                 /* IGUALDAD_  */
  YYSYMBOL_DISTINTO_ = 14,                 /* DISTINTO_  */
  YYSYMBOL_MAYORIGUAL_ = 15,               /* MAYORIGUAL_  */
  YYSYMBOL_MENORIGUAL_ = 16,               /* MENORIGUAL_  */
  YYSYMBOL_AND_ = 17,                      /* AND_  */
  YYSYMBOL_OR_ = 18,                       /* OR_  */
  YYSYMBOL_MAS_ = 19,                      /* MAS_  */
  YYSYMBOL_MENOS_ = 20,                    /* MENOS_  */
  YYSYMBOL_POR_ = 21,                      /* POR_  */
  YYSYMBOL_DIV_ = 22,                      /* DIV_  */
  YYSYMBOL_NOT_ = 23,                      /* NOT_  */
  YYSYMBOL_ASIG_ = 24,                     /* ASIG_  */
  YYSYMBOL_MAYOR_ = 25,                    /* MAYOR_  */
  YYSYMBOL_MENOR_ = 26,                    /* MENOR_  */
  YYSYMBOL_AP_ = 27,                       /* AP_  */
  YYSYMBOL_CP_ = 28,                       /* CP_  */
  YYSYMBOL_ALLAVE_ = 29,                   /* ALLAVE_  */
  YYSYMBOL_CLLAVE_ = 30,                   /* CLLAVE_  */
  YYSYMBOL_ACOR_ = 31,                     /* ACOR_  */
  YYSYMBOL_CCOR_ = 32,                     /* CCOR_  */
  YYSYMBOL_PCOMA_ = 33,                    /* PCOMA_  */
  YYSYMBOL_COMA_ = 34,                     /* COMA_  */
  YYSYMBOL_ID_ = 35,                       /* ID_  */
  YYSYMBOL_CTE_ = 36,                      /* CTE_  */
  YYSYMBOL_UMINUS = 37,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 38,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_listDecla = 42,                 /* listDecla  */
  YYSYMBOL_decla = 43,                     /* decla  */
  YYSYMBOL_declaVar = 44,                  /* declaVar  */
  YYSYMBOL_const = 45,                     /* const  */
  YYSYMBOL_tipoSimp = 46,                  /* tipoSimp  */
  YYSYMBOL_declaFunc = 47,                 /* declaFunc  */
  YYSYMBOL_48_2 = 48,                      /* $@2  */
  YYSYMBOL_paramForm = 49,                 /* paramForm  */
  YYSYMBOL_listParamForm = 50,             /* listParamForm  */
  YYSYMBOL_bloque = 51,                    /* bloque  */
  YYSYMBOL_declaVarLocal = 52,             /* declaVarLocal  */
  YYSYMBOL_listInst = 53,                  /* listInst  */
  YYSYMBOL_inst = 54,                      /* inst  */
  YYSYMBOL_instExpre = 55,                 /* instExpre  */
  YYSYMBOL_instEntSal = 56,                /* instEntSal  */
  YYSYMBOL_instSelec = 57,                 /* instSelec  */
  YYSYMBOL_instIter = 58,                  /* instIter  */
  YYSYMBOL_expreOP = 59,                   /* expreOP  */
  YYSYMBOL_expre = 60,                     /* expre  */
  YYSYMBOL_expreLogic = 61,                /* expreLogic  */
  YYSYMBOL_expreIgual = 62,                /* expreIgual  */
  YYSYMBOL_expreRel = 63,                  /* expreRel  */
  YYSYMBOL_expreAd = 64,                   /* expreAd  */
  YYSYMBOL_expreMul = 65,                  /* expreMul  */
  YYSYMBOL_expreUna = 66,                  /* expreUna  */
  YYSYMBOL_expreSufi = 67,                 /* expreSufi  */
  YYSYMBOL_paramAct = 68,                  /* paramAct  */
  YYSYMBOL_listParamAct = 69               /* listParamAct  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    84,    98,    99,   102,   103,   107,   114,
     123,   139,   140,   141,   144,   145,   150,   149,   193,   194,
     197,   204,   216,   223,   224,   227,   228,   231,   232,   233,
     234,   235,   239,   240,   244,   255,   262,   269,   277,   281,
     289,   294,   311,   338,   343,   349,   358,   360,   366,   375,
     377,   383,   389,   395,   404,   406,   412,   421,   423,   429,
     438,   440,   446,   452,   461,   466,   471,   482,   506,   528,
     531,   535,   540
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_", "BOOL_", "IF_",
  "ELSE_", "FOR_", "RETURN_", "READ_", "PRINT_", "TRUE_", "FALSE_",
  "IGUALDAD_", "DISTINTO_", "MAYORIGUAL_", "MENORIGUAL_", "AND_", "OR_",
  "MAS_", "MENOS_", "POR_", "DIV_", "NOT_", "ASIG_", "MAYOR_", "MENOR_",
  "AP_", "CP_", "ALLAVE_", "CLLAVE_", "ACOR_", "CCOR_", "PCOMA_", "COMA_",
  "ID_", "CTE_", "UMINUS", "UPLUS", "$accept", "programa", "$@1",
  "listDecla", "decla", "declaVar", "const", "tipoSimp", "declaFunc",
  "$@2", "paramForm", "listParamForm", "bloque", "declaVarLocal",
  "listInst", "inst", "instExpre", "instEntSal", "instSelec", "instIter",
  "expreOP", "expre", "expreLogic", "expreIgual", "expreRel", "expreAd",
  "expreMul", "expreUna", "expreSufi", "paramAct", "listParamAct", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -86,    39,   -86,   -86,    23,   -86,   -86,   -86,   -86,   -23,
     -86,   -13,    10,    23,    19,   -86,   -86,   -86,   -86,    26,
      49,    44,   -86,    29,   -86,    42,   -86,    58,    23,    69,
     -86,   -86,   -86,   -86,    23,   -86,    73,    33,    34,    77,
      83,    -4,    90,    93,   107,   107,   107,    -4,   -86,   -86,
     -14,   -86,   -86,   -86,   -86,   -86,   -86,    95,    12,    37,
      48,    51,    74,   -86,   -86,    -4,    -4,    99,    98,    -4,
     -22,   -86,   -86,   -86,   108,    70,    -4,    -4,    -4,   -86,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   111,   112,   -86,   110,   113,   116,    -4,   -86,
     -86,   -86,   114,   118,   -86,   115,    37,    37,    48,    48,
      51,    51,    51,    51,    74,    74,   -86,   -86,   102,    -4,
     -86,   117,   119,   121,    -4,   -86,   125,   145,   122,   -86,
     -86,   -86,   -86,    -4,   102,    -4,   -86,   -86,   126,   102,
     -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     3,    14,    15,     5,     6,     0,
       7,     0,     0,    18,     0,     8,    12,    13,    11,     0,
       0,     0,    19,     0,     9,    20,    16,     0,     0,     0,
      10,    21,    23,    17,    25,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    25,    33,
      66,    64,    26,    28,    29,    30,    31,     0,    40,    43,
      46,    49,    54,    57,    60,     0,    38,     0,     0,     0,
      66,    62,    61,    63,     0,     0,     0,    69,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,    65,
      27,    41,    71,     0,    70,     0,    44,    45,    47,    48,
      52,    53,    50,    51,    55,    56,    58,    59,     0,     0,
      22,     0,     0,     0,     0,    68,    67,     0,     0,    34,
      35,    67,    72,     0,     0,    38,    42,    36,     0,     0,
      37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   -86,   -86,   -86,   123,   144,     0,   -86,   -86,
     -86,   130,   -86,   -86,   120,   -85,   -86,   -86,   -86,   -86,
      24,   -41,   -86,    21,    41,     1,    27,   -43,   -86,   -86,
      36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,     7,     8,    51,    20,    10,    29,
      21,    22,    33,    34,    37,    52,    53,    54,    55,    56,
      93,    57,    58,    59,    60,    61,    62,    63,    64,   103,
     104
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      67,    71,    72,    73,     9,    77,    74,    16,    17,    98,
      76,    12,    11,    77,    13,    44,    45,    78,    14,    46,
      15,    16,    17,    47,    92,    94,     5,     6,    97,    80,
      81,    50,    18,   127,    36,   101,   102,   105,    39,     3,
      40,    41,    42,    43,    16,    17,    18,   116,   117,   137,
      82,    83,    44,    45,   140,    23,    46,   123,    12,    24,
      47,    27,    48,    84,    85,    14,    49,    15,    50,    18,
      88,    89,    26,    86,    87,    39,    28,    40,   128,    42,
      43,    16,    17,   102,    25,   110,   111,   112,   113,    44,
      45,    30,   136,    46,    94,    90,    91,    47,    32,    48,
     100,   106,   107,    49,    65,    50,    18,    39,    38,    40,
      66,    42,    43,    16,    17,   114,   115,    68,    16,    17,
      69,    44,    45,   108,   109,    46,    44,    45,    79,    47,
      46,    48,    95,    96,    47,    49,    99,    50,    18,   118,
     120,   121,    70,    18,   122,   119,   125,   126,   124,   133,
     129,   134,   130,   131,   139,   135,    19,    35,    31,   138,
     132,     0,     0,     0,     0,     0,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      41,    44,    45,    46,     4,    27,    47,    11,    12,    31,
      24,    24,    35,    27,    27,    19,    20,    31,    31,    23,
      33,    11,    12,    27,    65,    66,     3,     4,    69,    17,
      18,    35,    36,   118,    34,    76,    77,    78,     5,     0,
       7,     8,     9,    10,    11,    12,    36,    90,    91,   134,
      13,    14,    19,    20,   139,    36,    23,    98,    24,    33,
      27,    32,    29,    15,    16,    31,    33,    33,    35,    36,
      19,    20,    28,    25,    26,     5,    34,     7,   119,     9,
      10,    11,    12,   124,    35,    84,    85,    86,    87,    19,
      20,    33,   133,    23,   135,    21,    22,    27,    29,    29,
      30,    80,    81,    33,    27,    35,    36,     5,    35,     7,
      27,     9,    10,    11,    12,    88,    89,    27,    11,    12,
      27,    19,    20,    82,    83,    23,    19,    20,    33,    27,
      23,    29,    33,    35,    27,    33,    28,    35,    36,    28,
      30,    28,    35,    36,    28,    33,    28,    32,    34,    24,
      33,     6,    33,    32,    28,    33,    12,    34,    28,   135,
     124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,     0,    42,     3,     4,    43,    44,    46,
      47,    35,    24,    27,    31,    33,    11,    12,    36,    45,
      46,    49,    50,    36,    33,    35,    28,    32,    34,    48,
      33,    50,    29,    51,    52,    44,    46,    53,    35,     5,
       7,     8,     9,    10,    19,    20,    23,    27,    29,    33,
      35,    45,    54,    55,    56,    57,    58,    60,    61,    62,
      63,    64,    65,    66,    67,    27,    27,    60,    27,    27,
      35,    66,    66,    66,    60,    53,    24,    27,    31,    33,
      17,    18,    13,    14,    15,    16,    25,    26,    19,    20,
      21,    22,    60,    59,    60,    33,    35,    60,    31,    28,
      30,    60,    60,    68,    69,    60,    62,    62,    63,    63,
      64,    64,    64,    64,    65,    65,    66,    66,    28,    33,
      30,    28,    28,    60,    34,    28,    32,    54,    60,    33,
      33,    32,    69,    24,     6,    33,    60,    54,    59,    28,
      54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    41,    40,    42,    42,    43,    43,    44,    44,
      44,    45,    45,    45,    46,    46,    48,    47,    49,    49,
      50,    50,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    55,    55,    56,    56,    57,    58,    59,    59,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    63,
      63,    63,    63,    63,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    67,    67,    67,    67,    67,    68,
      68,    69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     1,     1,     3,     5,
       6,     1,     1,     1,     1,     1,     0,     7,     0,     1,
       2,     4,     7,     0,     2,     0,     2,     3,     1,     1,
       1,     1,     2,     1,     5,     5,     7,     9,     0,     1,
       1,     3,     6,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     2,     2,     2,     1,     3,     1,     4,     4,     0,
       1,     1,     3
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
  case 2: /* $@1: %empty  */
#line 84 "src/asin.y"
    {
      niv = 0; dvar = 0;
      cargaContexto(niv); /* Cargar contexto global */
    }
#line 1282 "asin.c"
    break;

  case 3: /* programa: $@1 listDecla  */
#line 89 "src/asin.y"
    {
      if (!hayMain) {
        yyerror("No existe la funcion main");
      }
      /* Aqui NO mostramos la TdS, ni falta hace */
      descargaContexto(niv); /* Descargar contexto global */
    }
#line 1294 "asin.c"
    break;

  case 8: /* declaVar: tipoSimp ID_ PCOMA_  */
#line 108 "src/asin.y"
        {
          if (!insTdS((yyvsp[-1].ident), VARIABLE, (yyvsp[-2].tipo), niv, dvar, -1))
            yyerror("Identificador repetido");
          else 
            dvar += TALLA_TIPO_SIMPLE;
        }
#line 1305 "asin.c"
    break;

  case 9: /* declaVar: tipoSimp ID_ ASIG_ const PCOMA_  */
#line 115 "src/asin.y"
        {
          if (!sonTiposCompatibles((yyvsp[-4].tipo), (yyvsp[-1].tipo)))
            yyerror("Error de tipos en la inicializacion de la variable");
          if (!insTdS((yyvsp[-3].ident), VARIABLE, (yyvsp[-4].tipo), niv, dvar, -1))
            yyerror("Identificador repetido");
          else 
            dvar += TALLA_TIPO_SIMPLE;
        }
#line 1318 "asin.c"
    break;

  case 10: /* declaVar: tipoSimp ID_ ACOR_ CTE_ CCOR_ PCOMA_  */
#line 124 "src/asin.y"
        {
          int numelem = (yyvsp[-2].cent);
          if (numelem <= 0) {
            yyerror("Talla inapropiada del array");
            numelem = 0;
          }
          int refe = insTdA((yyvsp[-5].tipo), numelem);
          if (!insTdS((yyvsp[-4].ident), VARIABLE, T_ARRAY, niv, dvar, refe))
            yyerror("Identificador repetido");
          else 
            dvar += numelem * TALLA_TIPO_SIMPLE;
        }
#line 1335 "asin.c"
    break;

  case 11: /* const: CTE_  */
#line 139 "src/asin.y"
               { (yyval.tipo) = T_ENTERO; }
#line 1341 "asin.c"
    break;

  case 12: /* const: TRUE_  */
#line 140 "src/asin.y"
               { (yyval.tipo) = T_LOGICO; }
#line 1347 "asin.c"
    break;

  case 13: /* const: FALSE_  */
#line 141 "src/asin.y"
               { (yyval.tipo) = T_LOGICO; }
#line 1353 "asin.c"
    break;

  case 14: /* tipoSimp: INT_  */
#line 144 "src/asin.y"
                { (yyval.tipo) = T_ENTERO; }
#line 1359 "asin.c"
    break;

  case 15: /* tipoSimp: BOOL_  */
#line 145 "src/asin.y"
                { (yyval.tipo) = T_LOGICO; }
#line 1365 "asin.c"
    break;

  case 16: /* $@2: %empty  */
#line 150 "src/asin.y"
           {
             niv = 1;
             guardadvar = dvar;
             dvar = 0;
             cargaContexto(niv);

             nomFunActual = (yyvsp[-3].ident);
             tipoFunActual = (yyvsp[-4].tipo);

             if ((yyvsp[-1].ref) == -1) {
               refFunActual = insTdD(-1, T_VACIO);
             } else {
               refFunActual = (yyvsp[-1].ref);
             }

             if (!insTdS((yyvsp[-3].ident), FUNCION, (yyvsp[-4].tipo), 0, 0, refFunActual))
                yyerror("Funcion repetida");

             if (strcmp((yyvsp[-3].ident), "main")==0) {
               if (hayMain) {
                 yyerror("Hay mas de una funcion main");
               } else {
                 INF infoMain = obtTdD(refFunActual);
                 if (infoMain.tsp != 0)
                   yyerror("La funcion main no debe tener parametros");
                 hayMain = TRUE;
               }
             }
           }
#line 1399 "asin.c"
    break;

  case 17: /* declaFunc: tipoSimp ID_ AP_ paramForm CP_ $@2 bloque  */
#line 180 "src/asin.y"
           {
             if (verTdS) mostrarTdS();
             descargaContexto(niv);
             niv = 0;
             dvar = guardadvar;
             nomFunActual = NULL;
             tipoFunActual = T_ERROR;
             refFunActual = -1;
           }
#line 1413 "asin.c"
    break;

  case 18: /* paramForm: %empty  */
#line 193 "src/asin.y"
           { (yyval.ref) = insTdD(-1, T_VACIO); }
#line 1419 "asin.c"
    break;

  case 19: /* paramForm: listParamForm  */
#line 194 "src/asin.y"
                         { (yyval.ref) = (yyvsp[0].ref); }
#line 1425 "asin.c"
    break;

  case 20: /* listParamForm: tipoSimp ID_  */
#line 198 "src/asin.y"
             {
               int refdom = insTdD(-1, (yyvsp[-1].tipo));
               if (!insTdS((yyvsp[0].ident), PARAMETRO, (yyvsp[-1].tipo), 1, -TALLA_TIPO_SIMPLE, -1))
                  yyerror("Identificador de parametro repetido");
               (yyval.ref) = refdom;
             }
#line 1436 "asin.c"
    break;

  case 21: /* listParamForm: tipoSimp ID_ COMA_ listParamForm  */
#line 205 "src/asin.y"
             {
               int refdom = insTdD((yyvsp[0].ref), (yyvsp[-3].tipo));
               INF info = obtTdD(refdom);
               int despParam = -info.tsp; 
               if (!insTdS((yyvsp[-2].ident), PARAMETRO, (yyvsp[-3].tipo), 1, despParam, -1))
                  yyerror("Identificador de parametro repetido");
               (yyval.ref) = refdom;
             }
#line 1449 "asin.c"
    break;

  case 22: /* bloque: ALLAVE_ declaVarLocal listInst RETURN_ expre PCOMA_ CLLAVE_  */
#line 217 "src/asin.y"
      {
        if (!sonTiposCompatibles(tipoFunActual, (yyvsp[-2].atr).tipo))
          yyerror("Error de tipos en el 'return'");
      }
#line 1458 "asin.c"
    break;

  case 32: /* instExpre: expre PCOMA_  */
#line 239 "src/asin.y"
                        { }
#line 1464 "asin.c"
    break;

  case 33: /* instExpre: PCOMA_  */
#line 240 "src/asin.y"
                         { }
#line 1470 "asin.c"
    break;

  case 34: /* instEntSal: READ_ AP_ ID_ CP_ PCOMA_  */
#line 245 "src/asin.y"
          {
            SIMB s = obtTdS((yyvsp[-2].ident));
            if (s.t == T_ERROR) yyerror("Objeto no declarado");
            else {
              if (s.t != T_ENTERO)
                yyerror("El argumento del 'read' debe ser entero");
              if (s.t == T_ARRAY)
                yyerror("El argumento del 'read' debe ser entero (no array)");
            }
          }
#line 1485 "asin.c"
    break;

  case 35: /* instEntSal: PRINT_ AP_ expre CP_ PCOMA_  */
#line 256 "src/asin.y"
          {
            checkEntero((yyvsp[-2].atr).tipo, "La expresion del 'print' debe ser entera");
          }
#line 1493 "asin.c"
    break;

  case 36: /* instSelec: IF_ AP_ expre CP_ inst ELSE_ inst  */
#line 263 "src/asin.y"
          {
            checkLogico((yyvsp[-4].atr).tipo, "La expresion del 'if' debe ser logica");
          }
#line 1501 "asin.c"
    break;

  case 37: /* instIter: FOR_ AP_ expreOP PCOMA_ expre PCOMA_ expreOP CP_ inst  */
#line 270 "src/asin.y"
         {
           checkLogico((yyvsp[-4].atr).tipo, "La expresion del 'for' debe ser logica");
         }
#line 1509 "asin.c"
    break;

  case 38: /* expreOP: %empty  */
#line 277 "src/asin.y"
        {
          (yyval.atr).tipo = T_VACIO; 
          (yyval.atr).ref = -1;
        }
#line 1518 "asin.c"
    break;

  case 39: /* expreOP: expre  */
#line 282 "src/asin.y"
        {
          (yyval.atr).tipo = (yyvsp[0].atr).tipo;
          (yyval.atr).ref = (yyvsp[0].atr).ref;
        }
#line 1527 "asin.c"
    break;

  case 40: /* expre: expreLogic  */
#line 290 "src/asin.y"
     {
       (yyval.atr).tipo = (yyvsp[0].atr).tipo; 
       (yyval.atr).ref = (yyvsp[0].atr).ref; 
     }
#line 1536 "asin.c"
    break;

  case 41: /* expre: ID_ ASIG_ expre  */
#line 295 "src/asin.y"
     {
       SIMB s = obtTdS((yyvsp[-2].ident));
       if (s.t == T_ERROR) {
         yyerror("Objeto no declarado");
         (yyval.atr).tipo = T_ERROR;
       } else {
         if (!sonTiposCompatibles(s.t, (yyvsp[0].atr).tipo))
           yyerror("Error de tipos en la 'instruccion de asignacion'");
         if (s.t == T_ARRAY)
           yyerror("Error de tipos en la asignacion a un 'array'");
         if ((yyvsp[0].atr).tipo == T_ARRAY)
           yyerror("No se puede asignar un array completo a una variable simple");
         (yyval.atr).tipo = s.t;
       }
       (yyval.atr).ref = -1;
     }
#line 1557 "asin.c"
    break;

  case 42: /* expre: ID_ ACOR_ expre CCOR_ ASIG_ expre  */
#line 312 "src/asin.y"
     {
       SIMB s = obtTdS((yyvsp[-5].ident));
       if (s.t == T_ERROR) {
         yyerror("Objeto no declarado");
         (yyval.atr).tipo = T_ERROR; (yyval.atr).ref = -1;
       } else {
         if (s.t != T_ARRAY && s.t!=T_ERROR)
           yyerror("La variable debe ser de tipo 'array'");
         checkIndiceArray((yyvsp[-3].atr).tipo);
         if (s.t == T_ARRAY) {
           DIM dim = obtTdA(s.ref);
           if (dim.telem == T_ERROR) {
             yyerror("Error con el array");
             (yyval.atr).tipo = T_ERROR; 
           } else {
             if (!sonTiposCompatibles(dim.telem, (yyvsp[0].atr).tipo))
               yyerror("Error de tipos en la asignacion a un 'array'");
             (yyval.atr).tipo = dim.telem;
           }
         } else (yyval.atr).tipo = T_ERROR;
         (yyval.atr).ref = -1;
       }
     }
#line 1585 "asin.c"
    break;

  case 43: /* expreLogic: expreIgual  */
#line 339 "src/asin.y"
           {
             (yyval.atr).tipo = (yyvsp[0].atr).tipo; 
             (yyval.atr).ref = (yyvsp[0].atr).ref;
           }
#line 1594 "asin.c"
    break;

  case 44: /* expreLogic: expreLogic AND_ expreIgual  */
#line 344 "src/asin.y"
           {
             if (!sonTiposCompatibles((yyvsp[-2].atr).tipo, (yyvsp[0].atr).tipo) || (yyvsp[-2].atr).tipo!=T_LOGICO)
               yyerror("Error en 'expresion logica'");
             (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
           }
#line 1604 "asin.c"
    break;

  case 45: /* expreLogic: expreLogic OR_ expreIgual  */
#line 350 "src/asin.y"
           {
             if (!sonTiposCompatibles((yyvsp[-2].atr).tipo, (yyvsp[0].atr).tipo) || (yyvsp[-2].atr).tipo!=T_LOGICO)
               yyerror("Error en 'expresion logica'");
             (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
           }
#line 1614 "asin.c"
    break;

  case 46: /* expreIgual: expreRel  */
#line 359 "src/asin.y"
           { (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = (yyvsp[0].atr).ref; }
#line 1620 "asin.c"
    break;

  case 47: /* expreIgual: expreIgual IGUALDAD_ expreRel  */
#line 361 "src/asin.y"
           {
             if (!sonTiposCompatibles((yyvsp[-2].atr).tipo, (yyvsp[0].atr).tipo))
               yyerror("Error en 'expresion de igualdad'");
             (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
           }
#line 1630 "asin.c"
    break;

  case 48: /* expreIgual: expreIgual DISTINTO_ expreRel  */
#line 367 "src/asin.y"
           {
             if (!sonTiposCompatibles((yyvsp[-2].atr).tipo, (yyvsp[0].atr).tipo))
               yyerror("Error en 'expresion de igualdad'");
             (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
           }
#line 1640 "asin.c"
    break;

  case 49: /* expreRel: expreAd  */
#line 376 "src/asin.y"
         { (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = (yyvsp[0].atr).ref; }
#line 1646 "asin.c"
    break;

  case 50: /* expreRel: expreRel MAYOR_ expreAd  */
#line 378 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
         }
#line 1656 "asin.c"
    break;

  case 51: /* expreRel: expreRel MENOR_ expreAd  */
#line 384 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
         }
#line 1666 "asin.c"
    break;

  case 52: /* expreRel: expreRel MAYORIGUAL_ expreAd  */
#line 390 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
         }
#line 1676 "asin.c"
    break;

  case 53: /* expreRel: expreRel MENORIGUAL_ expreAd  */
#line 396 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
         }
#line 1686 "asin.c"
    break;

  case 54: /* expreAd: expreMul  */
#line 405 "src/asin.y"
        { (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = (yyvsp[0].atr).ref; }
#line 1692 "asin.c"
    break;

  case 55: /* expreAd: expreAd MAS_ expreMul  */
#line 407 "src/asin.y"
        {
          if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
            yyerror("Error en 'expresion aditiva'");
          (yyval.atr).tipo = T_ENTERO; (yyval.atr).ref = -1;
        }
#line 1702 "asin.c"
    break;

  case 56: /* expreAd: expreAd MENOS_ expreMul  */
#line 413 "src/asin.y"
        {
          if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
            yyerror("Error en 'expresion aditiva'");
          (yyval.atr).tipo = T_ENTERO; (yyval.atr).ref = -1;
        }
#line 1712 "asin.c"
    break;

  case 57: /* expreMul: expreUna  */
#line 422 "src/asin.y"
         { (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = (yyvsp[0].atr).ref; }
#line 1718 "asin.c"
    break;

  case 58: /* expreMul: expreMul POR_ expreUna  */
#line 424 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion multiplicativa'");
           (yyval.atr).tipo = T_ENTERO; (yyval.atr).ref = -1;
         }
#line 1728 "asin.c"
    break;

  case 59: /* expreMul: expreMul DIV_ expreUna  */
#line 430 "src/asin.y"
         {
           if ((yyvsp[-2].atr).tipo!=T_ENTERO || (yyvsp[0].atr).tipo!=T_ENTERO)
             yyerror("Error en 'expresion multiplicativa'");
           (yyval.atr).tipo = T_ENTERO; (yyval.atr).ref = -1;
         }
#line 1738 "asin.c"
    break;

  case 60: /* expreUna: expreSufi  */
#line 439 "src/asin.y"
         { (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = (yyvsp[0].atr).ref; }
#line 1744 "asin.c"
    break;

  case 61: /* expreUna: MENOS_ expreUna  */
#line 441 "src/asin.y"
         {
           if ((yyvsp[0].atr).tipo != T_ENTERO && (yyvsp[0].atr).tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = -1;
         }
#line 1754 "asin.c"
    break;

  case 62: /* expreUna: MAS_ expreUna  */
#line 447 "src/asin.y"
         {
           if ((yyvsp[0].atr).tipo != T_ENTERO && (yyvsp[0].atr).tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           (yyval.atr).tipo = (yyvsp[0].atr).tipo; (yyval.atr).ref = -1;
         }
#line 1764 "asin.c"
    break;

  case 63: /* expreUna: NOT_ expreUna  */
#line 453 "src/asin.y"
         {
           if ((yyvsp[0].atr).tipo != T_LOGICO && (yyvsp[0].atr).tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           (yyval.atr).tipo = T_LOGICO; (yyval.atr).ref = -1;
         }
#line 1774 "asin.c"
    break;

  case 64: /* expreSufi: const  */
#line 462 "src/asin.y"
          {
            (yyval.atr).tipo = (yyvsp[0].tipo); 
            (yyval.atr).ref = -1;
          }
#line 1783 "asin.c"
    break;

  case 65: /* expreSufi: AP_ expre CP_  */
#line 467 "src/asin.y"
          {
            (yyval.atr).tipo = (yyvsp[-1].atr).tipo; 
            (yyval.atr).ref = (yyvsp[-1].atr).ref;
          }
#line 1792 "asin.c"
    break;

  case 66: /* expreSufi: ID_  */
#line 472 "src/asin.y"
          {
            SIMB s = obtTdS((yyvsp[0].ident));
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              (yyval.atr).tipo = T_ERROR;
            } else {
              (yyval.atr).tipo = s.t;
            }
            (yyval.atr).ref = -1;
          }
#line 1807 "asin.c"
    break;

  case 67: /* expreSufi: ID_ ACOR_ expre CCOR_  */
#line 483 "src/asin.y"
          {
            SIMB s = obtTdS((yyvsp[-3].ident));
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              (yyval.atr).tipo = T_ERROR; (yyval.atr).ref = -1;
            } else {
              if (s.t != T_ARRAY && s.t!=T_ERROR)
                yyerror("La variable debe ser de tipo 'array'");
              checkIndiceArray((yyvsp[-1].atr).tipo);
              if (s.t == T_ARRAY) {
                DIM dim = obtTdA(s.ref);
                if (dim.telem == T_ERROR) {
                  yyerror("Error con el array");
                  (yyval.atr).tipo = T_ERROR; 
                } else {
                  (yyval.atr).tipo = dim.telem;
                }
              } else {
                (yyval.atr).tipo = T_ERROR; 
              }
              (yyval.atr).ref = -1;
            }
          }
#line 1835 "asin.c"
    break;

  case 68: /* expreSufi: ID_ AP_ paramAct CP_  */
#line 507 "src/asin.y"
          {
            SIMB s = obtTdS((yyvsp[-3].ident));
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              (yyval.atr).tipo = T_ERROR; (yyval.atr).ref = -1;
            } else {
              INF info = obtTdD(s.ref);
              if (info.tipo == T_ERROR) {
                yyerror("Objeto no es funcion");
                (yyval.atr).tipo = T_ERROR; (yyval.atr).ref = -1;
              } else {
                if (!cmpDom((yyvsp[-1].ref), s.ref))
                  yyerror("Dominio de parametros actual no coincide con el formal");
                (yyval.atr).tipo = info.tipo; (yyval.atr).ref = -1;
              }
            }
          }
#line 1857 "asin.c"
    break;

  case 69: /* paramAct: %empty  */
#line 528 "src/asin.y"
         {
           (yyval.ref) = insTdD(-1, T_VACIO);
         }
#line 1865 "asin.c"
    break;

  case 70: /* paramAct: listParamAct  */
#line 531 "src/asin.y"
                        { (yyval.ref) = (yyvsp[0].ref); }
#line 1871 "asin.c"
    break;

  case 71: /* listParamAct: expre  */
#line 536 "src/asin.y"
            {
              int refDom = insTdD(-1, (yyvsp[0].atr).tipo);
              (yyval.ref) = refDom;
            }
#line 1880 "asin.c"
    break;

  case 72: /* listParamAct: expre COMA_ listParamAct  */
#line 541 "src/asin.y"
            {
              int refDom = insTdD((yyvsp[0].ref), (yyvsp[-2].atr).tipo);
              (yyval.ref) = refDom;
            }
#line 1889 "asin.c"
    break;


#line 1893 "asin.c"

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

#line 547 "src/asin.y"


/* Sin yyerror aquí. Definida en principal.c */

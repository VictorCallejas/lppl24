/*****************************************************************************/
/** Cabecera general para MenosC, con constantes y estructuras.             **/
/*****************************************************************************/
#ifndef _HEADER_H
#define _HEADER_H

/* Estructura para expresiones */
typedef struct exp {
    int t; /* Tipo de la expresion */
    int d; /* Desplazamiento o valor */
} EXP;

/* Estructura para controlar bucles for */
typedef struct for_s {
    int verdad; /* Etiqueta cuando condicion es verdadera */
    int falso;  /* Etiqueta cuando condicion es falsa */
    int ant_si; /* Lugar donde regresar en el ciclo */
} FORSTRUCT;

/* Estructura para organizar informacion inicial del programa */
typedef struct inicio {
    int inc_t; /* Lista pendiente para reserva global */
    int go_t;  /* Lista pendiente para saltar a main */
} INICIO;

/* Constantes generales */
#define TRUE                1
#define FALSE               0
#define NOT                 0
#define MAS                 1
#define MENOS               2
#define TALLA_TIPO_SIMPLE   1
#define TALLA_SEGENLACES    2

/* Variables externas compartidas con el analizador */
extern int  yylex();
extern int  yyparse();
extern FILE *yyin;
extern int  yylineno;
extern char *yytext;

/* Se usara para ver la TDS si es necesario */
extern int verTdS;

/* Funcion de manejo de errores y variables globales */
extern void yyerror(const char *msg);
extern int verbosidad;
extern int numErrores;

#endif /* _HEADER_H */

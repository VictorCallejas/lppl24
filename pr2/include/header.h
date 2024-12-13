#ifndef _HEADER_H
#define _HEADER_H

#define TRUE  1
#define FALSE 0

/* Talla asociada a los tipos simples (int, bool) */
#define TALLA_TIPO_SIMPLE 1
#define TALLA_SEGENLACES 2

extern int yylex();
extern int yyparse();

extern FILE *yyin;
extern int   yylineno;
extern char *yytext;

extern void yyerror(const char * msg);

extern int verbosidad;  /* Flag si se desea una traza */
extern int numErrores;  /* Contador del número de errores */
extern int verTdS;      /* Flag para mostrar la TdS */

/* Definición de la estructura Atributos */
typedef struct {
    int tipo;  
    int ref;   
} Atributos;

#endif

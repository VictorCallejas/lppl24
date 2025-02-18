/*****************************************************************************/
/**   Ejemplo de un posible fichero de cabeceras donde situar las           **/
/** definiciones de constantes, variables y estructuras para MenosC. Los    **/
/** alumnos deberán adaptarlo al desarrollo de su propio compilador.        **/
/*****************************************************************************/
#ifndef _HEADER_H
#define _HEADER_H

/****************************************************** Constantes generales */
#define TRUE  1
#define FALSE 0
/************************************* Variables externas definidas en el AL */
extern int yylex();
extern int yyparse();

extern FILE *yyin;                           /* Fichero de entrada           */
extern int   yylineno;                       /* Contador del número de línea */
extern char *yytext;                         /* Patrón detectado             */
/********* Funciones y variables externas definidas en el Programa Principal */
extern void yyerror(const char * msg);       /* Tratamiento de errores       */

extern int verbosidad;                       /* Flag si se desea una traza   */
extern int numErrores;                       /* Contador del número de errores */

#endif  /* _HEADER_H */
/*****************************************************************************/


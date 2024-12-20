/*****************************************************************************/
/*  Programa principal y tratamiento de errores.                             */
/*                       Jose Miguel Benedi v.24                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "header.h"

int verbosidad = FALSE;                    /* Si se desea una traza o no     */
int numErrores = 0;                       /* Contador del número de errores */
/*****************************************************************************/
void yyerror(const char * msg)
/*  Tratamiento de errores.                                                  */
{
  numErrores++;  fflush(stdout);
  fprintf(stdout, "\nError en %d: %s\n", yylineno, msg);
}
/*****************************************************************************/
int main (int argc, char **argv) 
/* Gestiona la línea de comandos e invoca al analizador sintáctico-semántico */
{ int i, n = 1;

  for (i=1; i<argc; ++i) { 
    if (strcmp(argv[i], "-v")==0) { verbosidad = TRUE; n++; }
  }
  if (argc == n+1) {
    if ((yyin = fopen (argv[n], "r")) == NULL) {
      fprintf (stderr, "El fichero '%s' no es válido\n", argv[n]);
      fprintf (stderr, "Uso: cmc [-v] fichero\n");
    }      
    else {        
      if (verbosidad == TRUE) fprintf(stdout,"%3d.- ", yylineno);
      yyparse ();
      if (numErrores > 0) 
        fprintf(stderr,"\nNúmero de errores:      %d\n", numErrores);
    }   
  }
  else fprintf (stderr, "Uso: cmc [-v] fichero\n");

  return (0);
} 
/*****************************************************************************/


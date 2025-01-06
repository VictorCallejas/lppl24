/*****************************************************************************/
/**  Analizador lexico para MenosC (version sin acentos).                   **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"
#include "asin.h"

/* Macro que devuelve tokens y muestra texto si verboseFlag esta activo */
#define retornar(tokenValue) { if (verbosidad) ECHO; return (tokenValue); }
%}

/* Opciones para no generar input() y unput(), y contar lineas con yylineno */
%option noinput
%option nounput
%option yylineno

/* Expresiones regulares */
whitespace  [ \t\n]+
number      ([0-9]+([.][0-9]*)?|[.][0-9]+)
identifier  [a-zA-Z][_a-zA-Z0-9]*
commentLine [\/][\/].*

%%

{whitespace} {
  /* Ignorar espacios y saltos de linea, solo mostrar si verbosidad */
  if (verbosidad) ECHO;
}

{commentLine} {
  /* Comentarios de linea: no generan token */
  if (verbosidad) ECHO;
}

/* Palabras reservadas */
"int"           { retornar(INT_); }
"true"          { retornar(TRUE_); }
"false"         { retornar(FALSE_); }
"bool"          { retornar(BOOL_); }
"return"        { retornar(RETURN_); }
"read"          { retornar(READ_); }
"print"         { retornar(PRINT_); }
"if"            { retornar(IF_); }
"else"          { retornar(ELSE_); }
"for"           { retornar(FOR_); }

/* Operadores multiples */
">="            { retornar(MAYI_); }
"<="            { retornar(MENI_); }
"&&"            { retornar(AND_); }
"||"            { retornar(OR_); }
"!="            { retornar(NOTEQUAL_); }
"=="            { retornar(EQUALS_); }

/* Operadores simples */
"+"             { retornar(MAS_); }
"-"             { retornar(MENOS_); }
"*"             { retornar(POR_); }
"/"             { retornar(DIV_); }
"("             { retornar(PARA_); }
")"             { retornar(PARC_); }
";"             { retornar(PUNTC_); }
"="             { retornar(IGUAL_); }
"["             { retornar(CORA_); }
"]"             { retornar(CORC_); }
"{"             { retornar(BRAA_); }
"}"             { retornar(BRAC_); }
","             { retornar(COMA_); }
">"             { retornar(MAYOR_); }
"<"             { retornar(MENOR_); }
"!"             { retornar(NOT_); }

/* Convertir a entero (truncado por enunciado) */
{number} {
  yylval.lexInt = atoi(yytext);
  retornar(CTE_);
}

/* Identificadores */
{identifier} {
  yylval.lexId = strdup(yytext);
  retornar(ID_);
}

/* Cualquier otro caracter es desconocido */
. {
  if (verbosidad) ECHO;
  yyerror("Caracter desconocido");
}

%%

%{
    #include <stdio.h>
    #include <string.h>
    #include "header.h"
    #include "asin.h"
    #define retornar(x) { if (verbosidad) ECHO; return x; }

    extern int yylineno;
    extern int verbosidad;
%}

%option noyywrap
%option yylineno

delimitador     [ \t]+
digito          [0-9]
letra           [a-zA-Z]
identificador   {letra}({letra}|{digito}|_)*
numero          {digito}+(\.{digito}*)?|\.{digito}+

comentario     \/\/.*

%%

{delimitador}  { if(verbosidad) ECHO ; }
{comentario}   { if(verbosidad) ECHO ; }
"\n"           { if(verbosidad) {ECHO; printf("  %d.-", yylineno);}  }

"int"                        { retornar(INT_); }
"bool"                       { retornar(BOOL_); }
"if"                         { retornar(IF_); }
"else"                       { retornar(ELSE_); }
"for"                        { retornar(FOR_); }
"return"                     { retornar(RETURN_); }
"read"                       { retornar(READ_); }
"print"                      { retornar(PRINT_); }
"true"                       { retornar(TRUE_); }
"false"                      { retornar(FALSE_); }

"=="                         { retornar(IGUALDAD_); }
"!="                         { retornar(DISTINTO_); }
">="                         { retornar(MAYORIGUAL_); }
"<="                         { retornar(MENORIGUAL_); }
"&&"                         { retornar(AND_); }
"\|\|"                       { retornar(OR_); }

"+"                          { retornar(MAS_); }
"-"                          { retornar(MENOS_); }
"*"                          { retornar(POR_); }
"/"                          { retornar(DIV_); }
"!"                          { retornar(NOT_); }
"="                          { retornar(ASIG_); }
">"                          { retornar(MAYOR_); }
"<"                          { retornar(MENOR_); }

"("                          { retornar(AP_); }
")"                          { retornar(CP_); }
"{"                          { retornar(ALLAVE_); }
"}"                          { retornar(CLLAVE_); }
"["                          { retornar(ACOR_); }
"]"                          { retornar(CCOR_); }
";"                          { retornar(PCOMA_); }
","                          { retornar(COMA_); }

{identificador} {
    yylval.ident = strdup(yytext);
    retornar(ID_);
}

{numero} {
    yylval.cent = atoi(yytext);
    retornar(CTE_);
}

. { yyerror("Caracter desconocido"); return 0; }

%%

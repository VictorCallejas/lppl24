%{
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
%}

%union {
    char *ident;
    int cent;
    int tipo;
    int ref;
    Atributos atr;
}

%token INT_ BOOL_ IF_ ELSE_ FOR_ RETURN_ READ_ PRINT_ TRUE_ FALSE_
%token IGUALDAD_ DISTINTO_ MAYORIGUAL_ MENORIGUAL_ AND_ OR_
%token MAS_ MENOS_ POR_ DIV_ NOT_ ASIG_ MAYOR_ MENOR_
%token AP_ CP_ ALLAVE_ CLLAVE_ ACOR_ CCOR_ PCOMA_ COMA_
%token <ident> ID_
%token <cent> CTE_

%type <atr> expre expreOP expreLogic expreIgual expreRel expreAd expreMul expreUna expreSufi
%type <tipo> tipoSimp const
%type <ref> paramForm listParamForm paramAct listParamAct

%right ASIG_
%right OR_ AND_
%nonassoc IGUALDAD_ DISTINTO_
%nonassoc MAYOR_ MENOR_ MAYORIGUAL_ MENORIGUAL_
%left MAS_ MENOS_
%left POR_ DIV_
%right NOT_
%right UMINUS UPLUS

%%

programa:
    {
      niv = 0; dvar = 0;
      cargaContexto(niv); /* Cargar contexto global */
    }
    listDecla
    {
      if (!hayMain) {
        yyerror("No existe la funcion main");
      }
      /* Aqui NO mostramos la TdS, ni falta hace */
      descargaContexto(niv); /* Descargar contexto global */
    }
    ;

listDecla:
          | listDecla decla
          ;

decla: declaVar
     | declaFunc
     ;

/* Declaracion de variables */
declaVar: tipoSimp ID_ PCOMA_
        {
          if (!insTdS($2, VARIABLE, $1, niv, dvar, -1))
            yyerror("Identificador repetido");
          else 
            dvar += TALLA_TIPO_SIMPLE;
        }
      | tipoSimp ID_ ASIG_ const PCOMA_
        {
          if (!sonTiposCompatibles($1, $4))
            yyerror("Error de tipos en la inicializacion de la variable");
          if (!insTdS($2, VARIABLE, $1, niv, dvar, -1))
            yyerror("Identificador repetido");
          else 
            dvar += TALLA_TIPO_SIMPLE;
        }
      | tipoSimp ID_ ACOR_ CTE_ CCOR_ PCOMA_
        {
          int numelem = $4;
          if (numelem <= 0) {
            yyerror("Talla inapropiada del array");
            numelem = 0;
          }
          int refe = insTdA($1, numelem);
          if (!insTdS($2, VARIABLE, T_ARRAY, niv, dvar, refe))
            yyerror("Identificador repetido");
          else 
            dvar += numelem * TALLA_TIPO_SIMPLE;
        }
        ;

/* Constantes */
const: CTE_    { $$ = T_ENTERO; }
     | TRUE_   { $$ = T_LOGICO; }
     | FALSE_  { $$ = T_LOGICO; }
     ;

tipoSimp: INT_  { $$ = T_ENTERO; }
        | BOOL_ { $$ = T_LOGICO; }
        ;

/* Declaracion de funciones */
declaFunc: tipoSimp ID_ AP_ paramForm CP_ 
           {
             niv = 1;
             guardadvar = dvar;
             dvar = 0;
             cargaContexto(niv);

             nomFunActual = $2;
             tipoFunActual = $1;

             if ($4 == -1) {
               refFunActual = insTdD(-1, T_VACIO);
             } else {
               refFunActual = $4;
             }

             if (!insTdS($2, FUNCION, $1, 0, 0, refFunActual))
                yyerror("Funcion repetida");

             if (strcmp($2, "main")==0) {
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
           bloque
           {
             if (verTdS) mostrarTdS();
             descargaContexto(niv);
             niv = 0;
             dvar = guardadvar;
             nomFunActual = NULL;
             tipoFunActual = T_ERROR;
             refFunActual = -1;
           }
         ;

/* Parametros formales */
paramForm:
           { $$ = insTdD(-1, T_VACIO); }
         | listParamForm { $$ = $1; }
         ;

listParamForm: tipoSimp ID_
             {
               int refdom = insTdD(-1, $1);
               if (!insTdS($2, PARAMETRO, $1, 1, -TALLA_TIPO_SIMPLE, -1))
                  yyerror("Identificador de parametro repetido");
               $$ = refdom;
             }
             | tipoSimp ID_ COMA_ listParamForm
             {
               int refdom = insTdD($4, $1);
               INF info = obtTdD(refdom);
               int despParam = -info.tsp; 
               if (!insTdS($2, PARAMETRO, $1, 1, despParam, -1))
                  yyerror("Identificador de parametro repetido");
               $$ = refdom;
             }
             ;

/* Bloque de funcion */
bloque: ALLAVE_ declaVarLocal listInst RETURN_ expre PCOMA_ CLLAVE_
      {
        if (!sonTiposCompatibles(tipoFunActual, $5.tipo))
          yyerror("Error de tipos en el 'return'");
      }
      ;

declaVarLocal:
              | declaVarLocal declaVar
              ;

listInst:
         | listInst inst
         ;

inst: ALLAVE_ listInst CLLAVE_
    | instExpre
    | instEntSal
    | instSelec
    | instIter
    ;

/* Instruccion de expresion */
instExpre: expre PCOMA_ { }
          | PCOMA_       { }
          ;

/* Instrucciones E/S */
instEntSal: READ_ AP_ ID_ CP_ PCOMA_
          {
            SIMB s = obtTdS($3);
            if (s.t == T_ERROR) yyerror("Objeto no declarado");
            else {
              if (s.t != T_ENTERO)
                yyerror("El argumento del 'read' debe ser entero");
              if (s.t == T_ARRAY)
                yyerror("El argumento del 'read' debe ser entero (no array)");
            }
          }
          | PRINT_ AP_ expre CP_ PCOMA_
          {
            checkEntero($3.tipo, "La expresion del 'print' debe ser entera");
          }
          ;

/* if */
instSelec: IF_ AP_ expre CP_ inst ELSE_ inst
          {
            checkLogico($3.tipo, "La expresion del 'if' debe ser logica");
          }
          ;

/* for */
instIter: FOR_ AP_ expreOP PCOMA_ expre PCOMA_ expreOP CP_ inst
         {
           checkLogico($5.tipo, "La expresion del 'for' debe ser logica");
         }
         ;

/* expreOP (expresion opcional) */
expreOP:
        {
          $$.tipo = T_VACIO; 
          $$.ref = -1;
        }
        | expre 
        {
          $$.tipo = $1.tipo;
          $$.ref = $1.ref;
        }
        ;

/* Expresiones */
expre: expreLogic
     {
       $$.tipo = $1.tipo; 
       $$.ref = $1.ref; 
     }
     | ID_ ASIG_ expre
     {
       SIMB s = obtTdS($1);
       if (s.t == T_ERROR) {
         yyerror("Objeto no declarado");
         $$.tipo = T_ERROR;
       } else {
         if (!sonTiposCompatibles(s.t, $3.tipo))
           yyerror("Error de tipos en la 'instruccion de asignacion'");
         if (s.t == T_ARRAY)
           yyerror("Error de tipos en la asignacion a un 'array'");
         if ($3.tipo == T_ARRAY)
           yyerror("No se puede asignar un array completo a una variable simple");
         $$.tipo = s.t;
       }
       $$.ref = -1;
     }
     | ID_ ACOR_ expre CCOR_ ASIG_ expre
     {
       SIMB s = obtTdS($1);
       if (s.t == T_ERROR) {
         yyerror("Objeto no declarado");
         $$.tipo = T_ERROR; $$.ref = -1;
       } else {
         if (s.t != T_ARRAY && s.t!=T_ERROR)
           yyerror("La variable debe ser de tipo 'array'");
         checkIndiceArray($3.tipo);
         if (s.t == T_ARRAY) {
           DIM dim = obtTdA(s.ref);
           if (dim.telem == T_ERROR) {
             yyerror("Error con el array");
             $$.tipo = T_ERROR; 
           } else {
             if (!sonTiposCompatibles(dim.telem, $6.tipo))
               yyerror("Error de tipos en la asignacion a un 'array'");
             $$.tipo = dim.telem;
           }
         } else $$.tipo = T_ERROR;
         $$.ref = -1;
       }
     }
     ;

/* Expresiones logicas */
expreLogic: expreIgual
           {
             $$.tipo = $1.tipo; 
             $$.ref = $1.ref;
           }
           | expreLogic AND_ expreIgual
           {
             if (!sonTiposCompatibles($1.tipo, $3.tipo) || $1.tipo!=T_LOGICO)
               yyerror("Error en 'expresion logica'");
             $$.tipo = T_LOGICO; $$.ref = -1;
           }
           | expreLogic OR_ expreIgual
           {
             if (!sonTiposCompatibles($1.tipo, $3.tipo) || $1.tipo!=T_LOGICO)
               yyerror("Error en 'expresion logica'");
             $$.tipo = T_LOGICO; $$.ref = -1;
           }
           ;

/* Expresiones de igualdad */
expreIgual: expreRel
           { $$.tipo = $1.tipo; $$.ref = $1.ref; }
           | expreIgual IGUALDAD_ expreRel
           {
             if (!sonTiposCompatibles($1.tipo, $3.tipo))
               yyerror("Error en 'expresion de igualdad'");
             $$.tipo = T_LOGICO; $$.ref = -1;
           }
           | expreIgual DISTINTO_ expreRel
           {
             if (!sonTiposCompatibles($1.tipo, $3.tipo))
               yyerror("Error en 'expresion de igualdad'");
             $$.tipo = T_LOGICO; $$.ref = -1;
           }
           ;

/* Expresiones relacionales */
expreRel: expreAd
         { $$.tipo = $1.tipo; $$.ref = $1.ref; }
         | expreRel MAYOR_ expreAd
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           $$.tipo = T_LOGICO; $$.ref = -1;
         }
         | expreRel MENOR_ expreAd
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           $$.tipo = T_LOGICO; $$.ref = -1;
         }
         | expreRel MAYORIGUAL_ expreAd
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           $$.tipo = T_LOGICO; $$.ref = -1;
         }
         | expreRel MENORIGUAL_ expreAd
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion relacional'");
           $$.tipo = T_LOGICO; $$.ref = -1;
         }
         ;

/* Expresiones aditivas */
expreAd: expreMul
        { $$.tipo = $1.tipo; $$.ref = $1.ref; }
        | expreAd MAS_ expreMul
        {
          if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
            yyerror("Error en 'expresion aditiva'");
          $$.tipo = T_ENTERO; $$.ref = -1;
        }
        | expreAd MENOS_ expreMul
        {
          if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
            yyerror("Error en 'expresion aditiva'");
          $$.tipo = T_ENTERO; $$.ref = -1;
        }
        ;

/* Expresiones multiplicativas */
expreMul: expreUna
         { $$.tipo = $1.tipo; $$.ref = $1.ref; }
         | expreMul POR_ expreUna
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion multiplicativa'");
           $$.tipo = T_ENTERO; $$.ref = -1;
         }
         | expreMul DIV_ expreUna
         {
           if ($1.tipo!=T_ENTERO || $3.tipo!=T_ENTERO)
             yyerror("Error en 'expresion multiplicativa'");
           $$.tipo = T_ENTERO; $$.ref = -1;
         }
         ;

/* Expresiones unarias */
expreUna: expreSufi
         { $$.tipo = $1.tipo; $$.ref = $1.ref; }
         | MENOS_ expreUna
         {
           if ($2.tipo != T_ENTERO && $2.tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           $$.tipo = $2.tipo; $$.ref = -1;
         }
         | MAS_ expreUna
         {
           if ($2.tipo != T_ENTERO && $2.tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           $$.tipo = $2.tipo; $$.ref = -1;
         }
         | NOT_ expreUna
         {
           if ($2.tipo != T_LOGICO && $2.tipo != T_ERROR)
             yyerror("Error en 'expresion unaria'");
           $$.tipo = T_LOGICO; $$.ref = -1;
         }
         ;

/* Expresiones sufijas */
expreSufi: const
          {
            $$.tipo = $1; 
            $$.ref = -1;
          }
          | AP_ expre CP_
          {
            $$.tipo = $2.tipo; 
            $$.ref = $2.ref;
          }
          | ID_
          {
            SIMB s = obtTdS($1);
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              $$.tipo = T_ERROR;
            } else {
              $$.tipo = s.t;
            }
            $$.ref = -1;
          }
          | ID_ ACOR_ expre CCOR_
          {
            SIMB s = obtTdS($1);
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              $$.tipo = T_ERROR; $$.ref = -1;
            } else {
              if (s.t != T_ARRAY && s.t!=T_ERROR)
                yyerror("La variable debe ser de tipo 'array'");
              checkIndiceArray($3.tipo);
              if (s.t == T_ARRAY) {
                DIM dim = obtTdA(s.ref);
                if (dim.telem == T_ERROR) {
                  yyerror("Error con el array");
                  $$.tipo = T_ERROR; 
                } else {
                  $$.tipo = dim.telem;
                }
              } else {
                $$.tipo = T_ERROR; 
              }
              $$.ref = -1;
            }
          }
          | ID_ AP_ paramAct CP_
          {
            SIMB s = obtTdS($1);
            if (s.t == T_ERROR) {
              yyerror("Objeto no declarado");
              $$.tipo = T_ERROR; $$.ref = -1;
            } else {
              INF info = obtTdD(s.ref);
              if (info.tipo == T_ERROR) {
                yyerror("Objeto no es funcion");
                $$.tipo = T_ERROR; $$.ref = -1;
              } else {
                if (!cmpDom($3, s.ref))
                  yyerror("Dominio de parametros actual no coincide con el formal");
                $$.tipo = info.tipo; $$.ref = -1;
              }
            }
          }
          ;

/* Parametros actuales */
paramAct:
         {
           $$ = insTdD(-1, T_VACIO);
         }
         | listParamAct { $$ = $1; }
         ;

/* Lista de parametros actuales */
listParamAct: expre
            {
              int refDom = insTdD(-1, $1.tipo);
              $$ = refDom;
            }
            | expre COMA_ listParamAct
            {
              int refDom = insTdD($3, $1.tipo);
              $$ = refDom;
            }
            ;

%%

/* Sin yyerror aquí. Definida en principal.c */

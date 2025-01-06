/*****************************************************************************/
/**  Analizador sintactico-semantico para MenosC (version adaptada).        **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include <header.h>
#include <libtds.h>
#include <libgci.h>
%}

/* Union de atributos que empleara el analizador sintactico:
   - lexId: para guardar identificadores
   - lexInt: para guardar constantes numericas
   - exprData, initInfo, loopCtl: estructuras definidas en header.h
     para manejar expresiones, informacion inicial y control de bucles for */
%union { 
    char* lexId;     
    int   lexInt;    
    EXP   exprData;  
    INICIO initInfo; 
    FORSTRUCT loopCtl;
}

/* Lista de tokens que el analizador lexico puede reconocer */
%token PARA_ PARC_ MAS_ MENOS_ POR_ DIV_
%token INT_ PUNTC_ IGUAL_ CORA_ CORC_
%token TRUE_ FALSE_ BOOL_ BRAA_ BRAC_ RETURN_
%token READ_ PRINT_ IF_ ELSE_ FOR_ COMA_
%token MAYOR_ MENOR_ MAYI_ MENI_ NOT_ AND_ 
%token OR_ EQUALS_ NOTEQUAL_ DOU_BAR_

/* Tokens con atributos:
   - CTE_ (lexInt) para constantes numericas,
   - ID_ (lexId) para identificadores */
%token<lexInt>  CTE_
%token<lexId>   ID_

/* Asociacion de no-terminales con tipos concretos del %union */
%type<lexInt>  tipoSimp opUna opMul opAd opRel opIgual opLogic
%type<lexInt>  paramForm listParamForm paramAct listParamAct
%type<lexInt>  listInt inst instExpre instSelec instEntSal
%type<lexInt>  listDecla declaVar declaFunc decla declaVarLocal bloque

%type<exprData> expreMul expreAd expreSufi expreUna expreLogic
%type<exprData> expre expreRel expreIgual expreOP constValue

%type<initInfo> programa
%type<loopCtl>  instIter

%%

/* ------------------------------------------------------------------------ */
/*  REGLA PRINCIPAL: programa                                                */
/*  Esta regla define la estructura global de un programa MenosC.           */
/* ------------------------------------------------------------------------ */
programa : 
  {
    /* Inicializa variables globales del compilador:
       dvar  => desplazamiento de variables
       niv   => nivel de anidamiento
       si    => contador de linea para el codigo intermedio */
    dvar = 0;
    niv  = 0;
    si   = 0;

    /* Crea el contexto de nivel global en la TdS */
    cargaContexto(niv);

    /* Reserva de espacio global: 
       1) Creamos una lista de instrucciones no satisfechas (creaLans).
       2) Emitimos instruccion INCTOP con argumento -1 que se completara mas tarde. */
    $<initInfo>$.inc_t = creaLans(si);
    emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));

    /* Preparamos un salto para llegar a la funcion main, aun no sabemos su direccion */
    $<initInfo>$.go_t = creaLans(si);
    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
  }
  listDecla
  {
    /* Al acabar la declaracion de funciones y variables, 
       verificamos que se haya declarado EXACTAMENTE una funcion main */
    if ($2 != 1) {
      yyerror("Se debe declarar exactamente una funcion 'main()'");
    }

    /* Completamos la instruccion INCTOP para reservar la cantidad de variables globales (dvar) */
    completaLans($<initInfo>1.inc_t, crArgEnt(dvar));

    /* Obtenemos el simbolo de 'main' y completamos el salto para que vaya a su direccion */
    SIMB mainSymbol = obtTdS("main");
    completaLans($<initInfo>1.go_t, crArgEnt(mainSymbol.d));
  }
  ;

/* ------------------------------------------------------------------------ */
/*  listDecla: permite una o varias declaraciones (variables o funciones)   */
/* ------------------------------------------------------------------------ */
listDecla : 
    decla
    {
      /* Guardamos la suma de los "marcadores" que indican
         si se declaro main en algun punto */
      $<lexInt>$ = $1;
    }
  | listDecla decla
    {
      /* Si la segunda parte es 1 cuando declara main, se suma */
      $$ = $1 + $2;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  decla: puede ser una declaracion de variable o de funcion.              */
/* ------------------------------------------------------------------------ */
decla :
    declaVar
    {
      /* Devuelve 0 si no es main */
      $<lexInt>$ = 0;
    }
  | declaFunc
    {
      /* declaFunc podria devolver 1 si es la funcion main */
      $$ = $1;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  declaVar: declara una variable: simple, con inicializacion, o array.    */
/* ------------------------------------------------------------------------ */
declaVar :
    /* (1) Variable tipo simple: "tipoSimp ID ;" */
    tipoSimp ID_ PUNTC_
    {
      /* Insertamos la variable en la TdS. 
         Si ya existe, error. Si no, sumamos la talla del tipo al desplazamiento */
      if (!insTdS($2, VARIABLE, $1, niv, dvar, -1)) {
        yyerror("Variable duplicada");
      }
      else {
        dvar += TALLA_TIPO_SIMPLE;
      }
    }
  | /* (2) Variable tipo simple con inicializacion: "tipoSimp ID = const ;" */
    tipoSimp ID_ IGUAL_ constValue PUNTC_
    {
      /* Verificamos que el tipo del valor coincida con el tipo declarado */
      if ($1 != $4.t) {
        yyerror("Inicializacion con tipo inconsistente");
      }
      /* Insertamos la variable en la TdS */
      if (!insTdS($2, VARIABLE, $1, niv, dvar, -1)) {
        yyerror("Variable duplicada");
      }
      else {
        /* Si no coinciden los tipos, marcamos error, pero igual emitimos instruccion */
        if ($1 != $4.t) {
          $$ = T_ERROR;
        }
        /* Emitimos la instruccion de asignacion de esa constante a la variable */
        emite(EASIG, crArgEnt($4.d), crArgNul(), crArgPos(niv, dvar));
        dvar += TALLA_TIPO_SIMPLE;
      }
    }
  | /* (3) Array: "tipoSimp ID [ CTE ] ;" */
    tipoSimp ID_ CORA_ CTE_ CORC_ PUNTC_
    {
      int cantElem = $4;
      /* Si la talla del array no es positiva, avisamos */
      if (cantElem <= 0) {
        yyerror("Tamano de array no valido");
        cantElem = 0;
      }
      /* Insertar la definicion del array en la Tabla de Arrays y la TdS */
      int arrRef = insTdA($1, cantElem);
      if (!insTdS($2, VARIABLE, T_ARRAY, niv, dvar, arrRef)) {
        yyerror("Variable duplicada");
      }
      else {
        dvar += cantElem * TALLA_TIPO_SIMPLE;
      }
    }
  ;

/* ------------------------------------------------------------------------ */
/*  constValue: define como tratar las constantes numericas, true o false   */
/* ------------------------------------------------------------------------ */
constValue :
    CTE_
    {
      $$.t = T_ENTERO;
      $$.d = $1; /* Guardamos el valor entero de la constante */
    }
  | TRUE_
    {
      $$.t = T_LOGICO;
      $$.d = 1; /* true es 1 */
    }
  | FALSE_
    {
      $$.t = T_LOGICO;
      $$.d = 0; /* false es 0 */
    }
  ;

/* ------------------------------------------------------------------------ */
/*  tipoSimp: tipos basicos (int, bool)                                     */
/* ------------------------------------------------------------------------ */
tipoSimp :
    INT_
    {
      $$ = T_ENTERO;
    }
  | BOOL_
    {
      $$ = T_LOGICO;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  declaFunc: declara una funcion con su firma (parametros) y su bloque    */
/* ------------------------------------------------------------------------ */
declaFunc : 
  tipoSimp ID_
  {
    /* Guardamos el desplazamiento actual para restaurarlo mas tarde.
       Ademas, preparamos dvar para que empiece en -2 (enlaces de control). */
    $<lexInt>$ = dvar;
    dvar = -TALLA_SEGENLACES;
    /* Subimos el nivel (estamos dentro de la funcion) y cargamos contexto */
    niv++;
    cargaContexto(niv);
  }
  PARA_               /* parentesis de apertura */
  paramForm           /* parametros formales */
  PARC_               /* parentesis de cierre */
  {
    /* Una vez procesados los parametros, ponemos dvar = 0 para variables locales */
    dvar = 0;
    /* Insertamos la funcion en la TdS (nivel 0, si = si actual) */
    if(!insTdS($2, FUNCION, $1, 0, si, $5)) {
      yyerror("Funcion duplicada");
    }
  }
  bloque
  {
    /* Si no se detecto error antes, pero la comprobacion dice que es T_ERROR => forzamos error */
    if($1 != T_ERROR) {
      $$ = T_ERROR;
    }
    /* Verificamos que el tipo de retorno sea el mismo que se declaro para la funcion */
    else if ($1 != $8) {
      yyerror("Tipo de retorno inadecuado");
    }
    /* Recuperamos el desplazamiento que teniamos antes de la declaracion de la funcion */
    dvar = $<lexInt>3;
    /* Mostramos la tabla de simbolos, descargamos contexto y bajamos nivel */
    mostrarTdS();
    descargaContexto(niv);
    niv--;

    /* Si la funcion se llama 'main', devolvemos 1 para indicar que existe main */
    if(strcmp($2,"main") == 0) {
      $<lexInt>$ = 1;
    } else {
      $<lexInt>$ = 0;
    }
  }
  ;

/* ------------------------------------------------------------------------ */
/*  paramForm: Parametros formales de la funcion (puede haber 0 o varios)   */
/* ------------------------------------------------------------------------ */
paramForm :
    {
      /* Sin parametros => se crea un dominio vacio */
      $$ = insTdD(-1, T_VACIO);
    }
  | listParamForm
    {
      $$ = $1;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  listParamForm: declaracion de uno o mas parametros formales             */
/* ------------------------------------------------------------------------ */
listParamForm:
    /* Un solo parametro: "tipoSimp ID" */
    tipoSimp ID_
    {
      /* Insertamos un PARAMETRO en la TdS, con desplazamiento decreciente */
      insTdS($2, PARAMETRO, $1, niv, --dvar, -1);
      /* Insertamos en la tabla de dominios paramForm */
      $$ = insTdD(-1, $1);
    }
  | /* Varios parametros: "tipoSimp ID , listParamForm" */
    tipoSimp ID_ COMA_ listParamForm
    {
      /* Insertar el parametro en la tabla de dominios */
      insTdD($4, $1);
      /* Insertar el parametro en la TdS con desplazamiento decrementado */
      int okParam = insTdS($2, PARAMETRO, $1, niv, --dvar, -1);
      if (!okParam) {
        yyerror("Parametro repetido");
      }
      $$ = $4;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  bloque: cuerpo de la funcion, incluye declaraciones locales e insts     */
/* ------------------------------------------------------------------------ */
bloque :
  {
    /* 1) Emitimos PUSHFP y FPTOP para apilar el Frame Pointer
       2) Creamos una lista no satisfecha para INCTOP con -1,
          reservando espacio para variables locales */
    emite(PUSHFP, crArgNul(), crArgNul(), crArgNul());
    emite(FPTOP, crArgNul(), crArgNul(), crArgNul());
    $<lexInt>$ = creaLans(si);
    emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));
  }
  BRAA_ declaVarLocal listInt RETURN_ expre PUNTC_ BRAC_
  {
    /* Al salir del bloque, recuperamos info de la funcion actual (obtdTdD) */
    INF funcData = obtTdD(-1);
    /* retAddr => lugar donde guardar el valor de retorno en la pila */
    int retAddr = TALLA_SEGENLACES + funcData.tsp + TALLA_TIPO_SIMPLE;

    /* Completamos la instruccion INCTOP con dvar, la cantidad de espacio local */
    completaLans($<lexInt>1, crArgEnt(dvar));

    /* Movemos el valor del return (expre) a la posicion -retAddr en la pila */
    emite(EASIG, crArgPos(niv, $6.d), crArgNul(), crArgPos(niv, -retAddr));

    /* Restauramos el puntero de marco */
    emite(TOPFP, crArgNul(), crArgNul(), crArgNul());
    emite(FPPOP, crArgNul(), crArgNul(), crArgNul());

    /* Si el tipo de la funcion no era T_ERROR, verificamos coincidencia con la expre retornada */
    if (funcData.tipo != T_ERROR) {
      if (funcData.tipo != $6.t) {
        yyerror("El tipo devuelto no coincide con la funcion");
      }
    }

    /* Si la funcion se llama main, emitimos FIN, de lo contrario RET */
    if (strcmp(funcData.nom, "main") == 0) {
      emite(FIN, crArgNul(), crArgNul(), crArgNul());
    } else {
      emite(RET, crArgNul(), crArgNul(), crArgNul());
    }
    /* Devolvemos el desplazamiento del resultado para usos posteriores */
    $<lexInt>$ = $6.d;
  }
  ;

/* ------------------------------------------------------------------------ */
/*  declaVarLocal: permite tener 0 o mas declaraciones locales              */
/* ------------------------------------------------------------------------ */
declaVarLocal :
    /* vacio */
  | declaVarLocal declaVar
  ;

/* ------------------------------------------------------------------------ */
/*  listInt: secuencia de instrucciones, puede estar vacia                  */
/* ------------------------------------------------------------------------ */
listInt :
    /* vacio */
  | listInt inst
  ;

/* ------------------------------------------------------------------------ */
/*  inst: una instruccion (compuesta, expresion, E/S, if, for)              */
/* ------------------------------------------------------------------------ */
inst :
    BRAA_ listInt BRAC_
  | instExpre
  | instEntSal
  | instSelec
  | instIter
  ;

/* ------------------------------------------------------------------------ */
/*  instExpre: una instruccion que es simplemente una expresion o ";"       */
/* ------------------------------------------------------------------------ */
instExpre :
    expre PUNTC_
    {
      /* Devolvemos el tipo de la expresion */
      $$ = $1.t;
    }
  | PUNTC_
  ;

/* ------------------------------------------------------------------------ */
/*  instEntSal: instrucciones de E/S: read(x) o print(expr)                 */
/* ------------------------------------------------------------------------ */
instEntSal :
    /* read(x); */
    READ_ PARA_ ID_ PARC_ PUNTC_
    {
      SIMB readSimb = obtTdS($3);
      /* Verificamos que x exista y sea entero */
      if (readSimb.t == T_ERROR) {
        $$ = T_ERROR;
      }
      else if (readSimb.t != T_ENTERO) {
        yyerror("El argumento de 'read' debe ser entero");
        $$ = T_ERROR;
      }
      /* Emitimos instruccion EREAD, guardando el valor en la posicion de x */
      emite(EREAD, crArgNul(), crArgNul(), crArgPos(readSimb.n, readSimb.d));
    }
  | /* print(expr); */
    PRINT_ PARA_ expre PARC_ PUNTC_
    {
      /* Solo imprime expresiones enteras */
      if ($3.t == T_ERROR) {
        $$ = T_ERROR;
      }
      if ($3.t != T_ENTERO) {
        yyerror("El argumento de 'print' debe ser entero");
        $$ = T_ERROR;
      }
      emite(EWRITE, crArgNul(), crArgNul(), crArgPos(niv, $3.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  instSelec: if (expresion logica) instruccion [else instruccion]         */
/* ------------------------------------------------------------------------ */
instSelec : 
  IF_ PARA_ expre PARC_
  {
    /* Verificamos que la expre sea de tipo logico */
    if($3.t == T_ERROR) {
      $<lexInt>$ = T_ERROR;
    }
    else if ($3.t != T_LOGICO) {
      yyerror("La condicion del 'if' debe ser logica");
    }
    /* Creamos una lista no satisfecha para el salto si la condicion es falsa */
    $<lexInt>$ = creaLans(si);
    emite(EIGUAL, crArgPos(niv, $3.d), crArgEnt(0), crArgEtq(-1));
  }
  inst
  {
    /* Creamos otra lista para el salto incondicional al final del if */
    $<lexInt>$ = creaLans(si);
    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
    /* Completamos el salto de la lista anterior (condicion falsa) para que vaya aqui */
    completaLans($<lexInt>5, crArgEtq(si));
  }
  ELSE_
  inst
  {
    /* Completamos el salto incondicional del if para saltar al final del else */
    completaLans($<lexInt>7, crArgEnt(si));
  }
  ;

/* ------------------------------------------------------------------------ */
/*  instIter: for con 3 expresiones (o menos)                                */
/* ------------------------------------------------------------------------ */
instIter :
  FOR_ PARA_ expreOP PUNTC_
  {
    /* Primera expresion del for (puede ser T_ENTERO, T_LOGICO o vacio) */
    if (!($3.t == T_ERROR || $3.t == T_ENTERO || $3.t == T_VACIO || $3.t == T_LOGICO)) {
      yyerror("La expresion inicial del for debe ser simple");
      $<lexInt>$ = T_ERROR;
    }
    /* Guardamos en $<lexInt>$ la linea actual para volver despues */
    $<lexInt>$ = si;
  }
  expre PUNTC_
  {
    /* Segunda expresion del for debe ser logica */
    if (!($6.t == T_LOGICO)) {
      yyerror("La segunda expresion del for debe ser logica");
      $<loopCtl>$.verdad = -1;
      $<lexInt>$ = T_ERROR;
    }
    /* Creamos la lista para cuando la condicion sea verdadera y cuando sea falsa */
    $<loopCtl>$.verdad = creaLans(si);
    emite(EIGUAL, crArgPos(niv, $6.d), crArgEnt(1), crArgEtq(-1));

    $<loopCtl>$.falso = creaLans(si);
    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));

    /* Guardamos la direccion de la siguiente instruccion */
    $<loopCtl>$.ant_si = si;
  }
  expreOP PARC_
  {
    /* Al acabar la tercera expresion, volvemos al principio (al $<lexInt>5) */
    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq($<lexInt>5));
    /* Completamos la lista "verdad" para que continue aqui */
    completaLans($<loopCtl>8.verdad, crArgEnt(si));
  }
  inst
  {
    /* Despues del cuerpo, saltamos de nuevo a la instruccion del "tercer" campo del for */
    if (!($9.t == T_ERROR || $9.t == T_ENTERO || $9.t == T_VACIO || $9.t == T_LOGICO)) {
      yyerror("La expresion final del for debe ser simple");
      $<lexInt>$ = T_ERROR;
    }
    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq($<loopCtl>8.ant_si));
    /* Completamos la lista "falso" para que vaya al final del for */
    completaLans($<loopCtl>8.falso, crArgEnt(si));
  }
  ;

/* ------------------------------------------------------------------------ */
/*  expreOP: expresion opcional en el for (puede estar vacia)               */
/* ------------------------------------------------------------------------ */
expreOP :
    {
      $$.t = T_VACIO; /* Vacio */
    }
  | expre
    {
      /* Si no es vacio, entonces la expresion debe ser ENTERO o LOGICO */
      $$ = $1;
      if (!($1.t == T_ENTERO || $1.t == T_LOGICO)) {
        yyerror("La expreOP del for debe ser simple");
        $$.t = T_ERROR;
      }
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expre: representa asignaciones o expresiones logicas/arithmetic.        */
/* ------------------------------------------------------------------------ */
expre :
    /* Simplemente una expreLogic */
    expreLogic
    {
      $$ = $1;
    }
  | /* Asignacion: ID = expre */
    ID_ IGUAL_ expre
    {
      SIMB varSym = obtTdS($1);
      $$.t = T_ERROR;
      /* Solo si la expresion no es error */
      if($3.t != T_ERROR) {
        if (varSym.t == T_ERROR) {
          yyerror("Variable no declarada");
        } 
        else if (varSym.t == T_ARRAY) {
          yyerror("No se puede asignar directamente a un array");
        }
        else if (!(((varSym.t == T_LOGICO) && ($3.t == T_LOGICO)) 
                || ((varSym.t == T_ENTERO) && ($3.t == T_ENTERO)))) {
          yyerror("Asignacion con tipos incompatibles");
        } else {
          $$.t = $3.t;
        }
      }
      $$.d = $3.d;
      /* Emitimos la asignacion en codigo intermedio */
      emite(EASIG, crArgPos(niv, $3.d), crArgNul(), crArgPos(varSym.n, varSym.d));
    }
  | /* Asignacion en array: ID [ expre ] = expre */
    ID_ CORA_ expre CORC_ IGUAL_ expre
    {
      SIMB arraySym = obtTdS($1);
      /* La posicion debe ser ENTERO */
      if ($3.t != T_ENTERO) {
        yyerror("El indice del array debe ser entero");
      }
      else if (arraySym.t != T_ARRAY) {
        yyerror("Se requiere un array en la indexacion");
      } else {
        /* Verificamos la consistencia de tipos */
        DIM arrayDim = obtTdA(arraySym.ref);
        int elemType = arrayDim.telem;
        if (elemType != T_ERROR && $3.t != T_ERROR && $6.t != T_ERROR) {
          /* Verificamos que elemento y valor a asignar coincidan en tipo */
          if (!(((elemType == T_ENTERO) && ($6.t == T_ENTERO)) ||
                ((elemType == T_LOGICO) && ($6.t == T_LOGICO)))) {
            $$.t = T_ERROR;
            yyerror("Asignacion en array con tipos incompatibles");
          } else {
            $$.t = T_ARRAY;
          }
        } else {
          $$.t = T_ERROR;
        }
      }
      $$.d = $6.d;
      /* Emitimos la instruccion EVA (arraySym[expre] = expre) */
      emite(EVA, crArgPos(arraySym.n, arraySym.d),
                  crArgPos(niv, $3.d),
                  crArgPos(niv, $6.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreLogic: maneja operaciones logicas && y ||, apoyandose en expreIgual */
/* ------------------------------------------------------------------------ */
expreLogic :
    expreIgual
    {
      $$ = $1;
    }
  | expreLogic opLogic expreIgual
    {
      $$.t = T_ERROR;
      /* Deben ser ambos de tipo logico */
      if($1.t != T_ERROR && $3.t != T_ERROR) {
        if($1.t != T_LOGICO || $3.t != T_LOGICO) {
          yyerror("Tipos no validos en operador logico");
        } else if ($1.t == T_ARRAY) {
          yyerror("Operadores logicos no aplican a arrays");
        } else {
          $$.t = T_LOGICO;
        }
      }
      $$.d = creaVarTemp();
      /* EMULT => AND, ESUM => OR */
      if ($2 == EMULT) {
        emite(EMULT, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgPos(niv, $$.d));
      } else {
        emite(ESUM, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgPos(niv, $$.d));
        /* Truco para convertir el resultado en booleano: si es > 1 => 1 */
        emite(EMEN, crArgPos(niv, $$.d), crArgEnt(1), crArgEtq(si + 2));
        emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.d));
      }
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreIgual: manejo de == y !=                                           */
/* ------------------------------------------------------------------------ */
expreIgual :
    expreRel
    {
      $$ = $1;
    }
  | expreIgual opIgual expreRel
    {
      $$.t = T_ERROR;
      /* Requiere que ambos sean del mismo tipo y no sean arrays */
      if($1.t != T_ERROR && $3.t != T_ERROR) {
        if($1.t != $3.t) {
          yyerror("Comparacion de igualdad con tipos distintos");
        } else if ($1.t == T_ARRAY) {
          yyerror("No se comparan arrays con == o !=");
        } else {
          $$.t = T_LOGICO;
        }
      }
      $$.d = creaVarTemp();
      /* Inicialmente, asumimos 'true' */
      emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.d));
      /* Si la condicion no se cumple, saltara a la siguiente instruccion y pondra 0 */
      emite($2, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgEtq(si + 2));
      emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, $$.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreRel: manejo de <, >, <=, >= entre expreAd (enteras)                */
/* ------------------------------------------------------------------------ */
expreRel :
    expreAd
    {
      $$ = $1;
    }
  | expreRel opRel expreAd
    {
      $$.t = T_ERROR;
      if($1.t != T_ERROR && $3.t != T_ERROR) {
        if ($1.t != $3.t) {
          yyerror("Operadores relacionales con tipos diferentes");
        } else if ($1.t == T_LOGICO) {
          yyerror("Operadores relacionales no aplican a booleanos");
        } else {
          $$.t = T_LOGICO;
        }
      }
      $$.d = creaVarTemp();
      /* Inicialmente asumimos 'true' */
      emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.d));
      /* Si no se cumple, pondra 0 */
      emite($2, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgEtq(si + 2));
      emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, $$.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreAd: suma y resta (+ y -) entre expreMul                            */
/* ------------------------------------------------------------------------ */
expreAd :
    expreMul
    {
      $$ = $1;
    }
  | expreAd opAd expreMul
    {
      $$.t = T_ERROR;
      /* Ambos deben ser enteros */
      if($1.t != T_ERROR && $3.t != T_ERROR) {
        if($1.t != T_ENTERO || $3.t != T_ENTERO) {
          yyerror("Suma o resta no entera");
        } else {
          $$.t = T_ENTERO;
        }
      }
      $$.d = creaVarTemp();
      /* Emitimos la instruccion (ESUM o EDIF) */
      emite($2, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgPos(niv, $$.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreMul: multiplicacion y division (* y /) entre expreUna              */
/* ------------------------------------------------------------------------ */
expreMul :
    expreUna
    {
      $$ = $1;
    }
  | expreMul opMul expreUna
    {
      $$.t = T_ERROR;
      /* Ambos deben ser enteros */
      if($1.t != T_ERROR && $3.t != T_ERROR) {
        if($1.t != T_ENTERO || $3.t != T_ENTERO) {
          yyerror("Multiplicacion o division no entera");
        } else {
          $$.t = T_ENTERO;
        }
      }
      $$.d = creaVarTemp();
      emite($2, crArgPos(niv, $1.d), crArgPos(niv, $3.d), crArgPos(niv, $$.d));
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreUna: operadores unarios (+, -, !) sobre expreSufi                 */
/* ------------------------------------------------------------------------ */
expreUna :
    expreSufi
    {
      $$ = $1;
    }
  | opUna expreUna
    {
      $$.t = T_ERROR;
      /* opUna: 0 => +, 1 => -, 2 => ! */
      if($2.t != T_ERROR) {
        if($2.t == T_ENTERO) {
          /* No se puede aplicar '!' a enteros */
          if($1 == 2) {
            yyerror("Operador '!' no aplica a enteros");
          } else {
            $$.t = T_ENTERO;
          }
        }
        else if ($2.t == T_LOGICO) {
          /* No se puede aplicar + o - a booleanos */
          if($1 == 2) {
            $$.t = T_LOGICO;
          } else {
            yyerror("Operador '+' o '-' no aplican a booleanos");
          }
        }
      }
      $$.d = creaVarTemp();
      if ($1 == 0) {
        /* + expr => no cambia nada */
      }
      else if ($1 == 1) {
        /* - expr => cambia el signo */
        emite(ESIG, crArgPos(niv, $2.d), crArgNul(), crArgPos(niv, $$.d));
      }
      else {
        /* ! expr => 1 - expr */
        emite(EDIF, crArgEnt(1), crArgPos(niv, $2.d), crArgPos(niv, $$.d));
      }
    }
  ;

/* ------------------------------------------------------------------------ */
/*  expreSufi: constantes, (expr), ID, ID[expr], o llamada a funcion ID()    */
/* ------------------------------------------------------------------------ */
expreSufi :
    /* Una constante */
    constValue
    {
      $$.t = $1.t;
      /* Creamos una variable temporal para guardar la constante */
      $$.d = creaVarTemp();
      emite(EASIG, crArgEnt($1.d), crArgNul(), crArgPos(niv, $$.d));
    }
  | /* (expre) => solo reenviamos $$ = $2 */
    PARA_ expre PARC_
    {
      $$ = $2;
    }
  | /* ID => variable */
    ID_
    {
      SIMB tmpSymb = obtTdS($1);
      $$.t = T_ERROR;
      if(tmpSymb.t == T_ERROR) {
        yyerror("Variable no declarada");
      } else if (tmpSymb.t != T_ARRAY) {
        $$.t = tmpSymb.t;
      }
      /* Creamos una temporal y asignamos su contenido */
      $$.d = creaVarTemp();
      emite(EASIG, crArgPos(tmpSymb.n, tmpSymb.d), crArgNul(), crArgPos(niv, $$.d));
    }
  | /* ID[expre] => acceso a elemento de un array */
    ID_ CORA_ expre CORC_
    {
      SIMB tmpArr = obtTdS($1);
      $$.t = T_ERROR;
      if($3.t != T_ENTERO) {
        yyerror("Indice debe ser entero");
      }
      if(tmpArr.t == T_ARRAY) {
        DIM arrDim = obtTdA(tmpArr.ref);
        $$.t = arrDim.telem;
      } else {
        yyerror("Se esperaba un array");
      }
      /* Creamos la temporal y emitimos EAV => varTemporal = array[indice] */
      $$.d = creaVarTemp();
      emite(EAV, crArgPos(tmpArr.n, tmpArr.d),
                  crArgPos(niv, $3.d),
                  crArgPos(niv, $$.d));
    }
  | /* ID(...) => llamada a funcion. 
       Aqui se muestra un truco: emite(INCTOP, ...) justo antes, 
       luego paramAct, etc. */
    ID_
    {
      emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(1));
    }
    PARA_ paramAct PARC_
    {
      SIMB callSym = obtTdS($1);
      INF callInfo = obtTdD(callSym.ref);
      $$.t = T_ERROR;
      /* Verificamos que la funcion exista y no sea T_ERROR */
      if(callSym.t == T_ERROR) {
        yyerror("La funcion llamada es erronea");
      }
      else if(callInfo.tipo == T_ERROR) {
        yyerror("La referencia de la funcion es erronea");
      }
      else {
        /* Comprobamos que los parametros sean correctos (cmpDom) */
        if(!cmpDom(callSym.ref, $4)) {
          yyerror("Los parametros de la llamada no coinciden");
        } else {
          /* Tipo de la funcion */
          $$.t = callInfo.tipo;
          /* Generamos la llamada: CALL y luego DECTOP para desapilar args */
          emite(CALL, crArgNul(), crArgNul(), crArgEtq(callSym.d));
          emite(DECTOP, crArgNul(), crArgNul(), crArgEnt(callInfo.tsp));
          /* Creamos una temporal para recibir el valor de retorno (EPOP) */
          $$.d = creaVarTemp();
          emite(EPOP, crArgNul(), crArgNul(), crArgPos(niv, $$.d));
        }
      }
    }
  ;

/* ------------------------------------------------------------------------ */
/*  paramAct: lista de parametros actuales (argumentos) o vacia            */
/* ------------------------------------------------------------------------ */
paramAct :
    {
      /* Sin argumentos => dominio vacio */
      $$ = insTdD(-1, T_VACIO);
    }
  | listParamAct
    {
      $$ = $1;
    }
  ;

/* ------------------------------------------------------------------------ */
/*  listParamAct: uno o varios argumentos expre, separados por comas        */
/* ------------------------------------------------------------------------ */
listParamAct :
    expre
    {
      /* Insertamos el tipo de la expresion en la tabla de dominios */
      $$ = insTdD(-1, $1.t);
      /* Emitimos EPUSH para apilar el valor de la expresion */
      emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, $1.d));
    }
  | expre
    {
      /* Caso particular: se vuelve a apilar, luego se unira con COMA_ */
      emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, $1.d));
    }
    COMA_ listParamAct
    {
      /* El primer argumento se inserta con su tipo en la lista, 
         luego se combinan con la listaParamAct final */
      $$ = insTdD($4, $1.t);
    }
  ;

/* ------------------------------------------------------------------------ */
/*  opLogic, opIgual, opRel, opAd, opMul, opUna: correspondencias de tokens */
/*  con codigos de operacion en 3-direcciones (p. ej., ESUM, EDIF, etc.).    */
/* ------------------------------------------------------------------------ */
opLogic : 
    AND_ { $$ = EMULT; }
  | OR_  { $$ = ESUM; }
  ;

opIgual :
    EQUALS_   { $$ = EIGUAL; }
  | NOTEQUAL_ { $$ = EDIST; }
  ;

opRel :
    MAYOR_ { $$ = EMAY; }
  | MENOR_ { $$ = EMEN; }
  | MAYI_  { $$ = EMAYEQ; }
  | MENI_  { $$ = EMENEQ; }
  ;

opAd :
    MAS_   { $$ = ESUM; }
  | MENOS_ { $$ = EDIF; }
  ;

opMul :
    POR_ { $$ = EMULT; }
  | DIV_ { $$ = EDIVI; }
  ;

/* opUna traduce los tokens:
   MAS => 0 (unario +),
   MENOS => 1 (unario -),
   NOT => 2 (!). */
opUna :
    MAS_   { $$ = 0; }
  | MENOS_ { $$ = 1; }
  | NOT_   { $$ = 2; }
  ;

%%
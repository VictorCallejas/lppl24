%{
    #include <stdio.h>
    #include <string.h>
    #include "header.h"
    #include "asin.h"
%}

%union {
    char *ident;
    int cent;
}

%token INT_ BOOL_ IF_ ELSE_ FOR_ RETURN_ READ_ PRINT_ TRUE_ FALSE_
%token IGUALDAD_ DISTINTO_ MAYORIGUAL_ MENORIGUAL_ AND_ OR_
%token MAS_ MENOS_ POR_ DIV_ NOT_ ASIG_ MAYOR_ MENOR_
%token AP_ CP_ ALLAVE_ CLLAVE_ ACOR_ CCOR_ PCOMA_ COMA_
%token ID_ CTE_

%type <ident> ID_
%type <cent> CTE_

%%

programa: listDecla
        ;

listDecla:
          | listDecla decla
        ;

decla: declaVar
     | declaFunc
     ;

declaVar: tipoSimp ID_ PCOMA_
        | tipoSimp ID_ ASIG_ const PCOMA_
        | tipoSimp ID_ ACOR_ CTE_ CCOR_ PCOMA_
        ;

const: CTE_
     | TRUE_
     | FALSE_
     ;

tipoSimp: INT_
        | BOOL_
        ;

declaFunc: tipoSimp ID_ AP_ paramForm CP_ bloque
         ;

paramForm:
          | listParamForm
         ;

listParamForm: tipoSimp ID_
             | tipoSimp ID_ COMA_ listParamForm
             ;

bloque: ALLAVE_ declaVarLocal listInst RETURN_ expre PCOMA_ CLLAVE_
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

instExpre: expre PCOMA_
         | PCOMA_
         ;

instEntSal: READ_ AP_ ID_ CP_ PCOMA_
          | PRINT_ AP_ expre CP_ PCOMA_
          ;

instSelec: IF_ AP_ expre CP_ inst ELSE_ inst
         ;

instIter: FOR_ AP_ expreOP PCOMA_ expre PCOMA_ expreOP CP_ inst
        ;

expreOP:
        | expre
        ;

expre: expreLogic
     | ID_ ASIG_ expre
     | ID_ ACOR_ expre CCOR_ ASIG_ expre
     ;

expreLogic: expreIgual
          | expreLogic opLogic expreIgual
          ;

expreIgual: expreRel
          | expreIgual opIgual expreRel
          ;

expreRel: expreAd
        | expreRel opRel expreAd
        ;

expreAd: expreMul
       | expreAd opAd expreMul
       ;

expreMul: expreUna
        | expreMul opMul expreUna
        ;

expreUna: expreSufi
        | opUna expreUna
        ;

expreSufi: const
         | AP_ expre CP_
         | ID_
         | ID_ ACOR_ expre CCOR_
         | ID_ AP_ paramAct CP_
         ;

paramAct:
         | listParamAct
         ;

listParamAct: expre
            | expre COMA_ listParamAct
            ;

opLogic: AND_
       | OR_
       ;

opIgual: IGUALDAD_
       | DISTINTO_
       ;

opRel: MAYOR_
     | MENOR_
     | MAYORIGUAL_
     | MENORIGUAL_
     ;

opAd: MAS_
    | MENOS_
    ;

opMul: POR_
     | DIV_
     ;

opUna: MAS_
     | MENOS_
     | NOT_
     ;

%%
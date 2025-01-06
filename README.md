1. Extender el Analizador Lexico (alex.l)
Objetivo: Reconocer las nuevas palabras o simbolos relacionados con la instruccion.

lex
Copy code
/* 1) Incluir en las palabras reservadas o seccion de patrones */
"using"        { retornar(USING_); }
"times"        { retornar(TIMES_); }
"do"           { retornar(DO_); }

/* 2) Verificar que no exista un choque con otros tokens:
   - no usar la misma palabra para un token ya existente
   - si es necesario, introducir mas definiciones */
Comentarios:

Declaracion: Se anade la palabra en la seccion de patrones.
Retorno: Se crea un token (por ejemplo, USING_) para cada palabra.
Chequeos: Revisar que no coincidan con otras palabras reservadas (por ejemplo, "use").
2. Declarar los Tokens en el Parser (asin.y)
Objetivo: Permitir que Bison conozca USING_, TIMES_, DO_.

bison
Copy code
%token USING_ TIMES_ DO_
Comentarios:

Sintaxis: Asi Bison sabra que esos tokens existen.
Tipado: Normalmente no llevan valor semantico (son palabras reservadas).
3. Agregar la Regla Sintactica
Objetivo: Incluir en el no-terminal de instrucciones (inst, por ejemplo) la nueva construccion.

bison
Copy code
/* Asumimos que "inst" es donde van las instrucciones del lenguaje */
inst
  : ...
  | instruccionUsing
  ;

/* La regla que define la nueva instruccion */
instruccionUsing
  : USING_ ID_ expre TIMES_ DO_ inst
    {
      /* Aqui iran las acciones semanticas */
      ...
    }
  ;
Comentarios:

Produccion: Se define instruccionUsing que usa USING_, un ID_, una expre, el token TIMES_, el token DO_, y finalmente otra instruccion inst.
Orden: Asegurarse de que coincide con la sintaxis propuesta en el enunciado.
4. Semantica I: Comprobaciones de Tipos (Acciones Semanticas)
Objetivo: Comprobar que las partes de la instruccion cumplen con la semantica (ej. variable entera, expresion entera).

bison
Copy code
instruccionUsing
  : USING_ ID_ expre TIMES_ DO_ inst
    {
      /* 1) Declaracion: Obtener la info del ID en la Tabla de Simbolos */
      SIMB simbVar = obtTdS($2);
      if (simbVar.t == T_ERROR) {
        yyerror("La variable de 'using' no esta declarada");
      } else if (simbVar.t != T_ENTERO) {
        yyerror("La variable en 'using' debe ser de tipo entero");
      }

      /* 2) Comprobar que la expresion sea entera */
      if ($3.t != T_ENTERO && $3.t != T_ERROR) {
        yyerror("La expresion del 'using' debe ser entera");
      }

      /* 3) Revisar la instruccion $6, por si tu lenguaje requiere algo extra 
         (generalmente no es necesario si 'inst' ya se comprueba por si sola). */

      /* 4) Si todo va bien, preparar datos para generacion de codigo */
      $$.t = T_VACIO;  /* o el tipo que manejes para las instrucciones */
      ...
    }
;
Comentarios:

Paso 1: Declaracion -> invocar obtTdS($2) para ver si la variable existe y es entera.
Paso 2: Comprobar que $3 es la expresion, su tipo t debe ser entero.
Paso 3: Instruccion en $6 (ya se comprueba dentro de inst).
Paso 4: Si OK, guardamos atributos para el paso de generacion de codigo.
5. Semantica II: Generar Codigo Intermedio
Objetivo: Transformar la nueva instruccion a una secuencia de codigo 3-direcciones.

Ejemplo generico: Suponiendo que using x E times do S; se traduce en:

c
Copy code
x = 1;
while (x <= E) {
  S;
  x = x + 1;
}
El pseudo-codigo para 3-direcciones podria ser:

bison
Copy code
{
  /* 1) Asignar x = 1 */
  emite(EASIG,
        crArgEnt(1),   /* arg1: 1 */
        crArgNul(),    /* arg2: vacio */
        crArgPos(simbVar.n, simbVar.d) /* destino: variable x */);

  /* 2) Crear etiqueta de inicio de bucle */
  int etqInicio = si;

  /* 3) Comparar x <= E => saltar si falso */
  int listaFallo = creaLans(si);
  emite(EMENEQ,
        crArgPos(simbVar.n, simbVar.d),
        crArgPos(niv, $3.d),
        crArgEtq(-1) /* salto si no se cumple */);

  /* 4) Emitir el codigo de la instruccion $6 (S).
     Normalmente, $6 ya tiene su generacion de codigo hecha.
     Solo asegurate de que se ejecute antes de incrementar x. */

  /* 5) Instruccion x = x + 1 */
  emite(ESUM,
        crArgPos(simbVar.n, simbVar.d),
        crArgEnt(1),
        crArgPos(simbVar.n, simbVar.d));

  /* 6) Salto incondicional a etqInicio */
  emite(GOTOS,
        crArgNul(),
        crArgNul(),
        crArgEtq(etqInicio));

  /* 7) Completar la listaFallo con la etiqueta actual => fin del bucle */
  completaLans(listaFallo, crArgEnt(si));
}
Comentarios:

emite: funciones para emitir codigo 3D.
crArgPos, crArgEnt: crean argumentos de tipo posicion (nivel, desplazamiento) o entero.
EMENEQ: compara <=, ESUM suma, etc. Ajustar a tu libreria.
6. Probar con un Fichero de Ejemplo
Objetivo: Comprobar que todo funciona.

prueba.c:
c
Copy code
int main() {
  using i 5 times do {
    print(i);
  }
  return 0;
}
Compilar, ver la tabla de simbolos, el codigo intermedio.
Ejecutar en la maquina virtual (mvm, etc.) para verificar que imprime 1 2 3 4 5.
Resumen Final
Lexico: anade las nuevas palabras a tu fichero alex.l.
Parser: declara los tokens, anade la regla en asin.y.
Semantica:
Comprobaciones de tipos y declaraciones en la accion de la regla (verificar ID_ y expre).
Si error, yyerror(...).
Codigo Intermedio:
Equivalencia con un patron (ej. un while).
Emitir secuencia de asignaciones, comparaciones, saltos.
Probar con un ejemplo y revisar que la salida sea la esperada.

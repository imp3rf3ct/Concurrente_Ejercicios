Practica 2 Programacion Concurrente y en Tiempo Real
====================================================

En cada ejercicio encontraras 5 tipos de directorios segun se necesite o no:

data/ :
En el se encuentran los archivos necesarios para testear los archivos "exec"

exec/ :
En el se encuentran los archivos compilados de la practica 1

obj/  :
En el se encuentran los archivos objeto de la practica 1

src/ :
En el se encuentran los archivos codigo fuente de la practica 1

include/ :
En el se encuentran los archivos de cabecera que incluyen funciones necesarias para el funcionamiento del programa

EJERCICIO 1
---------
Creacion de procesos Decoder para decodificar una cadena introducida por la linea de argumentos y cuando haya un simbolo especial llamar al sym_decoder:`./manager <cadena> <nºdecoder> <tam max tarea>`

`MANAGER - Crea los procesos y los gestiona`

`DECODER - Decodifica la cadena e invoca al proceso:`
          `SYM_DECODER - Si es necesario traducir algun caracter especial`

EJERCICIO 2
---------
Creacion de procesos Factorer para factorizar un numerador y un denominador dado por la linea de argumentos: `./manager <numerador> <denominador>`

`MANAGER - Crea los procesos y los gestiona`

`FACTORER - Factoriza los numeros dados y simplifica el resultado`

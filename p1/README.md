Practica 1 Programacion Concurrente y en Tiempo Real
====================================================

En cada ejercicio encontraras 5 tipos de directorios:

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
Creacion de procesos simple con acto de espera a su finalización: `./manager <nºPA> <nºPB> <TimeMax>`
  
  `MANAGER - Crea los procesos y los gestiona`
  
  `PA - Duerme x segundos y termina`
  
  `PB - Duerme x segundos en bucle`

EJERCICIO 2
--------
Creacion de procesos simple con varios actos: `./manager <archivo> <patrón>`
  
  `MANAGER - Crea los procesos y los gestiona`
  
  `CONTADOR - Cuenta las palabras que tiene cada linea del archivo (1 Proceso contador por linea)`
  
  `PROCESADOR - Busca un patrón en la linea del archivo (1 Proceso procesador por linea)`
  
EJERCICIO 3
--------
Creacion de procesos con condicion de carrera (al no estar en sincronizacion): `./manager <Filepath> <nºproc>`

  `MANAGER - Crea los procesos y los gestiona`
  
  `SUMADOR - Suma una unidad al entero que contiene el archivo`
  
  `RESTADOR - Resta una unidad al entero que contiene el archivo`
  

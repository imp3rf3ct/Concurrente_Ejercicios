EJERCICIO 3
==========

Construya, utilizando ANSI C estándar, un sistema compuesto por tres ejecutables que
simule el funcionamiento que se detalla a continuación. El sistema contará con tres tipos de
procesos: i) manager, ii) SUMADOR y iii) RESTADOR. Además de llevar a cabo la
implementación del sistema, reflexione sobre las cuestiones que se plantean al final del
enunciado.

El proceso manager será el responsable de crear un número determinado de procesos de
tipo SUMADOR y de tipo RESTADOR, gestionando de manera adecuada su finalización y
liberando los recursos previamente reservados. Tanto los procesos de tipo SUMADOR como
los de tipo RESTADOR recibirán como argumento en el momento de su creación la ruta a un
archivo que contendrá una única línea con un número natural comprendido entre 1 y 10. Los
procesos de tipo SUMADOR abrirán ese archivo, leerán el número que contiene, lo
incrementarán en una unidad y, finalmente, escribirán el resultado obtenido en el propio archivo
(sustituyendo el valor anterior). Los procesos de tipo RESTADOR llevarán a cabo la misma
operativa, pero restando una unidad en lugar de sumarla.

El número de procesos de cada tipo, así como la ruta al único archivo manipulado por los
procesos, será indicado por el usuario a través de la línea de órdenes al ejecutar el único
proceso de tipo manager:

`./exec/manager <ruta_archivo> <n_procesos>`

donde <ruta_archiva> representa la ruta al archivo a manipular y <n_procesos> el
número de procesos de tipo SUMADOR y de tipo RESTADOR a lanzar (si este argumento
tiene un valor de 7, entonces se lanzarán 7 SUMADORES y 7 RESTADORES).

La finalización de la simulación ocurrirá si...

1- Todos los procesos finalizan su ejecución. El proceso manager, tras detectar esta
situación, liberará recursos.

2- El usuario pulsa la combinación de teclas Ctrl + C. El proceso manager, tras detectar
este evento, enviará una señal de finalización a todos los procesos de tipo SUMADOR
y RESTADOR que estén en ejecución y liberará recursos.

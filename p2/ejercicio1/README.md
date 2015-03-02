EJERCICIO 1
===========

Construya, utilizando ANSI C estándar, tres ejecutables que modelen el siguiente sistema. La simulación
constará de un proceso manager que cargará una cadena de la línea de órdenes y encargará su traducción a
un conjunto de procesos decoder. El usuario ejecutará un proceso manager indicándole tres argumentos:

`./exec/manager <cadena> <num_proc_decoder> <tam_max_tarea>`

Este proceso manager cargará cadena en un array de caracteres empleando el punto como separador de elementos. Esta
cadena estará formada por números enteros (entre 1 y 57) que tendrán que traducir a caracteres los procesos decoder
(con ayuda del proceso symbol_decoder).

En num_proc_decoder se indicará el número de procesos decoder que se lanzarán para traducir el array y tam_max_tarea
será el tamaño máximo de cada tarea o subvector (cada proceso decoder traducirá del array original suministrado por el
manager un máximo de n_tasks tareas).

El sistema contará con un único proceso symbol_decoder que se encargará de traducir los símbolos de puntuación que se corresponden con los valores enteros del 53 al 57 inclusive.
Así, cuando un proceso decoder encuentre uno de estos valores, 'despertará' al proceso symbol_decoder que escribirá en una variable
de memoria compartida el resultado de traducir ese signo de puntuación, volviendo a 'dormir' después de realizar su trabajo. El proceso
decoder leerá ese valor y lo usará como resultado de la traducción final.

Los procesos decoder atenderán peticiones de traducción hasta que el manager les envíe la señal de terminación. En cada petición el proceso
manager les indicará el índice de inicio y fin de cada tarea (subvector). Los procesos decoder actualizarán directamente el resultado en el array creado por el
manager. 

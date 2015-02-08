EJERCICIO 2
==============
Construya, utilizando ANSI C estándar, un sistema compuesto por tres ejecutables que simule el
funcionamiento que se detalla a continuación. El sistema contará con tres tipos de procesos: i) manager, ii)
PROCESADOR y iii) CONTADOR.
El proceso manager será responsable de crear un número determinado de procesos de tipo
PROCESADOR y de tipo CONTADOR, gestionando de manera adecuada su finalización y liberando los
recursos previamente reservados. Este proceso abrirá un fichero, cuyo nombre recibirá por la línea de
órdenes, y leerá su contenido línea a línea. Por cada línea creará un proceso PROCESADOR y uno
CONTADOR .
Por una parte, los procesos de tipo PROCESADOR recibirán en el momento de su creación un número de
línea, una línea y un patrón. Su función consistirá en comprobar si este patrón se corresponde con alguna de
las palabras que conforman la línea recibida.
Por otra parte, los procesos de tipo CONTADOR recibirán en el momento de su creación un número de
línea y una línea. Su función consistirá en contar el número de palabras que conforman la línea recibida.
La ruta al archivo a procesar y el patrón a buscar serán indicados por el usuario a través de la línea de
órdenes al ejecutar el único proceso de tipo manager:
./exec/manager <archivo> <patrón>
donde <archivo> representa dicha ruta y <patrón> el propio patrón.
La finalización de la simulación tendrá lugar si se cumple una de las dos condiciones siguientes:
1. Todos los procesos de tipo PROCESADOR y CONTADOR finalizan su ejecución. El proceso
manager, tras detectar esta situación, liberará recursos.
2. El usuario pulsa la combinación de teclas Ctrl + C. El proceso manager, tras detectar este evento,
enviará una señal de finalización a todos los procesos de tipo PROCESADOR y CONTADOR que estén en
ejecución y liberará recursos.

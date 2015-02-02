EJERCICIO 1
==============
Construya, utilizando ANSI C estándar, un sistema compuesto por tres ejecutables que simule el funcionamiento que se detalla a continuación. El sistema contará con tres tipos de procesos: i) manager, ii) PA y iii) PB.

El proceso manager será el responsable de crear un número determinado de procesos de tipo PA y de tipo PB, 
gestionando de manera adecuada su finalización y liberando los recursos previamente reservados.

Por una parte, los procesos de tipo PA simplemente dormirán un número aleatorio de segundos, definido
entre 1 y el número indicado a través del primer argumento recibido por línea de órdenes.
A continuación, finalizarán su ejecución.

Por otra parte, los procesos de tipo PB ejecutarán un bucle infinito en el que en cada iteración dormirán
un número aleatorio de segundos, definido entre 1 y el número indicado en el primer argumento recibido por
línea de órdenes.

El número de procesos de cada tipo, así como el tiempo máximo de espera, será indicado por el usuario a
través de la línea de órdenes al ejecutar el único proceso de tipo
manager : ./exec/manager <n_procesos_PA> <n_procesos_PB> <t_max_espera> donde <n_procesos_PA> representa el número de procesos de tipo PA a crear,
<n_procesos_PB> el número de procesos de tipo PB y, finalmente, <t_max_espera> representa el tiempo máximo de espera de
los procesos (tiempo que duermen) que será comunicado a los procesos PA y PB en el momento de su creación.
La finalización de la simulación tendrá lugar si se cumple una de las dos condiciones siguientes:
1.Todos los procesos de tipo PA finalizan su ejecución. El proceso manager, tras detectar esta
situación, enviará una señal de finalización a los procesos de tipo PB y liberará recursos.
2. El usuario pulsa la combinación de teclas Ctrl + C. El proceso manager, tras detectar este evento,
enviará una señal de finalización a todos los procesos de tipo PA y PB que estén en ejecución y liberará
recursos.

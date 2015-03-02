EJERCICIO 2
==========
Construya, utilizando ANSI C estándar, los ejecutables que modelen un sistema que calcule la
fracción canónica (irreducible) a partir de la descomposición del numerador y denominador como producto de sus
factores primos del modo que se detalla a continuación:

• Un proceso manager recibe el numerador y el denominador de una fracción. Éstos se deberán descomponer factorialmente y sus potencias deberán ser reducidas. Para ello, se lanzará una serie de
procesos factorer. Habrá un proceso factorer para cada número primo , es decir, uno para el 2, otro para el 3, otro para el 5, etc. hasta N_PRIME_NUMBERS.

• Cada uno de estos procesos factorer se encarga de calcular cuántas veces el numerador y el denominador que el proceso
manager ha recibido son divisibles entre el número primo que dicho proceso factorer debe procesar, y que le ha sido indicado por el proceso
manager. A continuación, deberá eliminar aquél con menor exponente, dejando la diferencia al contrario

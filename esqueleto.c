/* Programa esqueleto de ejercicios de creacion de procesos simples
   ################ Carlos Jesus Cebrian Sanchez ################ */

/* ¡¡NO COMPILA!! ES ORIENTATIVO */

#include <stdio.h>
#include <unistd.h> /* _exit(), fork(), exec*(), get*id() */
#include <sys/wait.h> /* wait*() */
#include <sys/types.h> /* wait*(), get*id(), kill() */
#include <stdlib.h> /* MACROS EXIT_FAILURE & EXIT_SUCCESS , malloc(), free() */
#include <signal.h> /* signal(), kill() */

/* 1º Creacion de la estructura de la tabla de procesos */
/* Creacion de los tipos de procesos que va a contener la tabla */

enum TipoProceso_tabla{/*Introducir los tipos de procesos que tenga el problema*/};

/* EJEMPLO:
   enum TipoProceso{A,B}...
   enum TipoProceso{CONTADOR,PROCESADOR}...
   enum TipoProceso{Juan,Pepe,Manolo} */

/* Creacion de la estructura que va a tener la tabla */

struct TablaProcesos tabla{
  enum TipoProceso_tabla tipo;
  pid_t pid;
};

/* Estructura tipo:
   ------------------
   ----tipo-----pid--
   |CONTADOR  |20155|
   |PROCESADOR|20159|
   |CONTADOR  |20170|
   ------------------
   ------------------ 
   Obligatoriamente el tipo tiene que ser uno de los establecidos anteriormente
   en el enum */

/* 2º Variables globales del programa */

int g_numProc; /* Numero total de procesos que se van a crear */
struct TablaProcesos *g_pids; /* Creacion de una tabla

/* 3º Funciones que necesita el programa */
void handler(int sig);
void liberarRecursos(void);
void finalizarProcesos(void);

/* 4º Inicio del programa */

int main(int argc, char *argv[]){
  
  /* 5º Variables que necesita el programa */
  /* Ejemplo:
     FILE *fp...
     int nProcesos...
     char *patron */

  /* 6º Controlar el numero de argumentos */
  if(argc < /*DEPENDENCIA*/){
    fprintf(stderr,"Error, Use: programa ...\n");
    _exit(EXIT_FAILURE);
  }

  /* 7º Instalador del manejador de señal de CTRL+C */
  if(signal(SIGINT,handler) == SIG_ERR){
    fprintf(stderr,"Error in Installation of signal handler\n");
    _exit(EXIT_FAILURE);
  }

  /* 8º Reservar memoria para la tabla de procesos */
  g_pids = malloc(g_numProc * sizeof(struct TablaProcesos));

  /* 9º Creacion de procesos */
  /* Depende del tipo de programa
     algo que no se puede incluir en el esqueleto */
  /* EJEMPLO:
     fork()..exec()
     
     fork()
     .exec()
     .
     fork()
     exec()

     fork()
     .exec()
     ..fork()
     ..exec()

  /* 10º Esperar a que los procesos finalicen */
  /* Depende tambien del tipo de programa */

  /* EJEMPLO:
     Cuando solo los procesos de un tipo terminan:
     while(numProcesosA > 0)

     Cuando tenemos que esperar a que todos terminen:
     while(numProc > 0)

     Siempre hay que ir borrando los procesos de la tabla:
     g_pids[i].pid = 0; Ya que ningun proceso va a tener la pid = 0; */
  
  /* 11º Finalizar Procesos */
  finalizarProcesos();

  /* 12º Liberar Recursos */
  liberarRecursos();
  
  return EXIT_SUCCESS;

}

/* 13º Implementar handler(), finalizarProcesos() y liberarRecursos() */

void handler(int sig){
  printf("\nCTRL+C captured\n");
  printf("Terminating processes & set free resources\n");
  finalizarProcesos();
  liberarRecursos();
  _exit(EXIT_SUCCESS);
}

void finalizarProcesos(void){
  int i;
  printf("-----------Terminating processes-----------\n");

  for(i = 0; i < g_numProc;i++){
    if(g_pids[i].pid != 0){
      printf("Killing [%s][%d]\n",g_pids[i].tipo, g_pids[i].pid);
      if(kill(g_pids[i].pid,SIGINT) == -1){
	fprintf(stderr,"Error killing processes\n");
	_exit(EXIT_FAILURE);
      }
    }
  }
  printf("¡¡All procesess finished successfuly!!\n");
}

void liberarRecursos(void){
  /* Liberar la memoria de la tabla de procesos */
  free(g_pids);
}

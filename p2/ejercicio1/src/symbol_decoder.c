/* Ejercicio 1 Practica 2 --- Programacion Concurrente y Tiempo Real

   Carlos Jesus Cebrian Sanchez ---- 48686394V */

#include <stdio.h>
#include <unistd.h> /* getpid() */
#include <sys/types.h> /* getpid() */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include <sys/mman.h> /* shm_open(), mmap() */
#include <sys/stat.h> /* shm_open() */
#include <fcntl.h> /* shm_open()*/

#include <definitions.h>
#include <semaphoreI.h>

/* FUNCIONES */
void get_shm_segments(int *shm_symbol, struct TSymbol_t **p_symbol);
void get_sems(sem_t **p_sem_symbol_ready,sem_t **p_sem_symbol_read);
void get_and_process_task(sem_t *sem_symbol_ready, sem_t *sem_symbol_decoded,struct TSymbol_t *symbol);

int main(int argc,char *argv[]){
  int shm_symbol; /* Descriptor del archivo de simbolos */
  
  struct TSymbol_t *symbol; /* Estructura de datos de simbolos */

  sem_t *sem_symbol_ready; /* Indica que el simbolo esta listo */
  sem_t *sem_symbol_decoded; /* Indica que el simbolo esta decodificado */

  /* Crear segmentos de memoria compartida */
  get_shm_segments(&shm_symbol,&symbol);
  
  /* Obtener semaforos */
  get_sems(&sem_symbol_ready,&sem_symbol_decoded);

  while(1){
    get_and_process_task(sem_symbol_ready,sem_symbol_decoded,symbol);
  }
  
  return EXIT_SUCCESS;
}

/* CREAR SEGMENTOS DE MEMORIA COMPARTIDA */
void get_shm_segments(int *shm_symbol, struct TSymbol_t **p_symbol){
  *shm_symbol = shm_open(SHM_SYMBOL,O_RDWR,0644);
  *p_symbol = mmap(NULL,sizeof(struct TSymbol_t),PROT_READ | PROT_WRITE,MAP_SHARED,*shm_symbol,0);
}

/* OBTENER SEMAFOROS */
void get_sems(sem_t **p_sem_symbol_ready,sem_t **p_sem_symbol_decoded){
  *p_sem_symbol_ready = get_semaphore(SEM_SYMBOL_READY);
  *p_sem_symbol_decoded = get_semaphore(SEM_SYMBOL_DECODED);
}

/* PROCESAR TAREAS */
void get_and_process_task(sem_t *sem_symbol_ready, sem_t *sem_symbol_decoded,struct TSymbol_t *symbol){
  wait_semaphore(sem_symbol_ready);
  switch(symbol->value){
  case 53:symbol->value = 46;break;
  case 54:symbol->value = 44;break;
  case 55:symbol->value = 33;break;
  case 56:symbol->value = 63;break;
  case 57:symbol->value = 95;break;
  }
  signal_semaphore(sem_symbol_decoded);
}


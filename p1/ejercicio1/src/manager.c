/* Ejercicio 1 Practica 1 Programacion Concurrente y en tiempo real 
   El ejercicio consiste en llamar un numero de procesos PA y PB que realicen
   una funcion determinada:
   
   PA: duerme un numero de segundos y despues termina
   PB: duerme un numero de segundos y despues renicia el bucle y vuelve a dormir

   Condicion de salida: Los procesos PA terminan o el usuario pulsa CTRL+C

   CARLOS JESUS CEBRIAN SANCHEZ */

/* USO : manager <num_PA> <num_PB> <TimeMAX> */

/* Archivos de cabecera y definiciones */
#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h> /* EXIT_FAILURE & EXIT_SUCCESS, atoi() */
#include <string.h> /* strerror() */
#include <signal.h> /* kill(), signal() */
#include <sys/wait.h>
#include <sys/types.h> /* kill() */
#include <unistd.h> /* _exit(), sleep() */
#include <errno.h> /* errno */
#include <linux/limits.h>

#include <definitions.h> /* Archivo de cabecera para la definicion 
			    de la tabla de procesos */

/* Variables globales */
int g_nProc ; /* Numero total de procesos a crear */

/* Tabla de procesos */
struct TProcess_t *g_tablaprocesos;

/* Funciones del programa POR ORDEN DE EJECUCION*/

void parse_argv(int argc,char *argv[], int *nPA, int *nPB, char **TimeMAX_wait); /* Analiza la entrada de argumentos */

void install_signal_handler(); /* Instala el manejador de señal 
				  CTRL +C */

void signal_handler(int sig); /* Funcion a realizar cuando se 
				 pulsa CTRL + C */

void init_TProc(int nPA,int nPB); /* Inicia la tabla de procesos */

void create_proc_byclass(enum ProcessClass_t class, int num_NewProc, int index_procTable, char *TimeMAX_wait); /* Funcion inicializadora
					    de procesos */

void get_Proc_info(enum ProcessClass_t class, char **path,char **str_process_class); /* Recoge informacion del proceso a traves de las macros
	      definidas en <definitions.h> */

pid_t create_single_proc(const char *str_process_class,const char *path,const char *arg); /* Crea cada proceso a traves de la recogida de 
		      informacion de get_Proc_info */

void wait_proc(int nPA); /* Funcion que espera a que los procesos A
			    terminen */

void termProc(); /* Funcion de terminacion de procesos */

void freeResources(); /* Libera los recursos reservados */

int main(int argc,char *argv[]){
  char *TimeMAX_wait = NULL;
  int nPA,nPB;

  parse_argv(argc,argv,&nPA,&nPB,&TimeMAX_wait);
  install_signal_handler();

  init_TProc(nPA,nPB);

  create_proc_byclass(PB,nPB,0,TimeMAX_wait);
  create_proc_byclass(PA,nPA,nPB,TimeMAX_wait);

  wait_proc(nPA);

  printf("[MANAGER] Program Termination (all PA processes terminated)\n");
  termProc();
  freeResources();

  return EXIT_SUCCESS;
}

void parse_argv(int argc,char *argv[], int *nPA, int *nPB, char **TimeMAX_wait){
  if(argc != 4){
    fprintf(stderr,"Argument Error, use: manager <num_PA> <num_PB> <TimeMAX>\n");
    _exit(EXIT_FAILURE);
  }
  
  *nPA = atoi(argv[1]);
  *nPB = atoi(argv[2]);
  *TimeMAX_wait = argv[3]; /* Al tener que pasarlo a los procesos en
			     forma de str entonces no se convierte 
			     a int */
  
}

void install_signal_handler(){
  if(signal(SIGINT,signal_handler) == SIG_ERR){
    fprintf(stderr,"Signal installer error: %s\n",strerror(errno));
    _exit(EXIT_FAILURE);
  }
}

void signal_handler(int sig){
  printf("[MANAGER] Program termination CTRL + C\n");
  termProc();
  freeResources();
  _exit(EXIT_SUCCESS);
}

void termProc(){
  int i;

  printf("\n ------[MANAGER] Terminating running child processes ------ \n");
  
  for(i = 0; i < g_nProc;i++){
    if(g_tablaprocesos[i].pid != 0){
      printf("[MANAGER] Terminating %s process [%d]...\n",g_tablaprocesos[i].str_process_class,g_tablaprocesos[i].pid);
      if(kill(g_tablaprocesos[i].pid,SIGINT) == -1){
	fprintf(stderr,"Error killing process [%d]: %s\n",g_tablaprocesos[i].pid,strerror(errno));
	_exit(EXIT_FAILURE);
      }
    }
  }
}

void freeResources(){
  free(g_tablaprocesos);
}

void init_TProc(int nPA,int nPB){
  int i;

  g_nProc = nPA + nPB;
  g_tablaprocesos = malloc(g_nProc * sizeof(struct TProcess_t));
  
  for(i = 0;i < g_nProc;i++){
    g_tablaprocesos[i].pid = 0;
  }
}

void create_proc_byclass(enum ProcessClass_t class, int num_NewProc, int index_procTable, char *TimeMAX_wait){
  char *path = NULL,*str_process_class = NULL;
  int i;
  pid_t pid;

  get_Proc_info(class, &path, &str_process_class);

  for(i = index_procTable;i < (index_procTable + num_NewProc);i++){
    pid = create_single_proc(path,str_process_class,TimeMAX_wait);
    
    g_tablaprocesos[i].class = class;
    g_tablaprocesos[i].pid = pid;
    g_tablaprocesos[i].str_process_class = str_process_class;
  }
  
  printf("[MANAGER] %d %s processes created\n",num_NewProc,str_process_class);
  sleep(1);
}

void get_Proc_info(enum ProcessClass_t class, char **path,char **str_process_class){
  switch(class){
  case PA:
    *path = PA_PATH;
    *str_process_class = PA_CLASS;
    break;
  case PB:
    *path = PB_PATH;
    *str_process_class = PB_CLASS;
    break;
  }
}

pid_t create_single_proc(const char *path,const char *str_process_class,const char *arg){
  pid_t pid;
  switch(pid = fork()){
  case -1:
    fprintf(stderr,"Error forking %s type: %s\n",str_process_class,strerror(errno));
    termProc();
    freeResources();
    _exit(EXIT_FAILURE);
  case 0:
    if(execl(path,str_process_class,arg,NULL) == -1){
      fprintf(stderr,"Exec Error: %s\n",strerror(errno));
      _exit(EXIT_FAILURE);
    }
  }
  return pid;
}

void wait_proc(int nPA){
  int i;
  pid_t pid;
  
  while(nPA > 0){
    pid = wait(NULL);
    for(i = 0;i < g_nProc;i++){
      if(pid == g_tablaprocesos[i].pid){
	g_tablaprocesos[i].pid = 0;
	if(g_tablaprocesos[i].class == PA){
	  nPA--;
	}
	break;
      }
    }
  }
}

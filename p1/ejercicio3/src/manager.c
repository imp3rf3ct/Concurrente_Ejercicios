/* Codigo fuente manager.c que maneja los procesos sumadores y restadores */

#define POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>

#include <definitions.h>

int g_nProcesses;

struct TProcess_t *g_process_table;

void install_signal_handler();
void signal_handler(int sig);
void terminate_processes();
void free_resources();
void parse_argv(int argc,char *argv[],char **ruta,int *nPSum,int *nPRes);
void init_process_table(int nPSum, int nPRes);
void create_processes_by_class(enum ProcessClass_t class, int n_new_processes,int index_process_table,char *ruta);
void get_str_process_info(enum ProcessClass_t class,char **path,char **str_process_class);
int create_single_process(char *path, char *str_process_class,char *ruta);
void wait_processes();


int main(int argc,char *argv[]){
  int nPSum,nPRes;
  char *ruta;

  parse_argv(argc,argv,&ruta,&nPSum,&nPRes);
  install_signal_handler();

  init_process_table(nPSum,nPRes);
  create_processes_by_class(SUMADOR,nPSum,0,ruta);
  create_processes_by_class(RESTADOR,nPRes,nPSum,ruta);
  wait_processes();

  printf("[MANAGER %d] All Processes terminated\n",getpid());
  
  return EXIT_SUCCESS;
}

void install_signal_handler(){
  if(signal(SIGINT,signal_handler) == SIG_ERR){
    fprintf(stderr,"[MANAGER %d] Signal Install Error: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
  }
}

void signal_handler(int sig){
  printf("[MANAGER %d] Program Termination (CTRL + C)\n",getpid());
  terminate_processes();
  free_resources();
  _exit(EXIT_SUCCESS);
}

void terminate_processes(){
  int i;
  printf("-------[MANAGER %d] Terminating running child processes -------\n",getpid());
  for(i = 0; i < g_nProcesses;i++){
    if(g_process_table[i].pid != 0){
      printf("[MANAGER %d] Terminating %s process[%d]\n",getpid(),g_process_table[i].str_process_class, g_process_table[i].pid);
      if(kill(g_process_table[i].pid,SIGINT) == -1){
	fprintf(stderr,"[MANAGER %d] Error KILL %s [%d]: %s\n",getpid(),g_process_table[i].str_process_class, g_process_table[i].pid,strerror(errno));
      }
      g_process_table[i].pid = 0;
    }
  }
}

void free_resources(){
  free(g_process_table);
}

void parse_argv(int argc,char *argv[],char **ruta,int *nPSum,int *nPRes){
  if(argc != 3){
    fprintf(stderr,"[MANAGER %d] Argument error use: ./manager <file> <numProcesses>\n",getpid());
    _exit(EXIT_FAILURE);
  }

  *ruta = argv[1];
  *nPSum = atoi(argv[2]);
  *nPRes = atoi(argv[2]);

}

void init_process_table(int nPSum, int nPRes){
  int i;
  
  g_nProcesses = nPSum + nPRes;

  g_process_table = malloc(g_nProcesses * sizeof(struct TProcess_t));

  for(i = 0; i < g_nProcesses; i++){
    g_process_table[i].pid = 0;
  }
}

void create_processes_by_class(enum ProcessClass_t class, int n_new_processes,int index_process_table,char *ruta){
  char *path = NULL, *str_process_class = NULL;
  int i;
  pid_t pid;

  get_str_process_info(class,&path,&str_process_class);

  for(i = index_process_table; i < (index_process_table + n_new_processes);i++){
    pid = create_single_process(path,str_process_class,ruta);

    g_process_table[i].pid = pid;
    g_process_table[i].class = class;
    g_process_table[i].str_process_class = str_process_class;
  }
  printf("[MANAGER %d] %d %s Processes created\n",getpid(),n_new_processes,str_process_class);
}

void get_str_process_info(enum ProcessClass_t class,char **path,char **str_process_class){
  switch(class){
  case SUMADOR:
    *path = SUMADOR_PATH;
    *str_process_class = SUMADOR_CLASS;
    break;
  case RESTADOR:
    *path = RESTADOR_PATH;
    *str_process_class = RESTADOR_CLASS;
    break;
  }
}

int create_single_process(char *path, char *str_process_class, char *ruta){
  pid_t pid;

  switch(pid = fork()){
  case -1:
    fprintf(stderr,"[MANAGER %d] Forking Error: %s\n",getpid(),strerror(errno));
    terminate_processes();
    free_resources();
    _exit(EXIT_FAILURE);
  case 0:
    if(execl(path,str_process_class,ruta,NULL) == -1){
      fprintf(stderr,"[%s %d] Exec error: %s\n",str_process_class, getpid(),strerror(errno));
      _exit(EXIT_FAILURE);
    }
  }
  return pid;
}

void wait_processes(){
  int i,cont = g_nProcesses;
  pid_t pid;

  while(cont > 0){
    pid = wait(NULL);
    for(i = 0; i< g_nProcesses;i++){
      if(g_process_table[i].pid == pid){
	g_process_table[i].pid = 0;
	cont--;
	break;
      }
    }
  }
}

#include <stdio.h>
#include <errno.h> /* errno */
#include <signal.h> /* kill(), signal() */
#include <stdlib.h> /* EXIT_FAILURE & EXIT_SUCCESS, atoi(), 
		       srand(), rand() */
#include <string.h> /* strerror() */
#include <unistd.h> /* _exit() */

void run(int t_wait);

void install_signal_handler();
void signal_handler(int sig);
void parse_argv(int argc, char *argv[], int *t_wait);

int main(int argc, char *argv[]){
  int t_wait;

  install_signal_handler(); /* Instala el manejador de CTRL + C */
  
  parse_argv(argc,argv,&t_wait); /* Controla la linea de argumentos                                  */
  run(t_wait); /* Ejecuta el programa */

  return EXIT_SUCCESS;
}

void install_signal_handler(){
  if(signal(SIGINT,signal_handler) == SIG_ERR){
    fprintf(stderr,"[PB %d] Error signal handling: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
  }
}

void signal_handler(int sig){
  printf("[PB %d] terminated (SIGINT)\n",getpid());
  _exit(EXIT_SUCCESS);
}

void parse_argv(int argc, char *argv[], int *t_wait){
  if(argc != 2){
    fprintf(stderr,"[PB %d] Argument error\n",getpid());
    _exit(EXIT_FAILURE);
  }

  srand((int)getpid()); /* Crea una semilla de aleatoriedad */
  *t_wait = 1 + (rand() % atoi(argv[1])); /* Crea el num aleatorio 
					   */
}

void run(int t_wait){
  while(1){
    printf("[PB %d] sleeps %d seconds\n",getpid(),t_wait);
    sleep(t_wait);
  }
}

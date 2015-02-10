/* Codigo de sumador.c Abre un archivo indicado con un numero en su interior
   natural del 1 al 10 y le suma 1 unidad */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <linux/limits.h>
#include <fcntl.h>

#define MAX_SIZE 5

void install_signal_handler();
void signal_handler(int sig);
void parse_argv(int argc,char *argv[],char **ruta);
void run(char *ruta);

int main(int argc, char *argv[]){
char *ruta;
  
  install_signal_handler();
  parse_argv(argc,argv,&ruta);
  run(ruta);

  return EXIT_SUCCESS;
}

void install_signal_handler(){
  if(signal(SIGINT,signal_handler) == SIG_ERR){
    fprintf(stderr,"[SUMADOR %d] Signal install error: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
  }
}

void signal_handler(int sig){
  printf("[SUMADOR %d] Terminated (SIGINT)\n",getpid());
  _exit(EXIT_SUCCESS);
}

void parse_argv(int argc,char *argv[],char **ruta){
  if(argc != 2){
    fprintf(stderr,"[SUMADOR %d] Argument error: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
  }

  *ruta = argv[1];
}

void run(char *ruta){
  int num;
  FILE *fp;
  char cnum [MAX_SIZE],c[MAX_SIZE];

  if((fp = fopen(ruta,"r")) == NULL){
    fprintf(stderr,"[SUMADOR %d] File Open Error 'R': %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
    }

  if((c[0] = fgetc(fp)) == EOF){
    fprintf(stderr,"[SUMADOR %d] Read Error: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
  }

  fclose(fp);

  c[1] = '\0';
  printf("%s",c);

  num = atoi(c);
  
  printf("[SUMADOR %d] Sumando 1 al numero %s\n",getpid(),c);

  num++;

  sprintf(cnum,"%d",num);

  printf("%s\n",cnum);

  if((fp = fopen(ruta,"w")) == NULL){
    fprintf(stderr,"[SUMADOR %d] File Open Error 'W': %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
    }
  
  if(fputs(cnum,fp)== EOF){
    fprintf(stderr,"[SUMADOR %d] Write Error: %s\n",getpid(),strerror(errno));
    _exit(EXIT_FAILURE);
    }

    fclose(fp);

}

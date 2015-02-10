/* Archivo Definitions.h donde se definiran las constantes y estructuras
   necesarias para realizar el ejercicio 3 */

#define SUMADOR_CLASS "SUMADOR"
#define RESTADOR_CLASS "RESTADOR"
#define SUMADOR_PATH "./exec/sumador"
#define RESTADOR_PATH "./exec/restador"

enum ProcessClass_t {SUMADOR,RESTADOR};

struct TProcess_t {
  enum ProcessClass_t class;
  pid_t pid;
  char *str_process_class;
};

    

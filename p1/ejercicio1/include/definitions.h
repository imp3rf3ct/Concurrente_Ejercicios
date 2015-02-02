#define PA_CLASS "PA"
#define PB_CLASS "PB"
#define PA_PATH "./exec/pa"
#define PB_PATH "./exec/pb"

enum ProcessClass_t {PA, PB};

struct TProcess_t {
  enum ProcessClass_t class;
  pid_t pid;
  char *str_process_class;
};

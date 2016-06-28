#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
  sem_t* sem = sem_open("/test.sem", O_CREAT, ALLPERMS, 66);

  exit(EXIT_SUCCESS);
}

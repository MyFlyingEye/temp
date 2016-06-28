#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHMNAME "/test.shm"
#define SHMSZ 1048576

int main() {
  int id = shm_open(SHMNAME, O_CREAT, ALLPERMS);
  ftruncate(id, SHMSZ);
  void* addr = mmap(NULL, SHMSZ, PROT_WRITE, MAP_SHARED, id, 0);

  memset(addr, 13, SHMSZ);

  sleep(10);

  munmap(addr, SHMSZ);
  shm_unlink(SHMNAME);

  exit(EXIT_SUCCESS);
}

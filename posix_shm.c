#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define SHMNAME "/test.shm"
#define SHMSZ 1048576

int main() {
  int id = shm_open(SHMNAME, O_CREAT | O_RDWR, ALLPERMS);
  if (id < 0) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }
  ftruncate(id, SHMSZ);
  void* addr = mmap(NULL, SHMSZ, PROT_WRITE, MAP_SHARED, id, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  memset(addr, 13, SHMSZ);

  sleep(10);

  munmap(addr, SHMSZ);
  shm_unlink(SHMNAME);

  exit(EXIT_SUCCESS);
}

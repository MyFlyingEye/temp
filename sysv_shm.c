#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
  key_t key = ftok("/tmp/mem.temp", 1);
  int shmid = shmget(key, 1024, IPC_CREAT | 0666);

  void* addr = shmat(shmid, NULL, 0);
  memset(addr, 72, 1024);

  sleep(10);

  shmdt(addr);
  shmctl(shmid, IPC_RMID, NULL);

  exit(EXIT_SUCCESS);
}

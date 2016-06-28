#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMNUM 16

int main() {
  key_t key = ftok("/tmp/sem.temp", 1);

  int semid = semget(key, SEMNUM, IPC_CREAT);

  union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* _buf;
  } arg;

  for (int num = 0; num < SEMNUM; ++num) {
    arg.val = num;
    semctl(semid, num, SETVAL, arg.val);
  }

  exit(EXIT_SUCCESS);
}

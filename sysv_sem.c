#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEMNUM 16
#define PERM 0666

int main() {
  key_t key = ftok("/tmp/sem.temp", 1);

  int semid = semget(key, SEMNUM, PERM | IPC_CREAT);

  union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* _buf;
  } arg;

  int num;
  for (num = 0; num < SEMNUM; ++num) {
    arg.val = num;
    semctl(semid, num, SETVAL, arg);
  }

  sleep(10);

  semctl(semid, 0, IPC_RMID);

  exit(EXIT_SUCCESS);
}

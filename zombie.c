#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
  FILE* f;
  f = fopen("/home/box/pid_parent", "w");
  fprintf(f, "%d", getpid());
  fclose(f);

  pid_t pid;
  pid = fork();
  if (pid) {
    f = fopen("/home/box/pid_child", "w");
    fprintf(f, "%d", pid);
    fclose(f);

    int status;
    wait(&status);
  }

  pause();

  exit(EXIT_SUCCESS);
}

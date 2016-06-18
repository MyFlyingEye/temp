#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  FILE* f = fopen("/home/box/pid", "w");
  fprintf(f, "%d", getpid());
  fclose(f);

  struct sigaction action, old_action;
  bzero(&action, sizeof(action));
  action.sa_handler = SIG_IGN;
  action.sa_flags = SA_RESTART;

  sigaction(SIGINT, &action, &old_action);
  sigaction(SIGTERM, &action, &old_action);

  pause();

  exit(EXIT_SUCCESS);
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("/home/box/result.out", O_WRONLY | O_CREAT);
  dup2(fd, 1);
  close(fd);

  char* st = NULL;
  size_t stlen = 0;
  getline(&st, &stlen, stdin);

  system(st);

  free(st);

  exit(EXIT_SUCCESS);
}

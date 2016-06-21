#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
  if (fork()) {
    close(fd[0]);
    wait(NULL);
  } else {
    close(fd[1]);
    sleep(30);
  }

  return 0;
}

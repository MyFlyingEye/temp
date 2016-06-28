#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  mq_unlink("/test.mq");

  mqd_t mqd = mq_open("/test.mq", O_CREAT | O_RDONLY, 0666, NULL);

  char buf[256];

  ssize_t msglen = mq_receive(mqd, buf, sizeof(buf), NULL);
  if (msglen < 0) {
    perror("mq_receive");
    exit(EXIT_FAILURE);
  }

  int f = open("/home/box/message.txt", O_WRONLY | O_TRUNC);
  write(f, buf, msglen);
  close(f);

  exit(EXIT_SUCCESS);
}

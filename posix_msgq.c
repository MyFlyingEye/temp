#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main() {
  struct mq_attr attr;
  bzero(&attr, sizeof(attr));
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 1024;

  mq_unlink("/test.mq");
  mqd_t mqd = mq_open("/test.mq", O_CREAT | O_RDONLY, 0666, &attr);

  char buf[1024];
  ssize_t msglen = mq_receive(mqd, buf, sizeof(buf), NULL);
  if (msglen < 0) {
    perror("mq_receive");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr, "mq_receive: Received %ld bytes", msglen);

  int f = open("/home/box/message.txt", O_WRONLY | O_TRUNC);
  write(f, buf, msglen);
  close(f);

  exit(EXIT_SUCCESS);
}

struct mq_attr {
  long mq_flags;
  long mq_maxmsg;  // max len of queue (max num of queues)
  // do not set when create queue:
  long mq_msgsize;  // max size of message
  long mq_curmsgs;  // current num of messages
}

    We can change only O_NONBLOCK

int mq_getattr(mqd, *attr)  // load attrs
    int mq_setattr(mqd, *attr, *oldattr);

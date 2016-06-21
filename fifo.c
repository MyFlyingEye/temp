#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char chname_one[] = "/home/box/in.fifo";
  char chname_two[] = "/home/box/out.fifo";
  mode_t mode = 0666;

  mkfifo(chname_one, mode);
  mkfifo(chname_two, mode);

  int in = open(chname_one, O_RDONLY);
  int out = open(chname_two, O_WRONLY);

  char buf[256];

  ssize_t len = read(in, buf, sizeof(buf));
  while (len > 0) {
    write(out, buf, len);
    len = read(in, buf, sizeof(buf));
  }

  close(in);
  close(out);
  unlink(chname_one);
  unlink(chname_two);
}

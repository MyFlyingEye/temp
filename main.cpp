#include <unistd.h>

#include <fstream>


void* foo(void*) {
  sleep(10);
  return nullptr;
}


int main() {
  {
    std::fstream pidfile("/home/box/main.pid");
    pidfile << getpid();
    pidfile.close();
  }

  pthread_t thread_id;
  pthread_create(&thread_id, nullptr, &foo, nullptr);
  pthread_join(thread_id, nullptr);

  return 0;
}

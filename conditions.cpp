#include <unistd.h>

#include <iostream>
#include <fstream>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_barrier_t barrier;

void* thread_condwait(void*) {
  pthread_cond_wait(&cond, &mutex);
  std::cerr << "Wait finished" << std::endl;
  sleep(1);
  pthread_barrier_wait(&barrier);
  std::cerr << "First after barrier done" << std::endl;

  return nullptr;
}

void* thread_barrier(void*) {
  std::cerr << "Waiting for barrier" << std::endl;
  pthread_barrier_wait(&barrier);
  sleep(1);
  std::cerr << "Second after barrier done" << std::endl;

  return nullptr;
}

int main() {
  {
    std::ofstream pidfile("/home/box/main.pid");
    pidfile << getpid();
    pidfile.close();
  }

  pthread_barrier_init(&barrier, nullptr, 2);
  pthread_mutex_lock(&mutex);

  pthread_t thread_cond;
  pthread_create(&thread_cond, nullptr, &thread_condwait, nullptr);

  pthread_t thread_barr;
  pthread_create(&thread_barr, nullptr, &thread_barrier, nullptr);

  std::cerr << "Threads created, start sleeping" << std::endl;

  sleep(10);

  std::cerr << "Sleep is over, notifying condition" << std::endl;

  sleep(1);

  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);

  pthread_join(thread_cond, nullptr);
  pthread_join(thread_barr, nullptr);

  return 0;
}

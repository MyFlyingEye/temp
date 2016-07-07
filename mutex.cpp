#include <unistd.h>

#include <iostream>
#include <fstream>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t spinlock;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* wait_mutex(void*) {
  pthread_mutex_lock(&mutex);
  std::cerr << "Done mutex" << std::endl;
  pthread_mutex_unlock(&mutex);

  return nullptr;
}

void* wait_spinlock(void*) {
  pthread_spin_lock(&spinlock);
  std::cerr << "Done spinlock" << std::endl;
  pthread_spin_unlock(&spinlock);

  return nullptr;
}

void* wait_rlock(void*) {
  pthread_rwlock_rdlock(&rwlock);
  std::cerr << "Done read lock" << std::endl;
  pthread_rwlock_unlock(&rwlock);

  return nullptr;
}

void* wait_wlock(void*) {
  pthread_rwlock_wrlock(&rwlock);
  std::cerr << "Done write lock" << std::endl;
  pthread_rwlock_unlock(&rwlock);

  return nullptr;
}

int main() {
  {
    std::fstream pidfile("/home/box/main.pid", );
    pidfile << getpid();
    pidfile.close();
  }

  pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
  pthread_mutex_lock(&mutex);
  pthread_spin_lock(&spinlock);
  pthread_rwlock_wrlock(&rwlock);

  std::cerr << "Locked all" << std::endl;

  pthread_t thread_mutex;
  pthread_create(&thread_mutex, nullptr, &wait_mutex, nullptr);

  pthread_t thread_spin;
  pthread_create(&thread_spin, nullptr, &wait_spinlock, nullptr);

  pthread_t thread_rlock;
  pthread_create(&thread_rlock, nullptr, &wait_rlock, nullptr);

  pthread_t thread_wlock;
  pthread_create(&thread_wlock, nullptr, &wait_wlock, nullptr);

  std::cerr << "Start sleeping" << std::endl;

  sleep(10);

  std::cerr << "Sleep is over" << std::endl;

  pthread_mutex_unlock(&mutex);
  pthread_spin_unlock(&spinlock);
  pthread_rwlock_unlock(&rwlock);

  pthread_join(thread_mutex, nullptr);
  pthread_join(thread_spin, nullptr);
  pthread_join(thread_rlock, nullptr);
  pthread_join(thread_wlock, nullptr);

  return 0;
}

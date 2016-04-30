#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

pthread_t tid[2];
int x = 0;
int i;

void* addNumbers() {
  for(i = 0; i < 100000; i++) {
    x++;
  }
}
int main() {
  pthread_attr_t myattr;
  cpu_set_t cpuset;

  pthread_attr_init(&myattr);
  CPU_ZERO(&cpuset);
  CPU_SET(0, &cpuset);
  pthread_attr_setaffinity_np(&myattr, sizeof(cpu_set_t), &cpuset);

  pthread_create(&(tid[0]), &myattr, &addNumbers, NULL);
  pthread_create(&(tid[1]), &myattr, &addNumbers, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  printf("Final output of x should be 200,000\n");
  printf("x: %i\n", x);
}

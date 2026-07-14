// Compile with gcc -Wall -o 3_example 3_example.c -pthread

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_THREADS 10

void *func(void *arg) {
  printf("Thread %lu\n", (unsigned long)pthread_self());
  return NULL;
}

int main(void) {
  pthread_attr_t attr;
  pthread_t thid[MAX_THREADS];
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  for (int j = 0; j < MAX_THREADS; j++)
    pthread_create(&thid[j], &attr, func, NULL);

  pthread_attr_destroy(&attr);
  sleep(5);
  return 0;
}

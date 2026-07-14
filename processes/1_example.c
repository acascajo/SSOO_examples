// Compile with gcc -Wall -o 1_example 1_example.c -pthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {
  for (int i = 0; i < 2; i++) {
    printf("Thread says hi!\n");
    sleep(1);
  }
  printf("Thread exit\n");
  return NULL;
}

int main(void) {
  pthread_t mythread;
  int rc = pthread_create(&mythread, NULL, thread_function, NULL);
  if (rc != 0) {
    fprintf(stderr, "error creating thread: %d\n", rc);
    abort();
  }

  printf("Wait for join to exit\n");
  rc = pthread_join(mythread, NULL);
  if (rc != 0) {
    fprintf(stderr, "error joining thread: %d\n", rc);
    abort();
  }
  return 0;
}

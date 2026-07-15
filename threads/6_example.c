// Compile with: gcc -o 6_example 6_example.c -pthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int dato = 5;       /* resource */
int n_lectores = 0; /* number of readers */

pthread_mutex_t mutex;          /* control access to data */
pthread_mutex_t mutex_lectores; /* control access to n_lectores */
pthread_cond_t no_lectores;     /* control access to n_lectores */

void *Escritor(void) { /* code of the writer */
  pthread_mutex_lock(&mutex);
  dato = dato + 2; /* modify the resource */
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

void *Lector(void) { /* code of the reader */
  pthread_mutex_lock(&mutex_lectores);
  n_lectores++;
  if (n_lectores == 1)
    pthread_mutex_lock(&mutex); // steal the mutex from the writers
  pthread_mutex_unlock(&mutex_lectores);

  printf("%d\n", dato); /* read data */

  pthread_mutex_lock(&mutex_lectores);
  n_lectores--;
  if (n_lectores == 0)
    pthread_mutex_unlock(&mutex);
  pthread_mutex_unlock(&mutex_lectores);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {

  pthread_t th1, th2, th3, th4;

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&mutex_lectores, NULL);
  pthread_cond_init(&no_lectores, NULL);

  pthread_create(&th1, NULL, (void *)Lector, NULL);
  pthread_create(&th2, NULL, (void *)Escritor, NULL);
  pthread_create(&th3, NULL, (void *)Lector, NULL);
  pthread_create(&th4, NULL, (void *)Escritor, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
  pthread_join(th4, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_lectores);
  exit(0);
}

// Compile with: gcc -o 5_example 5_example.c -pthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024         /* size of buffer */
#define DATOS_A_PRODUCIR 100000 /* data to produce */

pthread_mutex_t mutex;   /* mutex for accessing the shared buffer */
pthread_cond_t no_lleno; /* controls buffer filling */
pthread_cond_t no_vacio; /* controls buffer emptying */

int n_elementos;        /* number of elements in the buffer */
int buffer[MAX_BUFFER]; /* shared buffer */

void *Productor(void) { /* producer code */
  int dato, i, pos = 0;
  for (i = 0; i < DATOS_A_PRODUCIR; i++) {
    dato = i;                               /* produce data */
    pthread_mutex_lock(&mutex);             /* access the buffer */
    while (n_elementos == MAX_BUFFER)       /* if buffer is full */
      pthread_cond_wait(&no_lleno, &mutex); /* it blocks itself */
    buffer[pos] = i;
    pos = (pos + 1) % MAX_BUFFER;
    n_elementos++;
    pthread_cond_signal(&no_vacio);
    pthread_mutex_unlock(&mutex);
    /* buffer not empty */
  }
  pthread_exit(0);
}

void *Consumidor(void) { /* consumer code */
  int dato, i, pos = 0;
  for (i = 0; i < DATOS_A_PRODUCIR; i++) {
    pthread_mutex_lock(&mutex);             /* access the buffer */
    while (n_elementos == 0)                /* if buffer is empty */
      pthread_cond_wait(&no_vacio, &mutex); /* it blocks itself */
    dato = buffer[pos];
    pos = (pos + 1) % MAX_BUFFER;
    n_elementos--;
    pthread_cond_signal(&no_lleno);
    pthread_mutex_unlock(&mutex);
    printf("Consume %d \n", dato); /* buffer not full */
    /* consume dato */
  }
  pthread_exit(0);
}

int main(int argc, char *argv[]) {

  pthread_t th1, th2;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&no_lleno, NULL);
  pthread_cond_init(&no_vacio, NULL);

  pthread_create(&th1, NULL, (void *)Productor, NULL);
  pthread_create(&th2, NULL, (void *)Consumidor, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_lleno);
  pthread_cond_destroy(&no_vacio);

  exit(0);
}
// Compile with: gcc -o 2_example 2_example.c -pthread

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// SEMAPHORES WITHOUT NAME

#define MAX_BUFFER 1024         /* Size of buffer */
#define DATOS_A_PRODUCIR 100000 /* Data to produce */

sem_t elementos; /* elements in the buffer */
sem_t huecos;    /* empty slots in the buffer */

int buffer[MAX_BUFFER]; /* shared buffer */

void *Productor(void) /* Producer */
{
  int pos = 0; /* pos inside the buffer */
  int dato;
  int i;
  /* data to produce */
  for (i = 0; i < DATOS_A_PRODUCIR; i++) {
    dato = i;          /* produce data */
    sem_wait(&huecos); /* one empty slot less */
    buffer[pos] = i;
    pos = (pos + 1) % MAX_BUFFER;
    printf("Productor: %d\n", i);
    sem_post(&elementos); /* one element more */
  }
  pthread_exit(0);
}

void *Consumidor(void) /* Consumer */
{
  int pos = 0;
  int dato;
  int i;
  for (i = 0; i < DATOS_A_PRODUCIR; i++) {
    sem_wait(&elementos); /* one element less */
    dato = buffer[pos];
    pos = (pos + 1) % MAX_BUFFER;
    printf("Consumidor: %d\n", dato);
    sem_post(&huecos); /* one empty slot more */
    /* cosumir dato */
  }
  pthread_exit(0);
}

int main() {
  pthread_t th1, th2; /* threads id */

  /* Initialization */
  sem_init(&elementos, 0, 0);
  sem_init(&huecos, 0, MAX_BUFFER);

  /* Thread creation */
  pthread_create(&th1, NULL, (void *)Productor, NULL);
  pthread_create(&th2, NULL, (void *)Consumidor, NULL);

  /* Wait for their completion */
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  /* Release the resources */
  sem_destroy(&huecos);
  sem_destroy(&elementos);
  exit(0);
}
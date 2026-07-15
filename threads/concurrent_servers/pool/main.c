// Compile with: gcc -o pool main.c -pthread

#include "peticion.h"
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static long petid = 0;

#define MAX_BUFFER 128
peticion_t buffer[MAX_BUFFER];
int n_elementos;
int pos_servicio = 0;
pthread_mutex_t mutex;
pthread_cond_t no_lleno;
pthread_cond_t no_vacio;

pthread_mutex_t mfin;
int fin = 0;

void recibir_peticion(peticion_t *p) {
  int delay;
  fprintf(stderr, "Receiving request\n");
  p->id = petid++;

  /* Simulación de tiempo de E/S */
  delay = rand() % 5;
  sleep(delay);

  fprintf(stderr, "Request %ld received after %d seconds\n", p->id, delay);
}

void responder_peticion(peticion_t *p) {
  int delay, i;
  double x;
  fprintf(stderr, "Sending request %ld\n", p->id);

  /* Simulación de tiempo de procesamiento */
  for (i = 0; i < 1000000; i++) {
    x = 2.0 * i;
  }

  /* Simulación de tiempo de E/S */
  delay = rand() % 20;
  sleep(delay);

  fprintf(stderr, "Request %ld sent after %d seconds\n", p->id, delay);
}

void copia_peticion(peticion_t *p, peticion_t *c) {
  memcpy(p, c, sizeof(peticion_t));
}

void *servicio(void *param) {
  peticion_t p;

  for (;;) {
    pthread_mutex_lock(&mutex);
    while (n_elementos == 0) {
      if (fin == 1) {
        fprintf(stderr, "Finalizing service\n");
        pthread_mutex_unlock(&mutex);
        pthread_exit(0);
      }
      pthread_cond_wait(&no_vacio, &mutex);
    } // while
    fprintf(stderr, "Serving position %d\n", pos_servicio);
    p = buffer[pos_servicio];
    pos_servicio = (pos_servicio + 1) % MAX_BUFFER;
    n_elementos--;
    pthread_cond_signal(&no_lleno);
    pthread_mutex_unlock(&mutex);
    responder_peticion(&p);
  }

  pthread_exit(0);
  return NULL;
}

void *receptor(void *param) {
  const int MAX_PETICIONES = 5;
  peticion_t p;
  int i, pos = 0;

  for (i = 0; i < MAX_PETICIONES; i++) {
    recibir_peticion(&p);
    pthread_mutex_lock(&mutex);
    while (n_elementos == MAX_BUFFER)
      pthread_cond_wait(&no_lleno, &mutex);
    buffer[pos] = p;
    pos = (pos + 1) % MAX_BUFFER;
    n_elementos++;
    pthread_cond_signal(&no_vacio);
    pthread_mutex_unlock(&mutex);
  }
  fprintf(stderr, "Finalizing receptor\n");
  pthread_mutex_lock(&mfin);
  fin = 1;

  pthread_mutex_unlock(&mfin);
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&no_vacio);
  pthread_mutex_unlock(&mutex);

  fprintf(stderr, "Finalized receptor\n");
  pthread_exit(0);
  return NULL;
}
int main() {
  time_t t1, t2;
  double dif;
  pthread_t thr;
  const int MAX_SERVICIO = 5;
  int i;
  pthread_t ths[MAX_SERVICIO];

  t1 = time(NULL);

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&no_lleno, NULL);
  pthread_cond_init(&no_vacio, NULL);
  pthread_mutex_init(&mfin, NULL);

  pthread_create(&thr, NULL, receptor, NULL);
  for (i = 0; i < MAX_SERVICIO; i++) {
    pthread_create(&ths[i], NULL, servicio, NULL);
  }

  pthread_join(thr, NULL);
  for (i = 0; i < MAX_SERVICIO; i++) {
    pthread_join(ths[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_lleno);
  pthread_cond_destroy(&no_vacio);
  pthread_mutex_destroy(&mfin);

  t2 = time(NULL);

  dif = difftime(t2, t1);
  printf("Time: %lf\n", dif);

  return 0;
}

// Compile with: gcc -o threads main.c -pthread

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
sem_t snhijos;

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

void *servicio(void *p) {
  // PROBLEMA DE CONCURRENCIA
  peticion_t pet;
  copia_peticion(&pet, (peticion_t *)p);

  fprintf(stderr, "Starting service\n");
  responder_peticion(&pet);
  sem_post(&snhijos);

  fprintf(stderr, "Ending service\n");
  pthread_exit(0);
  return NULL;
}

void *receptor(void *param) {
  const int MAX_PETICIONES = 5;
  int nservicio = 0;
  int i;
  peticion_t p;
  pthread_t th_hijo;

  for (i = 0; i < MAX_PETICIONES; i++) {
    recibir_peticion(&p);
    nservicio++;
    pthread_create(&th_hijo, NULL, servicio,
                   &p); // crea thread y vuelve al loop
    clear
  }

  for (i = 0; i < nservicio; i++) {
    fprintf(stderr, "Making wait\n");
    sem_wait(&snhijos);
    fprintf(stderr, "Exiting wait\n");
  }

  pthread_exit(0);
  return NULL;
}

int main() {
  time_t t1, t2;
  double dif;
  pthread_t thr;

  t1 = time(NULL);

  sem_init(&snhijos, 0, 0);
  pthread_create(&thr, NULL, receptor, NULL);
  pthread_join(thr, NULL);
  sem_destroy(&snhijos);

  t2 = time(NULL);
  dif = difftime(t2, t1);
  printf("Time: %lf\n", dif);

  return 0;
}

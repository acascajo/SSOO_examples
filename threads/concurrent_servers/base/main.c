// Compile with: gcc -o base main.c -lm

#include "peticion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static long petid = 0;

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

int main() {
  int i;
  const int MAX_PETICIONES = 5;
  time_t t1, t2;
  double dif;
  peticion_t p;

  t1 = time(NULL);
  for (i = 0; i < MAX_PETICIONES; i++) {
    recibir_peticion(&p);
    responder_peticion(&p);
  }
  t2 = time(NULL);

  dif = difftime(t2, t1);
  printf("Time: %lf\n", dif);

  return 0;
}

// Compile with: gcc -o procesos main.c -pthread

#include "peticion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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
  int pid, hijos = 0;

  t1 = time(NULL);
  for (i = 0; i < MAX_PETICIONES; i++) {
    recibir_peticion(&p);

    do {
      fprintf(stderr, "Checking children\n");
      // Intenta recoger a los hijos que hayan terminado
      pid = waitpid(-1, NULL, WNOHANG);
      if (pid > 0)
        hijos--;
    } while (pid > 0);

    pid = fork();
    if (pid < 0)
      fprintf(stderr, "Error in child process creation\n");
    if (pid == 0) {
      responder_peticion(&p);
      exit(0);
    }
    if (pid != 0)
      hijos++;
  }

  fprintf(stderr, "Checking %d children\n", hijos);
  while (hijos > 0) {
    pid = waitpid(-1, NULL, WNOHANG); // inmediato
    if (pid > 0) {
      hijos--;
    }
  }

  t2 = time(NULL);
  dif = difftime(t2, t1);
  printf("Time: %lf\n", dif);

  return 0;
}

// Compile with gcc -Wall -o 4_example 4_example.c

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // Registro del manejador de la señal SIGSEGV
  struct sigaction act;
  act.sa_handler = SIG_IGN;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);     // conjunto de señales vacío
  sigaction(SIGINT, &act, NULL); // add al conjunto

  printf("Bucle infinito imparable\n");
  while (1) {
    // El programa seguirá ejecutándose incluso si se presiona Ctrl+C
  }

  // ¿Se puede crear un programa que ignore todas las señales?

  return 0;
}
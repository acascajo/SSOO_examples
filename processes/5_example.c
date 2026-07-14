// Compile with gcc -Wall -o 5_example 5_example.c

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void capturar(int sig) {
  (void)sig;
  write(STDERR_FILENO, "SIGSEGV\n", 8);
  _Exit(128 + SIGSEGV);
}

int main(int argc, char *argv[]) {
  struct sigaction act = {0};
  act.sa_handler = capturar;
  sigemptyset(&act.sa_mask);
  sigaction(SIGSEGV, &act, NULL);
  *(int *)0 = 5;
}

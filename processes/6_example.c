#include <signal.h>
#include <unistd.h>

static void alarma(int sig) {
  (void)sig;
  write(STDOUT_FILENO, "Activada\n", 9);
}

int main(void) {
  struct sigaction act = {0};
  sigemptyset(&act.sa_mask);
  act.sa_handler = alarma;
  sigaction(SIGALRM, &act, NULL);

  for (;;) {
    alarm(10);
    pause();
  }
}

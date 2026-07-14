// Compile with gcc -Wall -o 7_example 7_example.c

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// This program executes a command with a time limit of 5 seconds. If the
// command does not finish within that time, it will be killed.

pid_t pid;

// Envía señal de fin a proceso hijo
void tratar_alarma() { kill(pid, SIGKILL); }

int main(int argc, char **argv) {
  int status;
  char **argumentos;

  struct sigaction act;
  argumentos = &argv[1];

  pid = fork();
  switch (pid) {
  case -1: /* error del fork() */
    perror("fork");
    exit(-1);
  case 0: /* proceso hijo */
    printf("I am the child and I am going to execute the command: %s\n",
           argumentos[0]);
    execvp(argumentos[0], argumentos);
    exit(-1);
  default: /* padre */
    /* establece el manejador */
    printf("I am the parent and I am going to give my child 10 seconds to "
           "finish\n");
    act.sa_handler = tratar_alarma;
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);
    alarm(5);
    printf("I am the parent and I am waiting for my child...\n");
    wait(&status);
    printf("I am the parent and I have finished waiting for my child\n");
  }
  exit(0);
}
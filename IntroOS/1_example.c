// Compile with gcc -Wall -o 1_example 1_example.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
    return 1;
  }
  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    return 1;
  case 0:
    execvp(argv[1], &argv[1]);
    perror("execvp");
    _exit(127);
  default:
    waitpid(pid, NULL, 0);
    printf("Process parent\n");
  }
  return 0;
}

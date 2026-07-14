// Compile with gcc -Wall -o 3_example 3_example.c

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int fd = open("fichero", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  pid_t pid = fork();
  if (pid == 0) {
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execlp("ls", "ls", (char *)NULL);
    perror("execlp");
    _exit(127);
  }
  close(fd);
  waitpid(pid, NULL, 0);
  return 0;
}

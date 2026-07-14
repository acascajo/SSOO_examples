// Compile with gcc -Wall -o 2_example 2_example.c

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 4096

int main(int argc, char **argv) {
  int fd_ent, fd_sal;
  char buffer[BUFSIZE];
  ssize_t n_read;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s source destination\n", argv[0]);
    return 1;
  }

  fd_ent = open(argv[1], O_RDONLY);
  if (fd_ent < 0) {
    perror("open source");
    return 1;
  }

  fd_sal = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd_sal < 0) {
    perror("open destination");
    close(fd_ent);
    return 1;
  }
}
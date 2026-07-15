// Compile with: gcc -o 1_example 1_example.c
// Create the file datos.txt with the desired content before running the program

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  struct stat dstat;
  int i, n;
  char *c;
  char *vec;

  fd = open("datos.txt", O_RDONLY);

  fstat(fd, &dstat);

  vec = mmap(NULL, dstat.st_size, PROT_READ, MAP_SHARED, fd, 0);

  close(fd);
  c = vec;
  for (i = 0; i < dstat.st_size; i++) {
    if (*c == ' ') {
      n++;
    }
    c++;
  }
  munmap(vec, dstat.st_size);
  printf("n = % d\n", n);
  return 0;
}
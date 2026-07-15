// Compile with: gcc -o 2_example 2_example.c
// Create the file datos.txt with the desired content before running the program

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int i, fd1, fd2;
  struct stat dstat;
  char *vec1, *vec2, *p, *q;

  fd1 = open("datos.txt", O_RDONLY);
  fd2 = open("f2", O_CREAT | O_TRUNC | O_RDWR, 0640);

  fstat(fd1, &dstat);
  ftruncate(fd2, dstat.st_size);

  vec1 = mmap(0, dstat.st_size, PROT_READ, MAP_SHARED, fd1, 0);
  vec2 = mmap(0, dstat.st_size, PROT_READ, MAP_SHARED, fd2, 0);

  close(fd1);
  close(fd2);

  p = vec1;
  q = vec2;
  for (i = 0; i < dstat.st_size; i++) {
    *q++ = *p++;
  }

  munmap(vec1, dstat.st_size);
  munmap(vec2, dstat.st_size);

  return 0;
}
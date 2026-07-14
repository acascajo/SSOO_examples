// Compile with gcc -Wall -o 1_example 1_example.c

#include <stdio.h>
int main(int argc, char *argv[]) {
  int x, y;
  x = 1; /* cierto */
  y = 2; /* cierto */
  if (x = y) {
    printf("Iguales\n");
  }
  return 0;
}

// Compile with gcc -Wall -o 7_example 7_example.c

#include <stdio.h>

void acumula(int *s, int x) { /* Pointer s*/ *s += x; }

int main(int argc, char *argv[]) {
  int suma = 0;
  int i;
  for (i = 0; i < 10; i++) {
    acumula(&suma, x); /* Address of suma */
  }
  printf("1 + 9 = % d\n", suma);
}

// Compile with gcc -Wall -o 4_example 4_example.c

#include <stdio.h>

int suma(int a, int b); /* Prototype */

int main(int argc, char *argv[]) {
  int x, y;
  x = 3;
  y = suma(x, 2); /* Function call */
  printf("%d + %d = %d\n", x, 2, y);
  return 0;
}

int suma(int a, int b) { /* Definition */ return a + b; }

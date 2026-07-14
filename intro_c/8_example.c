// Compile with gcc -Wall -o 8_example 8_example.c

#include <stdio.h>

void funcion(int a, int b); /* prototype */

int main(int argc, char *argv[]) {
  int x = 2;
  int y = 5;

  printf("Before x = %d, y = %d\n", x, y);

  funcion(x, y);

  printf("After x = %d, y = %d\n", x, y);
}

void funcion(int a, int b) {
  a = 0;
  b = 0;

  printf("Inside function, a = %d, b = %d\n", a, b);
  return;
}

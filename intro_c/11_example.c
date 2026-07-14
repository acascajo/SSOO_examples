// Compile with gcc -Wall -o 11_example 11_example.c

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int contar(char *c, char x) {
  int n = 0;
  char *q = c;
  while (q != NULL) {
    if (*c == x) {
      n++;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char *c = "Hello world";
  char x = 'o';
  int n = contar(c, x);
  printf("The character %c appears %d times in the string %s\n", x, n, c);
  return 0;
}
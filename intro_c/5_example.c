// Compile with gcc -Wall -o 5_example 5_example.c

#include <stdio.h>

int main(int argc, char *argv[]) {
  int x;   /* var of type int */
  int y;   /* variable of type int */
  int *px; /* variable of type
              pointer to int */

  x = 5;
  px = &x; /* assigns to px the address of x */
  y = *px; /* assigns to y the content of the
              address stored in px */

  printf("x = %d\n", x);
  printf("y = %d\n", y);
  printf("*px = %d\n", *px);
}

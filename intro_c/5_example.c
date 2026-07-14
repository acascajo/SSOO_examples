// Compile with gcc -Wall -o 5_example 5_example.c

#include <stdio.h>

int main(int argc, char *argv[]) {
  int x;   /* variable de tipo entero */
  int y;   /* variable de tipo entero */
  int *px; /* variable de tipo
              puntero a entero */

  x = 5;
  px = &x; /* asigna a px la direccion de x */
  y = *px; /* asigna a y el contenido de la
              direccion almacenada en px */

  printf("x = %d\n", x);
  printf("y = %d\n", y);
  printf("*px = %d\n", *px);
}

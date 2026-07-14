// Compile with gcc -Wall -o 6_example 6_example.c

#include <stdio.h>

int main(int argc, char *argv[]) {
  float n1;
  float n2;
  float *p1;
  float *p2;

  n1 = 4.0;
  p1 = &n1;

  printf("n1 = %f\n", n1);
  printf("p1 = %p\n", p1);

  p2 = p1;
  n2 = *p2;
  n1 = *p1 + *p2;
  printf("n2 = %f\n", n2);
  printf("n1 = %f\n", n1);
}
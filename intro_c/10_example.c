// Compile with gcc -Wall -o 10_example 10_example.c

#include <stdio.h>

double suma_array(double *v, int n) {
  int i;
  double s = 0.0;
  for (i = 0; i < n; i++) {
    s += v[i];
  }
  return s;
}

int main() {
  double w[10];
  for (int i = 0; i < 10; i++) {
    w[i] = 1.0 * i;
  }
  printf("suma %lf\n", suma_array(w, 10));
  return 0;
}

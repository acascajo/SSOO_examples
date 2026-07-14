// Compile with gcc -Wall -o 12_example 12_example.c

#include <stdio.h>
#include <stdlib.h>

double promedio(double *w, int n) {
  double s = 0.0;
  int i;
  for (i = 0; i < n; i++) {
    s += w[i];
  }
  return s / n;
}

int main(int argc, char *argv[]) {
  int n, i;
  double *v;
  printf("Num of values =");
  scanf("%d", &n);
  v = (double *)malloc(sizeof(double) * n);
  for (i = 0; i < n; i++) {
    printf("v[%d]=", i);
    scanf("%lf", &v[i]);
  }
  printf("Average = %lf\n", promedio(v, n));
  free(v);
  return 0;
}

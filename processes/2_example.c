// Compile with gcc -Wall -o 2_example 2_example.c -pthread

#include <pthread.h>
#include <stdio.h>

struct sumapar {
  int n, m, r;
};
typedef struct sumapar sumapar_t;

void *suma(void *arg) {
  sumapar_t *par = arg;
  int total = 0;
  for (int i = par->n; i <= par->m; i++) {
    total += i;
  }
  par->r = total;
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  sumapar_t s1 = {1, 50, 0};
  sumapar_t s2 = {51, 100, 0};

  pthread_create(&th1, NULL, suma, &s1);
  pthread_create(&th2, NULL, suma, &s2);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Sum =%d\n", s1.r + s2.r);
  return 0;
}

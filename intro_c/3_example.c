// Compile with gcc -Wall -o 3_example 3_example.c

int main(int argc, char *argv[]) {
  int v[100];
  double w[] = {1.0, 3.5, 7.0}; /* Tamaño = 3 */
  float y[];                    /* ERROR. Necesita tamaño */

  v[0] = 3;
  v[10] = v[0];
  v[-1] = 0;   /* Comp. No definido */
  v[100] = 17; /* Comp. No definido */

  return 0;
}
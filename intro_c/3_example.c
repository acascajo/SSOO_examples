// Compile with gcc -Wall -o 3_example 3_example.c

int main(int argc, char *argv[]) {
  int v[100];
  double w[] = {1.0, 3.5, 7.0}; /* Size = 3 */
  float y[];                    /* ERROR. Needs size */

  v[0] = 3;
  v[10] = v[0];
  v[-1] = 0;   /* Comp. Not defined */
  v[100] = 17; /* Comp. Not defined */

  return 0;
}
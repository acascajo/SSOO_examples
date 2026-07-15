// Compile with gcc -Wall -o 1_example 1_example.c

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 256

int main(int argc, char **argv) {
  DIR *dirp;
  struct dirent *dp;
  char buf[MAX_BUF];

  /* Print the current directory */
  getcwd(buf, MAX_BUF);
  printf("Current directory: %s\n", buf);
  /* Open the directory passed as an argument */
  dirp = opendir(argv[1]);

  if (dirp == NULL) {
    fprintf(stderr, "Cannot open %s\n", argv[1]);
  } else {
    /* read entry by entry */
    while ((dp = readdir(dirp)) != NULL)
      printf("%s\n", dp->d_name);
    closedir(dirp);
  }
  exit(0);
}

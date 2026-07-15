// Compile with: gcc -o 3_example 3_example.c -pthread

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// SEMAPHORES WITHOUT NAME

int *dato;       /* shared resource */
int *n_lectores; /* number of readers */
sem_t sem_lec;
sem_t mutex;

void lector(int pid) {
  sem_wait(&sem_lec);
  (*n_lectores)++;
  if (*n_lectores == 1)
    sem_wait(&mutex);
  sem_post(&sem_lec);

  printf("Reader %d reads data: %d\n", pid, *dato);

  sem_wait(&sem_lec);
  (*n_lectores)--;
  if (*n_lectores == 0)
    sem_post(&mutex);
  sem_post(&sem_lec);
}

void escritor(int pid) {
  sem_wait(&mutex);
  *dato = *dato + 2;
  printf("Writer %d writes data: %d\n", pid, *dato);
  sem_post(&mutex);
}

int main(int argc, char *argv[]) {
  int i, n;
  pid_t pid;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <num_processes>\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);

  /* Shared memory */
  dato = mmap(NULL, sizeof(int),
              PROT_READ | PROT_WRITE, // allows reading and writing the memory
              MAP_SHARED | MAP_ANONYMOUS, -1, 0); // not associated with a file

  n_lectores =
      mmap(NULL, sizeof(int),
           PROT_READ | PROT_WRITE, // allows reading and writing the memory
           MAP_SHARED | MAP_ANONYMOUS, -1, 0); // not associated with a file

  *dato = 5;
  *n_lectores = 0;

  /* Create semaphores (correct names) */
  sem_init(&mutex, 0, 1);
  sem_init(&sem_lec, 0, 1);

  /* Create processes */
  for (i = 0; i < n; i++) {
    pid = fork();

    if (pid < 0) {
      perror("Error in fork");
      exit(1);
    }

    if (pid == 0) {
      /* Childs = readers */
      lector(getpid());
      exit(0);
    } else {
      /* Parent = writers */
      escritor(getpid());
    }
  }

  /* Wait for the children */
  for (i = 0; i < n; i++) {
    wait(NULL);
  }

  /* Cleanup */
  sem_destroy(&mutex);
  sem_destroy(&sem_lec);

  munmap(dato, sizeof(int));
  munmap(n_lectores, sizeof(int));

  return 0;
}
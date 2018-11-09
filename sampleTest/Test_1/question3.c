#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

typedef char bool_t;

#define N_PRIME 100
#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif

bool_t prime_test(unsigned p) {
  for(unsigned i=2 ; i<p; ++i) {
    if (p%i != 0)
      continue;
    return FALSE;
  }
  return TRUE;
}

void print_prime(unsigned p, unsigned pid) {
  printf("\nFound by process %u, #%u is a prime number!", pid, p);
}

int main(int argc, char **argv) {

  unsigned n_prime = N_PRIME;
  if (argc >= 2)
    n_prime = (unsigned) atoi(argv[1]);

  int sz, pid = 0;
  {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    if (pid++ == 0) {
      unsigned prime = 0U;
        MPI_Irecv((void *)&prime, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
      for (unsigned i=pid ; i<n_prime ; i+=sz) {
        printf("\npid: %u -> test %u", pid, i);
        short is = prime_test(i);
        if (is)
          print_prime(i, pid);
      }
    } else {
      for (unsigned i=pid ; i<n_prime ; i+=sz) {
        //printf("\npid: %u -> test %u", pid, i);
        short is = prime_test(i);
        if (is) {
        // send answer
        }
      }
    }


    MPI_Finalize();
  }

  return 0;
}


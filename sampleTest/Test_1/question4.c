#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

typedef int bool_t;

#define N_PRIME 100
#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif

bool_t prime_test(unsigned p) {
    if (p<=1) return FALSE;
    for(unsigned i=2 ; i<p; ++i) {
        if (p%i == 0)
            return FALSE;
    }
    return TRUE;
}

void print_prime(unsigned p, unsigned pid) {
    pid = pid;
    //printf("\nFound by process #%u\t.n %u is a prime number!\n", pid, p);
    printf("\n%u", p);
}

int main(int argc, char **argv) {

    unsigned n_prime = N_PRIME;
    if (argc >= 2)
        n_prime = (unsigned) atol(argv[1]);

    int pid;
    #pragma omp parallel private(pid) shared(n_prime)
    {
        pid = omp_get_thread_num();
        #pragma omp for schedule(guided)
        for (unsigned iP=1; iP<n_prime ; ++iP) {
            // check if iP is prime
            if (prime_test(iP))
                print_prime(iP, pid);
        }
    }

    return 0;
}


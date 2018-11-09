#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

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
    printf("\nFound by process #%u\t", pid);
    printf("n.%u is a prime number!\n", p);
}

int main(int argc, char **argv) {

    unsigned n_prime = N_PRIME;
    if (argc >= 2)
        n_prime = (unsigned) atoi(argv[1]);

    int sz = 0, pid = 0;
    {
        int err = MPI_SUCCESS;
        err = MPI_Init(&argc, &argv);
        assert(err == MPI_SUCCESS);
        err = MPI_Comm_size(MPI_COMM_WORLD, &sz);
        assert(err == MPI_SUCCESS);
        err = MPI_Comm_rank(MPI_COMM_WORLD, &pid);
        assert(err == MPI_SUCCESS);

        unsigned chunk = (unsigned) ( n_prime / sz );
        unsigned rest = ( n_prime % sz );
        unsigned begin = chunk*pid+rest;
        unsigned end = begin+chunk+((pid==0)?0:rest);

        // master sends
        if (pid++ == 0) {
            chunk += rest;
            unsigned prime = 0U;
            MPI_Request req;
            short finished = sz-1;
            MPI_Status st;

            err = MPI_Irecv((void *)&prime, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &req);
            assert(err == MPI_SUCCESS);
            for (unsigned i=0 ; i<end ; ++i) {
                bool_t is = prime_test(i);
                if (is)
                    print_prime(i, pid-1);
                // check for answers
                err = MPI_Request_get_status( req, &is, &st );
                assert(err == MPI_SUCCESS);
                // TODO @Bretana the main thread
                // only check for coworker once every own find, not good!
                if (is) {
                    if (prime != 0) {
                        print_prime(prime, st.MPI_SOURCE); // TODO @Bretana sample pid
                    } else {
                        --finished;
                    }
                    err = MPI_Irecv((void *)&prime, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &req);
                    assert(err == MPI_SUCCESS);
                }
            }

            while (!finished) {
                MPI_Recv((void *)&prime, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &st);
                if (!prime)
                    --finished;
                else
                    print_prime(prime, st.MPI_SOURCE);
            }



        } else {
            for (unsigned i=begin; i<end ; ++i) {
                //printf("\npid: %u -> test %u", pid, i);
                int is = prime_test(i);
                if (is) {
                    // send answer TODO could be an ISend
                    MPI_Send((void *)&i, 1, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD);
                }
            }
            rest = 1;
            MPI_Send((void *)&rest, 0, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD);
        }


        MPI_Finalize();
    }

    return 0;
}


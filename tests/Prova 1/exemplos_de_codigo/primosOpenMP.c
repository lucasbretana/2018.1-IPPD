# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

int main ( int argc, char *argv[] );
void prime_number_sweep ( int n_lo, int n_hi, int n_factor );
int prime_number ( int n );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for PRIME_OPENMP.

  Discussion:

    This program calls a version of PRIME_NUMBER that includes
    OpenMP directives for parallel processing.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    06 August 2009
    12 June   2018

  Author:

    John Burkardt

  Editors:
    Bretana, L. E. - lebretana@inf.ufpel.edu.br
*/
{
  //  warning removal
  argc = argc;
  argv = argv;
  int n_factor;
  int n_hi;
  int n_lo;

  printf ( "\n" );
  printf ( "PRIME_OPENMP\n" );
  printf ( "  C/OpenMP version\n" );

  printf ( "\n" );
  printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
  printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );

  n_lo = 1;
  n_hi = 131072;
  n_factor = 2;

  prime_number_sweep ( n_lo, n_hi, n_factor );

  n_lo = 5;
  n_hi = 500000;
  n_factor = 10;

  prime_number_sweep ( n_lo, n_hi, n_factor );
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "PRIME_OPENMP\n" );
  printf ( "  Normal end of execution.\n" );

  return 0;
}
/******************************************************************************/

void prime_number_sweep ( int n_lo, int n_hi, int n_factor )

/******************************************************************************/
/*
  Purpose:

   PRIME_NUMBER_SWEEP does repeated calls to PRIME_NUMBER.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    06 August 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N_LO, the first value of N.

    Input, int N_HI, the last value of N.

    Input, int N_FACTOR, the factor by which to increase N after
    each iteration.
*/
{
  int n;
  int primes;
  double wtime;

  printf ( "\n" );
  printf ( "TEST01\n" );
  printf ( "  Call PRIME_NUMBER to count the primes from 1 to N.\n" );
  printf ( "\n" );
  printf ( "         N        Pi          Time\n" );
  printf ( "\n" );

  n = n_lo;

  while ( n <= n_hi )
  {
    wtime = omp_get_wtime ( );

    primes = prime_number ( n );

    wtime = omp_get_wtime ( ) - wtime;

    printf ( "  %8d  %8d  %14f\n", n, primes, wtime );

    n = n * n_factor;
  }
 
  return;
}
/******************************************************************************/

int prime_number ( int n )

/******************************************************************************/
/*
  Purpose:

    PRIME_NUMBER returns the number of primes between 1 and N.

  Edited:
    Now also prints the prime number and wich thread confirmed that.
    Also now the "is prime" action is also paralelized now

  Discussion:

    A naive algorithm is used.

    Mathematica can return the number of primes less than or equal to N
    by the command PrimePi[N].

                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

  Edited:
    Also now prints the primes found

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    21 May 2009
    12 Jun 2018

  Author:

    John Burkardt

  Editor:
    Bretana, L. E. - lebretana@inf.ufpel.edu.br

  Parameters:

    Input, int N, the maximum number to check.

    Output, int PRIME_NUMBER, the number of prime numbers up to N.
    Also prints the primes found
*/
{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel \
  shared ( n ) \
  private ( i, j, prime )
  

  // prime counter
  # pragma omp for reduction ( + : total )
  for ( i = 2; i <= n; i++ ) {
    prime = 1;

    // prime check, for a given i
    unsigned const fator = omp_get_num_threads();
    int j = 0;
    int r = 0;
    #pragma omp for shared(prime) private(j, r)
    for ( j = omp_get_thread_num() ; j < i && prime; j += fator ) {
      if ( (r = i % j) == 0 ) {
        fprintf(stderr, "(%d) NOT prime! -:> %d %% %d = %d != 0.\n", omp_get_thread_num(), i, j, r);
        prime = 0;
      }
    }
    if(prime && !omp_get_thread_num())
      fprintf(stderr, "(%d) prime! -:> %d.\n", tid, i);
    total = total + prime;
  }

  return total;
}

/**
 * @Name: Lucas Eduardo Bretana
 * @Github: lucasbretana
 * @Email: lebretana@inf.ufpel.edu.br
 * @Desc: implements a merge sort using openMP
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#define CHILD_ID pow(2, ite) + my_rank

#define DFLT_SZ 10
#define DFKT_N_TH 2

typedef struct array_{
  unsigned a, b;  // array boundaries [a,b]
  int *p;         // the array, also the first element of the complete array

  omp_lock_t *merge;
} array_t;

 //*  master: calculated offset = (array size / num thread) + (array size (.-) thread id)
/**
 * How to implement merge sort using OpenMP?
 *
 * master: all thread have a array_t *
 *
 */

/**
 * Divide part
 * #Parameters
 * array: array of the function, this array is going to be splited in half (dont touch it)
 * b: index begin
 * e: index end
 */
void mergesort(int *, int, int);

/**
 * Conquer part
 * #Parameters
 * int *: array to merge into another
 * int: left boundarie
 * int: middle boundaries (NOTE: this should be index of the first element on second array, and NOT be a valid index for the first array)
 * int: the right boundaries
 */
void merge(int *, int, int, int);

/**
 * Just print an array
 * int *: the array address
 * int: low boundarie (inclusive)
 * int: high bondarie (inclusive)
 */
void print(FILE *, int *, int , int );

/**
 * argv[0] = "<array size>"
 * argv[1] = "<number of thread>"
 */
int main(int argc, char **argv){

  int *array = createArray(DFLT_SZ);
  
  // pragma and stuff


  free(array);

  printf("\n");
  return 0;
}

int createArray(unsigned n) {
  int *array = calloc(n, sizeof(int));
  assert(array);

  return array;
}

/**
 * Divide part
 */
void mergesort(int *array, unsigned a, unsigned b) {
  if(e<=b) return;

  unsigned half = a + ((b - a + 1) / 2) - 1;

  


}

/**
 * Conquer part
 */
void merge(int *array, unsigned a, unsigned b, unsigned d) {
}

/**
 * Just print an array
 */
void print(FILE *s, int *array, unsigned a, unsigned b)
{
  for(unsigned i=a; i<=b; ++i) 
    fprintf(s, "array[%u] :: %u", i, array[i]);

  fprintf(s, "\n");
}
